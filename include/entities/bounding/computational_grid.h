//==============================================================================
// In charge of recalculating forces and calling PhysX library. Attached to a
// model, provides a means to simulate floating on water surface.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef COMPUTATIONAL_GRID_H
#define COMPUTATIONAL_GRID_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "computational_cell.h"
#include "renderable_object.h"
#include "computational_cells_arrays.h"
#include "physx_simulation.h"

using namespace glm;
using namespace std;
using namespace rendering;

class CComputationalGrid : CRenderableObject {
public:
	~CComputationalGrid();

	/**
	 * Loads information from computational_cells_arrays.h header and creates
	 * appropriate computational cells objects and updates PhysX actor shape.
	 */
	CComputationalGrid();

	/**
     * The grid will be rendered with usage of shipped matrices.
     *
     * @param view       View matrix of the scene.
     * @param projection Projection matrix of the scene.
     */
    void render(const float *view, const float *projection);

	/**
     * Updates model matrix via recalculating acting forces and performing
     * one step of PhysX's simulation.
     *
     * @param textureAsArray Water's heightfield texture projected
     *                       onto GLfloat array.
     * @param width          Width of the texture.
     * @param height         Height of the texture.
     * @param edgeSize       Length of the water edge in the simulation.
     */
    void updateHeightField(GLfloat* textureAsArray,
                           float width,
                           float height, float edgeSize);

	/**
     * Retrieves current transformation of the grid. It can be used to
     * update e.g. a model that the grid simulates.
     *
     * @return A matrix with all transformations of the grid.
     */
	mat4 getTransformation();

	/**
	 * Retrieves current position of the grid. It can be used to
	 * update e.g. a model that the grid simulates.
	 *
	 * @return A vector with the grid translation.
	 */
	vec3 getShipPosition();

	/**
     * Update linear dumping threshold.
     *
     * @param linearDumping New value of linear dumping of the grid.
     */
	void setLinearDamping(float linearDamping);

	/**
     * Update angular dumping threshold.
     *
     * @param angularDamping New value of angular dumping of the grid.
     */
	void setAngularDamping(float angularDamping);

	/**
     * Act on ship's hull with force. Force will be applied in
     * the front of the model.
     *
     * @param movementForce Force acting at the front of the ship hull.
     */
	void setMovementForce(const vec3& movementForce);

	/**
	 * @param movementForce Point at which movement force is applied.
	 */
	void setMovementPoint(const vec3& movementPoint);
	
private:
	PhysXSimulation              simulation;
    mat4                         _modelMatrix;
    vector<CComputationalCell *> _cells;
    float                        _mass;
	vec3                         _moveForce;
	vec3                         _movePoint;
};


#endif
