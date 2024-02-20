#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_NONE

#include <iostream>
#include <string>
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
#include "opengl/shader_functions.h"
#include "opengl/textures.h"
#include "opengl/text_render.h"

int main(){

    GLFWwindow* window = createWindow();
    glEnable(GL_DEPTH_TEST);
    Shader mainShader("shaders/basic_shader.vs", "shaders/basic_shader.fs");
    Shader phongShader("shaders/phong_lighting.vs", "shaders/phong_lighting.fs");
    Shader textShader("shaders/text_shader.vs", "shaders/text_shader.fs");

    phongShader.use();
    phongShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    phongShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    phongShader.setVec3("lightPos", glm::vec3(100.0f, 100.0f, 100.0f));


    // initialize sphere vertices
    std::vector<float> sphereShapeVertices;
    generateSphere(3.0f, POLY_RESOLUTION, sphereShapeVertices);
    float sphereVertices[sphereShapeVertices.size()];
    std::copy(sphereShapeVertices.begin(), sphereShapeVertices.end(), sphereVertices);
    unsigned int sphereVerticesByteSize = sizeof(sphereVertices);
    unsigned int sphereVerticesArraySize = sizeof(sphereVertices) / sizeof(sphereVertices[0]);

    // initialize phong sphere vertices
    std::vector<float> phongSphereShapeVertices;
    generatePhongSphere(3.0f, POLY_RESOLUTION, phongSphereShapeVertices);
    float phongSphereVertices[phongSphereShapeVertices.size()];
    std::copy(phongSphereShapeVertices.begin(), phongSphereShapeVertices.end(), phongSphereVertices);
    unsigned int phongSphereVerticesByteSize = sizeof(phongSphereVertices);
    unsigned int phongSphereVerticesArraySize = sizeof(phongSphereVertices) / sizeof(phongSphereVertices[0]);

    // initialize cone vertices
    std::vector<float> coneShapeVertices;
    generateCone(0.5f, 1.0f, POLY_RESOLUTION, coneShapeVertices);
    float coneVertices[coneShapeVertices.size()];
    std::copy(coneShapeVertices.begin(), coneShapeVertices.end(), coneVertices);
    unsigned int coneVerticesByteSize = sizeof(coneVertices);
    unsigned int coneVerticesArraySize = sizeof(coneVertices) / sizeof(coneVertices[0]);

    // initialize phong cone vertices
    std::vector<float> phongConeShapeVertices;
    generatePhongCone(0.5f, 1.0f, POLY_RESOLUTION, phongConeShapeVertices);
    float phongConeVertices[phongConeShapeVertices.size()];
    std::copy(phongConeShapeVertices.begin(), phongConeShapeVertices.end(), phongConeVertices);
    unsigned int phongConeVerticesByteSize = sizeof(phongConeVertices);
    unsigned int phongConeVerticesArraySize = sizeof(phongConeVertices) / sizeof(phongConeVertices[0]);

    // initialize tube vertices
    std::vector<float> tubeShapeVertices;
    generateCylinderVertices(0.5f, 1.0f, POLY_RESOLUTION, tubeShapeVertices);
    float tubeVertices[tubeShapeVertices.size()];
    std::copy(tubeShapeVertices.begin(), tubeShapeVertices.end(), tubeVertices);
    unsigned int tubeVerticesByteSize = sizeof(tubeVertices);
    unsigned int tubeVerticesArraySize = sizeof(tubeVertices) / sizeof(tubeVertices[0]);

    // initialize phong tube vertices
    std::vector<float> phongCylinderShapeVertices;
    generatePhongCylinderVertices(0.5f, 1.0f, POLY_RESOLUTION, phongCylinderShapeVertices);
    float phongCylinderVertices[phongCylinderShapeVertices.size()];
    std::copy(phongCylinderShapeVertices.begin(), phongCylinderShapeVertices.end(), phongCylinderVertices);
    unsigned int phongCylinderVerticesByteSize = sizeof(phongCylinderVertices);
    unsigned int phongCylinderVerticesArraySize = sizeof(phongCylinderVertices) / sizeof(phongCylinderVertices[0]);


    // ----- OBJECTS VERTICES BUFFERS ------

    unsigned int textVAO, textVBO, textEBO;
    generateVAOandEBO(textVAO, textVBO, textEBO, textVerticesByteSize, textIndicesByteSize, textVertices, textIndices);

    unsigned int boxVAO, boxVBO;
    generateVAO(boxVAO, boxVBO, boxVerticesByteSize, boxVertices);

    unsigned int pyramidVAO, pyramidVBO;
    generateVAO(pyramidVAO, pyramidVBO, pyramidVerticesByteSize, pyramidVertices);

    unsigned int sphereVAO, sphereVBO;
    generateVAO(sphereVAO, sphereVBO, sphereVerticesByteSize, sphereVertices);

    unsigned int coneVAO, coneVBO;
    generateVAO(coneVAO, coneVBO, coneVerticesByteSize, coneVertices);

    unsigned int tubeVAO, tubeVBO;
    generateVAO(tubeVAO, tubeVBO, tubeVerticesByteSize, tubeVertices);

    // VAO with phong shader

    unsigned int phongBoxVAO, phongBoxVBO;
    generatePhongVAO(phongBoxVAO, phongBoxVBO, phongBoxVerticesByteSize, phongBoxVertices);

    unsigned int phongFloorVAO, phongFloorVBO;
    generatePhongVAO(phongFloorVAO, phongFloorVBO, phongFloorVerticesByteSize, phongFloorVertices);

    unsigned int phongPyramidVAO, phongPyramidVBO;
    generatePhongVAO(phongPyramidVAO, phongPyramidVBO, phongPyramidVerticesByteSize, phongPyramidVertices);

    unsigned int phongConeVAO, phongConeVBO;
    generatePhongVAO(phongConeVAO, phongConeVBO, phongConeVerticesByteSize, phongConeVertices);

    unsigned int phongSphereVAO, phongSphereVBO;
    generatePhongVAO(phongSphereVAO, phongSphereVBO, phongSphereVerticesByteSize, phongSphereVertices);

    unsigned int phongCylinderVAO, phongCylinderVBO;
    generatePhongVAO(phongCylinderVAO, phongCylinderVBO, phongCylinderVerticesByteSize, phongCylinderVertices);



    // ----- TEXTURES -----
    unsigned int texture1, texture2;
    loadTexture(texture1, "resources/textures/blockTextureAtlas.png");
    loadTexture(texture2, "resources/textures/textAtlas.png");
    mainShader.use();
    mainShader.setInt("texture1", 0);
    mainShader.setInt("texture2", 1);

    phongShader.use();
    phongShader.setInt("texture1", 0);
    phongShader.setInt("texture2", 1);

    textShader.use();
    textShader.setInt("texture1", 0);
    textShader.setInt("texture2", 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);




    // first atlas values
    std::vector<float> boxAtlasUV = returnTextureUV(0, 0);
    std::vector<float> cobbleAtlasUV = returnTextureUV(1, 0);
    std::vector<float> oceroAtlasUV = returnTextureUV(2, 0);


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
    boxes[0].modelMatrix = glm::translate(boxes[0].modelMatrix, glm::vec3(1.0f, -0.5f, -3.0f));
    boxes[1].modelMatrix = glm::translate(boxes[1].modelMatrix, glm::vec3(1.0f, 0.5f, -3.0f));

    // 1 floor
    shape floors[1];
    floors[0].type = 2;
    int floorsArraySize = sizeof(floors) / sizeof(floors[0]);
    floors[0].modelMatrix = glm::translate(floors[0].modelMatrix, glm::vec3(0.0f, -2.0f, 0.0f));
    floors[0].modelMatrix = glm::scale(floors[0].modelMatrix, glm::vec3(15.0f));

    // 1 pyramid
    shape pyramids[1];
    pyramids[0].type = 3;
    int pyramidsArraySize = sizeof(pyramids) / sizeof(pyramids[0]);
    pyramids[0].modelMatrix = glm::translate(pyramids[0].modelMatrix, glm::vec3(0.0f, -1.0f, -3.0f));

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
    cones[0].modelMatrix = glm::translate(cones[0].modelMatrix, glm::vec3(-1.0f, -1.0f, -3.0f));

    // 1 tube
    shape tubes[1];
    int tubesArraySize = sizeof(tubes) / sizeof(tubes[0]);
    tubes[0].type = 6;
    tubes[0].modelMatrix = glm::translate(tubes[0].modelMatrix, glm::vec3(-2.0f, -1.0f, -3.0f));

    // ----- MAIN PROGRAM -----

    while (!glfwWindowShouldClose(window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.16f, 0.80f, 1.00f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        mainShader.use();
        mainShader.setMat4("view", view);
        mainShader.setMat4("projection", projection);

        phongShader.use();
        phongShader.setMat4("projection", projection);
        phongShader.setMat4("view", view);
        phongShader.setVec3("viewPos", cameraPos);



        // ----- DRAW OBJECTS ------

        for (int i = 0; i < boxesArraySize; i++){
            phongShader.use();
            glBindVertexArray(phongBoxVAO);

            setTextureUV(phongShader, boxAtlasUV, true);
            if (i == 1){
                setTextureUV(phongShader, oceroAtlasUV, true);
            }

            phongShader.setMat4("model", boxes[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        for (int i = 0; i < floorsArraySize; i++){
            phongShader.use();
            glBindVertexArray(phongFloorVAO);

            setTextureUV(phongShader, cobbleAtlasUV, true);

            phongShader.setMat4("model", floors[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        for (int i = 0; i < pyramidsArraySize; i++){
            phongShader.use();
            glBindVertexArray(phongPyramidVAO);

            setTextureUV(phongShader, boxAtlasUV, true);

            phongShader.setMat4("model", pyramids[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 18);
        }

        for (int i = 0; i < spheresArraySize; i++){
            phongShader.use();
            glBindVertexArray(phongSphereVAO);

            setTextureUV(phongShader, boxAtlasUV, true);

            phongShader.setMat4("model", spheres[i].modelMatrix);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, phongSphereVerticesArraySize);
        }

        for (int i = 0; i < conesArraySize; i++){
            phongShader.use();
            glBindVertexArray(phongConeVAO);

            setTextureUV(phongShader, boxAtlasUV, true);

            phongShader.setMat4("model", cones[i].modelMatrix);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, phongConeVerticesArraySize);
        }

        for (int i = 0; i < tubesArraySize; i++){
            phongShader.use();
            glBindVertexArray(phongCylinderVAO);

            setTextureUV(phongShader, boxAtlasUV, true);

            phongShader.setMat4("model", tubes[i].modelMatrix);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, phongCylinderVerticesArraySize);
        }

        // ----- DRAW TEXT ------

        std::string text =      "hello world! do you like my text renderer? no more need for a terminal!\\"
                                "this took me 3 & 1/2 hours of work! :-)\\\\"
                                "abcdefghijklmnopqrstuvwxyz.,?!:;()/\"-_=1234567890+*<>[]\'&\\\\"
                                "camera coordinates: [" + std::to_string(cameraPos.x) + ", "+ std::to_string(cameraPos.y) + ", " + std::to_string(cameraPos.z) + "]";

        renderText(textShader, textVAO, text);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}
