#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

struct shape {
    glm::mat4 modelMatrix = glm::mat4(1.0f); // initialized to an identity matrix
    unsigned int type = 0; // 1 = box, 2 = floor
};

extern float boxVertices[];
extern float boxVerticesByteSize;

extern float floorVertices[];
extern float floorVerticesByteSize;

extern std::vector<glm::vec3> initialBoxPositions;

void generateSurroundingPositions(std::vector<glm::vec3> &inputVector, int boxCount);
