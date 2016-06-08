// author: dybisz
#include "cuboid.h"

using namespace geometry;

CCuboid::CCuboid(vector<vec3> vertices) : _vertices(vertices){ }

Vertex *CCuboid::generateVertices() {
    Vertex *vertices = new Vertex[8];
    vertices[0].position = _vertices[0];
    vertices[1].position = _vertices[1];
    vertices[2].position = _vertices[2];
    vertices[3].position = _vertices[3];
    vertices[4].position = _vertices[4];
    vertices[5].position = _vertices[5];
    vertices[6].position = _vertices[6];
    vertices[7].position = _vertices[7];
    return vertices;
}

GLuint *CCuboid::generateIndices() {
    // 6 sides, each with 2 triangles created from 3 vertices
    _totalIndices = 6 * 2 * 3;
    GLuint *indices = new GLuint[6 * 2 * 3];
    int offset = 0;

    indices[offset++] = 0;
    indices[offset++] = 4;
    indices[offset++] = 5;
    indices[offset++] = 5;
    indices[offset++] = 1;
    indices[offset++] = 0;

    //top face
    indices[offset++] = 3;
    indices[offset++] = 6;
    indices[offset++] = 7;
    indices[offset++] = 3;
    indices[offset++] = 2;
    indices[offset++] = 6;

    //front face
    indices[offset++] = 7;
    indices[offset++] = 6;
    indices[offset++] = 4;
    indices[offset++] = 6;
    indices[offset++] = 5;
    indices[offset++] = 4;

    //back face
    indices[offset++] = 2;
    indices[offset++] = 3;
    indices[offset++] = 1;
    indices[offset++] = 3;
    indices[offset++] = 0;
    indices[offset++] = 1;

    //left face
    indices[offset++] = 3;
    indices[offset++] = 7;
    indices[offset++] = 0;
    indices[offset++] = 7;
    indices[offset++] = 4;
    indices[offset++] = 0;

    //right face
    indices[offset++] = 6;
    indices[offset++] = 2;
    indices[offset++]= 5;
    indices[offset++]= 2;
    indices[offset++] = 1;
    indices[offset++] = 5;

    return indices;
}

int CCuboid::getTotalVertices() {
    return 8;
}

int CCuboid::getTotalIndices() {
    return _totalIndices;
}