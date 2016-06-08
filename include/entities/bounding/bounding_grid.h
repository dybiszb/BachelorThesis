//==============================================================================
// TODO
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef BOUNDING_GRID_H
#define BOUNDING_GRID_H

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "bounding_box.h"
#include "renderable_object.h"
#include "obj_model.h"

using namespace glm;
using namespace std;
using namespace rendering;

class CBoundingGrid : CRenderableObject{
public:
    CBoundingGrid(COBJModel& model, float boxSize);
    ~CBoundingGrid();
    void render(const float *view, const float *projection);
    void setModelMatrix(mat4& modelMatrix);
    void setModelBoxesVisibility(bool modelBoxesVisibility);
    void setEmptyBoxesVisibility(bool emptyBoxesVisibility);
private:
    mat4 _modelMatrix;
    vector<CBoundingBox*> _boxes;
    bool _modelBoxesVisibility;
    bool _emptyBoxesVisibility;
};


#endif
