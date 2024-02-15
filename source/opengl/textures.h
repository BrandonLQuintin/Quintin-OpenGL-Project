#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <vector>
#include <shader_m.h>

void loadTexture(unsigned int &textureInt, const char* imagePath);

void assignTextureUV(std::vector<float> &textureAtlasUV, unsigned int x, unsigned int y);

void setTextureUV(Shader &shader, std::vector<float> &atlasUV, bool isFirstAtlas);
