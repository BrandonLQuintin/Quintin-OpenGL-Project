#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include <shader_m.h>
#include <vector>

// game settings
extern bool mainMenu;

const bool CONTROLS_ENABLED = true;
const bool IS_RAINING = true;

const float PI = 3.14159265358979323846f;
const unsigned int POLY_RESOLUTION = 35;
const unsigned int CHUNK_SIZE = 1000;
const float VIEW_DISTANCE = 100.0f;
const float DESPAWN_DISTANCE = 60.0f;
const float FOG_DENSITY = 0.001f;


// player variables
extern float terrainCoordBelowCamera;

// screen settings
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;
const float CAMERA_SPEED = 5.0f;
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
