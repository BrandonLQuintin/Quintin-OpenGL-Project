#pragma once
#include "../globals.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

struct shape {
    glm::mat4 modelMatrix = glm::mat4(1.0f); // initialized to an identity matrix
};

extern float textVertices[];
extern unsigned int textIndices[];
extern unsigned int textVerticesByteSize;
extern unsigned int textIndicesByteSize;

extern float healthVertices[];
extern unsigned int healthIndices[];
extern unsigned int healthVerticesByteSize;
extern unsigned int healthIndicesByteSize;

extern float phongBillboardVertices[];
extern unsigned int phongBillboardIndices[];
extern unsigned int phongBillboardVerticesByteSize;
extern unsigned int phongBillboardIndicesByteSize;

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
void generatePhongVAOandEBO(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, unsigned int verticesByteSize, unsigned int indicesByteSize, float vertices[], unsigned int indices[]);
void generateVAOandEBO(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, unsigned int verticesByteSize, unsigned int indicesByteSize, float vertices[], unsigned int indices[]);
void generateSphere(float radius, int numSegments, std::vector<float>& sphereVertices);
void generatePhongSphere(float radius, int numSegments, std::vector<float>& sphereVertices);
void generateCone(float radius, float height, int numSegments, std::vector<float>& data);
void generatePhongCone(float radius, float height, int numSegments, std::vector<float>& data);
void generateCylinderVertices(float radius, float height, int numSegments, std::vector<float>& vertices);
void generatePhongCylinderVertices(float radius, float height, int numSegments, std::vector<float>& vertices);
