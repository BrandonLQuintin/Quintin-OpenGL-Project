#pragma once
#include <glad/glad.h> // loads OpenGL pointers
#include <GLFW/glfw3.h>

extern bool firstMouse;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);

GLFWwindow* createWindow();
