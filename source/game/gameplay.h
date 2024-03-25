#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include "../globals.h"
#include "../opengl/camera_variables.h"
#include "../shapes/terrain.h"
#include "entity.h"
#include "../opengl/text_render.h"
#include "sound.h"

void rotateCameraAroundPoint(const glm::vec3 &player, glm::vec3 &cameraPos, float deltaTime, float rotationSpeed);
void rotatePlayerAroundEnemy(float deltaTime, bool isPlayer);

void moveToPoint(glm::vec3 &objectPos, const glm::vec3 &destinationPos, float deltaTime, float speed);
void moveEnemyToPoint(const glm::vec3 destinationPos, float deltaTime, float speed);

float calculateDistance(glm::vec3 objectPos, glm::vec3 destinationPos);

void movePlayerToPoint(float deltaTime, float speed);

int calculateOrientationSpriteIndex(const glm::mat4 &transformationMatrix, const glm::vec3 &characterVertex, const glm::vec3 &targetVertex);

void calculateTimeSinceLastPunch(float &timeSinceSomething, float currentFrame, bool &toggle);

void calculatePunchParticles(bool leftSide, glm::vec3 playerPos, glm::vec3 enemyPos);

void handleFightAnimations(float distanceFromEnemy, float currentFrame, std::vector<float> &playerUV, bool isPlayer);

void handleAnimationMode(std::string &outputText);

void handleGameOver(glm::mat4 &player, glm::mat4 &enemy, std::string &animationText);

extern std::vector<punchEntity> existingPunches;
