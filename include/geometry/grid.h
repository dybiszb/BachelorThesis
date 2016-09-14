//==============================================================================
// Class in charge of creating rectangular, tessellated grid.
// It is only useful to produce vertices with appropriate indexing.
// such information can be later on supplied into Vertex Array Object to
// render the shape.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef GRID_H
#define GRID_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "vertex.h"
#include "geometry_object.h"

namespace geometry {

    class CGrid : public IGeometryObject {
    public:
        /**
         * Enables to specify size of the grind in world space and its
         * accuracy (via number of quads on  each axis. What is more one can
         * position the shape specifying its bottom corner (vertices will be
         * shifted accordingly).
         *
         * @param quadsOnX      How many quads on X axis.
         * @param quadsOnZ      How many quads on Z axis.
         * @param gridSizeX     Grid length on X in world space
         * @param gridSizeZ     Grid length on Z in world space
         * @param bottomCorner  Bottom corner of the grid on XZ plane
         */
        CGrid(int quadsOnX,
             int quadsOnZ,
             float gridSizeX,
             float gridSizeZ,
             glm::vec2 bottomCorner);

        /**
         * According to private members set in the constructor, it produces
         * a dynamically allocated array of type Vertex. Vertices constitutes
         * a base for the tessellated grid.
         * Size of the array can be obtain by calling getTotalVertices() method.
         *
         * @return Pointer to the first element of the array.
         */
        virtual Vertex *generateVertices();

        /**
         * According to private members set in the constructor, it produces
         * a dynamically allocated array of type GLuint. The array is filled with
         * indices corresponding to vertices produced by generateVertices() method.
         * They are arranged in a way that OpenGl can draw triangles, which form
         * the grid (normally glDrawElements should be called with GL_TRIANGLES
         * parameters).
         * Size of the array can be obtain by calling getTotalIndices() method.
         *
         * @return Pointer to the first element of the array.
         */
        virtual GLuint *generateIndices();

        /**
         * @return Number of vertices used to produce the grid.
         */
        virtual int getTotalVertices();

        /**
         * @return Number of indices used to produce the grid.
         */
        virtual int getTotalIndices();

    protected:
        int       _totalIndices;
        int       _totalVertices;
        int       _quadsOnX;
        int       _quadsOnZ;
        float     _gridSizeOnX;
        float     _gridSizeOnZ;
        glm::vec2 _bottomCorner;
    };
}

#endif
