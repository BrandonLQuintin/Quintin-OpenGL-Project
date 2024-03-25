#include "globals.h"

std::random_device rd;
std::mt19937 gen(rd()); // for use with random

// game settings
bool restartGame = false;
bool IS_RAINING = true;
bool SLOW_MO = false;
bool DISABLE_SLOW_MO = false;
bool HIGH_RENDER_DISTANCE = false;
bool ENABLE_VSYNC = false;
bool ENABLE_TEXT = true;
bool ENABLE_SOUND = true;
bool text = true;
bool FREECAM_CONTROLS_ENABLED = false;
bool CONTROLS_ENABLED = true;

bool gameOver = false;

int playerLives = 3;
int enemyLives = 3;

float health = 0.0f;
float normalizedScore = 0.0f;

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

std::string dialogue;
int dialogueChoice = 0;

// player
glm::mat4 player = glm::mat4(1.0f);
bool playerCurrentlyFighting = false;
bool playerFightingToggle = false;
float timeSinceLastPunch = 0.0f;
bool firstPunchFrame = false;
bool punchFrameToggle = true; // this makes it so the hit registration doesnt count hundreds of time per second
bool punchAnimationBounceBack = false;
bool initializeFightAnimation = false;
bool playerShieldEnabled = false;
bool playerShieldToggle = false;
bool allowPlayerTeleportation = false;

// controls
float timeSinceLastInput = 0.0f;
bool teleportKeyPressed = false;

// enemy
glm::mat4 enemy = glm::mat4(1.0f);
glm::vec3 enemyGoTo = glm::vec3(0.0f, 0.0f, 0.0f);
bool enemyReachedDestination = false;
float enemyWaitTime = 0.0f;
float timeSinceLastEnemyWait = 0.0f;
float timeSinceLastEnemyThought = 0.0f;
bool enemyFightingToggle = false;
float timeSinceEnemyFightInit = 0.0f;
bool enemyOffensiveMode = false;
bool ENEMY_MOVMENT = true;

float lastX = 0;
float lastY = 0;

// animation mode
bool animationModeActivate = false;
float timeSinceAnimationActivation = 0.0f;
float animationDeltaTime = 0.0f;

glm::vec3 direction; // used for camera rotation (in mouseCallback)
float yaw = -90.0f;
float pitch = 0.0f;

std::vector<float> fpsVector;
float timeSinceLastFPSCalculation = 0.0f;

float terrainCoordBelowCamera = 0.0f;

float randomInRange(float min, float max) {
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}
