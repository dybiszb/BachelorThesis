//==============================================================================
// TODO
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef BOUNDING_GRID_H
#define BOUNDING_GRID_H

#pragma comment(lib,PhysX3Gpu_x64.lib)

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "computational_cell.h"
#include "renderable_object.h"
#include "computational_cells_arrays.h"

using namespace glm;
using namespace std;
using namespace rendering;


class CComputationalGrid : CRenderableObject {
public:
    CComputationalGrid();

    ~CComputationalGrid();

    void updateModelMatrix();

    void render(const float *view, const float *projection);

    void setModelMatrix(mat4 &modelMatrix);

    void setCellsVisibility(bool modelBoxesVisibility);

    void updateHeightField(GLfloat* textureAsArray,
                           float width,
                           float height, float edgeSize);

private:
    mat4 _modelMatrix;
    vector<CComputationalCell *> _cells;
    bool _cellsVisibility;
    float _mass;
};


#endif
