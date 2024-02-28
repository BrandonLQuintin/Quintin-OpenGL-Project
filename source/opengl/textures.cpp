#include "textures.h"
#include <iostream>

void loadTexture(unsigned int &textureInt, const char* imagePath) {
    glGenTextures(1, &textureInt);
    glBindTexture(GL_TEXTURE_2D, textureInt);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

std::vector<float> returnTextureUV(unsigned int x, unsigned int y){
    // assuming the texture is a 16x16 grid.
    // if selecting grid (1, 1), type in (0, 0) instead.
    std::vector<float> outputUV(4);

    unsigned int gridSize = 16;
    float gridlength = 1.0f / gridSize;

    float vEnd = 1.0f - (y * gridlength);
    float vStart = vEnd - gridlength;

    float uStart = x * gridlength;
    float uEnd = uStart + gridlength;

    outputUV[0] = uStart;
    outputUV[1] = uEnd;
    outputUV[2] = vStart;
    outputUV[3] = vEnd;

    return outputUV;
}

void setTextureUV(Shader &shader, std::vector<float> &atlasUV, bool isText){
    if (!isText){
        shader.setBool("firstTextureAtlas", true);
    }

    else{
        shader.setBool("firstTextureAtlas", false);
    }
    shader.setVec2("u", glm::vec2(atlasUV[0], atlasUV[1]));
    shader.setVec2("v", glm::vec2(atlasUV[2], atlasUV[3]));
}
