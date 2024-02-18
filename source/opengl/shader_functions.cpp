#include "shader_functions.h"

void useShader(Shader &shader, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec3 cameraPosition){ // this works, but don't call it since this only needs to be done once in a frame
    shader.use();
    shader.setMat4("projection", projectionMatrix);
    shader.setMat4("view", viewMatrix);
    shader.setVec3("viewPos", cameraPosition);
}
