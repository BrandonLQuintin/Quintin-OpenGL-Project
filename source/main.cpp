#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <iostream>
#include <vector>

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
#include "shapes/shapes.h" // stores both shape vertices AND initial object coordinates

// functions
#include "opengl/window_functions.h"
#include "opengl/textures.h"

int main(){

    GLFWwindow* window = createWindow();
    glEnable(GL_DEPTH_TEST);
    Shader mainShader("shaders/shader.vs", "shaders/shader.fs");

    // ----- OBJECTS VERTICES BUFFERS ------
    unsigned int boxVAO, boxVBO;
    generateVAO(boxVAO, boxVBO, boxVerticesByteSize, boxVertices);

    unsigned int floorVAO, floorVBO, floorEBO;
    generateFloorVAO(floorVAO, floorVBO, floorEBO, floorVerticesByteSize, floorVertices);

    unsigned int pyramidVAO, pyramidVBO;
    generateVAO(pyramidVAO, pyramidVBO, pyramidVerticesByteSize, pyramidVertices);

    // ----- TEXTURES -----
    unsigned int texture1, texture2;
    loadTexture(texture1, "../resources/textures/crate.png");
    loadTexture(texture2, "../resources/textures/crate.png");
    mainShader.use();
    mainShader.setInt("texture1", 0);
    mainShader.setInt("texture2", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    mainShader.setMat4("view", view);

    // ----- INITIALIZE OBJECTS -----

    // initialize various box positions
    generateSurroundingPositions(initialBoxPositions, 25);
    float s = 10.0f;
    glm::vec3 scaleFactor(s, s, s);
    for (int i = 0; i < initialBoxPositions.size(); i++){
        initialBoxPositions[i] = initialBoxPositions[i] * scaleFactor;
    }

    // initialize 25 boxes
    shape boxes[25];
    int boxesArrSize = sizeof(boxes) / sizeof(boxes[0]);
    for (int i = 0; i < boxesArrSize; i++){
        boxes[i].modelMatrix = glm::translate(boxes[i].modelMatrix, initialBoxPositions[i]);
    }

    // initialize 1 floor
    shape floors[1];
    floors[0].type = 2;
    int floorsArrSize = sizeof(floors) / sizeof(floors[0]);
    floors[0].modelMatrix = glm::translate(floors[0].modelMatrix, glm::vec3(0.0f, -1.0f, 0.0f));
    floors[0].modelMatrix = glm::scale(floors[0].modelMatrix, glm::vec3(15.0f, 0.0f, 15.0f));

    // initialize 1 pyramid

    shape pyramids[1];
    int pyramidsArrSize = sizeof(pyramids) / sizeof(pyramids[0]);
    pyramids[0].modelMatrix = glm::translate(pyramids[0].modelMatrix, glm::vec3(0.0f, 0.0f, -3.0f));


    // ----- MAIN PROGRAM -----

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.16f, 0.80f, 1.00f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        mainShader.setMat4("view", view);
        mainShader.setMat4("projection", projection);


        // ----- DRAW OBJECTS ------

        for (int i = 0; i < boxesArrSize; i++){
            glBindVertexArray(boxVAO);
            mainShader.setMat4("model", boxes[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        for (int i = 0; i < floorsArrSize; i++){
            glBindVertexArray(floorVAO);
            mainShader.setMat4("model", floors[i].modelMatrix);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, floorEBO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        for (int i = 0; i < pyramidsArrSize; i++){
            glBindVertexArray(pyramidVAO);
            mainShader.setMat4("model", pyramids[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 100);
        }


        // ----- END OF PROGRAM -----

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;

}


