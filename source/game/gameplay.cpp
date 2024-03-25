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

        float cameraHeightAboveTerrain = getHeight(cameraPos.x, cameraPos.z);

        if (cameraPos.y < cameraHeightAboveTerrain + 1.0f)
            cameraPos.y = cameraHeightAboveTerrain + 1.0f;
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

        float cameraHeightAboveTerrain = getHeight(cameraPos.x, cameraPos.z);

        if (cameraPos.y < cameraHeightAboveTerrain + 1.0f)
            cameraPos.y = cameraHeightAboveTerrain + 1.0f;
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

    float enemyHeightAboveTerrain = getHeight(enemyPos.x, enemyPos.z);
    if (enemyPos.y < enemyHeightAboveTerrain + 0.5f){
        enemy[3][1] = enemyHeightAboveTerrain + 0.5f;
    }
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
    player[3][0] = playerPos.x;
    player[3][1] = playerPos.y;
    player[3][2] = playerPos.z;
    glm::vec3 playerMovement = playerPos - oldPlayerPos;
    cameraPos += playerMovement;
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
        float terrainY = getHeight(playerPos.x, playerPos.z);
        if (playerPos.y < terrainY + 0.5f){
            playerPos.y = terrainY + 0.5f;
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
                    if (isPlayer)
                        health += 1.0f;
                    else
                        if (!playerShieldToggle)
                            health -= 1.0f;
                    normalizedScore = (static_cast<float>(health) / 100.0f) / 10;
                    healthVertices[10] = normalizedScore;
                    healthVertices[15] = normalizedScore;

                    if (ENABLE_SOUND)
                        playSound();

                    if (health >= 300 || health <= -300){
                        if (health >= 300){
                            enemyLives -= 1;
                            if (enemyLives < 0)
                                gameOver = true;
                            dialogue = "";
                        }
                        else
                            playerLives -=1;
                            if (playerLives < 0)
                                gameOver = true;
                        animationModeActivate = true;
                        timeSinceAnimationActivation = glfwGetTime();
                    }



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
                    if (isPlayer)
                        health += 1.0f;
                    else
                        if (!playerShieldToggle)
                            health -= 1.0f;
                    normalizedScore = (static_cast<float>(health) / 100.0f) / 10;
                    healthVertices[10] = normalizedScore;
                    healthVertices[15] = normalizedScore;

                    if (ENABLE_SOUND)
                        playSound();

                    if (health > 300 || health < -300){
                        if (health >= 300){
                            enemyLives -= 1;
                            if (enemyLives < 0)
                                gameOver = true;
                            dialogue = "";
                        }
                        else
                            playerLives -=1;
                            if (playerLives < 0)
                                gameOver = true;
                        animationModeActivate = true;
                        timeSinceAnimationActivation = glfwGetTime();
                    }


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


void handleAnimationMode(std::string &outputText){
    CONTROLS_ENABLED = false;
    ENEMY_MOVMENT = false;
    playerCurrentlyFighting = false;
    playerFightingToggle = false;

    float currentFrame = glfwGetTime();
    deltaTime = 0.0f;
    float adjustedDeltaTime = currentFrame - lastFrame;
    lastFrame = glfwGetTime();

    bool playerIsLoser = false;
    if (health >= 300)
        playerIsLoser = false;
    else
        playerIsLoser = true;

    glm::vec3 playerPos = glm::vec3(player[3][0], player[3][1], player[3][2]);
    glm::vec3 enemyPos = glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]);

    float playerTerrainY = getHeight(playerPos.x, playerPos.z);
    float enemyTerrainY = getHeight(enemyPos.x, enemyPos.z);

    if (!playerIsLoser && enemyPos.y > enemyTerrainY + 0.5f){
            enemyPos.y -= 3.0f * adjustedDeltaTime;
            enemy[3][1] = enemyPos.y;
    }


    if (playerIsLoser && playerPos.y > playerTerrainY + 0.5f){
            playerPos.y -= 3.0f * adjustedDeltaTime;
            player[3][1] = playerPos.y;
    }
    rotateCameraAroundPoint(glm::vec3(player[3][0], player[3][1], player[3][2]),
                                cameraPos, adjustedDeltaTime, -CAMERA_ROTATE_SPEED * 0.5);

    if ((currentFrame - timeSinceAnimationActivation) > 5.0f && playerIsLoser){
        outputText = "\\\\\\\\\\\\\\                                  remaining lives: " + std::to_string(playerLives);
    }
    if ((currentFrame - timeSinceAnimationActivation) > 5.0f && !playerIsLoser){
        outputText = "\\\\\\\\\\\\\\                                remaining enemy lives: " + std::to_string(enemyLives);
    }

    if ((currentFrame - timeSinceAnimationActivation) > 10.0f){
        CONTROLS_ENABLED = true;
        ENEMY_MOVMENT = true;
        animationModeActivate = false;

        health = 0;

        float normalizedScore = (static_cast<float>(health) / 100.0f) / 10;
        healthVertices[10] = normalizedScore;
        healthVertices[15] = normalizedScore;
    }
}

void handleGameOver(glm::mat4 &player, glm::mat4 &enemy, std::string &animationText){
    health = 0.0f;
    CONTROLS_ENABLED = false;
    ENEMY_MOVMENT = false;
    playerCurrentlyFighting = false;
    playerFightingToggle = false;
    bool playerWin;
    if (playerLives > enemyLives)
        playerWin = true;
    else
        playerWin = false;
    animationText = "\\\\\\\\\\\\                       game over! press backspace to play again!";
    if (playerWin)
        animationText += "\\                                     player win!";
    if (!playerWin)
        animationText += "\\                                     enemy win!";

    if (restartGame){
        restartGame = false;
        gameOver = false;
        animationModeActivate = false;
        CONTROLS_ENABLED = true;
        ENEMY_MOVMENT = true;
        timeSinceAnimationActivation = 0.0f;
        playerLives = 3;
        enemyLives = 3;

        timeSinceLastEnemyWait = glfwGetTime();

        player[3][0] = 0.0f;
        player[3][1] = getHeight(0.0f, -5.0f) + 10.0f;
        player[3][2] = -3.5f;

        enemyGoTo = glm::vec3(0.0f, 0.0f, 0.0f);
        enemyGoTo.y = getHeight(enemyGoTo.x, enemyGoTo.z) + 10.0f;
        enemy[3][0] = enemyGoTo.x;
        enemy[3][1] = enemyGoTo.y;
        enemy[3][2] = enemyGoTo.z;

        cameraPos.x = player[3][0];
        cameraPos.y = player[3][1];
        cameraPos.z = player[3][2] + 3.5f;

        normalizedScore = (static_cast<float>(health) / 100.0f) / 10;
        healthVertices[10] = normalizedScore;
        healthVertices[15] = normalizedScore;
    }
}
