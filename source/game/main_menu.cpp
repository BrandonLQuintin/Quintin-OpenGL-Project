#include "main_menu.h"
void processMainMenu(GLFWwindow* window, Shader t, int &choice){
    glfwSetKeyCallback(window, key_callback);
    glClearColor(0.16f, 0.80f, 1.00f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    renderText(t, "press enter to select");
    if (choice == 0)
        renderText(t, "\\\\x play game");
    else
        renderText(t, "\\\\  play game");

    if (choice == 1)
        renderText(t, std::string("\\\\\\x enable_vsync (disabled for now): ") + (ENABLE_VSYNC ? "true" : "false"));
    else // REMOVE glfwSwapInterval(0); CODE FROM WINDOW FUNCTIONS TO RESTORE FUNCTIONALITY
        renderText(t, std::string("\\\\\\  enable_vsync (disabled for now): ") + (ENABLE_VSYNC ? "true" : "false"));

    if (choice == 2)
        renderText(t, std::string("\\\\\\\\x is_raining: ") + (IS_RAINING ? "true" : "false"));
    else
        renderText(t, std::string("\\\\\\\\  is_raining: ") + (IS_RAINING ? "true" : "false"));

    if (choice == 3)
        renderText(t, std::string("\\\\\\\\\\x high_render_distance: ") + (HIGH_RENDER_DISTANCE ? "true" : "false"));
    else
        renderText(t, std::string("\\\\\\\\\\  high_render_distance: ") + (HIGH_RENDER_DISTANCE ? "true" : "false"));

    if (choice == 4)
        renderText(t, std::string("\\\\\\\\\\\\x slow_mo: ") + (SLOW_MO ? "true" : "false"));
    else
        renderText(t, std::string("\\\\\\\\\\\\  slow_mo: ") + (SLOW_MO ? "true" : "false"));

    if (choice == 5)
        renderText(t, std::string("\\\\\\\\\\\\\\x enable_text: ") + (text ? "true" : "false"));
    else
        renderText(t, std::string("\\\\\\\\\\\\\\  enable_text: ") + (text ? "true" : "false"));


    if (enterKeyPressed){
        if (choice == 1){
            if (ENABLE_VSYNC)
                ENABLE_VSYNC = false;
            else
                ENABLE_VSYNC = true;
            enterKeyPressed = false;
        }
        else if (choice == 2){
            if (IS_RAINING)
                IS_RAINING = false;
            else
                IS_RAINING = true;
            enterKeyPressed = false;
        }
        else if (choice == 3){
            if (HIGH_RENDER_DISTANCE)
                HIGH_RENDER_DISTANCE = false;
            else
                HIGH_RENDER_DISTANCE = true;
            enterKeyPressed = false;
        }
        else if (choice == 4){
            if (SLOW_MO)
                SLOW_MO = false;
            else
                SLOW_MO = true;
            enterKeyPressed = false;
        }
        else if (choice == 5){
            if (text)
                text = false;
            else
                text = true;
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
            ENABLE_TEXT = text;
            mainMenu = false;
            lastFrame = glfwGetTime();
        }
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}
