#pragma once
#include <glad/glad.h> // loads OpenGL pointers
#include <GLFW/glfw3.h>
#include "../globals.h"
#include "camera_variables.h"
#include "../shapes/terrain.h"
#include "../game/gameplay.h"

extern bool firstMouse;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLFWwindow* createWindow();
