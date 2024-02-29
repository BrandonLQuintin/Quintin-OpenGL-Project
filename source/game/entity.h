#pragma once
#include "../shapes/shapes.h"
#include "../opengl/camera_variables.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void setShadowLocation(shape &shape, glm::vec3 targetPos, float groundY);

struct rainEntity {
    glm::mat4 modelMatrix = glm::mat4(1.0f); // initialized to an identity matrix
    float initialY = modelMatrix[3][1];
    float speed = 5;
};
