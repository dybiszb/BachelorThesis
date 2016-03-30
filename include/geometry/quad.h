//==============================================================================
// TODO vetices and indices adapt to glDrawElements(GL_TRIANGLES,
// TODO CQuad::getTotalIndices(), GL_UNSIGNED_INT, 0); with vertices and
// TODO indices pinned as GL_ARRAY_BUFFER and GL_ELEMENT_ARRAY_BUFFER  respectively/
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef QUAD_H
#define QUAD_H

#include "geometry_object.h"
#include <glm/glm.hpp>
#include "vertex.h"

using namespace glm;

// TODO adapt to general case of 2 points in 3D

namespace geometry {
    class CQuad : public IGeometryObject{
    public:
        /**
         * Default: stretched between (-1, 1) and (1,-1), 0 on z axis
         */
        CQuad();
        virtual Vertex *generateVertices();
        virtual GLuint *generateIndices();
        virtual int getTotalVertices();
        virtual int getTotalIndices();
    private:
        int _totalIndices;
        int _totalVertices;
    };
}

#endif
