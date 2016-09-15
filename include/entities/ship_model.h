//==============================================================================
// Following class represents a model of ship that can be rendered on the
// scene. One is able to move it around via movement force. In addition, the
// class invlolves computational grid, which calculates ship's buoyancy
// force and updates its model.
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
    ~CShipModel();

    /**
     * @param settings Settings struct filled with information loaded from
     *                 .ini file
     */
    CShipModel(Settings &settings);

    /**
     * Ship model along with its textures is render with usage of shipped
     * matrices.
     *
     * @param view       View matrix of the scene.
     * @param projection Projection matrix of the scene.
     */
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
     * @param movementForce Force acting at the front of the ship hull.
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

    /**
     * Update linear dumping threshold.
     *
     * @param linearDumping New value of linear dumping of the ship simulation.
     */
    void setModelLinearDamping(float linearDamping);

    /**
     * Update angular dumping threshold.
     *
     * @param angularDamping New value of angular dumping of the ship
     *        simulation.
     */
    void setModelAngularDamping(float angularDamping);

    /**
     * Updates current light direction. The ship will be shaded using
     * the direction.
     *
     * @param directionalLight Three dimensional vector with light direction.
     */
    void setDirectionalLight(vec3 & directionalLight);

    /**
     * Updates current camera position for correct drawing of the ship.
     *
     * @param cameraPosition Current camera position.
     */
    void setCameraPosition(vec3& cameraPosition);

    /**
     * @return Three dimensional vector with current ship position in world
     *         coordinates.
     */
    vec3 getShipPosition();

private:
    CComputationalGrid _computationalGrid;
    bool               _computationalGridVisibility;
    vec3               _movementForce;
    vec3               _modelLocalTranslation;
    float              _modelLocalScale;
};


#endif
