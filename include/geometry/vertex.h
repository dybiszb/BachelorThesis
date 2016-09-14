//==============================================================================
// Base class for all procedures related to sending vertex data into OpenGL.
// Structure enables neat offsetting due to its consistent memory usage.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texCoord;
};

#endif
