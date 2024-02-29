#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <iostream>
#include <string>
#include <vector>
#include <random>
std::random_device rd;
std::mt19937 gen(rd());

// opengl libraries
#include <glad/glad.h> // loads OpenGL pointers
#include <GLFW/glfw3.h> // window manager

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

float randomInRange(float min, float max);

int main(){

    GLFWwindow* window = createWindow();
    glEnable(GL_DEPTH_TEST);
    Shader billboardShader("shaders/billboard_shader.vs", "shaders/billboard_shader.fs");
    Shader phongShader("shaders/phong_lighting.vs", "shaders/phong_lighting.fs");
    Shader t("shaders/text_shader.vs", "shaders/text_shader.fs"); // shortened so I can call it faster with renderText()

    billboardShader.use();
    billboardShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    billboardShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    billboardShader.setVec3("lightPos", glm::vec3(100.0f, 100.0f, 100.0f));

    phongShader.use();
    phongShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    phongShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    phongShader.setVec3("lightPos", glm::vec3(100.0f, 100.0f, 100.0f));

    initializeAllShapes();

    // ----- TEXTURES -----
    unsigned int texture1, texture2;
    loadTexture(texture1, "resources/textures/TextureAtlas.png");
    loadTexture(texture2, "resources/textures/TextAtlas.png");
    billboardShader.use();
    billboardShader.setInt("texture1", 0);
    billboardShader.setInt("texture2", 1);

    phongShader.use();
    phongShader.setInt("texture1", 0);
    phongShader.setInt("texture2", 1);

    t.use();
    t.setInt("texture1", 0);
    t.setInt("texture2", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // first atlas values
    std::vector<float> boxAtlasUV = returnTextureUV(0, 0);
    std::vector<float> cobbleAtlasUV = returnTextureUV(1, 0);
    std::vector<float> oceroAtlasUV = returnTextureUV(2, 0);
    std::vector<float> shadowAtlasUV = returnTextureUV(0, 2);
    std::vector<float> rainAtlasUV = returnTextureUV(2, 2);

    // ----- INITIALIZE OBJECTS -----

    // initialize various sphere locations
    generateSurroundingPositions(initialSpherePositions, 25);
    for (int i = 0; i < initialSpherePositions.size(); i++){
        initialSpherePositions[i] = initialSpherePositions[i] * glm::vec3(30.0f, 30.0f, 30.0f);
    }

    // 2 boxes
    shape boxes[2];
    boxes[0].type = 1;
    int boxesArraySize = sizeof(boxes) / sizeof(boxes[0]);
    boxes[0].modelMatrix = glm::translate(boxes[0].modelMatrix, glm::vec3(1.0f, 1.5f, -3.0f));
    boxes[1].modelMatrix = glm::translate(boxes[1].modelMatrix, glm::vec3(1.0f, 0.5f, -3.0f));

    // 1 floor
    shape floors[1];
    floors[0].type = 2;
    int floorsArraySize = sizeof(floors) / sizeof(floors[0]);
    floors[0].modelMatrix = glm::translate(floors[0].modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    floors[0].modelMatrix = glm::scale(floors[0].modelMatrix, glm::vec3(15.0f));

    // 1 pyramid
    shape pyramids[1];
    pyramids[0].type = 3;
    int pyramidsArraySize = sizeof(pyramids) / sizeof(pyramids[0]);
    pyramids[0].modelMatrix = glm::translate(pyramids[0].modelMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

    // 25 spheres
    shape spheres[25];
    int spheresArraySize = sizeof(spheres) / sizeof(spheres[0]);
    for (int i = 0; i < spheresArraySize; i++){
        spheres[i].type = 4;
        spheres[i].modelMatrix = glm::translate(spheres[i].modelMatrix, initialSpherePositions[i]);
    }

    // 1 cone
    shape cones[1];
    int conesArraySize = sizeof(cones) / sizeof(cones[0]);
    cones[0].type = 5;
    cones[0].modelMatrix = glm::translate(cones[0].modelMatrix, glm::vec3(-1.0f, 0.0f, -3.0f));

    // 1 tube
    shape tubes[1];
    int tubesArraySize = sizeof(tubes) / sizeof(tubes[0]);
    tubes[0].type = 6;
    tubes[0].modelMatrix = glm::translate(tubes[0].modelMatrix, glm::vec3(-2.0f, 0.0f, -3.0f));

    // 1 billboard
    shape billboards[3];
    int billboardsArraySize = sizeof(billboards) / sizeof(billboards[0]);
    for (int i = 0; i < billboardsArraySize; i++){
        billboards[i].type = 7;
        billboards[i].modelMatrix = glm::translate(billboards[i].modelMatrix, glm::vec3(1 - (i * 1.1), 1.0f, -5.0f));
    }

    // 1 shadow
    shape shadows[1 + billboardsArraySize];
    int shadowsArraySize = sizeof(shadows) / sizeof(shadows[0]);
    shadows[0].type = 8;

    // rain drops
    rainEntity rainDrops[1000];
    int rainDropsArraySize = sizeof(rainDrops) / sizeof(rainDrops[0]);
    for (int i = 0; i < rainDropsArraySize; i++){
        rainDrops[i].modelMatrix[3][0] = cameraPos.x + randomInRange(-10.0f, 10.0f);
        rainDrops[i].modelMatrix[3][1] = cameraPos.y + randomInRange(1.0f, 10.0f);
        rainDrops[i].initialY = rainDrops[i].modelMatrix[3][1];
        rainDrops[i].modelMatrix[3][2] = cameraPos.z + randomInRange(-10.0f, 10.0f);
    }


    // ----- MAIN PROGRAM -----
isRaining = true;
    while (!glfwWindowShouldClose(window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        if (isRaining){
            glClearColor(0.792f, 0.957f, 1.00f, 1.0f);
        }
        else{
            glClearColor(0.16f, 0.80f, 1.00f, 1.0f);
        }



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


        // ----- DRAW OBJECTS ------

        // ### BOXES
        for (int i = 0; i < boxesArraySize; i++){
            phongShader.use();
            glBindVertexArray(phongBoxVAO);
            setTextureUV(phongShader, boxAtlasUV, false);
            if (i == 1){
                setTextureUV(phongShader, oceroAtlasUV, false);
            }
            phongShader.setMat4("model", boxes[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // ### FLOORS
        phongShader.use();
        glBindVertexArray(phongFloorVAO);
        setTextureUV(phongShader, cobbleAtlasUV, false);
        for (int i = 0; i < floorsArraySize; i++){

            phongShader.setMat4("model", floors[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // ### PYRAMIDS
        phongShader.use();
        glBindVertexArray(phongPyramidVAO);
        setTextureUV(phongShader, boxAtlasUV, false);
        for (int i = 0; i < pyramidsArraySize; i++){

            phongShader.setMat4("model", pyramids[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 18);
        }

        // ### SPHERES
        phongShader.use();
        glBindVertexArray(phongSphereVAO);
        setTextureUV(phongShader, boxAtlasUV, false);
        for (int i = 0; i < spheresArraySize; i++){

            phongShader.setMat4("model", spheres[i].modelMatrix);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, phongSphereVerticesArraySize);
        }

        // ### CONES
        phongShader.use();
        glBindVertexArray(phongConeVAO);
        setTextureUV(phongShader, boxAtlasUV, false);
        for (int i = 0; i < conesArraySize; i++){

            phongShader.setMat4("model", cones[i].modelMatrix);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, phongConeVerticesArraySize);
        }

        // ### TUBES
        phongShader.use();
        glBindVertexArray(phongCylinderVAO);
        setTextureUV(phongShader, boxAtlasUV, false);
        for (int i = 0; i < tubesArraySize; i++){

            phongShader.setMat4("model", tubes[i].modelMatrix);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, phongCylinderVerticesArraySize);
        }

        // ### BILLBOARDS
        billboardShader.use();
        glBindVertexArray(phongBillboardVAO);
        setTextureUV(billboardShader, oceroAtlasUV, false);
        for (int i = 0; i < billboardsArraySize; i++){
            billboards[i].modelMatrix[3][1] += 1 * deltaTime;
            billboards[i].modelMatrix[3][2] += -1 * deltaTime;

            billboardShader.setMat4("model", billboards[i].modelMatrix);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }


        // ### RAIN
        if (isRaining){
            billboardShader.use();
            glBindVertexArray(phongBillboardVAO);
            setTextureUV(billboardShader, rainAtlasUV, false);
            for (int i = 0; i < rainDropsArraySize; i++){
                rainDrops[i].modelMatrix[3][1] -= rainDrops[i].speed * deltaTime;

                if (rainDrops[i].modelMatrix[3][1] < cameraPos.y - 5){
                    std::mt19937 generator(i);
                    rainDrops[i].modelMatrix[3][0] = cameraPos.x + randomInRange(-8.0f, 8.0f);
                    rainDrops[i].modelMatrix[3][1] = cameraPos.y + 5;
                    rainDrops[i].initialY = rainDrops[i].modelMatrix[3][1] + randomInRange(-1.0f, 1.0f);
                    rainDrops[i].speed = randomInRange(5.0f, 8.0f);
                    rainDrops[i].modelMatrix[3][2] = cameraPos.z + randomInRange(-8.0f, 8.0f);
                }

                billboardShader.setMat4("model", rainDrops[i].modelMatrix);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }

        // ### SHADOWS
        for (int i = 0; i < shadowsArraySize; i++){
            float groundY = 0.01f;

            if (i > 0){ // after rendering player shadow, render billboard shadows
                shadows[i].modelMatrix[3][0] = billboards[i - 1].modelMatrix[3][0]; // x
                shadows[i].modelMatrix[3][2] = billboards[i - 1].modelMatrix[3][2]; // z
                setShadowLocation(shadows[i], glm::vec3(billboards[i - 1].modelMatrix[3][0], billboards[i - 1].modelMatrix[3][1], billboards[i - 1].modelMatrix[3][2]), groundY);
            }
            else{
                setShadowLocation(shadows[0], glm::vec3(cameraPos.x, cameraPos.y, cameraPos.z), groundY);
            }

            phongShader.use();
            glBindVertexArray(phongFloorVAO);
            setTextureUV(phongShader, shadowAtlasUV, false);
            phongShader.setMat4("model", shadows[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // ----- DRAW TEXT ------
        int fps = 1.0f / deltaTime;
        std::string text =      "\\ocero 3d game beta v1.0.2\\"
                                "camera coordinates: [" + std::to_string(cameraPos.x) + ", "+ std::to_string(cameraPos.y) + ", " + std::to_string(cameraPos.z) + "]\\"
                                "framerate: " + std::to_string(fps) + " fps";
                                if (isRaining){
                                    text += "\\" + std::to_string(rainDropsArraySize) + " active rain drops";
                                }

        renderText(t, text);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}

float randomInRange(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}
