#include "player_controls.h"

void rotateAroundPoint(const glm::vec3 &player, glm::vec3 &cameraPos, float deltaTime, float rotationSpeed){ // chatGPT generated
    float angleRadians = glm::radians(rotationSpeed) * deltaTime;

    glm::vec3 toCamera = cameraPos - player;

    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angleRadians, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 rotatedVector = glm::vec3(rotation * glm::vec4(toCamera, 1.0f));

    cameraPos = player + rotatedVector;
}

void moveToPoint(glm::vec3 &objectPos, const glm::vec3 &destinationPos, float deltaTime, float speed){ // chatGPT generated
    glm::vec3 direction = glm::normalize(destinationPos - objectPos);

    float maxDistance = speed * deltaTime;

    objectPos += direction * maxDistance;

}

float calculateDistance(glm::vec3 objectPos, glm::vec3 destinationPos){
    glm::vec3 direction = glm::normalize(destinationPos - objectPos);

    float distance = glm::distance(objectPos, destinationPos);

    return distance;
}

void movePlayerToPoint(float deltaTime, float speed){
    glm::vec3 destinationPos(enemy[3][0], enemy[3][1], enemy[3][2]);
    glm::vec3 playerPos = glm::vec3(player[3][0], player[3][1], player[3][2]);
    glm::vec3 oldPlayerPos = playerPos;

    float distanceFromEnemy = calculateDistance(playerPos, destinationPos);

    if (distanceFromEnemy > 1.0f){
            moveToPoint(playerPos, destinationPos, deltaTime, speed);
    }

    float playerHeightAboveTerrain = getHeight(player[3][0], player[3][2]) + 0.5f;

    player[3][0] = playerPos.x;
    player[3][1] = playerPos.y;
    player[3][2] = playerPos.z;
    glm::vec3 playerMovement = playerPos - oldPlayerPos;
    cameraPos += playerMovement;

    if (playerPos.y < playerHeightAboveTerrain){
        player[3][1] = playerHeightAboveTerrain;
    }
}

int calculateOrientationSpriteIndex(const glm::mat4 &transformationMatrix, const glm::vec3 &characterVertex, const glm::vec3 &targetVertex){
    float rotationY = atan2(transformationMatrix[2][0], transformationMatrix[0][0]);

    float dx = targetVertex.x - characterVertex.x;
    float dz = targetVertex.z - characterVertex.z;

    float angle = atan2(dz, dx) - rotationY;
    angle = fmod((angle + 2 * M_PI) * (180.0f / M_PI), 360.0f);

    int spriteIndex = 0; // Default to back view
    if ((angle >= 315.0f && angle < 360.0f) || (angle >= 0.0f && angle < 45.0f)) {
        spriteIndex = 1; // Right View
    } else if (angle >= 45.0f && angle < 135.0f) {
        spriteIndex = 2; // Front View
    } else if (angle >= 135.0f && angle < 225.0f) {
        spriteIndex = 3; // Left View
    } else if (angle >= 225.0f && angle < 315.0f) {
        spriteIndex = 0; // Back View
    }

    return spriteIndex;
}
