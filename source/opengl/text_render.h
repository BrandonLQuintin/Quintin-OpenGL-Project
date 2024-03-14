#pragma once
#include <map>
#include <vector>
#include "textures.h"
#include "../shapes/initialize_shape_vertices.h"
#include "../globals.h"


extern std::map<char, std::vector<float>> characterUV;
extern std::map<int, std::string> textOptions;

void renderText(Shader shader, std::string input);
void newDialogue();
