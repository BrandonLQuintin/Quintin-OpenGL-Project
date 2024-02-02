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

// variables
#include "globals.h"
#include "opengl/camera_variables.h"
#include "shapes/shapes.h" // stores both shape vertices AND object coordinates

// functions
#include "opengl/window_functions.h"
#include "opengl/textures.h"

int main(){

    GLFWwindow* window = createWindow();
    glEnable(GL_DEPTH_TEST);
    Shader mainShader("shaders/shader.vs", "shaders/shader.fs");

    // scale box vertices position
    generateBoxPositions(boxPositions, 25);


    float s = 10.0f;
    glm::vec3 scaleFactor(s, s, s);
    for (int i = 0; i < boxPositions.size(); i++){
        boxPositions[i] = boxPositions[i] * scaleFactor;
    }

    // ----- BOX VERTICES BUFFERS ------

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, boxVerticesByteSize, boxVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


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


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));


        glClearColor(0.16f, 0.80f, 1.00f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        mainShader.setMat4("view", view);
        mainShader.setMat4("projection", projection);

        for (unsigned int i = 0; i < boxPositions.size(); i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, boxPositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            mainShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;

}


