//==============================================================================
// TODO
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "assimp_texture.h"
#include "vertex.h"
#include "renderable_object.h"
#include "vertex_array.h"

using namespace rendering;
using namespace std;
using namespace glm;

class CMesh : public CRenderableObject {
public:
    CMesh(vector<Vertex> vertices,
         vector<GLuint> indices,
         vector<AssimpTexture> textures);

    void render(const float *view, const float *projection);
    void setModelMatrix(mat4 &modelMatrix);

private:
    vector<Vertex> _vertices;
    vector<GLuint> _indices;
    vector<AssimpTexture> _textures;
    mat4 _modelMatrix;
    CVertexArray vao;

    /**
     * Internal vector with textures holds AssimpTexture objects.
     * Each one of them can be identified either as a diffuse or specular
     * texture. Following procedure
     */
    void _mapTexturesOntoUniforms();

    /**
     * Loads a shader from file and compiles it. All attributes and uniforms
     * used by the class are defined.
     */
    void _initShader();

    /**
     * Initializes vertex array object with vertices and indices buffers.
     */
    void _initBuffers();

};


#endif
