//==============================================================================
// TODO
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <vector>
#include <glm/glm.hpp>
#include "renderable_object.h"
#include "cuboid.h"

using namespace rendering;
using namespace geometry;
using namespace glm;

class CBoundingBox : public CRenderableObject,
                     public CCuboid {
public:
    CBoundingBox(vector<vec3> boundingVertices);
    ~CBoundingBox();

    void render(const float *view, const float *projection);

    void setModelMatrix(mat4 &modelMatrix);
    void setModelBox(bool wireframe);
    bool isModelBox();
    void setVisible(bool visible);

private:
    mat4 _modelMatrix;
    bool _modelBox;
    bool _visible;

    void _initShader();

};


#endif
