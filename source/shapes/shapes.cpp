#include "shapes.h"
#include "../globals.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

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

    // Front face
     0.5f, 0.0f, -0.5f,  0.0f, 0.6f, -0.8f,  1.0f, 0.0f,
     0.5f, 0.0f,  0.5f,  0.0f, 0.6f, -0.8f,  1.0f, 1.0f,
    -0.5f, 0.0f,  0.5f,  0.0f, 0.6f, -0.8f,  0.0f, 1.0f,

    // Left face
    -0.5f, 0.0f,  0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, 0.0f, -0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     0.0f, 1.0f,  0.0f,  -1.0f, 0.0f, 0.0f,  0.5f, 0.5f,

    // Right face
     0.5f, 0.0f, -0.5f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f, 0.0f,  0.5f,  1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
     0.0f, 1.0f,  0.0f,  1.0f, 0.0f, 0.0f,   0.5f, 0.5f,

    // Back face
    -0.5f, 0.0f,  0.5f,  0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    0.5f, 0.0f,  0.5f,  0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,   0.5f, 0.5f
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
    -1.0f, 0.0f, -1.0f,       0.0f, 1.0f, 0.0f,          0.0f, 0.0f,
    1.0f, 0.0f, -1.0f,        0.0f, 1.0f, 0.0f,          1.0f, 0.0f,
    -1.0f, 0.0f, 1.0f,        0.0f, 1.0f, 0.0f,          0.0f, 1.0f,

    1.0f, 0.0f, -1.0f,        0.0f, 1.0f, 0.0f,          1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,         0.0f, 1.0f, 0.0f,          1.0f, 1.0f,
    -1.0f, 0.0f, 1.0f,        0.0f, 1.0f, 0.0f,          0.0f, 1.0f
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

void generateFloorVAO(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, unsigned int floorVerticesByteSize, float floorVertices[]){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, floorVerticesByteSize, floorVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorIndices), floorIndices, GL_STATIC_DRAW);

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

void generateCone(float radius, float height, int numSegments, std::vector<float>& data){ // generated by chatgpt
    const int vertexComponents = 5; // x, y, z, texture_x, texture_y

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
    const int vertexComponents = 8; // x, y, z, nx, ny, nz, texture_x, texture_y

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

void generateTubeVertices(float radius, float height, int numSegments, std::vector<float>& vertices) { // generated by chatgpt
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

void generatePhongTubeVertices(float radius, float height, int numSegments, std::vector<float>& vertices) { // generated by chatgpt
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

        // Calculate normal for the vertex
        float nx = cos(theta);
        float ny = 0.0f;
        float nz = sin(theta);

        // Normalize the normal
        float length = sqrt(nx * nx + ny * ny + nz * nz);
        if (length != 0) {
            nx /= length;
            ny /= length;
            nz /= length;
        }

        vertices.push_back(x_bottom);
        vertices.push_back(y_bottom);
        vertices.push_back(z_bottom);
        vertices.push_back(nx);
        vertices.push_back(ny);
        vertices.push_back(nz);
        vertices.push_back(u_bottom);
        vertices.push_back(v_bottom);

        vertices.push_back(x_top);
        vertices.push_back(y_top);
        vertices.push_back(z_top);
        vertices.push_back(nx);
        vertices.push_back(ny);
        vertices.push_back(nz);
        vertices.push_back(u_top);
        vertices.push_back(v_top);
    }
}
