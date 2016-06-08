//==============================================================================
// TODO
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
         *
         * @param 8 vertices
         */
        CCuboid(vector<vec3> vertices);
        /**
         * TODO
         *
         * @return Pointer to the first element of the array.
         */
        Vertex *generateVertices();

        /**
         *  TODO
         *
         * @return Pointer to the first element of the array.
         */
        GLuint *generateIndices();

        /**
         * @return Number of vertices used to produce the cuboid.
         */
        int getTotalVertices();

        /**
         * @return Number of indices used to produce the cuboid.
         */
        int getTotalIndices();

    private:
        vector<vec3> _vertices;
        int   _totalIndices;
    };
}

#endif
