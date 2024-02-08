#include "shapes.h"
#include "../globals.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

float boxVertices[] = {
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

float pyramidVertices[] = {
    -0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
    0.5f, 0.0f, -0.5f, 1.0f, 0.0f,
    -0.5f, 0.0f, 0.5f, 0.0f, 1.0f,

    0.5f, 0.0f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.0f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.0f, 0.5f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 0.5f, 0.5f,
    -0.5f, 0.0f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, -0.5f, 1.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 0.5f, 0.5f,
    0.5f, 0.0f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.5f, 1.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 0.5f, 0.5f,
    0.5f, 0.0f, 0.5f, 0.0f, 1.0f,
    -0.5f, 0.0f, 0.5f, 1.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 0.5f, 0.5f,
    -0.5f, 0.0f, 0.5f, 0.0f, 1.0f,
    -0.5f, 0.0f, -0.5f, 1.0f, 1.0f
};

unsigned int pyramidVerticesByteSize = sizeof(pyramidVertices);

float floorVertices[] = {
    -0.5f, 0.0f, 0.5f, 0.0f, 1.0f, // top left
    -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, // bottom left
    0.5f, 0.0f, -0.5f, 1.0f, 0.0f, // bottom right
    0.5f, 0.0f, 0.5f, 1.0f, 1.0f // top right
};
unsigned int floorIndices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

unsigned int floorVerticesByteSize = sizeof(floorVertices);

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


void generateSphere(float radius, int numSegments, std::vector<float>& sphereVertices) { // generated by chatGPT
    sphereVertices.clear();

    for (int i = 0; i < numSegments; ++i) {
        for (int j = 0; j < numSegments; ++j) {
            // Calculate indices for the current and next segments
            int idx0 = i * (numSegments + 1) + j;
            int idx1 = idx0 + 1;
            int idx2 = (i + 1) * (numSegments + 1) + j;
            int idx3 = idx2 + 1;

            // Triangle 1
            sphereVertices.push_back(radius * sin((float)i / numSegments * PI) * cos((float)j / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * sin((float)i / numSegments * PI) * sin((float)j / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * cos((float)i / numSegments * PI));
            sphereVertices.push_back((float)j / numSegments);
            sphereVertices.push_back(1.0f - (float)i / numSegments);

            sphereVertices.push_back(radius * sin((float)i / numSegments * PI) * cos((float)(j + 1) / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * sin((float)i / numSegments * PI) * sin((float)(j + 1) / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * cos((float)i / numSegments * PI));
            sphereVertices.push_back((float)(j + 1) / numSegments);
            sphereVertices.push_back(1.0f - (float)i / numSegments);

            sphereVertices.push_back(radius * sin((float)(i + 1) / numSegments * PI) * cos((float)j / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * sin((float)(i + 1) / numSegments * PI) * sin((float)j / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * cos((float)(i + 1) / numSegments * PI));
            sphereVertices.push_back((float)j / numSegments);
            sphereVertices.push_back(1.0f - (float)(i + 1) / numSegments);

            // Triangle 2
            sphereVertices.push_back(radius * sin((float)(i + 1) / numSegments * PI) * cos((float)j / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * sin((float)(i + 1) / numSegments * PI) * sin((float)j / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * cos((float)(i + 1) / numSegments * PI));
            sphereVertices.push_back((float)j / numSegments);
            sphereVertices.push_back(1.0f - (float)(i + 1) / numSegments);

            sphereVertices.push_back(radius * sin((float)i / numSegments * PI) * cos((float)(j + 1) / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * sin((float)i / numSegments * PI) * sin((float)(j + 1) / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * cos((float)i / numSegments * PI));
            sphereVertices.push_back((float)(j + 1) / numSegments);
            sphereVertices.push_back(1.0f - (float)i / numSegments);

            sphereVertices.push_back(radius * sin((float)(i + 1) / numSegments * PI) * cos((float)(j + 1) / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * sin((float)(i + 1) / numSegments * PI) * sin((float)(j + 1) / numSegments * 2.0f * PI));
            sphereVertices.push_back(radius * cos((float)(i + 1) / numSegments * PI));
            sphereVertices.push_back((float)(j + 1) / numSegments);
            sphereVertices.push_back(1.0f - (float)(i + 1) / numSegments);
        }
    }
}

