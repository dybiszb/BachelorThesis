#include "terrain_heightmap.h"

TerrainHeightMap::TerrainHeightMap(int width,
                                   int height,
                                   float accuracy) :
        Grid(width, height, accuracy) {
    _initShader();

    GLuint tex_2d = SOIL_load_OGL_texture
            (
                    "res/heightmaps/stewart-island.png",
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
                    SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
            );

    Vertex *vertices = Grid::generateVertices();
    GLuint *indices = Grid::generateIndices();
    GLsizei stride = sizeof(Vertex);

    _vao.bind();
    _vao.setVertices(Grid::getTotalVertices() * sizeof(Vertex), &vertices[0]);
    _vao.assignFloatAttribute(_shader["vVertex"], 3, stride, 0);
    _vao.assignFloatAttribute(_shader["vColor"], 3, stride,
                              (const GLvoid *) offsetof(Vertex, color));
    _vao.setIndices(Grid::getTotalIndices() * sizeof(GLuint), &indices[0]);


    delete[] vertices;
    delete[] indices;
}

TerrainHeightMap::~TerrainHeightMap() {

}

void TerrainHeightMap::render(const float *MVP) {
    _shader.Use();
    glUniformMatrix4fv(_shader("MVP"), 1, GL_FALSE, MVP);
    glDrawElements(GL_TRIANGLES, Grid::getTotalIndices(), GL_UNSIGNED_INT, 0);
    _shader.UnUse();
}

void TerrainHeightMap::_initShader() {
    _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/water.vert");
    _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/water.frag");

    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddAttribute("vVertex");
    _shader.AddAttribute("vColor");
    _shader.AddUniform("MVP");
    _shader.UnUse();
}
