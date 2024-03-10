#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../globals.h"
#include "../opengl/camera_variables.h"
#include "../shapes/terrain.h"

void rotateAroundPoint(const glm::vec3 &player, glm::vec3 &cameraPos, float deltaTime, float rotationSpeed);

void moveToPoint(glm::vec3 &objectPos, const glm::vec3 &destinationPos, float deltaTime, float speed);

float calculateDistance(glm::vec3 objectPos, glm::vec3 destinationPos);

void movePlayerToPoint(float deltaTime, float speed);
