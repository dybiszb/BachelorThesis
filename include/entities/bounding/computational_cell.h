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
#include "cube.h"

using namespace rendering;
using namespace geometry;
using namespace glm;

class CComputationalCell : public CRenderableObject,
                           public CCube {
public:
    CComputationalCell(vec3 centerVertex, float size = 1.0);

    ~CComputationalCell();

    void render(const float *view, const float *projection);

    void setModelMatrix(mat4 &modelMatrix);

    void setWireframe(bool wireframe);

    void setVisible(bool visible);

    bool isImmersed();

    void setImmersion(float waterHeight, float scaledCenterY);

    float getImmersion();


    vec3 &getCenter();

private:
    mat4 _modelMatrix;
    vec3 _localTranslation;
    float _immersion = 0;
    bool _isWireframe;
    bool _isVisible;

    void _initShader();
};


#endif
