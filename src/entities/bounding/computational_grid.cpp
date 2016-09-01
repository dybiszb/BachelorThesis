// author: dybisz
#include <glm/gtc/matrix_transform.hpp>
#include "computational_grid.h"


CComputationalGrid::CComputationalGrid() :
        _modelMatrix(mat4(1.0)) {

    for (auto cell : mediumAccuracyFishingBoat) {
        _mass += 1.0;
        simulation.addBox(cell);
        _cells.push_back(new CComputationalCell(cell));
    }
}

CComputationalGrid::~CComputationalGrid() {
    for (auto cell : _cells) delete cell;
}

void CComputationalGrid::render(const float *view, const float *projection) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (auto cell : _cells) {
        cell->setModelMatrix(_modelMatrix);
        cell->render(view, projection);
    }
    glDisable(GL_BLEND);
}

void CComputationalGrid::updateHeightField(GLfloat *textureAsArray,
                                           float width,
                                           float height, float edgeSize) {
    float ratio = edgeSize / width;
    float immersedMass = 0.0;
    std::map<float, float> b_x_map;
    std::map<float, float> b_y_map;
    std::map<float, float> b_z_map;

    for (auto cell : _cells) {
        vec3 cellCenter = cell->getCenter();
        vec4 scaledCenter = _modelMatrix * vec4(cellCenter, 1.0);
        int tex_u = (int) ((scaledCenter.x / ratio) + (width / 2.0));
        int tex_v = (int) ((scaledCenter.z / ratio) + (height / 2.0));
        float h = textureAsArray[int((tex_v * (width + 1)) + tex_u) * 4];
        cell->setImmersion(h, scaledCenter.y);

        if (cell->isImmersed()) {
            b_x_map[cellCenter.x] += cell->getImmersion();
            b_y_map[cellCenter.y] += cell->getImmersion();
            b_z_map[cellCenter.z] += cell->getImmersion();
            immersedMass += 1.0;
        }
    }

    float b_x = 0;
    float b_y = 0;
    float b_z = 0;
    float oceanWaterDensity =  1.027;

    for(int i = 0; i < 30; i++) {
        b_x += b_x_map[i] * oceanWaterDensity * ( 0.1 * i);
        b_y += b_y_map[i] * oceanWaterDensity * ( 0.1 * i);
        b_z += b_z_map[i] * oceanWaterDensity * ( 0.1 * i);
    }
    float b_force = 25.0f * oceanWaterDensity * immersedMass * 9.81f;
    delete textureAsArray;
    vec3 pointB = vec3(b_x / _mass, b_y / _mass, b_z /_mass);
    simulation.update(pointB, b_force, _moveForce, _movePoint);
    _modelMatrix = simulation.getTransformation();
}

mat4 CComputationalGrid::getTransformation() {
    return simulation.getTransformation();
}

vec3 CComputationalGrid::getShipPosition() {
    return simulation.getActorPose();
}

void CComputationalGrid::setLinearDamping(float linearDamping) {
    simulation.setLinearDamping(linearDamping);
}
void CComputationalGrid::setAngularDamping(float angularDamping) {
    simulation.setAngularDamping(angularDamping);
}

void CComputationalGrid::setMovementForce(const vec3& movementForce) {
    _moveForce = movementForce;
}
void CComputationalGrid::setMovementPoint(const vec3& movementPoint) {
    _movePoint = movementPoint;
}