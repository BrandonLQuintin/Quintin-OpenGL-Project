#include "shapes.h"
#include "../globals.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

float textVertices[] = {
    // xyz, tex coords
     0.025f/2,  0.025f, 0.0f,     1.0f, 1.0f,
     0.025f/2, -0.025f, 0.0f,     1.0f, 0.0f,
    -0.025f/2, -0.025f, 0.0f,     0.0f, 0.0f,
    -0.025f/2,  0.025f, 0.0f,     0.0f, 1.0f
};

unsigned int textIndices[] = {
    0, 1, 3,
    1, 2, 3
};

unsigned int textVerticesByteSize = sizeof(textVertices);
unsigned int textIndicesByteSize = sizeof(textIndices);

float phongBillboardVertices[] = {
    // xyz, normals, tex coords
    -0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    0.5f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f
};

unsigned int phongBillboardIndices[] = {
    0, 1, 2,
    1, 3, 2
};

unsigned int phongBillboardVerticesByteSize = sizeof(phongBillboardVertices);
unsigned int phongBillboardIndicesByteSize = sizeof(phongBillboardIndices);


float boxVertices[] = {
    // xyz, tex coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int boxVerticesByteSize = sizeof(boxVertices);

float phongBoxVertices[] = {
    // xyz, normals, tex coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

unsigned int phongBoxVerticesByteSize = sizeof(phongBoxVertices);

float pyramidVertices[] = {
    // xyz, tex coords
    -0.5f, 0.0f, -0.5f,  0.0f, 0.0f,
     0.5f, 0.0f, -0.5f,  1.0f, 0.0f,
    -0.5f, 0.0f,  0.5f,  0.0f, 1.0f,

     0.5f, 0.0f, -0.5f,  1.0f, 0.0f,
     0.5f, 0.0f,  0.5f,  1.0f, 1.0f,
    -0.5f, 0.0f,  0.5f,  0.0f, 1.0f,

     0.0f, 1.0f, 0.0f,   0.5f, 0.5f,
    -0.5f, 0.0f, -0.5f,  0.0f, 1.0f,
     0.5f, 0.0f, -0.5f,  1.0f, 1.0f,

     0.0f, 1.0f, 0.0f,   0.5f, 0.5f,
     0.5f, 0.0f, -0.5f,  0.0f, 1.0f,
     0.5f, 0.0f, 0.5f,   1.0f, 1.0f,

     0.0f, 1.0f, 0.0f,   0.5f, 0.5f,
     0.5f, 0.0f, 0.5f,   0.0f, 1.0f,
    -0.5f, 0.0f, 0.5f,   1.0f, 1.0f,

     0.0f, 1.0f, 0.0f,   0.5f, 0.5f,
    -0.5f, 0.0f, 0.5f,   0.0f, 1.0f,
    -0.5f, 0.0f, -0.5f,  1.0f, 1.0f
};

unsigned int pyramidVerticesByteSize = sizeof(pyramidVertices);

float phongPyramidVertices[] = {
    // Bottom face - Triangle 1
    -0.5f, 0.0f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
     0.5f, 0.0f, -0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
    -0.5f, 0.0f,  0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,

    // Bottom face - Triangle 2
     0.5f, 0.0f, -0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
     0.5f, 0.0f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
    -0.5f, 0.0f,  0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,

    // Front face (corrected normal)
    0.5f, 0.0f, -0.5f,  0.0f, 0.5f, -0.8f,  1.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,  0.0f, 0.5f, -0.8f,  0.0f, 0.0f,
    0.0f, 1.0f,  0.0f,  0.0f, 0.5f, -0.8f,  0.5f, 0.5f,

    // Left face (corrected normal)
    -0.5f, 0.0f, -0.5f,  -0.8f, 0.5f, 0.0f,  1.0f, 0.0f,
    -0.5f, 0.0f,  0.5f,  -0.8f, 0.5f, 0.0f,  0.0f, 0.0f,
    0.0f, 1.0f,  0.0f,  -0.8f, 0.5f, 0.0f,  0.5f, 0.5f,

    // Right face (corrected normal)
    0.5f, 0.0f,  0.5f,  0.8f, 0.5f, 0.0f,  0.0f, 0.0f,
    0.5f, 0.0f, -0.5f,  0.8f, 0.5f, 0.0f,  1.0f, 0.0f,
    0.0f, 1.0f,  0.0f,  0.8f, 0.5f, 0.0f,  0.5f, 0.5f,

    // Back face (corrected normal)
    -0.5f, 0.0f,  0.5f,  0.0f, 0.5f, 0.8f,  0.0f, 0.0f,
    0.5f, 0.0f,  0.5f,  0.0f, 0.5f, 0.8f,  1.0f, 0.0f,
    0.0f, 1.0f,  0.0f,  0.0f, 0.5f, 0.8f,  0.5f, 0.5f,
};



unsigned int phongPyramidVerticesByteSize = sizeof(phongPyramidVertices);

float floorVertices[] = {
    // xyz, tex coords
    -0.5f, 0.0f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0.0f, 1.0f,
     0.5f, 0.0f, -0.5f, 1.0f, 1.0f,

    -0.5f, 0.0f, 0.5f, 0.0f, 0.0f,
     0.5f, 0.0f, -0.5f, 1.0f, 1.0f,
     0.5f, 0.0f, 0.5f, 1.0f, 0.0f
};
unsigned int floorIndices[] = {
    0, 1, 3,
    1, 2, 3
};

unsigned int floorVerticesByteSize = sizeof(floorVertices);

float phongFloorVertices[] = {
    // Vertex Positions       // Normals                  // Texture Coordinates
    -0.5f, 0.0f, -0.5f,       0.0f, 1.0f, 0.0f,          0.0f, 0.0f,
    0.5f, 0.0f, -0.5f,        0.0f, 1.0f, 0.0f,          1.0f, 0.0f,
    -0.5f, 0.0f, 0.5f,        0.0f, 1.0f, 0.0f,          0.0f, 1.0f,

    0.5f, 0.0f, -0.5f,        0.0f, 1.0f, 0.0f,          1.0f, 0.0f,
    0.5f, 0.0f, 0.5f,         0.0f, 1.0f, 0.0f,          1.0f, 1.0f,
    -0.5f, 0.0f, 0.5f,        0.0f, 1.0f, 0.0f,          0.0f, 1.0f
};

unsigned int phongFloorVerticesByteSize = sizeof(phongFloorVertices);


std::vector<glm::vec3> initialSpherePositions;

void generateSurroundingPositions(std::vector<glm::vec3> &inputVector, int boxCount){
    for (int i = 0; i < boxCount; i++){
            float angle = (360 / boxCount) * i;
            float x = glm::cos(glm::radians(angle));
            float z = glm::sin(glm::radians(angle));

            glm::vec3 newPos(x, 0.0f, z);
            inputVector.push_back(newPos);

    }
}

void generateVAO(unsigned int &VAO, unsigned int &VBO, unsigned int boxVerticesByteSize, float boxVertices[]){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, boxVerticesByteSize, boxVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void generatePhongVAO(unsigned int &VAO, unsigned int &VBO, unsigned int boxVerticesByteSize, float boxVertices[]){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, boxVerticesByteSize, boxVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void generatePhongVAOandEBO(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, unsigned int verticesByteSize, unsigned int indicesByteSize, float vertices[], unsigned int indices[]){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesByteSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void generateVAOandEBO(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, unsigned int verticesByteSize, unsigned int indicesByteSize, float vertices[], unsigned int indices[]){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesByteSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}


void generateSphere(float radius, int numSegments, std::vector<float>& sphereVertices){ // generated by chatgpt
        sphereVertices.clear();

    for (int i = 0; i <= numSegments; ++i) {
        float phi = static_cast<float>(i) / numSegments * PI;
        for (int j = 0; j <= numSegments; ++j) {
            float theta = static_cast<float>(j) / numSegments * 2.0f * PI;

            // Calculate coordinates
            float x = radius * sin(phi) * cos(theta);
            float y = radius * sin(phi) * sin(theta);
            float z = radius * cos(phi);

            // Calculate normals
            float nx = x / radius;
            float ny = y / radius;
            float nz = z / radius;

            // Calculate texture coordinates
            float u = static_cast<float>(j) / numSegments;
            float v = 1.0f - static_cast<float>(i) / numSegments;

            // Push coordinates to the vector
            sphereVertices.push_back(x);
            sphereVertices.push_back(y);
            sphereVertices.push_back(z);

            sphereVertices.push_back(nx);
            sphereVertices.push_back(ny);
            sphereVertices.push_back(nz);

            sphereVertices.push_back(u);
            sphereVertices.push_back(v);

            // Repeat the first vertex for the triangle strip to close it
            if (j < numSegments) {
                float nextPhi = static_cast<float>(i + 1) / numSegments * PI;
                float nextX = radius * sin(nextPhi) * cos(theta);
                float nextY = radius * sin(nextPhi) * sin(theta);
                float nextZ = radius * cos(nextPhi);

                float nextNx = nextX / radius;
                float nextNy = nextY / radius;
                float nextNz = nextZ / radius;

                float nextU = static_cast<float>(j) / numSegments;
                float nextV = 1.0f - static_cast<float>(i + 1) / numSegments;

                sphereVertices.push_back(nextX);
                sphereVertices.push_back(nextY);
                sphereVertices.push_back(nextZ);

                sphereVertices.push_back(nextNx);
                sphereVertices.push_back(nextNy);
                sphereVertices.push_back(nextNz);

                sphereVertices.push_back(nextU);
                sphereVertices.push_back(nextV);
            }
        }
    }
}

void generatePhongSphere(float radius, int numSegments, std::vector<float>& sphereVertices) { // generated by chatgpt

    for (int y = 0; y < numSegments; ++y) {
        for (int x = 0; x < numSegments; ++x) {
            for (int i = 0; i < 2; ++i) {
                float xSegment1 = (float)x / numSegments;
                float ySegment1 = (float)y / numSegments;
                float xSegment2 = (float)(x + 1) / numSegments;
                float ySegment2 = (float)(y + 1) / numSegments;

                // Triangle 1
                std::vector<std::pair<float, float>> segments = {
                    {xSegment1, ySegment1}, {xSegment2, ySegment1}, {xSegment1, ySegment2},
                    {xSegment1, ySegment2}, {xSegment2, ySegment1}, {xSegment2, ySegment2}
                };

                for (int j = 0; j < 3; ++j) { // Three vertices per triangle
                    float xPos, yPos, zPos;
                    float xSeg = segments[i * 3 + j].first;
                    float ySeg = segments[i * 3 + j].second;

                    xPos = std::cos(xSeg * 2.0f * PI) * std::sin(ySeg * PI) * radius;
                    yPos = std::cos(ySeg * PI) * radius;
                    zPos = std::sin(xSeg * 2.0f * PI) * std::sin(ySeg * PI) * radius;

                    // Position
                    sphereVertices.push_back(xPos);
                    sphereVertices.push_back(yPos);
                    sphereVertices.push_back(zPos);

                    // Normal
                    float length = std::sqrt(xPos * xPos + yPos * yPos + zPos * zPos);
                    sphereVertices.push_back(xPos / length); // Normal X
                    sphereVertices.push_back(yPos / length); // Normal Y
                    sphereVertices.push_back(zPos / length); // Normal Z

                    // Texture Coordinate
                    sphereVertices.push_back(xSeg);
                    sphereVertices.push_back(ySeg);
                }
            }
        }
    }
}

void generateCone(float radius, float height, int numSegments, std::vector<float>& data){ // generated by chatgpt
    float angleIncrement = 2 * PI / numSegments;

    for (int i = 0; i < numSegments; ++i) {
        float angle1 = i * angleIncrement;
        float angle2 = (i + 1) * angleIncrement;

        // Vertices for the current triangle
        float x1 = radius * cos(angle1);
        float y1 = 0.0f;
        float z1 = radius * sin(angle1);

        float x2 = radius * cos(angle2);
        float y2 = 0.0f;
        float z2 = radius * sin(angle2);

        float x3 = 0.0f;
        float y3 = height;
        float z3 = 0.0f;

        // Texture coordinates (simple mapping for demonstration)
        float tx1 = static_cast<float>(i) / numSegments;
        float ty1 = 0.0f;

        float tx2 = static_cast<float>(i + 1) / numSegments;
        float ty2 = 0.0f;

        float tx3 = 0.5f;
        float ty3 = 1.0f;

        // Store vertices in the vector
        data.push_back(x1);
        data.push_back(y1);
        data.push_back(z1);
        data.push_back(tx1);
        data.push_back(ty1);

        data.push_back(x2);
        data.push_back(y2);
        data.push_back(z2);
        data.push_back(tx2);
        data.push_back(ty2);

        data.push_back(x3);
        data.push_back(y3);
        data.push_back(z3);
        data.push_back(tx3);
        data.push_back(ty3);

        // Additional triangle to close the bottom of the cone
        data.push_back(x1);
        data.push_back(y1);
        data.push_back(z1);
        data.push_back(tx1);
        data.push_back(ty1);

        data.push_back(x2);
        data.push_back(y2);
        data.push_back(z2);
        data.push_back(tx2);
        data.push_back(ty2);

        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.5f);
        data.push_back(0.0f);
    }
}

void generatePhongCone(float radius, float height, int numSegments, std::vector<float>& data) { // generated by chatgpt
    float angleIncrement = 2 * PI / numSegments;

    for (int i = 0; i < numSegments; ++i) {
        float angle1 = i * angleIncrement;
        float angle2 = (i + 1) * angleIncrement;

        // Vertices for the current triangle
        float x1 = radius * cos(angle1);
        float y1 = 0.0f;
        float z1 = radius * sin(angle1);

        float x2 = radius * cos(angle2);
        float y2 = 0.0f;
        float z2 = radius * sin(angle2);

        float x3 = 0.0f;
        float y3 = height;
        float z3 = 0.0f;

        // Calculate normal (cross product of two edges)
        float edge1x = x2 - x1;
        float edge1y = y2 - y1;
        float edge1z = z2 - z1;

        float edge2x = x3 - x1;
        float edge2y = y3 - y1;
        float edge2z = z3 - z1;

        // Calculate normal (cross product of two edges)
        float nx = edge1y * edge2z - edge1z * edge2y;
        float ny = edge1z * edge2x - edge1x * edge2z;
        float nz = edge1x * edge2y - edge1y * edge2x;

        // Ensure the normal is pointing outward
        float cx = x1 + x2 + x3;
        float cy = y1 + y2 + y3;
        float cz = z1 + z2 + z3;

        float dotProduct = (cx * nx + cy * ny + cz * nz);
        if (dotProduct < 0) {
            nx = -nx;
            ny = -ny;
            nz = -nz;
        }

        // Normalize the normal
        float length = sqrt(nx * nx + ny * ny + nz * nz);
        if (length != 0) {
            nx /= length;
            ny /= length;
            nz /= length;
        }

        // Texture coordinates (simple mapping for demonstration)
        float tx1 = static_cast<float>(i) / numSegments;
        float ty1 = 0.0f;

        float tx2 = static_cast<float>(i + 1) / numSegments;
        float ty2 = 0.0f;

        float tx3 = 0.5f;
        float ty3 = 1.0f;

        // Store vertices and normals in the vector
        data.push_back(x1);
        data.push_back(y1);
        data.push_back(z1);
        data.push_back(nx);
        data.push_back(ny);
        data.push_back(nz);
        data.push_back(tx1);
        data.push_back(ty1);

        data.push_back(x2);
        data.push_back(y2);
        data.push_back(z2);
        data.push_back(nx);
        data.push_back(ny);
        data.push_back(nz);
        data.push_back(tx2);
        data.push_back(ty2);

        data.push_back(x3);
        data.push_back(y3);
        data.push_back(z3);
        data.push_back(nx);
        data.push_back(ny);
        data.push_back(nz);
        data.push_back(tx3);
        data.push_back(ty3);

        // Additional triangle to close the bottom of the cone
        data.push_back(x1);
        data.push_back(y1);
        data.push_back(z1);
        data.push_back(nx);
        data.push_back(ny);
        data.push_back(nz);
        data.push_back(tx1);
        data.push_back(ty1);

        data.push_back(x2);
        data.push_back(y2);
        data.push_back(z2);
        data.push_back(nx);
        data.push_back(ny);
        data.push_back(nz);
        data.push_back(tx2);
        data.push_back(ty2);

        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(nx);
        data.push_back(ny);
        data.push_back(nz);
        data.push_back(0.5f);
        data.push_back(0.0f);
    }
}

void generateCylinderVertices(float radius, float height, int numSegments, std::vector<float>& vertices) { // generated by chatgpt
    vertices.clear();

    for (int i = 0; i <= numSegments; i++) { // <= to include the last segment
        float theta = static_cast<float>(i) / numSegments * 2.0f * PI;

        float x_bottom = radius * cos(theta);
        float y_bottom = 0.0f;
        float z_bottom = radius * sin(theta);

        float x_top = x_bottom;
        float y_top = height;
        float z_top = z_bottom;

        float u_bottom = static_cast<float>(i) / numSegments; // Use i / numSegments to include the last segment
        float v_bottom = 1.0f;

        float u_top = u_bottom;
        float v_top = 0.0f;

        vertices.push_back(x_bottom);
        vertices.push_back(y_bottom);
        vertices.push_back(z_bottom);
        vertices.push_back(u_bottom);
        vertices.push_back(v_bottom);

        vertices.push_back(x_top);
        vertices.push_back(y_top);
        vertices.push_back(z_top);
        vertices.push_back(u_top);
        vertices.push_back(v_top);
    }
}

void generatePhongCylinderVertices(float radius, float height, int numSegments, std::vector<float>& vertices) { // generated by chatgpt
    vertices.clear();

    // Generate side faces
    for (int i = 0; i < numSegments; i++) {
        float theta = static_cast<float>(i) / numSegments * 2.0f * PI;
        float nextTheta = static_cast<float>(i + 1) / numSegments * 2.0f * PI;

        // Bottom vertex
        float x_bottom = radius * cos(theta);
        float y_bottom = 0.0f;
        float z_bottom = radius * sin(theta);

        // Top vertex
        float x_top = x_bottom;
        float y_top = height;
        float z_top = z_bottom;

        // Next bottom vertex
        float x_bottom_next = radius * cos(nextTheta);
        float z_bottom_next = radius * sin(nextTheta);

        // Next top vertex
        float x_top_next = x_bottom_next;
        float z_top_next = z_bottom_next;

        // Calculate normal for the vertex
        float nx = cos(theta);
        float nz = sin(theta);

        // Vertices for the two triangles that make up the quad
        std::vector<double> quadVertices = {
            // First triangle
            x_bottom, y_bottom, z_bottom, nx, 0.0f, nz, static_cast<double>(i) / numSegments, 1.0f,
            x_top, y_top, z_top, nx, 0.0f, nz, static_cast<double>(i) / numSegments, 0.0f,
            x_top_next, y_top, z_top_next, cos(nextTheta), 0.0f, sin(nextTheta), static_cast<double>(i + 1) / numSegments, 0.0f,

            // Second triangle
            x_bottom, y_bottom, z_bottom, nx, 0.0f, nz, static_cast<double>(i) / numSegments, 1.0f,
            x_top_next, y_top, z_top_next, cos(nextTheta), 0.0f, sin(nextTheta), static_cast<double>(i + 1) / numSegments, 0.0f,
            x_bottom_next, y_bottom, z_bottom_next, cos(nextTheta), 0.0f, sin(nextTheta), static_cast<double>(i + 1) / numSegments, 1.0f,
        };

        vertices.insert(vertices.end(), quadVertices.begin(), quadVertices.end());
    }

    for (int cap = 0; cap < 2; cap++) { // 0 for bottom, 1 for top
        float y = (cap == 0) ? 0.0f : height;

        for (int i = 0; i < numSegments; i++) {
            float theta = static_cast<float>(i) / numSegments * 2.0f * PI;
            float nextTheta = static_cast<float>(i + 1) / numSegments * 2.0f * PI;

            // Center of the cap
            vertices.push_back(0.0f);
            vertices.push_back(y);
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
            vertices.push_back(cap == 0 ? -1.0f : 1.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.5f);
            vertices.push_back(0.5f);

            // First edge vertex
            vertices.push_back(radius * cos(theta));
            vertices.push_back(y);
            vertices.push_back(radius * sin(theta));
            vertices.push_back(0.0f);
            vertices.push_back(cap == 0 ? -1.0f : 1.0f);
            vertices.push_back(0.0f);
            vertices.push_back(cos(theta) * 0.5f + 0.5f);
            vertices.push_back(sin(theta) * 0.5f + 0.5f);

            // Second edge vertex
            vertices.push_back(radius * cos(nextTheta));
            vertices.push_back(y);
            vertices.push_back(radius * sin(nextTheta));
            vertices.push_back(0.0f);
            vertices.push_back(cap == 0 ? -1.0f : 1.0f);
            vertices.push_back(0.0f);
            vertices.push_back(cos(nextTheta) * 0.5f + 0.5f);
            vertices.push_back(sin(nextTheta) * 0.5f + 0.5f);
        }
    }
}
