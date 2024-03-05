#include "globals.h"

bool IS_RAINING = true;
bool SLOW_MO = false;
bool HIGH_RENDER_DISTANCE = false;
bool ENABLE_VSYNC = false;
bool ENABLE_TEXT = true;
bool text = true;

float VIEW_DISTANCE = 100.0f;
float DESPAWN_DISTANCE = 60.0f;
float FOG_DENSITY = 0.001f;

bool mainMenu = true;
int menuChoice = 0;
bool enterKeyPressed = false;

bool isRaining = true;
float fov = 90;

float deltaTime = 0.0f;
float lastFrame = 0.0f;


float lastX = 0;
float lastY = 0;

glm::vec3 direction; // used for camera rotation (in mouseCallback)
float yaw = -90.0f;
float pitch = 0.0f;

std::vector<float> fpsVector;
float timeSinceLastFPSCalculation = 0.0f;


float terrainCoordBelowCamera = 0.0f;
