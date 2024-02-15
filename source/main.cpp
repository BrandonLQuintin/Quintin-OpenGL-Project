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

    // initialize sphere vertices
    std::vector<float> sphereShapeVertices;
    generateSphere(3.0f, POLY_RESOLUTION, sphereShapeVertices);
    float sphereVertices[sphereShapeVertices.size()];
    std::copy(sphereShapeVertices.begin(), sphereShapeVertices.end(), sphereVertices);
    unsigned int sphereVerticesByteSize = sizeof(sphereVertices);
    unsigned int sphereVerticesArraySize = sizeof(sphereVertices) / sizeof(sphereVertices[0]);

    // initialize cone vertices
    std::vector<float> coneShapeVertices;
    generateCone(0.5f, 1.0f, POLY_RESOLUTION, coneShapeVertices);
    float coneVertices[coneShapeVertices.size()];
    std::copy(coneShapeVertices.begin(), coneShapeVertices.end(), coneVertices);
    unsigned int coneVerticesByteSize = sizeof(coneVertices);
    unsigned int coneVerticesArraySize = sizeof(coneVertices) / sizeof(coneVertices[0]);

    // initialize tube vertices
    std::vector<float> tubeShapeVertices;
    generateTubeVertices(0.5f, 1.0f, POLY_RESOLUTION, tubeShapeVertices);
    float tubeVertices[tubeShapeVertices.size()];
    std::copy(tubeShapeVertices.begin(), tubeShapeVertices.end(), tubeVertices);
    unsigned int tubeVerticesByteSize = sizeof(tubeVertices);
    unsigned int tubeVerticesArraySize = sizeof(tubeVertices) / sizeof(tubeVertices[0]);


    // ----- OBJECTS VERTICES BUFFERS ------

    unsigned int boxVAO, boxVBO;
    generateVAO(boxVAO, boxVBO, boxVerticesByteSize, boxVertices);

    unsigned int floorVAO, floorVBO, floorEBO;
    generateFloorVAO(floorVAO, floorVBO, floorEBO, floorVerticesByteSize, floorVertices);

    unsigned int pyramidVAO, pyramidVBO;
    generateVAO(pyramidVAO, pyramidVBO, pyramidVerticesByteSize, pyramidVertices);

    unsigned int sphereVAO, sphereVBO;
    generateVAO(sphereVAO, sphereVBO, sphereVerticesByteSize, sphereVertices);

    unsigned int coneVAO, coneVBO;
    generateVAO(coneVAO, coneVBO, coneVerticesByteSize, coneVertices);

    unsigned int tubeVAO, tubeVBO;
    generateVAO(tubeVAO, tubeVBO, tubeVerticesByteSize, tubeVertices);



    // ----- TEXTURES -----
    unsigned int texture1, texture2;
    loadTexture(texture1, "../resources/textures/blockTextureAtlas.png");
    loadTexture(texture2, "../resources/textures/textureAtlas.png");
    mainShader.use();
    mainShader.setInt("texture1", 0);
    mainShader.setInt("texture2", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    mainShader.setMat4("view", view);

    // first atlas values
    std::vector<float> boxAtlasUV(4);
    assignTextureUV(boxAtlasUV, 0, 0);

    std::vector<float> cobbleAtlasUV(4);
    assignTextureUV(cobbleAtlasUV, 1, 0);

    // second atlas values
    std::vector<float> oceroAtlasUV(4);
    assignTextureUV(oceroAtlasUV, 0, 0);


    // ----- INITIALIZE OBJECTS -----

    // initialize various sphere locations
    generateSurroundingPositions(initialSpherePositions, 25);
    for (int i = 0; i < initialSpherePositions.size(); i++){
        initialSpherePositions[i] = initialSpherePositions[i] * glm::vec3(30.0f, 30.0f, 30.0f);
    }

    // initialize 2 boxes
    shape boxes[2];
    boxes[0].type = 1;
    int boxesArraySize = sizeof(boxes) / sizeof(boxes[0]);
    boxes[0].modelMatrix = glm::translate(boxes[0].modelMatrix, glm::vec3(1.0f, -0.5f, -3.0f));
    boxes[1].modelMatrix = glm::translate(boxes[1].modelMatrix, glm::vec3(1.0f, 0.5f, -3.0f));

    // initialize 1 floor
    shape floors[1];
    floors[0].type = 2;
    int floorsArraySize = sizeof(floors) / sizeof(floors[0]);
    floors[0].modelMatrix = glm::translate(floors[0].modelMatrix, glm::vec3(0.0f, -3.0f, 0.0f));
    floors[0].modelMatrix = glm::scale(floors[0].modelMatrix, glm::vec3(15.0f, 0.0f, -15.0f));

    // initialize 1 pyramid
    shape pyramids[1];
    pyramids[0].type = 3;
    int pyramidsArraySize = sizeof(pyramids) / sizeof(pyramids[0]);
    pyramids[0].modelMatrix = glm::translate(pyramids[0].modelMatrix, glm::vec3(0.0f, -1.0f, -3.0f));

    // initialize 25 spheres
    shape spheres[25];
    int spheresArraySize = sizeof(spheres) / sizeof(spheres[0]);
    for (int i = 0; i < spheresArraySize; i++){
        spheres[i].type = 4;
        spheres[i].modelMatrix = glm::translate(spheres[i].modelMatrix, initialSpherePositions[i]);
    }

    // initialize 1 cone
    shape cones[1];
    int conesArraySize = sizeof(cones) / sizeof(cones[0]);
    cones[0].type = 5;
    cones[0].modelMatrix = glm::translate(cones[0].modelMatrix, glm::vec3(-1.0f, -1.0f, -3.0f));

    // initialize 1 tube
    shape tubes[1];
    int tubesArraySize = sizeof(tubes) / sizeof(tubes[0]);
    tubes[0].type = 6;
    tubes[0].modelMatrix = glm::translate(tubes[0].modelMatrix, glm::vec3(-2.0f, -1.0f, -3.0f));

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

        for (int i = 0; i < boxesArraySize; i++){
            setTextureUV(mainShader, boxAtlasUV, true);

            if (i == 1){
                setTextureUV(mainShader, oceroAtlasUV, false);
            }


            glBindVertexArray(boxVAO);
            mainShader.setMat4("model", boxes[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        for (int i = 0; i < floorsArraySize; i++){
            setTextureUV(mainShader, cobbleAtlasUV, true);


            glBindVertexArray(floorVAO);
            mainShader.setMat4("model", floors[i].modelMatrix);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }

        for (int i = 0; i < pyramidsArraySize; i++){
            setTextureUV(mainShader, boxAtlasUV, true);

            glBindVertexArray(pyramidVAO);
            mainShader.setMat4("model", pyramids[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 18);
        }

        for (int i = 0; i < spheresArraySize; i++){
            setTextureUV(mainShader, boxAtlasUV, true);

            glBindVertexArray(sphereVAO);
            mainShader.setMat4("model", spheres[i].modelMatrix);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, sphereVerticesArraySize);
        }

        for (int i = 0; i < conesArraySize; i++){
            setTextureUV(mainShader, boxAtlasUV, true);

            glBindVertexArray(coneVAO);
            mainShader.setMat4("model", cones[i].modelMatrix);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, coneVerticesArraySize);
        }

        for (int i = 0; i < tubesArraySize; i++){
            setTextureUV(mainShader, boxAtlasUV, true);

            glBindVertexArray(tubeVAO);
            mainShader.setMat4("model", tubes[i].modelMatrix);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, tubeVerticesArraySize);
        }



        // ----- END OF PROGRAM -----

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;

}


