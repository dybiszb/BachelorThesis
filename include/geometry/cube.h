//==============================================================================
// Class in charge of creating cube. It is only useful to produce vertices
// with appropriate indexing. Such information can be later on supplied into
// Vertex Array Object to render the shape.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include "vertex.h"
#include "geometry_object.h"

namespace geometry {

    class CCube : public IGeometryObject {
    public:
        /**
         *
         * @param Size of the cube's edges.
         */
        CCube(int size);
        /**
         * TODO
         *
         * @return Pointer to the first element of the array.
         */
        virtual Vertex *generateVertices();

        /**
         *  TODO
         *
         * @return Pointer to the first element of the array.
         */
        virtual GLuint *generateIndices();

        /**
         * @return Number of vertices used to produce the cube.
         */
        virtual int getTotalVertices();

        /**
         * @return Number of indices used to produce the cube.
         */
        virtual int getTotalIndices();

    private:
        int   _totalIndices;
        int   _size;
    };

}
#endif
