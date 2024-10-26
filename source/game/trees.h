#pragma once
#include "../globals.h"
#include "../shapes/shapes.h"
#include "../shapes/terrain.h"

extern std::array<std::array<int, TREE_AMOUNT * 2>, 9> randomNums;
extern std::array<std::array<int, TREE_AMOUNT>, 9> xOffset;
extern std::array<std::array<int, TREE_AMOUNT>, 9> zOffset;

extern std::array<std::array<tree, TREE_AMOUNT>, 9> trees;
extern std::vector<tree> activeTrees;

std::array<int, TREE_AMOUNT * 2> generateRandomConsistentNumbers(int chunkX, int chunkZ);
uint32_t hashCombine(int x, int y, int z);

std::pair<int, int> getChunkCoordinates(float playerX, float playerZ);

void generateSurroundingChunks(std::array<std::pair<int, int>, 9> &renderingChunks, const std::pair<int, int> origin);

void initializeTreeLocations(const std::array<std::pair<int, int>, 9> renderingChunks);
