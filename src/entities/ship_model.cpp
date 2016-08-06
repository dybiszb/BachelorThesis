// author: dybisz

#include "ship_model.h"

CShipModel::CShipModel(Settings &settings) : COBJModel(
        "res/models/boat_fishing/",
        "res/models/boat_fishing/boat_fishing_02"
                ".obj") {
    _modelMatrix = scale(_modelMatrix, vec3(0.002f, 0.002f, 0.002f));
    _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 25.0f, 0.0f));
}

CShipModel::~CShipModel() {
}

void CShipModel::updateComputationalGrid(GLfloat *textureAsArray,
                                         float width,
                                         float height, float edgeSize) {
    _computationalGrid.updateHeightField(textureAsArray, width, height,
                                         edgeSize);
}

void CShipModel::render(const float *view,
                        const float *projection) {
//    COBJModel::render(view, projection);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _computationalGrid.render(view, projection);
    glDisable(GL_BLEND);
}

void CShipModel::moveShip(vec3 &translation) {
    _modelMatrix = glm::translate(_modelMatrix, translation);
}