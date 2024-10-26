#include "trees.h"

std::array<std::array<int, TREE_AMOUNT * 2>, 9> randomNums;
std::array<std::array<int, TREE_AMOUNT>, 9> xOffset;
std::array<std::array<int, TREE_AMOUNT>, 9> zOffset;

std::array<std::array<tree, TREE_AMOUNT>, 9> trees;
std::vector<tree> activeTrees;

std::array<int, TREE_AMOUNT * 2> generateRandomConsistentNumbers(int chunkX, int chunkZ){
    uint32_t seed = static_cast<uint32_t>((chunkX * 73856093) ^ (chunkZ * 19349663));

    std::array<int, TREE_AMOUNT * 2> randomNumbers;
    uint32_t x = seed;
    for (int i = 0; i < TREE_AMOUNT * 2; ++i) {
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        randomNumbers[i] = x % SMALL_CHUNK_SIZE;
    }
    return randomNumbers;
}

std::pair<int, int> getChunkCoordinates(float playerX, float playerZ) {
    int chunkX = static_cast<int>(std::floor(playerX / SMALL_CHUNK_SIZE));
    int chunkZ = static_cast<int>(std::floor(playerZ / SMALL_CHUNK_SIZE));
    return {chunkX, chunkZ};
}

void generateSurroundingChunks(std::array<std::pair<int, int>, 9> &renderingChunks, const std::pair<int, int> origin){
    int arrCounter = 0;
    for (int x = -1; x <= 1; x++){ // x
        for (int z = -1; z <= 1; z++){
            if (x == -1){
                renderingChunks[arrCounter].first = origin.first - 1;
            }
            else if (x == 0){
                renderingChunks[arrCounter].first = origin.first;
            }
            else{
                renderingChunks[arrCounter].first = origin.first + 1;
            }

            if (z == -1){
                renderingChunks[arrCounter].second = origin.second - 1;
            }
            else if (z == 0){
                renderingChunks[arrCounter].second = origin.second;
            }
            else{
                renderingChunks[arrCounter].second = origin.second + 1;
            }

            arrCounter += 1;
        }
    }
}

void initializeTreeLocations(const std::array<std::pair<int, int>, 9> renderingChunks){
    for (int x = 0; x < 9; x++){
        randomNums[x] = generateRandomConsistentNumbers(renderingChunks[x].first, renderingChunks[x].second);
    }

    for (int x = 0; x < 9; x++){
        for (int i = 0; i < TREE_AMOUNT * 2; i++) {
            if (i % 2 == 0) {
                xOffset[x][i / 2] = randomNums[x][i];
            } else {
                zOffset[x][i / 2] = randomNums[x][i];
            }
        }
    }

    for (int x = 0; x < 9; x++){
        for (int i = 0; i < trees[x].size(); i++){
            trees[x][i].modelMatrix[3][0] = (std::floor(renderingChunks[x].first) * SMALL_CHUNK_SIZE) + xOffset[x][i];
            trees[x][i].modelMatrix[3][2] = (std::floor(renderingChunks[x].second) * SMALL_CHUNK_SIZE) + zOffset[x][i];

            trees[x][i].modelMatrix[3][1] = getHeight(trees[x][i].modelMatrix[3][0], trees[x][i].modelMatrix[3][2]) + 2.3f;
        }

        for (int i = 0; i < trees[x].size(); i++){
            trees[x][i].cloneModelMatrix = trees[x][i].modelMatrix;
        }
        for (int i = 0; i < trees[x].size(); i++){
            trees[x][i].cloneModelMatrix = glm::rotate(trees[x][i].cloneModelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            trees[x][i].cloneModelMatrix[3][0] = trees[x][i].modelMatrix[3][0] + 0.55f;
            trees[x][i].cloneModelMatrix[3][1] = trees[x][i].modelMatrix[3][1];
            trees[x][i].cloneModelMatrix[3][2] = trees[x][i].modelMatrix[3][2] + 0.55f;
        }
    }
}
