//==============================================================================
// TODO
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#include <sstream>
#include "mesh.h"

CMesh::CMesh(vector<Vertex> vertices, vector<GLuint> indices,
           vector<AssimpTexture> textures) : _modelMatrix(1.0) {
    _vertices = vertices;
    _indices = indices;
    _textures = textures;
    _initShader();
    _initBuffers();
}

void CMesh::render(const float *view, const float *projection) {
    _shader.Use();
    _vao.bind();
    _vao.bindBuffers();

    /* ----- Bind All Textures ----- */
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    for(GLuint i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        stringstream ss;
        string number;
        string name = _textures[i].type;
        if(name == "u_textureDiffuse")
            ss << diffuseNr++;
        else if(name == "u_textureSpecular")
            ss << specularNr++;
        number = ss.str();

        /* ----- Samplers and Binding ----- */
        glUniform1i(_shader((name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, _textures[i].id);
    }

    /* ----- Bind Other Uniforms ----- */
    glUniformMatrix4fv(_shader("u_modelMatrix"), 1, GL_FALSE, & _modelMatrix[0][0]);
    glUniformMatrix4fv(_shader("u_viewMatrix"), 1, GL_FALSE, view);
    glUniformMatrix4fv(_shader("u_projectionMatrix"), 1, GL_FALSE, projection);

    /* ----- Draw Mesh ----- */
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

    /* ----- Unbind Textures ----- */
    for (GLuint i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    _vao.unbindBuffers();
    _vao.unbind();
    _shader.UnUse();
}

void CMesh::setModelMatrix(mat4& modelMatrix) {
    _modelMatrix = modelMatrix;
}

void CMesh::_mapTexturesOntoUniforms() {
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    for (GLuint i = 0; i < _textures.size(); i++) {
        stringstream ss;
        string number;
        string name = _textures[i].type;
        if (name == "u_textureDiffuse")
            ss << diffuseNr++;
        else if (name == "u_textureSpecular")
            ss << specularNr++;
        number = ss.str();
        _shader.AddUniform((name + number).c_str());
    }
}

void CMesh::_initShader() {
    _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/mesh.vert");
    _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/mesh.frag");
    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddUniform("u_modelMatrix");
    _shader.AddUniform("u_viewMatrix");
    _shader.AddUniform("u_projectionMatrix");
    _mapTexturesOntoUniforms();
    _shader.UnUse();
}

void CMesh::_initBuffers() {
    _vao.setBuffer("vertex_buffer", GL_ARRAY_BUFFER);
    _vao.setBuffer("index_buffer", GL_ELEMENT_ARRAY_BUFFER);
    _vao.bind();

    CBuffer *vbo = _vao.getBuffer("vertex_buffer");
    vbo->bind();
    vbo->setDataStatic(_vertices.size() * sizeof(Vertex), &_vertices[0]);

    _vao.assignFloatAttribute(0, 3, sizeof(Vertex),
                              (GLvoid *) 0);
    _vao.assignFloatAttribute(1, 3, sizeof(Vertex),
                              (GLvoid *) offsetof(Vertex, normal));
    _vao.assignFloatAttribute(2, 3, sizeof(Vertex),
                              (GLvoid *) offsetof(Vertex, texCoord));

    CBuffer *ibo = _vao.getBuffer("index_buffer");
    ibo->bind();
    ibo->setDataStatic(_indices.size() * sizeof(GLuint), &_indices[0]);

    _vao.unbind();
}