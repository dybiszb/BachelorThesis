//==============================================================================
// TODO
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
    CComputationalGrid();

    ~CComputationalGrid();

    void render(const float *view, const float *projection);

    void updateHeightField(GLfloat* textureAsArray,
                           float width,
                           float height, float edgeSize);
	mat4 getTransformation();
	void setLinearDamping(float linearDamping);
	void setAngularDamping(float angularDamping);
	void setMovementForce(const vec3& movementForce);
	void setMovementPoint(const vec3& movementPoint);
private:
	PhysXSimulation simulation;
    mat4 _modelMatrix;
    vector<CComputationalCell *> _cells;
    float _mass;
	vec3 _moveForce;
	vec3 _movePoint;
};


#endif
