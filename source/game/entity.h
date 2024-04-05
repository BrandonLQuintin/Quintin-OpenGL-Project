#pragma once
#include "../shapes/shapes.h"
#include "../opengl/camera_variables.h"
#include "../globals.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct rainEntity {
    glm::mat4 modelMatrix = glm::mat4(1.0f); // initialized to an identity matrix

    float speed = 5;
};

struct punchEntity {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    float timeSinceExistence = glfwGetTime();
    int textureXCoord = 0;
};

struct dustEntity {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    float timeSinceExistence = glfwGetTime();
};


void setShadowLocation(shape &shape, glm::vec3 targetPos, float groundY);

void setRainLocation(rainEntity &rain);

void initializeRainLocation(rainEntity &rain);

