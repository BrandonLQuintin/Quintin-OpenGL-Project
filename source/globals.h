#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>
#include <shader_m.h>
#include <vector>
#include <random>
#include <SFML/Audio.hpp>


float randomInRange(float min, float max);

// game settings
extern bool restartGame;
extern bool mainMenu;
const float MOVEMENT_SPEED = 12.0f;
extern bool gameOver;

extern int playerLives;
extern int enemyLives;

extern float health;
extern float normalizedScore;

extern bool FREECAM_CONTROLS_ENABLED;
extern bool CONTROLS_ENABLED;
extern bool IS_RAINING;
extern bool SLOW_MO;
extern bool DISABLE_SLOW_MO;
extern bool HIGH_RENDER_DISTANCE;
extern bool ENABLE_VSYNC;
extern bool ENABLE_TEXT;
extern bool ENABLE_SOUND;
extern bool text;

const float PI = 3.14159265358979323846f;
const unsigned int POLY_RESOLUTION = 35;
const unsigned int CHUNK_SIZE = 1000;
extern float VIEW_DISTANCE;
extern float DESPAWN_DISTANCE;
extern float FOG_DENSITY;

extern std::string dialogue;
extern int dialogueChoice;

// main menu
extern bool enterKeyPressed;
extern int menuChoice;


// player variables
extern float terrainCoordBelowCamera;
extern glm::mat4 player;
extern bool playerCurrentlyFighting;
extern bool playerFightingToggle;
extern bool firstPunchFrame;
extern float timeSinceLastPunch;
extern bool punchAnimationBounceBack;
extern bool initializeFightAnimation;
extern bool punchFrameToggle;
extern bool playerShieldEnabled;
extern bool playerShieldToggle;
extern bool allowPlayerTeleportation;

// controls
extern float timeSinceLastInput;
extern bool teleportKeyPressed;

// enemy variables
extern glm::mat4 enemy;
extern glm::vec3 enemyGoTo;
extern bool enemyReachedDestination;
extern float enemyWaitTime;
extern float timeSinceLastEnemyWait;
extern float timeSinceLastEnemyThought;
extern bool enemyOffensiveMode;

extern bool enemyFightingToggle;
extern float timeSinceEnemyFightInit;
extern bool ENEMY_MOVMENT;

// animation mode
extern bool animationModeActivate;
extern float timeSinceAnimationActivation;
extern float animationDeltaTime;

// screen settings
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;
const float CAMERA_SPEED = 5.0f;
const float CAMERA_ROTATE_SPEED = 150.0f;
extern float fov;

// timing
extern float deltaTime;
extern float lastFrame;
const float SLOW_MO_MULTIPLIER = 1.3f;

// mouse controls
extern float lastX;
extern float lastY;
extern glm::vec3 direction;
extern float yaw;
extern float pitch;

// fps calculation
extern std::vector<float> fpsVector;
extern float timeSinceLastFPSCalculation;
