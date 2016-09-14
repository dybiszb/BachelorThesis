//==============================================================================
// Class in charge of creating cuboid. It is only useful to produce vertices
// with appropriate indexing. Such information can be later on supplied into
// Vertex Array Object to render the shape.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef CUBOID_H
#define CUBOID_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "vertex.h"
#include "geometry_object.h"

using namespace std;
using namespace glm;

namespace geometry {
    class CCuboid : public IGeometryObject{
    public:
        /**
         * @param vertices 8 vertices that defines a cuboid in its local
         *                 coordinates.
         */
        CCuboid(vector<vec3> vertices);

        /**
         * @return Pointer to the first element of the array containing
         *         cuboids vertices packed in Vertex struct.
         */
        Vertex *generateVertices();

        /**
         * @return Pointer to the first element of the array containing
         *         indices for vertices generated via generateVertices
         *         procedure.
         */
        GLuint *generateIndices();

        /**
         * @return Number of vertices used to produce cuboid.
         */
        int getTotalVertices();

        /**
         * @return Number of indices used to produce cuboid.
         */
        int getTotalIndices();

    private:
        vector<vec3> _vertices;
        int          _totalIndices;
    };
}

#endif
