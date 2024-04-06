#include "terrain.h"
const float MIN_HEIGHT = -80.0f; // Define the minimum height of the terrain
const float MAX_HEIGHT = 300.0f; // Define the maximum height of the terrain

int heightMapWidth, heightMapHeight, heightMapChannels;
unsigned char* heightMap = stbi_load("resources/HeightMap.png", &heightMapWidth, &heightMapHeight, &heightMapChannels, STBI_grey);
int VERTEX_COUNT = 128;
std::vector<std::vector<float>> heights(VERTEX_COUNT, std::vector<float>(VERTEX_COUNT));
std::vector<float> phongTerrainVector;
std::vector<int> phongTerrainIndicesVector;

void generatePlaneVertices(std::vector<float> &outputVector, std::vector<int> &indicesVector) {
    float halfSize = CHUNK_SIZE / 2.0f;
    float vertexSpacing = CHUNK_SIZE / (float)(VERTEX_COUNT - 1);
    float yOffsetAmount = (MIN_HEIGHT + MAX_HEIGHT) / 2;
    for(int i = 0; i < VERTEX_COUNT; i++) {
        for(int j = 0; j < VERTEX_COUNT; j++) {
            float x = j * vertexSpacing - halfSize;
            float z = i * vertexSpacing - halfSize;
            float y = getTerrainHeight(j, i) - yOffsetAmount;

            heights[j][i] = y;
            outputVector.insert(outputVector.end(), {x, y, z});

            // Normals (upwards - y direction)
            glm::vec3 normals = getNormals(j, i);
            outputVector.insert(outputVector.end(), {normals.x, normals.y, normals.z});

            // Texture coordinates
            float texCoordX = (float)j / (VERTEX_COUNT - 1);
            float texCoordY = (float)i / (VERTEX_COUNT - 1);
            outputVector.insert(outputVector.end(), {texCoordX, texCoordY});
        }
    }

    // Generating indices for a 2D grid of vertices
    for(int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
        for(int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
            int topLeft = (gz * VERTEX_COUNT) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
            int bottomRight = bottomLeft + 1;

            indicesVector.insert(indicesVector.end(), {topLeft, bottomLeft, topRight, topRight, bottomLeft, bottomRight});
        }
    }
}

float getTerrainHeight(int x, int z) {
    if (!heightMap || x < 0 || x >= heightMapWidth || z < 0 || z >= heightMapHeight) {
        return MIN_HEIGHT; // Return the minimum height if out of bounds or image not loaded
    }

    int pixelIndex = (z * heightMapWidth + x);
    unsigned char heightValue = heightMap[pixelIndex];
    float heightScale = (heightValue / 255.0f); // This scales heightValue to a [0, 1] range
    return MIN_HEIGHT + (heightScale * (MAX_HEIGHT - MIN_HEIGHT)); // Scale within the new height range
}

float getHeight(float worldX, float worldZ){
    float halfSize = CHUNK_SIZE / 2.0f;
    float terrainX = worldX + halfSize;
    float terrainZ = worldZ + halfSize;
    float gridSquareSize = CHUNK_SIZE / static_cast<float>(heights.size() - 1);
    int gridX = static_cast<int>(glm::floor(terrainX / gridSquareSize));
    int gridZ = static_cast<int>(glm::floor(terrainZ / gridSquareSize));
    if (gridX >= heights.size() - 1 || gridZ >= heights.size() - 1 || gridX < 0 || gridZ < 0){
        return 0;
    }

    float xCoord = std::fmod(terrainX, gridSquareSize) / gridSquareSize;
    float zCoord = std::fmod(terrainZ, gridSquareSize) / gridSquareSize;
    float answer;

    if (xCoord <= (1.0f - zCoord)) {
        answer = barryCentric(glm::vec3(0, heights[gridX][gridZ], 0),
                              glm::vec3(1, heights[gridX + 1][gridZ], 0),
                              glm::vec3(0, heights[gridX][gridZ + 1], 1),
                              glm::vec2(xCoord, zCoord));
    } else {
        answer = barryCentric(glm::vec3(1, heights[gridX + 1][gridZ], 0),
                              glm::vec3(1, heights[gridX + 1][gridZ + 1], 1),
                              glm::vec3(0, heights[gridX][gridZ + 1], 1),
                              glm::vec2(xCoord, zCoord));
    }

    return answer;
}

glm::vec3 getNormals(int x, int z){
    float heightL = getTerrainHeight(x - 1, z);
    float heightR = getTerrainHeight(x + 1, z);
    float heightD = getTerrainHeight(x, z - 1);
    float heightU = getTerrainHeight(x, z + 1);
    glm::vec3 output = {heightL - heightR, 2.0f, heightD - heightU};

    return glm::normalize(output);
}

float barryCentric(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec2& pos){
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

float renderDistanceCheck(const glm::vec3& playerPos, const glm::vec3& treePos){
    return glm::distance(playerPos, treePos);
}
