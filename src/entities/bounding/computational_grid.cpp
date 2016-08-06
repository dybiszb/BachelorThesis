// author: dybisz

#include <glm/gtc/matrix_transform.hpp>
#include "computational_grid.h"


CComputationalGrid::CComputationalGrid() :
        _modelMatrix(scale(mat4(1.0), vec3(0.1, 0.1, 0.1))),
        _cellsVisibility(true) {

    for (auto cell : mediumAccuracyFishingBoat) {
        _mass += 1.0;
        _cells.push_back(new CComputationalCell(cell));
    }
}

CComputationalGrid::~CComputationalGrid() {
    for (auto cell : _cells) delete cell;
}

void CComputationalGrid::updateModelMatrix() {
    mat4 rotationMatrix = mat4(1.0);

}

void CComputationalGrid::render(const float *view, const float *projection) {
    updateModelMatrix();
    for (auto cell : _cells) {
        cell->setVisible(_cellsVisibility);
        cell->setModelMatrix(_modelMatrix);
        cell->render(view, projection);
    }
}

void CComputationalGrid::setModelMatrix(mat4 &modelMatrix) {
    _modelMatrix = modelMatrix;
}

void CComputationalGrid::setCellsVisibility(bool modelBoxesVisibility) {
    _cellsVisibility = modelBoxesVisibility;
}


void CComputationalGrid::updateHeightField(GLfloat *textureAsArray,
                                           float width,
                                           float height, float edgeSize) {
    float ratio = edgeSize / width;
    float immersedMass = 0.0;
    std::map<float, float> b_x_map;
    std::map<float, float> b_y_map;
    std::map<float, float> b_z_map;

    for (auto cell : _cells) {
        vec3 cellCenter = cell->getCenter();
        vec4 scaledCenter = _modelMatrix * vec4(cellCenter, 1.0);
        int tex_u = (int) ((scaledCenter.x / ratio) + (width / 2.0));
        int tex_v = (int) ((scaledCenter.z / ratio) + (height / 2.0));
        float h = textureAsArray[int((tex_v * (width + 1)) + tex_u) * 4];
        cell->setImmersion(h, scaledCenter.y);

        if (cell->isImmersed()) {
            b_x_map[cellCenter.x] += cell->getImmersion();
            b_y_map[cellCenter.y] += cell->getImmersion();
            b_z_map[cellCenter.z] += cell->getImmersion();
            immersedMass += 1.0;
        }
    }

    float b_x = 0;
    float b_y = 0;
    float b_z = 0;
    float oceanWaterDensity =  1.027;

    for(int i = 0; i < 30; i++) {
        b_x += b_x_map[i] * oceanWaterDensity * ( 0.1 * i);
        b_y += b_y_map[i] * oceanWaterDensity * ( 0.1 * i);
        b_z += b_z_map[i] * oceanWaterDensity * ( 0.1 * i);
    }
    float b_force = oceanWaterDensity * immersedMass * 9.81f;
    cout << "force: " << b_force << " at point: "
    << b_x / _mass << " " << b_y / _mass << " " << b_z /_mass
    << endl;
    delete textureAsArray;
}
