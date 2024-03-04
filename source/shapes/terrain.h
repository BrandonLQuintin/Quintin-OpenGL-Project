#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include "../opengl/textures.h"
#include "../globals.h"

extern int playerChunks[2];

extern std::vector<int> activeChunks; // unused
extern std::vector<float> phongTerrainVector;
extern std::vector<int> phongTerrainIndicesVector;

extern int heightMapWidth, heightMapHeight, heightMapChannels;
extern unsigned char* heightMap;
//const float MAX_HEIGHT = 40;
const float MAX_PIXEL_COLOR = 256 * 256 * 256;
extern int VERTEX_COUNT;

void findChunkCoords(glm::vec2 playerCoord);
void generatePlaneVertices(std::vector<float> &outputVector, std::vector<int> &indicesVector);

extern std::vector<std::vector<float>> heights;

float getTerrainHeight(int x, int z);
float getHeight(float worldX, float worldZ);
glm::vec3 getNormals(int x, int y);
float barryCentric(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec2& pos);
bool renderDistanceCheck(const glm::vec3& playerPos, const glm::vec3& treePos);
