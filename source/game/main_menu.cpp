#include "main_menu.h"

void processMainMenu(GLFWwindow* window, Shader t, int &choice){
    glfwSetKeyCallback(window, key_callback);
    glClearColor(0.16f, 0.80f, 1.00f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    processInput(window);

    std::string outputText;

    outputText = "'k' to attack\\'l' to block\\'w' to move forward\\'d' to move backwards\\press enter to select\\";

    if (choice == 0)
        outputText += "\\x play game";
    else
        outputText += "\\  play game";

    if (choice == 1)
        outputText += std::string("\\\\x freecam_controls_enabled: ") + (FREECAM_CONTROLS_ENABLED ? "true" : "false");
    else
        outputText += std::string("\\\\  freecam_controls_enabled: ") + (FREECAM_CONTROLS_ENABLED ? "true" : "false");

    if (choice == 2)
        outputText += std::string("\\x is_raining: ") + (IS_RAINING ? "true" : "false");
    else
        outputText += std::string("\\  is_raining: ") + (IS_RAINING ? "true" : "false");

    if (choice == 3)
        outputText += std::string("\\x enable_vsync: ") + (ENABLE_VSYNC ? "true" : "false");
    else
        outputText += std::string("\\  enable_vsync: ") + (ENABLE_VSYNC ? "true" : "false");

    if (choice == 4)
        outputText += std::string("\\x disable_slow_mo: ") + (DISABLE_SLOW_MO ? "true" : "false");
    else
        outputText += std::string("\\  disable_slow_mo: ") + (DISABLE_SLOW_MO ? "true" : "false");

    if (choice == 5)
        outputText += std::string("\\x enable_text: ") + (text ? "true" : "false");
    else
        outputText += std::string("\\  enable_text: ") + (text ? "true" : "false");
    if (choice == 6)
        outputText += std::string("\\x enable_sound: ") + (ENABLE_SOUND ? "true" : "false");
    else
        outputText += std::string("\\  enable_sound: ") + (ENABLE_SOUND ? "true" : "false");
    if (choice == 7)
        outputText += std::string("\\x show_fps: ") + (SHOW_FPS ? "true" : "false");
    else
        outputText += std::string("\\  show_fps: ") + (SHOW_FPS ? "true" : "false");

    renderText(t, outputText);

    if (enterKeyPressed){
        if (choice == 1){
            FREECAM_CONTROLS_ENABLED = !FREECAM_CONTROLS_ENABLED;
            enterKeyPressed = false;
        }
        else if (choice == 2){
            IS_RAINING = !IS_RAINING;
            enterKeyPressed = false;
        }
        else if (choice == 3){
            ENABLE_VSYNC = !ENABLE_VSYNC;
            enterKeyPressed = false;
        }
        else if (choice == 4){
            DISABLE_SLOW_MO = !DISABLE_SLOW_MO;
            enterKeyPressed = false;
        }
        else if (choice == 5){
            text = !text;
            enterKeyPressed = false;
        }
        else if (choice == 6){
            ENABLE_SOUND = !ENABLE_SOUND;
            enterKeyPressed = false;
        }
        else if (choice == 7){
            SHOW_FPS = !SHOW_FPS;
            enterKeyPressed = false;
        }
        else{
            if (HIGH_RENDER_DISTANCE){
                VIEW_DISTANCE = 1000.0f;
                DESPAWN_DISTANCE = 300.0f;
                FOG_DENSITY = 0.001f;
            }
            if (!ENABLE_VSYNC){
                glfwSwapInterval(0); // uncapped framerate
            }
            else
                glfwSwapInterval(1);
            ENABLE_TEXT = text;
            mainMenu = false;
            if (ENABLE_SOUND)
                music.play();
            lastFrame = glfwGetTime();

            cameraPos.x = player[3][0];
            cameraPos.y = player[3][1];
            cameraPos.z = player[3][2] + 3.5f;
        }
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}
