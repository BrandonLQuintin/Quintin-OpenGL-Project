#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

struct shape {
    glm::mat4 modelMatrix = glm::mat4(1.0f); // initialized to an identity matrix
    // UNUSED FOR NOW
    unsigned int type = 0; // 1 = box, 2 = floor

};

extern float boxVertices[];
extern unsigned int boxVerticesByteSize;

extern float pyramidVertices[];
extern unsigned int pyramidVerticesByteSize;

extern float floorVertices[];
extern unsigned int floorIndices[];
extern unsigned int floorVerticesByteSize;

extern std::vector<glm::vec3> initialBoxPositions;

void generateSurroundingPositions(std::vector<glm::vec3> &inputVector, int boxCount);
void generateVAO(unsigned int &VAO, unsigned int &VBO, unsigned int boxVerticesByteSize, float boxVertices[]);
void generateFloorVAO(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, unsigned int floorVerticesByteSize, float floorVertices[]);
