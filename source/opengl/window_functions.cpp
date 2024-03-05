#include "window_functions.h"
#include <iostream>


bool firstMouse = true;

GLFWwindow* createWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ocero 3D Game", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    if (CONTROLS_ENABLED){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouseCallback);
    }

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    return window;

}

void processInput(GLFWwindow* window){
    const float cameraSpeed = CAMERA_SPEED * deltaTime;
    const float collisionLimit = terrainCoordBelowCamera + 1.0f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (CONTROLS_ENABLED){
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            cameraPos += cameraSpeed * cameraFront;
            if (cameraPos.y <= collisionLimit){
                cameraPos.y = collisionLimit;
            }

        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            cameraPos -= cameraSpeed * cameraFront;
            if (cameraPos.y <= collisionLimit){
                cameraPos.y = collisionLimit;
            }

        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            if (cameraPos.y <= collisionLimit){
                cameraPos.y = (collisionLimit);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){

            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            if (cameraPos.y <= collisionLimit){
                cameraPos.y = (collisionLimit);
            }
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            cameraPos.y += (cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
            if (cameraPos.y >= collisionLimit){
                cameraPos.y -= (cameraSpeed);
                if (cameraPos.y <= collisionLimit){
                    cameraPos.y = collisionLimit;
                }
            }
        }

        if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) { // help from chatgpt
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            if (glfwGetWindowMonitor(window) == nullptr){
                glfwSetWindowMonitor(window, monitor, 0, 0, (*mode).width, (*mode).height, (*mode).refreshRate);
                projection = glm::perspective(glm::radians(fov), (float)(*mode).width / (float)(*mode).height, 0.1f, VIEW_DISTANCE);
                glViewport(0, 0, (*mode).width, (*mode).height);
            }
            else{
                glfwSetWindowMonitor(window, nullptr, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, GLFW_DONT_CARE);
                projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, VIEW_DISTANCE);
                glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            while (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS){
                glfwPollEvents();
            }
        }
    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS && !enterKeyPressed) {
        enterKeyPressed = true;
    }

    if (key == GLFW_KEY_UP && action == GLFW_PRESS && !enterKeyPressed) {
        if(menuChoice > 0){
            menuChoice -= 1;
        }
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && !enterKeyPressed) {
        if(menuChoice < 5){
            menuChoice += 1;
        }
    }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (CONTROLS_ENABLED){

        if (firstMouse){
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
        }

}

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    if (height == 0 || width == 0) {
        height = 1;
        width = 1;
    }
    projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, VIEW_DISTANCE);
    glViewport(0, 0, width, height);
}
