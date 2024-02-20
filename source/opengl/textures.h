#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <vector>
#include <shader_m.h>

void loadTexture(unsigned int &textureInt, const char* imagePath);

std::vector<float> returnTextureUV(unsigned int x, unsigned int y);

void setTextureUV(Shader &shader, std::vector<float> &atlasUV, bool isFirstAtlas);
