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
#include <vector>
#include <glm/glm.hpp>
#include "vertex.h"
#include "geometry_object.h"

using namespace glm;
using namespace std;

namespace geometry {

    class CCube : public IGeometryObject {
    public:
        /**
         * @param size Size of a cube's edges.
         */
        CCube(float size);

        /**
         * @param center Center of a cube. Vertices will be calculated
         *               accordingly with usage of side length.
         * @param size   Size of the cube's edges.
         */
        CCube(vec3 center, float size=1.0);

        /**
         * @return Pointer to the first element of the array containing
         *         cube vertices packed in Vertex struct.
         */
        virtual Vertex *generateVertices();

        /**
         * @return Pointer to the first element of the array containing
         *         indices for vertices generated via generateVertices
         *         procedure.
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

    protected:
        vec3  _vertices = vec3(0.0);
        float _size;

    private:
        int   _totalIndices;
    };

}
#endif
