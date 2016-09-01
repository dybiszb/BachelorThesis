// author: dybisz

#include "ship_model.h"

CShipModel::CShipModel(Settings &settings) : COBJModel(
        "res/models/black_pearl/",
        "res/models/black_pearl/black_pearl"
                ".obj"), _modelLocalScale(0.02) {
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
    _modelMatrix = _computationalGrid.getTransformation();
    _modelMatrix = glm::translate(_modelMatrix, _modelLocalTranslation);
    _modelMatrix = scale(_modelMatrix, vec3(_modelLocalScale, _modelLocalScale, _modelLocalScale));
    _modelMatrix = rotate(_modelMatrix, -3.14f/2.0f, vec3(0.0f, 1.0f, 0.0f));

    COBJModel::render(view, projection);

    if(!_computationalGridVisibility) return;
    _computationalGrid.render(view, projection);
}
void CShipModel::setMovementForce(const vec3 &movementForce) {
    _computationalGrid.setMovementForce(movementForce);
//    _movementForce = movementForce;
}

void CShipModel::setComputationalGridVisibility(bool isGridVisible) {
    _computationalGridVisibility = isGridVisible;
}

void CShipModel::setModelLocalTranslation(const vec3 &localTranslation) {
    _modelLocalTranslation = localTranslation;
}

void CShipModel::setModelScale(float scale) {
    _modelLocalScale = scale;
}

void CShipModel::setModelLinearDamping(float linearDamping) {

}
void CShipModel::setModelAngularDamping(float angularDamping) {

}