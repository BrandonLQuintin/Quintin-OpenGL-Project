#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader_m.h>
#include "../globals.h"
#include "../opengl/text_render.h"
#include "../opengl/window_functions.h"

void processMainMenu(GLFWwindow* window, Shader t, int &choice);
