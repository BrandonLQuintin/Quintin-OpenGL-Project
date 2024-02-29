#include "entity.h"

void setShadowLocation(shape &shape, glm::vec3 targetPos, float groundY){
    shape.modelMatrix[3][0] = targetPos.x; // x
    shape.modelMatrix[3][1] = groundY; // y
    shape.modelMatrix[3][2] = targetPos.z; // z

    float shadowSize = 0.5f;

    if (targetPos.y < groundY + 10 && targetPos.y > groundY + 0.5f){
        shape.modelMatrix[0][0] = shadowSize / targetPos.y;  // x
        shape.modelMatrix[1][1] = shadowSize / targetPos.y;  // y
        shape.modelMatrix[2][2] = shadowSize / targetPos.y;  // z
    }
};
