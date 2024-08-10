#pragma once
#include <glad/glad.h> // loads OpenGL pointers
#include <GLFW/glfw3.h>
#include "../globals.h"
#include "camera_variables.h"
#include "../shapes/terrain.h"
#include "../game/gameplay.h"

extern bool firstMouse;

extern bool dPadUp;
extern bool prevButtonUp;
extern bool dPadDown;
extern bool prevButtonDown;
extern bool dPadRight;
extern bool dPadLeft;


extern bool buttonX;
extern bool prevButtonX;
extern bool buttonA;
extern bool prevButtonA;

extern bool prevButtonB;
extern bool prevButtonY;
extern bool prevButtonStart;
extern bool prevButtonSelect;

extern bool leftTriggerHeld;
extern bool prevleftTrigger;

extern bool controllerConnected;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void fullscreen(GLFWwindow* window);
GLFWwindow* createWindow();
void detectController(int joystickId);
