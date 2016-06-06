// author: dybisz

#include "ship_model.h"

CShipModel::CShipModel() : COBJModel("res/models/black_pearl_export2/",
                                     "res/models/black_pearl_export2/black_pearl"
                                             ".obj") {
    _modelMatrix = scale(_modelMatrix, vec3(0.02f, 0.02f, 0.02f));
    _modelMatrix = glm::translate(_modelMatrix, glm::vec3(0.0f, 25.0f,
                                                             0.0f));
}