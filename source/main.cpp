#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// opengl & SFML
#include <glad/glad.h> // loads OpenGL pointers
#include <GLFW/glfw3.h> // window manager
#include <SFML/Audio.hpp>

//#include <stb_image.h> // helps load images (commented out because it's in textures.h)
#include <shader_m.h> // shader class from learnopengl.com on lesson "Coordinate Systems"

// opengl math libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// variables (may also contain functions)
#include "globals.h"
#include "opengl/camera_variables.h"
#include "shapes/shapes.h"
#include "shapes/initialize_shape_vertices.h"

// functions
#include "opengl/window_functions.h"
#include "opengl/shader_functions.h"
#include "opengl/textures.h"
#include "opengl/text_render.h"
#include "game/entity.h"
#include "game/calculate_fps.h"
#include "game/main_menu.h"
#include "game/gameplay.h"
#include "shapes/terrain.h"
#include "game/sound.h"


int main(){
    GLFWwindow* window = createWindow();
    glEnable(GL_DEPTH_TEST);
    Shader billboardShader("shaders/billboard_shader.vs", "shaders/billboard_shader.fs");
    Shader phongShader("shaders/phong_lighting.vs", "shaders/phong_lighting.fs");
    Shader t("shaders/text_shader.vs", "shaders/text_shader.fs"); // variable name shortened so I can call it faster with renderText()

    billboardShader.use();
    billboardShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    billboardShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    billboardShader.setVec3("lightPos", glm::vec3(-10000.0f, 1000.0f, 10000.0f));

    phongShader.use();
    phongShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    phongShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    phongShader.setVec3("lightPos", glm::vec3(-1000.0f, 1000.0f, 1000.0f));

    generatePlaneVertices(phongTerrainVector, phongTerrainIndicesVector);
    initializeAllShapes();

    // ----- TEXTURES -----
    unsigned int texture1, texture2, texture3;
    loadTexture(texture1, "resources/textures/TextureAtlas.png");
    loadTexture(texture2, "resources/textures/TextAtlas.png");
    loadTexture(texture3, "resources/textures/GrassTiles.png");
    billboardShader.use();
    billboardShader.setInt("texture1", 0);
    billboardShader.setInt("texture2", 1);

    phongShader.use();
    phongShader.setInt("texture1", 0);
    phongShader.setInt("texture2", 2);

    t.use();
    t.setInt("texture1", 0);
    t.setInt("texture2", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture3);

    // first atlas values
    std::vector<float> boxAtlasUV = returnTextureUV(0, 0);
    std::vector<float> cobbleAtlasUV = returnTextureUV(1, 0);
    std::vector<float> oceroAtlasUV = returnTextureUV(2, 0);
    std::vector<float> shadowAtlasUV = returnTextureUV(0, 2);
    std::vector<float> rainAtlasUV = returnTextureUV(2, 2);

    std::vector<float> playerBackUV = returnTextureUV(0, 3);
    std::vector<float> playerRightUV = returnTextureUV(0, 4);
    std::vector<float> playerFrontUV = returnTextureUV(0, 5);
    std::vector<float> playerLeftUV = returnTextureUV(0, 6);

    std::vector<float> playerInjuryUV = returnTextureUV(1, 5);
    std::vector<float> playerShieldUV = returnTextureUV(0, 1);

    std::vector<float> redSquareUV = returnTextureUV(1, 1);

    std::vector<float> cloudAtlasUV = {0.6875f, 1.0f, 0.25f, 0.375f}; // these textures take up multiple 64x64 pixel grids so I gave it hard coded numbers.
    std::vector<float> treeAtlasUV = {0.75f, 1.0f, 0.0625f, 0.25f};

    // ----- INITIALIZE SOUNDS -----
    if (!loadSoundBuffer("resources/sounds/punch.wav")) {
        std::cerr << "Could not load sound file." << std::endl;
        return -1;
    }
    playSoundSilentlyMultipleTimes(30);

    // ----- INITIALIZE OBJECTS -----

    // initialize various sphere locations
    float heightOffset = 50.0f;

    generateSurroundingPositions(initialSpherePositions, 25);
    for (int i = 0; i < initialSpherePositions.size(); i++){
        initialSpherePositions[i] = initialSpherePositions[i] * glm::vec3(30.0f, 30.0f, 30.0f);
        initialSpherePositions[i].y = 10.0f + heightOffset;
    }

    // enemy
    enemyGoTo = glm::vec3(0.0f, 0.0f, 0.0f);
    enemyGoTo.y = getHeight(enemyGoTo.x, enemyGoTo.z) + 10.0f;
    enemy[3][0] = enemyGoTo.x;
    enemy[3][1] = enemyGoTo.y;
    enemy[3][2] = enemyGoTo.z;

    // 1 terrain
    shape terrains[1];
    int terrainsArraySize = sizeof(terrains) / sizeof(terrains[0]);

    // 100 trees
    shape trees[5000];
    int treesArraySize = sizeof(trees) / sizeof(trees[0]);
    const float HALF_CHUNK_SIZE = CHUNK_SIZE / 2;
    for (int i = 0; i < treesArraySize; i++){
        trees[i].modelMatrix[3][0] = cameraPos.x + randomInRange(-HALF_CHUNK_SIZE, HALF_CHUNK_SIZE);
        trees[i].modelMatrix[3][2] = cameraPos.z + randomInRange(-HALF_CHUNK_SIZE, HALF_CHUNK_SIZE);
        trees[i].modelMatrix[3][1] = getHeight(trees[i].modelMatrix[3][0], trees[i].modelMatrix[3][2]) + 2.3f;
        trees[i].modelMatrix = glm::scale(trees[i].modelMatrix, glm::vec3(5.0f));
    }
    shape clonedTree[treesArraySize];
    for (int i = 0; i < treesArraySize; i++){
        clonedTree[i].modelMatrix = trees[i].modelMatrix;
    }
    for (int i = 0; i < treesArraySize; i++){
        clonedTree[i].modelMatrix = glm::rotate(clonedTree[i].modelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        clonedTree[i].modelMatrix[3][0] = trees[i].modelMatrix[3][0] + 0.55f;
        clonedTree[i].modelMatrix[3][1] = trees[i].modelMatrix[3][1];
        clonedTree[i].modelMatrix[3][2] = trees[i].modelMatrix[3][2] + 0.55f;
    }

    // 2 boxes
    shape boxes[2];
    int boxesArraySize = sizeof(boxes) / sizeof(boxes[0]);
    boxes[0].modelMatrix = glm::translate(boxes[0].modelMatrix, glm::vec3(1.0f, 0.5f + heightOffset, -3.0f));
    boxes[1].modelMatrix = glm::translate(boxes[1].modelMatrix, glm::vec3(1.0f, 1.5f + heightOffset, -3.0f));

    // 1 floor
    shape floors[1];
    int floorsArraySize = sizeof(floors) / sizeof(floors[0]);
    floors[0].modelMatrix = glm::translate(floors[0].modelMatrix, glm::vec3(0.0f, 0.0f + heightOffset, 0.0f));
    floors[0].modelMatrix = glm::scale(floors[0].modelMatrix, glm::vec3(500.0f));

    // 1 pyramid
    shape pyramids[1];
    int pyramidsArraySize = sizeof(pyramids) / sizeof(pyramids[0]);
    pyramids[0].modelMatrix = glm::translate(pyramids[0].modelMatrix, glm::vec3(0.0f, 0.0f + heightOffset, -3.0f));

    // 25 spheres
    shape spheres[25];
    int spheresArraySize = sizeof(spheres) / sizeof(spheres[0]);
    for (int i = 0; i < spheresArraySize; i++){
        spheres[i].modelMatrix = glm::translate(spheres[i].modelMatrix, initialSpherePositions[i]);
    }

    // 1 cone
    shape cones[1];
    int conesArraySize = sizeof(cones) / sizeof(cones[0]);
    cones[0].modelMatrix = glm::translate(cones[0].modelMatrix, glm::vec3(-1.0f, 0.0f + heightOffset, -3.0f));

    // 1 tube
    shape tubes[1];
    int tubesArraySize = sizeof(tubes) / sizeof(tubes[0]);
    tubes[0].modelMatrix = glm::translate(tubes[0].modelMatrix, glm::vec3(-2.0f, 0.0f + heightOffset, -3.0f));

    // 1 billboard
    shape billboards[3];
    int billboardsArraySize = sizeof(billboards) / sizeof(billboards[0]);
    for (int i = 0; i < billboardsArraySize; i++){
        billboards[i].modelMatrix = glm::translate(billboards[i].modelMatrix, glm::vec3(1 - (i * 1.1), 0.0f + heightOffset, -5.0f));
    }

    // rain drops
    rainEntity rainDrops[600];
    int rainDropsArraySize = sizeof(rainDrops) / sizeof(rainDrops[0]);
    for (int i = 0; i < rainDropsArraySize; i++)
        initializeRainLocation(rainDrops[i]);

    player[3][0] = 0.0f;
    player[3][1] = getHeight(0.0f, -5.0f) + 10.0f;
    player[3][2] = -3.5f;

    if (IS_RAINING){
        phongShader.use();
        phongShader.setBool("isRaining", true);
        phongShader.setFloat("fogDensity", FOG_DENSITY);
        billboardShader.use();
        billboardShader.setBool("isRaining", true);
        billboardShader.setFloat("fogDensity", FOG_DENSITY);
    }

    // ----- MAIN PROGRAM -----

    while (!glfwWindowShouldClose(window)){
        while (mainMenu){
            processMainMenu(window, t, menuChoice);
            timeSinceLastEnemyWait = glfwGetTime();
        }

        float currentFrame = glfwGetTime();
        std::string animationText;
        if (gameOver){
            handleGameOver(player, enemy, animationText);

        }
        else if (animationModeActivate){  // animation mode! (executes when health is less than -300 or greater than 300)
            animationDeltaTime = currentFrame - lastFrame;
            handleAnimationMode(animationText);
        }
        else{
            deltaTime = currentFrame - lastFrame;
        }


        if (SLOW_MO)
            deltaTime /= SLOW_MO_MULTIPLIER;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.792f, 0.957f, 1.00f, 1.0f);


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        billboardShader.use();
        billboardShader.setMat4("view", view);
        billboardShader.setMat4("projection", projection);
        billboardShader.setVec3("viewPos", cameraPos);

        phongShader.use();
        phongShader.setMat4("view", view);
        phongShader.setMat4("projection", projection);
        phongShader.setVec3("viewPos", cameraPos);

        // ----- DRAW PLAYER / ENEMY -----

        // ### PLAYER
        billboardShader.use();
        glBindVertexArray(phongBillboardVAO);
        int orientation = calculateOrientationSpriteIndex(view, glm::vec3(player[3][0], player[3][1], player[3][2]), glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]));
        glm::vec3 playerPos = glm::vec3(player[3][0], player[3][1], player[3][2]);
        glm::vec3 enemyPos = glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]);
        std::vector<float> playerUV = returnTextureUV(0, 3 + orientation);

        float playerHeightAboveTerrain = getHeight(player[3][0], player[3][2]);
        if (player[3][1] < playerHeightAboveTerrain + 0.5f){
            player[3][1] = playerHeightAboveTerrain + 0.5f;
        }

        // handle player teleporting (and teleporting rain particles)
        float distanceFromEnemy = calculateDistance(glm::vec3(player[3][0], player[3][1], player[3][2]), glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]));
        if (distanceFromEnemy > 50.0f)
            allowPlayerTeleportation = true;
        else
            allowPlayerTeleportation = false;

        if (teleportKeyPressed && allowPlayerTeleportation){
            player[3][0] = enemy[3][0] - 1.0f;
            player[3][1] = enemy[3][1];
            player[3][2] = enemy[3][2];

            cameraPos.x = player[3][0];
            cameraPos.y = player[3][1];
            cameraPos.z = player[3][2] + 3.5f;

            for (int i = 0; i < rainDropsArraySize; i++)
                initializeRainLocation(rainDrops[i]);
        }

        if (!FREECAM_CONTROLS_ENABLED){
            cameraPos.y = player[3][1];
            float cameraHeightAboveTerrain = getHeight(cameraPos.x, cameraPos.z);

            if (cameraPos.y < cameraHeightAboveTerrain + 1.0f){
                cameraPos.y = cameraHeightAboveTerrain + 1.0f;
            }

            // handle player animations
            if (!enemyFightingToggle){
                handleFightAnimations(distanceFromEnemy, currentFrame, playerUV, true);
            }

            cameraFront = glm::normalize(glm::vec3(player[3][0], player[3][1], player[3][2]) - cameraPos);
        }

        // render all punches
        for (int i = 0; i < existingPunches.size(); i++){
            float timeMultiplier = 0.05f;
            if (SLOW_MO){
                timeMultiplier *= SLOW_MO_MULTIPLIER;
            }

            if (currentFrame - existingPunches[i].timeSinceExistence > timeMultiplier){
                existingPunches.erase(existingPunches.begin() + i);
            }

            else{
                std::vector<float> punchTexture = returnTextureUV(existingPunches[i].textureXCoord, 1);
                setTextureUV(billboardShader, punchTexture, false);
                billboardShader.setMat4("model", existingPunches[i].modelMatrix);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }

        }

        // render player
        if (enemyFightingToggle && !playerShieldToggle)
            playerUV = playerInjuryUV;
        if (playerShieldEnabled || playerShieldToggle){
            setTextureUV(billboardShader, playerShieldUV, false);
            billboardShader.setMat4("model", player);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        setTextureUV(billboardShader, playerUV, false);
        billboardShader.setMat4("model", player);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // ### ENEMY
        float enemyHeightAboveTerrain = getHeight(enemy[3][0], enemy[3][2]);
        if (enemy[3][1] < enemyHeightAboveTerrain + 0.5f){
            enemy[3][1] = enemyHeightAboveTerrain + 0.5f;
        }

        float determinedTime = 10.0f;
        if (SLOW_MO){
            determinedTime *= SLOW_MO_MULTIPLIER;
        }
        if (playerFightingToggle && distanceFromEnemy < 1.3f && !(enemyWaitTime > determinedTime)) // if enemy is getting damaged
            playerUV = playerInjuryUV;
        else{
            orientation = calculateOrientationSpriteIndex(view, glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]), glm::vec3(player[3][0], player[3][1], player[3][2]));
            playerUV = returnTextureUV(0, 3 + orientation);
        }

        if (ENEMY_MOVMENT){
            float enemyGoToDistance = calculateDistance(enemyPos, enemyGoTo);
            float distanceFromPlayer = calculateDistance(enemyPos, playerPos);
            enemyWaitTime = currentFrame - timeSinceLastEnemyWait;

            if (enemyWaitTime > determinedTime && !enemyFightingToggle){
                moveEnemyToPoint(enemyGoTo, deltaTime, MOVEMENT_SPEED * 0.8);
                float terrainY = getHeight(enemy[3][0], enemy[3][2]);
                if (enemy[3][1] < terrainY){
                    enemy[3][1] = terrainY;
                }
            }

            if (distanceFromPlayer < 1.0f && !enemyFightingToggle){ // every half second there is a 20% chance of attack
                    if (currentFrame - timeSinceLastEnemyThought > 0.5f && !playerCurrentlyFighting && !enemyFightingToggle){
                        timeSinceLastEnemyThought = glfwGetTime();
                        int randomChance = randomInRange(0.0f, 100.0f);
                        if (randomChance <= 20.0f || enemyOffensiveMode){
                            if (playerShieldEnabled)
                                playerShieldToggle = true;
                            else
                                playerShieldToggle = false;

                            enemyFightingToggle = true;
                            timeSinceEnemyFightInit = glfwGetTime();
                        }
                    }
            }
            // handle enemy fighting animations
            if (enemyFightingToggle){
                if (currentFrame - timeSinceEnemyFightInit > 3.0f){
                    timeSinceLastEnemyThought = glfwGetTime();
                    playerShieldToggle = false;
                    enemyFightingToggle = false;
                    timeSinceEnemyFightInit = glfwGetTime();
                    cameraPos.x = player[3][0];
                    cameraPos.y = player[3][1];
                    cameraPos.z = player[3][2] + 3.5f;
                }
                else
                    handleFightAnimations(distanceFromPlayer, currentFrame, playerUV, false);
            }


            if (enemyGoToDistance < 1.0f){ // enemy calculates where to go next
                // calculate whether the enemy will be offensive or defensive
                float chance = randomInRange(0.0f, 100.0f);
                if (chance > 20.0f)
                    enemyOffensiveMode = true;
                else
                    enemyOffensiveMode = false;
                if (!enemyOffensiveMode){
                    glm::vec3 oldEnemyPos = glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]);
                    glm::vec3 newEnemyPos = glm::vec3(randomInRange(-300, 300), 0, randomInRange(-300, 300));
                    float distanceFromPos = calculateDistance(oldEnemyPos, newEnemyPos);
                    int attempts = 0;
                    while (distanceFromPos > 100.0f && attempts < 100){
                        newEnemyPos = glm::vec3(randomInRange(-300, 300), 0, randomInRange(-300, 300));
                        distanceFromPos = calculateDistance(oldEnemyPos, newEnemyPos);
                        attempts += 1;
                    }
                    enemyGoTo = newEnemyPos;
                    enemyGoTo.y = getHeight(enemyGoTo.x, enemyGoTo.z) + randomInRange(0.51f, 5.0f);
                }


                enemyWaitTime = glfwGetTime();
                timeSinceLastEnemyWait = currentFrame;
            }
            if (enemyOffensiveMode){
                enemyGoTo = glm::vec3(player[3][0], player[3][1], player[3][2]);
            }
        }

        billboardShader.use();
        glBindVertexArray(phongBillboardVAO);


        if (animationModeActivate){
            if (health >= 300.0f)
                playerUV = playerInjuryUV;
        }
        setTextureUV(billboardShader, playerUV, false);
        billboardShader.setMat4("model", enemy);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // ----- OBJECTS ------

        // ### TERRAIN
        for (int i = 0; i < terrainsArraySize; i++){
            phongShader.use();
            glBindVertexArray(phongTerrainVAO);
            setTextureUV(phongShader, oceroAtlasUV, true);

            phongShader.setMat4("model", terrains[i].modelMatrix);
            glDrawElements(GL_TRIANGLES, phongTerrainIndicesVector.size(), GL_UNSIGNED_INT, 0);
        }

        // ### TREES
        phongShader.use();
        phongShader.setBool("isTree", true);
        glBindVertexArray(phongBillboardVAO);
        setTextureUV(phongShader, treeAtlasUV, false);
        for (int i = 0; i < treesArraySize; i++) {
        glm::vec3 treePosition = glm::vec3(trees[i].modelMatrix[3]);

        if (renderDistanceCheck(cameraPos, treePosition)) {
            phongShader.setMat4("model", trees[i].modelMatrix);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            phongShader.setMat4("model", clonedTree[i].modelMatrix);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }
            phongShader.setBool("isTree", false);

        // ### RAIN
        if (IS_RAINING){
            billboardShader.use();
            glBindVertexArray(phongBillboardVAO);
            setTextureUV(billboardShader, rainAtlasUV, false);
            for (int i = 0; i < rainDropsArraySize; i++){
                rainDrops[i].modelMatrix[3][1] -= rainDrops[i].speed * deltaTime;

                if (rainDrops[i].modelMatrix[3][1] < player[3][1] - 5.0f){ // check if rain is below player first before performing other checks
                    setRainLocation(rainDrops[i]);
                }
                else{
                    float distanceFromPlayerZ = std::fabs(rainDrops[i].modelMatrix[3][2] - player[3][2]);
                    float distanceFromPlayerX = std::fabs(rainDrops[i].modelMatrix[3][0] - player[3][0]);

                    if (distanceFromPlayerZ > 15.0f || distanceFromPlayerX > 15.0f){
                        setRainLocation(rainDrops[i]);
                    }
                }



                billboardShader.setMat4("model", rainDrops[i].modelMatrix);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }

        // ----- DRAW TEXT ------
        int fps = calculateAverageFPS(timeSinceLastFPSCalculation, deltaTime, fpsVector, SLOW_MO);
        //float terrainCoordBelow = getHeight(player[3][0], player[3][2]);
        std::string text =      "\\ocero 3d game alpha v3.0.0"
                                //"camera coordinates: [" + std::to_string(cameraPos.x) + ", "+ std::to_string(cameraPos.y) + ", " + std::to_string(cameraPos.z) + "]\\"
                                //"player coordinates: [" + std::to_string(player[3][0]) + ", "+ std::to_string(player[3][1]) + ", " + std::to_string(player[3][2]) + "]\\"
                                //"terrain y coord (below player): " + std::to_string(terrainCoordBelow) +
                                "\\framerate: " + std::to_string(fps) + " fps";
                                //if (IS_RAINING){
                                //    text += "\\" + std::to_string(rainDropsArraySize) + " active rain drops";
                                //}
        float waitingTime = glfwGetTime() - timeSinceLastInput;
        if (allowPlayerTeleportation){
            text += "\\\\\\                              press space to teleport!";
        }
        if (waitingTime < 1.0f){
            if (allowPlayerTeleportation)
                text += "\\\\\\\\\\\\\\";
            else{
                for (int i = 0; i < 10; i++){
                text += "\\";
                }
            }

            text += "                                      ";
            text += std::to_string(waitingTime);
        }

        if(SLOW_MO)
            text += dialogue;
        else
            dialogue = "";

        if (FREECAM_CONTROLS_ENABLED){
            text += "\\\\freecam mode";
            text += "\\camera coordinates: [" + std::to_string(cameraPos.x) + ", "+ std::to_string(cameraPos.y) + ", " + std::to_string(cameraPos.z) + "]";
        }

        renderText(t, text);
        renderText(t, animationText);

        // ----- HEALTH BAR ----- (code is weird because it uses the text renderer to render both text and health bar)

        glDisable(GL_DEPTH_TEST);
        t.use();
        if (health < 0)
            t.setBool("invertColor", true);
        else
            t.setBool("blueColor", true);
        t.setFloat("textXOffset", 1.0f);
        t.setFloat("textYOffset", -1.8f);
        generateVAOandEBO(healthVAO, healthVBO, healthEBO, healthVerticesByteSize, healthIndicesByteSize, healthVertices, healthIndices);
        glBindVertexArray(healthVAO);
        setTextureUV(t, redSquareUV, false);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glEnable(GL_DEPTH_TEST);
        t.setBool("blueColor", false);
        renderText(t, "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\                             *enemy               player*");

        // end of a frame

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}


