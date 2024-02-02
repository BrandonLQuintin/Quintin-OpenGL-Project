#pragma once
#include <glm/glm.hpp>
#include <vector>

extern float boxVertices[];
extern float boxVerticesByteSize;

extern std::vector<glm::vec3> boxPositions;

void generateBoxPositions(std::vector<glm::vec3> &inputVector, int boxCount);
