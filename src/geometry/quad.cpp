// author: dybisz

#include "quad.h"

using namespace geometry;

/**
 * stretch between specified points
 */
CQuad::CQuad() {

}

Vertex * CQuad::generateVertices() {
    _totalVertices = 4;
    Vertex *vertices = new Vertex[_totalVertices];

    vertices[0].position = vec3(-1,1,0);
    vertices[0].texCoord = vec2(0,1);

    vertices[1].position = vec3(-1,-1,0);
    vertices[1].texCoord = vec2(0,0);

    vertices[2].position = vec3(1,1,0);
    vertices[2].texCoord = vec2(1,1);

    vertices[3].position = vec3(1,-1,0);
    vertices[3].texCoord = vec2(1,0);

    return vertices;
}

GLuint * CQuad::generateIndices() {
    _totalIndices = 2 * 3;
    GLuint *indices = new GLuint[_totalIndices];

    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 1;
    indices[5] = 3;

    return indices;
}

int CQuad::getTotalVertices() {
    return _totalVertices;
}

int CQuad::getTotalIndices() {
    return _totalIndices;
}