#include "gameplay.h"

std::vector<punchEntity> existingPunches;

void rotateCameraAroundPoint(const glm::vec3 &player, glm::vec3 &cameraPos, float deltaTime, float rotationSpeed){ // chatGPT generated
    float angleRadians = glm::radians(rotationSpeed) * deltaTime;

    glm::vec3 toCamera = cameraPos - player;

    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angleRadians, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 rotatedVector = glm::vec3(rotation * glm::vec4(toCamera, 1.0f));

    cameraPos = player + rotatedVector;
}

void rotatePlayerAroundEnemy(float deltaTime, bool isPlayer){
    glm::vec3 playerPos;
    glm::vec3 enemyPos;
    if (isPlayer){
        playerPos = glm::vec3(player[3][0], player[3][1], player[3][2]);
        enemyPos = glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]);
    }
    else{
        playerPos = glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]);
        enemyPos = glm::vec3(player[3][0], player[3][1], player[3][2]);
    }

    float rotationSpeed = 320.0f;
    float angleRadians = glm::radians(rotationSpeed) * deltaTime;

    glm::vec3 toPlayer = playerPos - enemyPos;

    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angleRadians, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 rotatedVector = glm::vec3(rotation * glm::vec4(toPlayer, 1.0f));

    playerPos = enemyPos + rotatedVector;
    if (isPlayer){
        player[3][0] = playerPos.x;
        player[3][1] = playerPos.y;
        player[3][2] = playerPos.z;

        enemy[3][0] = enemyPos.x;
        enemy[3][1] = enemyPos.y;
        enemy[3][2] = enemyPos.z;

        cameraPos.x = player[3][0];
        cameraPos.y = player[3][1];
        cameraPos.z = player[3][2] + 3.5f;
    }

    else{
        player[3][0] = enemyPos.x;
        player[3][1] = enemyPos.y;
        player[3][2] = enemyPos.z;

        enemy[3][0] = playerPos.x;
        enemy[3][1] = playerPos.y;
        enemy[3][2] = playerPos.z;

        cameraPos.x = player[3][0];
        cameraPos.y = player[3][1];
        cameraPos.z = player[3][2] + 2.5f;
    }

}

void moveToPoint(glm::vec3 &objectPos, const glm::vec3 &destinationPos, float deltaTime, float speed){ // chatGPT generated
    glm::vec3 direction = glm::normalize(destinationPos - objectPos);

    float maxDistance = speed * deltaTime;

    objectPos += direction * maxDistance;

}

void moveEnemyToPoint(const glm::vec3 destinationPos, float deltaTime, float speed){
    glm::vec3 enemyPos = glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]);
    glm::vec3 direction = glm::normalize(destinationPos - enemyPos);

    float maxDistance = speed * deltaTime;

    enemyPos += direction * maxDistance;

    enemy[3][0] = enemyPos.x;
    enemy[3][1] = enemyPos.y;
    enemy[3][2] = enemyPos.z;
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

    if (distanceFromEnemy > 1.0f || speed < 0){
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

void calculateTimeSinceLastPunch(float &timeSinceSomething, float currentFrame, bool &toggle){
    float time = currentFrame - timeSinceSomething;
    float adjustedTime = 0.03f;
    if (SLOW_MO){
        adjustedTime *= SLOW_MO_MULTIPLIER;
    }
    if (time > adjustedTime){
        timeSinceSomething = currentFrame;
        toggle = !toggle;
        punchFrameToggle = true;
    }
}

void calculatePunchParticles(bool leftSide, glm::vec3 playerPos, glm::vec3 enemyPos){
    punchEntity newPunch;
    float randXValue = randomInRange(13.0f, 16.0f);
    randXValue = std::floor(randXValue);
    newPunch.textureXCoord = randXValue;

    if (leftSide){
        newPunch.modelMatrix[3][0] = enemyPos.x + randomInRange(-0.5f, 0.0f);
    }
    else{
        newPunch.modelMatrix[3][0] = enemyPos.x + randomInRange(0.0f, 0.5f);
    }
    newPunch.modelMatrix[3][1] = enemyPos.y + randomInRange(-0.5f, 0.5f);
    newPunch.modelMatrix[3][2] = playerPos.z;
    existingPunches.push_back(newPunch);
    punchFrameToggle = false;
}

void handleFightAnimations(float distanceFromEnemy, float currentFrame, std::vector<float> &playerUV, bool isPlayer){
    if ((playerFightingToggle || enemyFightingToggle) && distanceFromEnemy < 1.3f){ // initialize player's fighting position to the left of the enemy
        glm::vec3 playerPos;
        glm::vec3 enemyPos;
        if (isPlayer){
            playerPos = glm::vec3(player[3][0], player[3][1], player[3][2]);
            enemyPos = glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]);
        }
        else{
            playerPos = glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]);
            enemyPos = glm::vec3(player[3][0], player[3][1], player[3][2]);
        }


        if (initializeFightAnimation == true){

            playerCurrentlyFighting = true;
            if (isPlayer){
                if (playerPos.x < enemyPos.x) // if player left, start fight left
                    playerPos.x = enemyPos.x - 1.0f;
                else
                    playerPos.x = enemyPos.x + 1.0f;
                newDialogue();
                playerPos.y = enemyPos.y;
                playerPos.z = enemyPos.z;
            }
            else{
                if (enemyPos.x < playerPos.x)
                    enemyPos.x = playerPos.x - 1.0f;
                else
                    enemyPos.x = playerPos.x + 1.0f;
                enemyPos.y = playerPos.y;
                enemyPos.z = playerPos.z;
            }
            initializeFightAnimation = false;
        }
        float adjustedDeltaTime = deltaTime;
        if (SLOW_MO){
            adjustedDeltaTime /= SLOW_MO_MULTIPLIER;
        }

        if (punchAnimationBounceBack == false){
            playerPos.y += 0.4f * adjustedDeltaTime;
            if (playerPos.y >= (enemyPos.y + 0.1f)){ // hit top
                punchAnimationBounceBack = true;
            }
        }
        else if (punchAnimationBounceBack == true){
            playerPos.y -= 0.4f * adjustedDeltaTime;
            if (playerPos.y <= (enemyPos.y - 0.1f)){ // hit bottom
                punchAnimationBounceBack = false;
            }
        }

        // set player position BEFORE rotation!
        if (isPlayer){
            player[3][0] = playerPos.x;
            player[3][1] = playerPos.y;
            player[3][2] = playerPos.z;

            enemy[3][0] = enemyPos.x;
            enemy[3][1] = enemyPos.y;
            enemy[3][2] = enemyPos.z;
        }
        else{
            player[3][0] = enemyPos.x;
            player[3][1] = enemyPos.y;
            player[3][2] = enemyPos.z;

            enemy[3][0] = playerPos.x;
            enemy[3][1] = playerPos.y;
            enemy[3][2] = playerPos.z;
        }

        rotatePlayerAroundEnemy(adjustedDeltaTime, isPlayer);
        calculateTimeSinceLastPunch(timeSinceLastPunch, currentFrame, firstPunchFrame);

        if (playerPos.x < enemyPos.x){ // if player is left, show the player punching from the left side
            if (firstPunchFrame){
                if (punchFrameToggle){
                    calculatePunchParticles(true, playerPos, enemyPos); // before punching enemy, generate punch particles.
                    if (ENABLE_SOUND)
                        playSound();
                    }
                playerUV = returnTextureUV(2,4);
                }
            else
            playerUV = returnTextureUV(3,4);
        }
        else{
            if (firstPunchFrame){
                if (punchFrameToggle){
                    calculatePunchParticles(false, playerPos, enemyPos);
                    if (ENABLE_SOUND)
                        playSound();
                    }
                    playerUV = returnTextureUV(2,6);
                }
                else
                    playerUV = returnTextureUV(3,6);
        }
    }
    else{ // if player is not in range of enemy
        playerCurrentlyFighting = false;
    }
}

