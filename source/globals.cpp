#include "globals.h"

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
