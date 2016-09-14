//==============================================================================
// The following class encapsulates calculations perform by PhysX library.
// Mirror representation of the computational grid is loaded in the library
// and one is able to change the two acting forces: buoyancy and movement.
// Via update method, simulation step can be computed and getTransformation
// along with getActorPose enables to acquire grid's current transformation and
// pose, respectively.
//
// NOTE: Private methods, as an internal part of the class rather than public
//       interface, are not commented.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef PHYSX_SIMULATION_H
#define PHYSX_SIMULATION_H

#pragma comment(lib, "PhysX3_x86.lib")
#pragma comment(lib, "PhysX3Common_x86.lib")
#pragma comment(lib, "PhysX3Extensions.lib")

#define PX_WINDOWS
#define NDEBUG

#include <PxPhysicsAPI.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

using namespace physx;
using namespace std;
using namespace glm;

// PhysX's way of handling errors. Needed to initialize the library.
static PxDefaultErrorCallback gDefaultErrorCallback;
// PhysX's-specific allocator. Needed to initialize the library.
static PxDefaultAllocator gDefaultAllocatorCallback;

class PhysXSimulation {
public:
    ~PhysXSimulation();

    /**
     * In general the procedure initializes a PhysX's scene.
     * In particular sdk, scene description, scene and actor objects are
     * set to their default values.
     */
    PhysXSimulation();

    /**
     * Updates the forces and performs next step of the simulation.
     *
     * @param pointB    Point of applying buoancy force.
     * @param forceB    Since buoyancy force direction is always upward only
     *                  its magnitude is needed.
     * @point forceMove Direction of a movement.
     * @point pointMove Point of applying movement force.
     */
    void update(vec3 &pointB, float forceB, vec3 &forceMove, vec3 &pointMove);

    /**
     * Since PhysX must mirror the computational grid, following procedure
     * allows one to extend the scene's actor via default box. In this way,
     * the actor can be set along loading particular boxes of the grid.
     * As experiments showed, PhysX must load a little bit bigger boxes that
     * the grid assumes. Their dimensions are 1.14 x 1.14 x 1.14 instead of
     * default 1 x 1 x 1.
     *
     * @param position Center of the box that one wants to add to the scene's
     *                 actor (local coordinates).
     */
    void addBox(vec3 &position);

    /**
     * Retrieves current transformation of the actor. It can be used to
     * update e.g. a model that the actor simulates.
     *
     * @return A matrix with all transformations of the actor.
     */
    mat4 getTransformation();

    /**
     * Retrieves current position of the actor. It can be used to
     * update e.g. a model that the actor simulates.
     *
     * @return A vector with the actor translation.
     */
    vec3 getActorPose();

    /**
     * Update linear dumping threshold.
     *
     * @param linearDumping New value of linear dumping of the actor
     */
    void setLinearDamping(float linearDamping);

    /**
     * Update angular dumping threshold.
     *
     * @param angularDamping New value of angular dumping of the actor.
     */
    void setAngularDamping(float angularDamping);

private:
    PxFoundation*   _foundation;
    PxPhysics*      _sdk;
    PxScene*        _scene;
    PxMaterial*     _material;
    PxRigidDynamic* _actor;
    PxVec3*         _buyoancyForce;
    PxVec3*         _buyoancyPosition;
    PxVec3*         _movementForce;
    PxVec3*         _movementPosition;
    PxReal          _timeStamp;

    void _physXMat4ToGlmMat4(const PxMat44 &mat4, glm::mat4 &newMat);
};


#endif
