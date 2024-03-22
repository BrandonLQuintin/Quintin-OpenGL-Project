#pragma once

#include <vector>
#include "../globals.h"
#include "shapes.h"
#include "terrain.h"


extern float sphereVertices[];
extern unsigned int sphereVerticesByteSize;
extern unsigned int sphereVerticesArraySize;

extern float phongSphereVertices[];
extern unsigned int phongSphereVerticesByteSize;
extern unsigned int phongSphereVerticesArraySize;

extern float coneVertices[];
extern unsigned int coneVerticesByteSize;
extern unsigned int coneVerticesArraySize;

extern float phongConeVertices[];
extern unsigned int phongConeVerticesByteSize;
extern unsigned int phongConeVerticesArraySize;

extern float tubeVertices[];
extern unsigned int tubeVerticesByteSize;
extern unsigned int tubeVerticesArraySize;

extern float phongCylinderVertices[];
extern unsigned int phongCylinderVerticesByteSize;
extern unsigned int phongCylinderVerticesArraySize;

extern float terrainVertices[];
extern unsigned int terrainVerticesByteSize;
extern unsigned int terrainIndicesByteSize;
extern unsigned int terrainVerticesArraySize;
extern unsigned int terrainIndicesArraySize;


extern unsigned int textVAO, textVBO, textEBO;
extern unsigned int healthVAO, healthVBO, healthEBO;
extern unsigned int boxVAO, boxVBO;
extern unsigned int pyramidVAO, pyramidVBO;
extern unsigned int sphereVAO, sphereVBO;
extern unsigned int coneVAO, coneVBO;
extern unsigned int tubeVAO, tubeVBO;

extern unsigned int phongBillboardVAO, phongBillboardVBO, phongBillboardEBO;
extern unsigned int phongTerrainVAO, phongTerrainVBO, phongTerrainEBO;
extern unsigned int phongBoxVAO, phongBoxVBO;
extern unsigned int phongFloorVAO, phongFloorVBO;
extern unsigned int phongPyramidVAO, phongPyramidVBO;
extern unsigned int phongConeVAO, phongConeVBO;
extern unsigned int phongSphereVAO, phongSphereVBO;
extern unsigned int phongCylinderVAO, phongCylinderVBO;


void initializeAllShapes();
