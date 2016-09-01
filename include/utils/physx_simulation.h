//==============================================================================
// Builder pattern implementation. TODO finish
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

static PxDefaultErrorCallback gDefaultErrorCallback;
static PxDefaultAllocator gDefaultAllocatorCallback;

class PhysXSimulation {
public:
    PhysXSimulation();
    ~PhysXSimulation();
    void update(vec3& point, float forceB, vec3& forceMove, vec3& movePoint);
    void addBox(vec3& position);
    mat4 getTransformation();
    void setLinearDamping(float linearDamping);
    void setAngularDamping(float angularDamping);
    vec3 getActorPose();
private:
    PxFoundation* _foundation;
    PxPhysics* _sdk;
    PxScene* _scene;
    PxMaterial* _material;
    PxRigidDynamic* _actor;
    PxVec3* _buyoancyForce;
    PxVec3* _buyoancyPosition;
    PxVec3* _movementForce;
    PxVec3* _movementPosition;
    PxReal _timeStamp;

    void _physXMat4ToGlmMat4(const PxMat44& mat4,glm::mat4& newMat);
};


#endif
