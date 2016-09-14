//==============================================================================
// Class in charge of creating quad. It is only useful to produce vertices
// with appropriate indexing. Such information can be later on supplied into
// Vertex Array Object to render the shape.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef QUAD_H
#define QUAD_H

#include <glm/glm.hpp>
#include "geometry_object.h"
#include "vertex.h"

using namespace glm;

namespace geometry {
    class CQuad : public IGeometryObject{
    public:
        /**
         * Creates a square, stretched between (-1, 1) and (1,-1) that lies
         * entirely on XY plane.
         */
        CQuad();

        /**
         * @return Pointer to the first element of the array containing
         *         quad vertices packed in Vertex struct.
         */
        virtual Vertex *generateVertices();

        /**
         * @return Pointer to the first element of the array containing
         *         indices for vertices generated via generateVertices
         *         procedure.
         */
        virtual GLuint *generateIndices();

        /**
         * @return Number of vertices used to produce the quad.
         */
        virtual int getTotalVertices();

        /**
         * @return Number of indices used to produce the quad.
         */
        virtual int getTotalIndices();

    private:
        int _totalIndices;
        int _totalVertices;
    };
}

#endif
