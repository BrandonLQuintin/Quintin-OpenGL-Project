#pragma once
#include <glad/glad.h> // loads OpenGL pointers
#include <GLFW/glfw3.h>

extern bool firstMouse;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

GLFWwindow* createWindow();
