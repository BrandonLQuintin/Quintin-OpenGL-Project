#include "entity.h"

void setShadowLocation(shape &shape, float groundY){
    shape.modelMatrix[3][0] = cameraPos.x; // x
    shape.modelMatrix[3][1] = groundY; // y
    shape.modelMatrix[3][2] = cameraPos.z; // z

    if (cameraPos.y < groundY + 10 && cameraPos.y > groundY + 1.0f){
        shape.modelMatrix[0][0] = 0.8f / cameraPos.y;  // x
        shape.modelMatrix[1][1] = 0.8f / cameraPos.y;  // y
        shape.modelMatrix[2][2] = 0.8f / cameraPos.y;  // z
    }
};
