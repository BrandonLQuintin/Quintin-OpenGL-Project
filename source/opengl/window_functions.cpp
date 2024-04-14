#include "window_functions.h"
#include <iostream>


bool firstMouse = true;
bool dPadUp = false;
bool prevButtonUp = false;
bool dPadDown = false;
bool prevButtonDown = false;
bool dPadRight = false;
bool dPadLeft = false;

bool buttonX = false;
bool prevButtonX = false;
bool buttonA = false;
bool prevButtonA = false;
bool prevButtonB = false;
bool prevButtonY = false;
bool prevButtonStart = false;
bool prevButtonSelect = false;

bool leftTriggerHeld = false;
bool prevleftTrigger = false;



GLFWwindow* createWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Ocero 3D Game", monitor, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    GLFWimage images[1];
    images[0].pixels = stbi_load("./game/icon.png", &images[0].width, &images[0].height, 0, 4); //rgba channels
    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(images[0].pixels);


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

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

    fullscreen(window);

    return window;

}

void processInput(GLFWwindow* window){
    float currentFrame = glfwGetTime();
    float timeElapsed = currentFrame - timeSinceLastInput;

    bool playerCurrentlyChargingUp = false;



    if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GLFW_TRUE){
        GLFWgamepadstate state;
        if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)){

            if (state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER])
                leftTriggerHeld = true;
            else
                leftTriggerHeld = false;

            if (prevleftTrigger && state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER] == GLFW_RELEASE && !enemyFightingToggle && timeElapsed > 1.0 && !animationModeActivate){ // on left trigger being released, execute this
                timeSinceLastInput = glfwGetTime();
            }
            prevleftTrigger = state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER] == GLFW_PRESS;

            if (state.buttons[GLFW_GAMEPAD_BUTTON_X])
                buttonX = true;
            else
                buttonX = false;



            if (!prevButtonX && state.buttons[GLFW_GAMEPAD_BUTTON_X] == GLFW_PRESS){ // initialize fighting
                if (!enemyFightingToggle && timeElapsed > 1.0f && CONTROLS_ENABLED) {
                    float playerToEnemyDistance = calculateDistance(glm::vec3(player[3][0], player[3][1], player[3][2]), glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]));
                    if (playerToEnemyDistance < 2.5f)
                        playerFightRangeInitializeCheck = true;
                    else
                        playerFightRangeInitializeCheck = false;
                    initializeFightAnimation = true;
                    timeSinceInitializePlayerFightAnimation = glfwGetTime();
                }
            }
            if (prevButtonX && state.buttons[GLFW_GAMEPAD_BUTTON_X] == GLFW_RELEASE){ // finalize fighting & start timer
                if (!enemyFightingToggle && CONTROLS_ENABLED) {
                    timeSinceLastInput = glfwGetTime();
                }
            }
            prevButtonX = state.buttons[GLFW_GAMEPAD_BUTTON_X] == GLFW_PRESS; // checks if X button is initialized or finalized

            if (state.buttons[GLFW_GAMEPAD_BUTTON_A])
                buttonA = true;
            else
                buttonA = false;

            if (prevButtonA && state.buttons[GLFW_GAMEPAD_BUTTON_A] == GLFW_RELEASE && !enemyFightingToggle && CONTROLS_ENABLED){
                timeSinceLastInput = glfwGetTime();
            }
            prevButtonA = state.buttons[GLFW_GAMEPAD_BUTTON_A] == GLFW_PRESS;

            if (!prevButtonB && state.buttons[GLFW_GAMEPAD_BUTTON_B] == GLFW_PRESS && allowPlayerTeleportation && CONTROLS_ENABLED)
                teleportKeyPressed = true;

            if (prevButtonB && state.buttons[GLFW_GAMEPAD_BUTTON_B] == GLFW_RELEASE && CONTROLS_ENABLED)
                teleportKeyPressed = false;

            prevButtonB = state.buttons[GLFW_GAMEPAD_BUTTON_B] == GLFW_PRESS;

            if (!prevButtonY && state.buttons[GLFW_GAMEPAD_BUTTON_Y] == GLFW_PRESS && gameOver)
                restartGame = true;

            prevButtonY = state.buttons[GLFW_GAMEPAD_BUTTON_X] == GLFW_PRESS;


            if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP]) // gameplay
                dPadUp = true;
            else
                dPadUp = false;

            if (!prevButtonUp && state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP] == GLFW_PRESS && !enterKeyPressed){ // menu
                if(menuChoice > 0){
                    menuChoice -= 1;
                }
                else
                    menuChoice = 7;
            }
            prevButtonUp = state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP] == GLFW_PRESS;

            if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN])
                dPadDown = true;
            else
                dPadDown = false;

            if (!prevButtonDown && state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN] == GLFW_PRESS && !enterKeyPressed){
                if(menuChoice < 7){
                    menuChoice += 1;
                }
                else
                    menuChoice = 0;
            }
            prevButtonDown = state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN] == GLFW_PRESS;

            if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT])
                dPadRight = true;
            else
                dPadRight = false;

            if (state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT])
                dPadLeft = true;
            else
                dPadLeft = false;

        }

        if (!prevButtonStart && state.buttons[GLFW_GAMEPAD_BUTTON_START] == GLFW_PRESS && !enterKeyPressed){
                enterKeyPressed = true;
            }
            prevButtonStart = state.buttons[GLFW_GAMEPAD_BUTTON_START] == GLFW_PRESS;


        if (!prevButtonSelect && state.buttons[GLFW_GAMEPAD_BUTTON_BACK] == GLFW_PRESS){
                music.pause();
                mainMenu = true;
                enterKeyPressed = false;
                ENABLE_TEXT = true;
            }
            prevButtonSelect = state.buttons[GLFW_GAMEPAD_BUTTON_BACK] == GLFW_PRESS;
    }

    const float cameraSpeed = CAMERA_SPEED * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {
        fullscreen(window);
    }

    if (FREECAM_CONTROLS_ENABLED){
        terrainCoordBelowCamera = getHeight(cameraPos.x, cameraPos.z);
        const float collisionLimit = terrainCoordBelowCamera + 1.0f;

        if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GLFW_TRUE){
            GLFWgamepadstate state;
            if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state)){
                    if (state.buttons[GLFW_GAMEPAD_BUTTON_A]){
                        cameraPos.y += (cameraSpeed);
                    }
                    if (state.buttons[GLFW_GAMEPAD_BUTTON_B]){
                        cameraPos.y -= (cameraSpeed);
                    }
                }
        }

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
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }

    if (CONTROLS_ENABLED && !FREECAM_CONTROLS_ENABLED){


        if ((glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS || leftTriggerHeld) && !enemyFightingToggle && timeElapsed > 1.0){
            laserAttackCharge += deltaTime * 10.0f;
            playerCurrentlyChargingUp = true;
            cameraPos.y = player[3][1];
            cameraPos.z = player[3][2] + 3.5f;

            float cameraHeightAboveTerrain = getHeight(cameraPos.x, cameraPos.z);

            if (cameraPos.y < cameraHeightAboveTerrain + 1.0f){
                cameraPos.y = cameraHeightAboveTerrain + 1.0f;
            }

            if ((currentFrame - timeSinceLastSpark) > 0.05f){
                dustEntity newSpark;
                newSpark.modelMatrix[3][0] = player[3][0] + randomInRange(-0.8f, 0.8f);
                newSpark.modelMatrix[3][1] = player[3][1] + randomInRange(-0.8f, 0.8f);
                newSpark.modelMatrix[3][2] = player[3][2] + 0.1f;
                cameraPos.x = player[3][0] + randomInRange(-0.05f, 0.05f);
                existingSparks.push_back(newSpark);
                timeSinceLastSpark = currentFrame;
            }


        }
        if (!playerCurrentlyChargingUp && laserAttackCharge > 0.0f)
            laserAttackCharge -= deltaTime * 3.0f;



        if ((glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS || buttonX) && glfwGetKey(window, GLFW_KEY_L) == !GLFW_PRESS && !enemyFightingToggle && timeElapsed > 1.0f
            && (currentFrame - timeSinceInitializePlayerFightAnimation) < 5.0f && playerFightRangeInitializeCheck && !playerCurrentlyChargingUp){
            playerFightingToggle = true;
            if (!DISABLE_SLOW_MO){
                SLOW_MO = true;
            }
        }

        else{
            playerFightingToggle = false;
            if (!DISABLE_SLOW_MO){
                SLOW_MO = false;
            }
        }


        float adjustedDeltaTime = deltaTime;
        if (SLOW_MO){
            adjustedDeltaTime *= SLOW_MO_MULTIPLIER;
        }

        if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || dPadLeft) == GLFW_PRESS && !enemyFightingToggle && !playerCurrentlyChargingUp){
            rotateCameraAroundPoint(glm::vec3(player[3][0], player[3][1], player[3][2]),
                                         cameraPos, adjustedDeltaTime, CAMERA_ROTATE_SPEED);
        }
        if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || dPadRight) && !enemyFightingToggle && !playerCurrentlyChargingUp){
            rotateCameraAroundPoint(glm::vec3(player[3][0], player[3][1], player[3][2]),
                                         cameraPos, adjustedDeltaTime, -CAMERA_ROTATE_SPEED);
        }
        if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || dPadUp) && !playerFightingToggle && !enemyFightingToggle && !playerShieldEnabled && timeElapsed > 1.0 && !playerCurrentlyChargingUp){
            movePlayerToPoint(deltaTime, MOVEMENT_SPEED);
        }

        if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || dPadDown) && !playerFightingToggle && !enemyFightingToggle && !playerShieldEnabled && timeElapsed > 1.0f && !playerCurrentlyChargingUp){
            if (player[3][0] < 400.0f && player[3][0] > -400.0f && player[3][2] < 400.0f && player[3][2] > -400.0f)
                movePlayerToPoint(deltaTime, -MOVEMENT_SPEED);
        }

        if ((glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS || buttonA) && !playerFightingToggle && !enemyFightingToggle && timeElapsed > 1.0f && !playerCurrentlyChargingUp){
            playerShieldEnabled = true;
        }
        else
            playerShieldEnabled = false;

    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){

    float timeElapsed = glfwGetTime() - timeSinceLastInput;

    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS && !enterKeyPressed) {
        enterKeyPressed = true;
    }

    if (key == GLFW_KEY_UP && action == GLFW_PRESS && !enterKeyPressed) {
        if(menuChoice > 0){
            menuChoice -= 1;
        }
        else
            menuChoice = 7;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && !enterKeyPressed) {
        if(menuChoice < 7){
            menuChoice += 1;
        }
        else
            menuChoice = 0;
    }
    if (key == GLFW_KEY_K && action == GLFW_PRESS && !enemyFightingToggle && timeElapsed > 1.0f && CONTROLS_ENABLED) {
        float playerToEnemyDistance = calculateDistance(glm::vec3(player[3][0], player[3][1], player[3][2]), glm::vec3(enemy[3][0], enemy[3][1], enemy[3][2]));
        if (playerToEnemyDistance < 2.5f)
            playerFightRangeInitializeCheck = true;
        else
            playerFightRangeInitializeCheck = false;
        initializeFightAnimation = true;
        timeSinceInitializePlayerFightAnimation = glfwGetTime();
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && allowPlayerTeleportation && CONTROLS_ENABLED){
        teleportKeyPressed = true;
    }
    if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS && gameOver){
       restartGame = true;
    }


    if (key == GLFW_KEY_K && action == GLFW_RELEASE && !enemyFightingToggle && CONTROLS_ENABLED) {
        timeSinceLastInput = glfwGetTime();
    }
    if (key == GLFW_KEY_L && action == GLFW_RELEASE && !enemyFightingToggle && CONTROLS_ENABLED) {
        timeSinceLastInput = glfwGetTime();
    }

    if (key == GLFW_KEY_J && action == GLFW_RELEASE && !enemyFightingToggle && CONTROLS_ENABLED) {
        timeSinceLastInput = glfwGetTime();
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE && CONTROLS_ENABLED) {
        teleportKeyPressed = false;
    }
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        music.pause();
        mainMenu = true;
        enterKeyPressed = false;
        ENABLE_TEXT = true;
    }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (FREECAM_CONTROLS_ENABLED){

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
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
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

void fullscreen(GLFWwindow* window){
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

        if (!ENABLE_VSYNC){
            glfwSwapInterval(0); // uncapped framerate
        }
        else
            glfwSwapInterval(1);
}
