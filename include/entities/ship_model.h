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

class CShipModel : public COBJModel {
public:
    CShipModel(Settings &settings);

    ~CShipModel();

    virtual void render(const float *view,
                        const float *projection);

    /**
     * Inform the computational grid about changes in the water surface.
     *
     * @param textureAsArray Water's heightfield texture projected
     *                       onto GLfloat array.
     * @param width          Width of the texture.
     * @param height         Height of the texture.
     * @param edgeSize       Length of the water edge in the simulation.
     */
    void updateComputationalGrid(GLfloat *textureAsArray,
                                 float width,
                                 float height,
                                 float edgeSize);

    /**
     * Act on ship's hull with force. Force will be applied in
     * the front of the model.
     *
     * @param movementForce
     */
    void setMovementForce(const vec3 &movementForce);

    /**
     * Should the grid's cubes be visible?
     *
     * @param isGridVisible True if one wants to see the grid,
     *                      false otherwise.
     */
    void setComputationalGridVisibility(bool isGridVisible);

    /**
     * Translate model to fit computational grid.
     *
     * @param localTranslation
     */
    void setModelLocalTranslation(const vec3 &localTranslation);

    /**
     * Scale the model to fit computational grid.
     *
     * @param scale
     */
    void setModelScale(float scale);

    void setModelLinearDamping(float linearDamping);
    void setModelAngularDamping(float angularDamping);

private:
    CComputationalGrid _computationalGrid;
    bool _computationalGridVisibility;
    vec3 _movementForce;
    vec3 _modelLocalTranslation;
    float _modelLocalScale;
};


#endif
