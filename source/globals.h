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
extern bool IS_RAINING;
extern bool SLOW_MO;
extern bool HIGH_RENDER_DISTANCE;
extern bool ENABLE_VSYNC;
extern bool ENABLE_TEXT;
extern bool text;


const float PI = 3.14159265358979323846f;
const unsigned int POLY_RESOLUTION = 35;
const unsigned int CHUNK_SIZE = 1000;
extern float VIEW_DISTANCE;
extern float DESPAWN_DISTANCE;
extern float FOG_DENSITY;

// main menu
extern bool enterKeyPressed;
extern int menuChoice;


// player variables
extern float terrainCoordBelowCamera;

// screen settings
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;
const float CAMERA_SPEED = 5.0f;
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
