#pragma once
#include <map>
#include <vector>
#include "textures.h"


extern std::map<char, std::vector<float>> characterUV;

void renderText(Shader shader, unsigned int VAO, std::string input);
