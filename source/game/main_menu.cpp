#include "main_menu.h"
void processMainMenu(GLFWwindow* window, Shader t, int choice){
    processInput(window);
    glClearColor(0.16f, 0.80f, 1.00f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderText(t, "hello world! press enter to continue!");

    glfwSwapBuffers(window);
    glfwPollEvents();
}
