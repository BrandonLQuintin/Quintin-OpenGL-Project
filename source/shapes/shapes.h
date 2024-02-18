#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

struct shape {
    glm::mat4 modelMatrix = glm::mat4(1.0f); // initialized to an identity matrix
    // UNUSED FOR NOW
    unsigned int type = 0; // 1 = box, 2 = floor, 3 = pyramid, 4 = spheres, 5 = cones

};

extern float boxVertices[];
extern unsigned int boxVerticesByteSize;

extern float phongBoxVertices[];
extern unsigned int phongBoxVerticesByteSize;

extern float pyramidVertices[];
extern unsigned int pyramidVerticesByteSize;

extern float phongPyramidVertices[];
extern unsigned int phongPyramidVerticesByteSize;

extern float floorVertices[];
extern unsigned int floorIndices[];
extern unsigned int floorVerticesByteSize;

extern float phongFloorVertices[];
extern unsigned int phongFloorVerticesByteSize;

extern std::vector<glm::vec3> initialSpherePositions;

void generateSurroundingPositions(std::vector<glm::vec3> &inputVector, int boxCount);
void generateVAO(unsigned int &VAO, unsigned int &VBO, unsigned int boxVerticesByteSize, float boxVertices[]);
void generatePhongVAO(unsigned int &VAO, unsigned int &VBO, unsigned int boxVerticesByteSize, float boxVertices[]);
void generateFloorVAO(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, unsigned int floorVerticesByteSize, float floorVertices[]);
void generateSphere(float radius, int numSegments, std::vector<float>& sphereVertices);
void generatePhongSphere(float radius, int numSegments, std::vector<float>& sphereVertices);
void generateCone(float radius, float height, int numSegments, std::vector<float>& data);
void generatePhongCone(float radius, float height, int numSegments, std::vector<float>& data);
void generateCylinderVertices(float radius, float height, int numSegments, std::vector<float>& vertices);
void generatePhongCylinderVertices(float radius, float height, int numSegments, std::vector<float>& vertices);
