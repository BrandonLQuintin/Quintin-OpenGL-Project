#include "entity.h"

void setShadowLocation(shape &shape, glm::vec3 targetPos, float groundY){
    shape.modelMatrix[3][0] = targetPos.x; // x
    shape.modelMatrix[3][1] = groundY; // y
    shape.modelMatrix[3][2] = targetPos.z; // z

    float shadowSize = 1.0f;

    if (targetPos.y < groundY + 10 && targetPos.y > groundY + 0.5f){
        shape.modelMatrix[0][0] = shadowSize / targetPos.y;  // x
        shape.modelMatrix[1][1] = shadowSize / targetPos.y;  // y
        shape.modelMatrix[2][2] = shadowSize / targetPos.y;  // z
    }
};
// UNUSED SHADOW CODE
/*

        // in main.cpp

        std::vector<float> shadowAtlasUV = returnTextureUV(0, 2);

        // 1 shadow
        shape shadows[1 + billboardsArraySize];
        int shadowsArraySize = sizeof(shadows) / sizeof(shadows[0]);
        shadows[0].type = 8;

        // ### SHADOWS
        for (int i = 0; i < shadowsArraySize; i++){
            glDisable(GL_DEPTH_TEST);
            float groundY = 0.01f;

            if (i > 0){ // after rendering player shadow, render billboard shadows
                shadows[i].modelMatrix[3][0] = billboards[i - 1].modelMatrix[3][0]; // x
                shadows[i].modelMatrix[3][2] = billboards[i - 1].modelMatrix[3][2]; // z
                setShadowLocation(shadows[i], glm::vec3(billboards[i - 1].modelMatrix[3][0], billboards[i - 1].modelMatrix[3][1], billboards[i - 1].modelMatrix[3][2]), groundY);
            }
            else{
                setShadowLocation(shadows[0], glm::vec3(cameraPos.x, cameraPos.y, cameraPos.z), terrainCoordBelowCamera);
            }

            phongShader.use();
            glBindVertexArray(phongFloorVAO);
            setTextureUV(phongShader, shadowAtlasUV, false);
            phongShader.setMat4("model", shadows[i].modelMatrix);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glEnable(GL_DEPTH_TEST);
        }

*/
