#ifndef BACHELOR_WATER_HEIGHTMAP_H
#define BACHELOR_WATER_HEIGHTMAP_H

#include <assert.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "renderable_object.h"
#include "vertex.h"
#include "grid.h"

using namespace rendering;
using namespace geometry;

class TerrainHeightMap : public RenderableObject,
                  public Grid {
public:
    TerrainHeightMap(int width, int height, float accuracy);

    virtual ~TerrainHeightMap();

    virtual void render(const float *MVP);
private:
    void _initShader();
};

#endif //BACHELOR_WATER_HEIGHTMAP_H
