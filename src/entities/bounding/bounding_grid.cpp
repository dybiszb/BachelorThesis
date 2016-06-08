// author: dybisz

#include <tiny_obj_loader.h>
#include "bounding_grid.h"

CBoundingGrid::CBoundingGrid(COBJModel &model, float boxSize) :
        _modelMatrix(1.0),
        _modelBoxesVisibility(true),
        _emptyBoxesVisibility(true) {

    float deltaX = model._xMinMax.y - model._xMinMax.x;
    float deltaY = model._yMinMax.y - model._yMinMax.x;
    float deltaZ = model._zMinMax.y - model._zMinMax.x;

    int boxesOnXAxis = (int) (deltaX / boxSize) + 1;
    int boxesOnYAxis = (int) (deltaY / boxSize) + 1;
    int boxesOnZAxis = (int) (deltaZ / boxSize) + 1;

    cout << "boxes on x: " << boxesOnXAxis << endl;
    cout << "boxes on y: " << boxesOnYAxis << endl;
    cout << "boxes on z: " << boxesOnZAxis << endl;

    for (float x = 0; x < boxesOnXAxis; x++) {
        for (float y = 0; y < boxesOnYAxis; y++) {
            for (float z = 0; z < boxesOnZAxis; z++) {

                vector<vec3> vertices;
                vec3 basePoint = vec3(model._xMinMax.x,
                                      model._yMinMax.x,
                                      model._zMinMax.y);


                vertices.push_back(basePoint + vec3(x * boxSize, y * boxSize,
                                                    -z * boxSize));
                vertices.push_back(
                        basePoint + vec3((x + 1) * boxSize, y * boxSize,
                                         -z * boxSize));
                vertices.push_back(basePoint + vec3((x + 1) * boxSize,
                                                    (y + 1) * boxSize,
                                                    -z * boxSize));
                vertices.push_back(basePoint + vec3(x * boxSize,
                                                    (y + 1) * boxSize,
                                                    -z * boxSize));



                vertices.push_back(basePoint + vec3(x * boxSize, y * boxSize,
                                                    -(z + 1) * boxSize));
                vertices.push_back(
                        basePoint + vec3((x + 1) * boxSize, y * boxSize,
                                         -(z + 1) * boxSize));
                vertices.push_back(basePoint + vec3((x + 1) * boxSize,
                                                    (y + 1) * boxSize,
                                                    -(z + 1) * boxSize));
                vertices.push_back(basePoint + vec3(x * boxSize,
                                                    (y + 1) * boxSize,
                                                    -(z + 1) * boxSize));
                CBoundingBox* box = new CBoundingBox(vertices);
                _boxes.push_back(box);
            }
        }
    }


    for (auto shape : model.getShapes()) {
        for (int i = 0; i < shape.mesh.positions.size(); i += 3) {

            /* ----- Collect Vertex ----- */
            float x = shape.mesh.positions[i];
            float y = shape.mesh.positions[i + 1];
            float z = shape.mesh.positions[i + 2];

            /* ----- Per Axis Index ----- */
            x = (int) ((x - model._xMinMax.x) / boxSize);
            y = (int) ((y - model._yMinMax.x) / boxSize);
            z = (int) ((model._zMinMax.y - z) / boxSize);

            /* ----- Global Index ----- */
            int boxIndex = x * boxesOnZAxis * boxesOnYAxis + y * boxesOnZAxis
                           + z;

            _boxes[boxIndex]->setModelBox(true);
        }
    }
}

CBoundingGrid::~CBoundingGrid() {
    for (auto box : _boxes) delete box;
}

void CBoundingGrid::render(const float *view, const float *projection) {
    for (auto box : _boxes) {

        if(box->isModelBox()) box->setVisible(_modelBoxesVisibility);
        else box->setVisible(_emptyBoxesVisibility);

        box->setModelMatrix(_modelMatrix);
        box->render(view, projection);
    }
}

void CBoundingGrid::setModelMatrix(mat4 &modelMatrix) {
    _modelMatrix = modelMatrix;
}

void CBoundingGrid::setModelBoxesVisibility(bool modelBoxesVisibility) {
    _modelBoxesVisibility = modelBoxesVisibility;
}

void CBoundingGrid::setEmptyBoxesVisibility(bool emptyBoxesVisibility) {
    _emptyBoxesVisibility = emptyBoxesVisibility;
}
