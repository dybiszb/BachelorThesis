//==============================================================================
// The computational grid consists of cells, which are represented in form of
// cubes. Following class encapsulated such a cube enabling specifying its
// position and calculating its immersion level.
//
// NOTE: Private methods, as an internal part of the class rather than public
//       interface, are not commented.
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
    ~CComputationalCell();

    /**
     * Generates a cube withing OpenGL context.
     *
     * @param center Center of cube.
     * @param size   Size of cube.
     */
    CComputationalCell(vec3 center, float size = 1.0);

    /**
     * Renders the cell according to provide matrices.
     *
     * @param view       View matrix of a scene.
     * @param projection Projection matrix of a scene.
     */
    void render(const float *view, const float *projection);

    /**
     * Updates model matrix in order to e.g. translate or rotate the cell
     * during rendering phase.
     *
     * @param modelMatrix Matrix with current model transformations.
     */
    void setModelMatrix(mat4 &modelMatrix);

    /**
     * @return True if cell is currently considered as immersed, false
     *         otherwise.
     */
    bool isImmersed();

    /**
     * Updates cell's immersion level.
     *
     * @param waterHeight   Height of the water in the cell.
     * @param scaledCenterY Y component of closest water vertex.
     */
    void setImmersion(float waterHeight, float scaledCenterY);

    /**
     * @return Immersion level.
     */
    float getImmersion();

    /**
     * @return The cell center.
     */
    vec3 &getCenter();

private:
    mat4  _modelMatrix;
    vec3  _localTranslation;
    float _immersion = 0;
    bool  _isWireframe;

    void _initShader();
};


#endif
