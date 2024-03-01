#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include <shader_m.h>
#include <vector>

// game settings
const bool CONTROLS_ENABLED = true;
extern bool isRaining;

const float PI = 3.14159265358979323846f;
const unsigned int POLY_RESOLUTION = 35;
const float VIEW_DISTANCE = 100.0f;

// screen settings
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;
const bool ENABLE_VSYNC = false;
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

// fps calculation
extern std::vector<float> fpsVector;
extern float timeSinceLastFPSCalculation;
