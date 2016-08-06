//==============================================================================
//
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#ifndef SHIP_MODEL_H
#define SHIP_MODEL_H

#include <glm/gtc/matrix_transform.hpp>
#include "obj_model.h"
#include "computational_grid.h"
#include "settings_struct.h"

using namespace rendering;
using namespace glm;

class CShipModel : public COBJModel{
public:
    CShipModel(Settings& settings);
    ~CShipModel();

    void updateComputationalGrid(GLfloat *textureAsArray,
                                 float width,
                                 float height,
                                 float edgeSize);

    virtual void render(const float *view,
                        const float *projection);

    void moveShip(vec3& translation);

private:
    CComputationalGrid _computationalGrid;
};


#endif
