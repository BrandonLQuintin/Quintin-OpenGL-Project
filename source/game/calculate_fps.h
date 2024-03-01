#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include <iostream>

int calculateAverageFPS(float &timeSinceCalculation, float deltaTime, std::vector<float> &fpsArray);
