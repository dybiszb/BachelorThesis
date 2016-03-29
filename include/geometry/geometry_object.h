//==============================================================================
// Class introduced to separate logic of generating geometrical shapes from
// rendering them. It is highly abstract interface, which should enable
// producing set of vertices along with an order of drawing them.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef GEOMETRY_OBJECT_H
#define GEOMETRY_OBJECT_H

#include "GL/glew.h"
#include "vertex.h"

namespace geometry {

    class IGeometryObject {
    public:
        /**
         * One should implement method, which produces an array filled with
         * Vertex type objects. Vertices produced must be suitable for passing
         * into OpenGl. Vertices describe a geometry object e.g  triangle'
         * array will consist of 3 vertices, quad's from 4, cube's from 8 etc.
         * Size of the array can be obtain by calling getTotalVertices() method.
         *
         * @return Pointer to the first element of the array.
         */
        virtual Vertex *generateVertices() = 0;

        /**
         * One should implement method, which produces an array filled with
         * indices corresponding to vertices produced by generateVertices
         * method. Arrangement of array's entries  will tell OpenGl drawing
         * order of the vertices. Size of the array can be obtain by calling
         * getTotalIndices() method.
         *
         * @return Pointer to the first element of the array.
         */
        virtual GLuint *generateIndices() = 0;

        /**
         * @return Number of vertices used. Size of an array returned by
         *         generateVertices() method.
         */
        virtual int getTotalVertices() = 0;

        /**
         * @return Number of indices used. Size of an array returned by
         *         generateIndices() method.
         */
        virtual int getTotalIndices() = 0;
    };
}

#endif
