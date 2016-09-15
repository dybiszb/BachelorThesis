// author: dybisz

#include "grid.h"
#include <iostream>

using namespace geometry;

CGrid::CGrid(int quadsOnX, int quadsOnZ, float gridSizeOnX, float gridSizeOnZ,
             glm::vec2 bottomCorner)
        :
        _quadsOnX(quadsOnX),
        _quadsOnZ(quadsOnZ),
        _gridSizeOnX(gridSizeOnX),
        _gridSizeOnZ(gridSizeOnZ),
        _bottomCorner(bottomCorner) { }

Vertex *CGrid::generateVertices() {

    _totalVertices = (_quadsOnX + 1) * (_quadsOnZ + 1);
    Vertex *vertices = new Vertex[_totalVertices];
    int vertIndex = 0;

    for (int x = 0; x <= _quadsOnZ; ++x) {
        for (int z = 0; z <= _quadsOnX; ++z) {

            /* ----- Position ----- */
            float stepOnX = float(x) / _quadsOnX;
            float stepOnZ = float(z) / _quadsOnZ;

            vertices[vertIndex].position =
                    glm::vec3(stepOnX * _gridSizeOnX + _bottomCorner.x,
                              0,
                              stepOnZ * _gridSizeOnZ + _bottomCorner.y);

            /* ----- Color ----- */
            vertices[vertIndex].color = glm::vec3(0,
                                                  0,
                                                  1.0f);
            /* ----- Texture Coordinates ----- */
            vertices[vertIndex].texCoord = glm::vec2(stepOnX, stepOnZ);

            vertIndex++;
        }
    }
    return vertices;
}

GLuint *CGrid::generateIndices() {
    _totalIndices = (_quadsOnX) * (_quadsOnZ) * 2 * 3;
    GLuint *indices = new GLuint[_totalIndices];

    int indicesIndex = 0;
    for (int y = 0; y < (_quadsOnZ); ++y) {
        for (int x = 0; x < (_quadsOnX); ++x) {
            GLuint start = (GLuint) (y * (_quadsOnX + 1) + x);
            indices[indicesIndex++] = (GLuint) start;
            indices[indicesIndex++] = (GLuint) (start + 1);
            indices[indicesIndex++] = (GLuint) (start + (_quadsOnX + 1));
            indices[indicesIndex++] = (GLuint) (start + 1);
            indices[indicesIndex++] = (GLuint) (start + 1 + (_quadsOnX + 1));
            indices[indicesIndex++] = (GLuint) (start + (_quadsOnX + 1));
        }
    }
    return indices;
}

int CGrid::getTotalVertices() {
    return _totalVertices;
}

int CGrid::getTotalIndices() {
    return _totalIndices;
}