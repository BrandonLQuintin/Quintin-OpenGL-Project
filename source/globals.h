#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>

// game settings
const bool CONTROLS_ENABLED = true;
const float PI = 3.14159265358979323846f;
const unsigned int POLY_RESOLUTION = 35;

// screen settings
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;
extern float fov;

// timing
extern float deltaTime;
extern float lastFrame;

// mouse controls
extern float lastX;
extern float lastY;
extern glm::vec3 direction;
extern float yaw;
extern float pitch;
