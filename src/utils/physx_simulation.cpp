// autohor: dybisz

#include "physx_simulation.h"
#include "glm/ext.hpp"

PhysXSimulation::PhysXSimulation() : _timeStamp(1.0f / 60.0f) {
    _foundation = PxCreateFoundation(PX_PHYSICS_VERSION,
                                     gDefaultAllocatorCallback,
                                     gDefaultErrorCallback);
    _sdk = PxCreatePhysics(PX_PHYSICS_VERSION, *_foundation, PxTolerancesScale());
    if (_sdk == NULL) {
        cerr << "Error creating PhysX3 device, Exiting..." << endl;
        exit(1);
    }

    PxSceneDesc sceneDesc(_sdk->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
    sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
    sceneDesc.filterShader = PxDefaultSimulationFilterShader;
    _scene = _sdk->createScene(sceneDesc);
    _buyoancyForce = new PxVec3(0.0, 0.0, 0.0);
    _buyoancyPosition = new PxVec3(0.0, 0.0, 0.0);
    _movementForce = new PxVec3(0.0, 0.0, 0.0);
    _movementPosition = new PxVec3((PxReal) -15.0, 1.0, 0);
    _material = _sdk->createMaterial(0.05, 0.05, 0.05);
    _actor = _sdk->createRigidDynamic(PxTransform(PxVec3(-10.f, -2.0f, 0.f)));
    _actor->setMass(0.0f);
    _actor->setLinearDamping(2.0);
    _actor->setAngularDamping(6.0);
    _scene->addActor(*_actor);
}

PhysXSimulation::~PhysXSimulation() {
    _actor->release();
    _material->release();
    _scene->release();
    _sdk->release();
    _foundation->release();
}

void PhysXSimulation::update(vec3 &pointB, float forceB, vec3 &forceMove, vec3& movePoint) {
    // Set new B force
    (*_buyoancyForce).y = forceB;
    (*_buyoancyPosition).x = pointB.x;
    (*_buyoancyPosition).y = pointB.y;
    (*_buyoancyPosition).z = pointB.z;

    // Set new movement Force
    (*_movementForce).x = -forceMove.x;
    (*_movementForce).y = forceMove.y;
    (*_movementForce).z = -forceMove.z;

    (*_movementPosition).x = -15.0f;
    (*_movementPosition).y = 0.0f;
    (*_movementPosition).z = 0.0f;

    // Contra Force
    PxVec3 cForce;
    cForce.x = 15.0f;
    cForce.y = 0.0f;
    cForce.z = 0.0f;



    // Apply Forces
    PxRigidBodyExt::updateMassAndInertia(*_actor, 10.5f);
    PxRigidBodyExt::addForceAtLocalPos(*_actor, *_buyoancyForce,
                                  *_buyoancyPosition, PxForceMode::eFORCE, true);
    PxRigidBodyExt::addLocalForceAtLocalPos(*_actor, *_movementForce,
                                            *_movementPosition,
                                            PxForceMode::eFORCE, true);
    PxRigidBodyExt::addLocalForceAtLocalPos(*_actor, PxVec3(0.0f,
            0.0f, forceMove.z),
                                  cForce,
                                  PxForceMode::eFORCE, true);


    // Simulate Scene
    _scene->simulate(_timeStamp);
    _scene->fetchResults(true);


}

void PhysXSimulation::addBox(vec3& position) {
    _actor->createShape(PxBoxGeometry(0.57, 0.57, 0.57), *_material, PxTransform
            (position.x, position.y, position.z));
    _actor->setMass(_actor->getMass() + 10.0f);
}

mat4 PhysXSimulation::getTransformation() {
    PxMat44 currentTransform = (PxMat44) _actor->getGlobalPose();
    mat4 returnMat;
    _physXMat4ToGlmMat4(currentTransform, returnMat);
    return returnMat;
}

void PhysXSimulation::setLinearDamping(float linearDamping) {
    _actor->setLinearDamping(linearDamping);
}

void PhysXSimulation::setAngularDamping(float angularDamping) {
    _actor->setAngularDamping(angularDamping);
}

vec3 PhysXSimulation::getActorPose() {
    PxTransform actorPose = _actor->getGlobalPose();
    vec3 pose;
    pose.x = actorPose.p.x;
    pose.y = actorPose.p.y;
    pose.z = actorPose.p.z;
    return pose;
}

void PhysXSimulation::_physXMat4ToGlmMat4(const PxMat44 &mat4, glm::mat4 &newMat) {

    newMat[0][0] = mat4[0][0];
    newMat[0][1] = mat4[0][1];
    newMat[0][2] = mat4[0][2];
    newMat[0][3] = mat4[0][3];

    newMat[1][0] = mat4[1][0];
    newMat[1][1] = mat4[1][1];
    newMat[1][2] = mat4[1][2];
    newMat[1][3] = mat4[1][3];

    newMat[2][0] = mat4[2][0];
    newMat[2][1] = mat4[2][1];
    newMat[2][2] = mat4[2][2];
    newMat[2][3] = mat4[2][3];

    newMat[3][0] = mat4[3][0];
    newMat[3][1] = mat4[3][1];
    newMat[3][2] = mat4[3][2];
    newMat[3][3] = mat4[3][3];

}