#include "initialize_shape_vertices.h"

unsigned int textVAO, textVBO, textEBO;
unsigned int boxVAO, boxVBO;
unsigned int pyramidVAO, pyramidVBO;
unsigned int sphereVAO, sphereVBO;
unsigned int coneVAO, coneVBO;
unsigned int tubeVAO, tubeVBO;

unsigned int phongBillboardVAO, phongBillboardVBO, phongBillboardEBO;
unsigned int phongBoxVAO, phongBoxVBO;
unsigned int phongFloorVAO, phongFloorVBO;
unsigned int phongPyramidVAO, phongPyramidVBO;
unsigned int phongConeVAO, phongConeVBO;
unsigned int phongSphereVAO, phongSphereVBO;
unsigned int phongCylinderVAO, phongCylinderVBO;

unsigned int phongCylinderVerticesArraySize;
unsigned int phongConeVerticesArraySize;
unsigned int phongSphereVerticesArraySize;

void initializeAllShapes(){
    // initialize sphere vertices
    std::vector<float> sphereShapeVertices;
    generateSphere(3.0f, POLY_RESOLUTION, sphereShapeVertices);
    float sphereVertices[sphereShapeVertices.size()];
    std::copy(sphereShapeVertices.begin(), sphereShapeVertices.end(), sphereVertices);
    unsigned int sphereVerticesByteSize = sizeof(sphereVertices);
    unsigned int sphereVerticesArraySize = sizeof(sphereVertices) / sizeof(sphereVertices[0]);

    // initialize phong sphere vertices
    std::vector<float> phongSphereShapeVertices;
    generatePhongSphere(3.0f, POLY_RESOLUTION, phongSphereShapeVertices);
    float phongSphereVertices[phongSphereShapeVertices.size()];
    std::copy(phongSphereShapeVertices.begin(), phongSphereShapeVertices.end(), phongSphereVertices);
    unsigned int phongSphereVerticesByteSize = sizeof(phongSphereVertices);
    phongSphereVerticesArraySize = sizeof(phongSphereVertices) / sizeof(phongSphereVertices[0]);

    // initialize cone vertices
    std::vector<float> coneShapeVertices;
    generateCone(0.5f, 1.0f, POLY_RESOLUTION, coneShapeVertices);
    float coneVertices[coneShapeVertices.size()];
    std::copy(coneShapeVertices.begin(), coneShapeVertices.end(), coneVertices);
    unsigned int coneVerticesByteSize = sizeof(coneVertices);
    unsigned int coneVerticesArraySize = sizeof(coneVertices) / sizeof(coneVertices[0]);

    // initialize phong cone vertices
    std::vector<float> phongConeShapeVertices;
    generatePhongCone(0.5f, 1.0f, POLY_RESOLUTION, phongConeShapeVertices);
    float phongConeVertices[phongConeShapeVertices.size()];
    std::copy(phongConeShapeVertices.begin(), phongConeShapeVertices.end(), phongConeVertices);
    unsigned int phongConeVerticesByteSize = sizeof(phongConeVertices);
    phongConeVerticesArraySize = sizeof(phongConeVertices) / sizeof(phongConeVertices[0]);

    // initialize tube vertices
    std::vector<float> tubeShapeVertices;
    generateCylinderVertices(0.5f, 1.0f, POLY_RESOLUTION, tubeShapeVertices);
    float tubeVertices[tubeShapeVertices.size()];
    std::copy(tubeShapeVertices.begin(), tubeShapeVertices.end(), tubeVertices);
    unsigned int tubeVerticesByteSize = sizeof(tubeVertices);
    unsigned int tubeVerticesArraySize = sizeof(tubeVertices) / sizeof(tubeVertices[0]);

    // initialize phong tube vertices
    std::vector<float> phongCylinderShapeVertices;
    generatePhongCylinderVertices(0.5f, 1.0f, POLY_RESOLUTION, phongCylinderShapeVertices);
    float phongCylinderVertices[phongCylinderShapeVertices.size()];
    std::copy(phongCylinderShapeVertices.begin(), phongCylinderShapeVertices.end(), phongCylinderVertices);
    unsigned int phongCylinderVerticesByteSize = sizeof(phongCylinderVertices);
    phongCylinderVerticesArraySize = sizeof(phongCylinderVertices) / sizeof(phongCylinderVertices[0]);

    // ----- OBJECTS VERTICES BUFFERS ------


    generateVAOandEBO(textVAO, textVBO, textEBO, textVerticesByteSize, textIndicesByteSize, textVertices, textIndices);
    generateVAO(boxVAO, boxVBO, boxVerticesByteSize, boxVertices);
    generateVAO(pyramidVAO, pyramidVBO, pyramidVerticesByteSize, pyramidVertices);
    generateVAO(sphereVAO, sphereVBO, sphereVerticesByteSize, sphereVertices);
    generateVAO(coneVAO, coneVBO, coneVerticesByteSize, coneVertices);
    generateVAO(tubeVAO, tubeVBO, tubeVerticesByteSize, tubeVertices);

    // VAO with phong shader

    generatePhongVAOandEBO(phongBillboardVAO, phongBillboardVBO, phongBillboardEBO, phongBillboardVerticesByteSize, phongBillboardIndicesByteSize, phongBillboardVertices, phongBillboardIndices);
    generatePhongVAO(phongBoxVAO, phongBoxVBO, phongBoxVerticesByteSize, phongBoxVertices);
    generatePhongVAO(phongFloorVAO, phongFloorVBO, phongFloorVerticesByteSize, phongFloorVertices);
    generatePhongVAO(phongPyramidVAO, phongPyramidVBO, phongPyramidVerticesByteSize, phongPyramidVertices);
    generatePhongVAO(phongConeVAO, phongConeVBO, phongConeVerticesByteSize, phongConeVertices);
    generatePhongVAO(phongSphereVAO, phongSphereVBO, phongSphereVerticesByteSize, phongSphereVertices);
    generatePhongVAO(phongCylinderVAO, phongCylinderVBO, phongCylinderVerticesByteSize, phongCylinderVertices);

};
