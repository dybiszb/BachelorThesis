// author: dybisz

#include "ship_model.h"

CShipModel::CShipModel(Settings& settings) : COBJModel("res/models/boat_fishing/",
                                     "res/models/boat_fishing/boat_fishing_02"
                                             ".obj") {
    _modelMatrix = scale(_modelMatrix, vec3(0.002f, 0.002f, 0.002f));
    _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 25.0f,
                                                             0.0f));

    _boundingGrid = new CBoundingGrid(*this, 70.0);
    _boundingGrid->setModelBoxesVisibility(settings.modelBoxes);
    _boundingGrid->setEmptyBoxesVisibility(settings.emptyBoxes);
}

CShipModel::~CShipModel() {
    delete _boundingGrid;
}

void CShipModel::updateBoundingGrid(bool modelBoxesVisible,
                                    bool emptyBoxesVisible) {
    _boundingGrid->setModelBoxesVisibility(modelBoxesVisible);
    _boundingGrid->setEmptyBoxesVisibility(emptyBoxesVisible);
}

void CShipModel::render(const float *view,
                    const float *projection) {
    COBJModel::render(view, projection);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    _boundingGrid->setModelMatrix(_modelMatrix);
    _boundingGrid->render(view, projection);
    glDisable(GL_BLEND);
}