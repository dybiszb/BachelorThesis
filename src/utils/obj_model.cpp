// author: dybisz

#include <tiny_obj_loader.h>
#include "obj_model.h"

using namespace rendering;

COBJModel::COBJModel(string directory, string objName)
        : _directory(directory),
          _objName(objName),
          _modelMatrix(1.0f) {
    _loadShapesAndMaterials();
    _createTexturesFromImages();
    _createBuffers();
    _loadDataToBuffers();
    _initializeShaderProgram();
}

COBJModel::~COBJModel() {
    delete _verticesBuffer;
    delete _indicesBuffer;
    delete _texCoordBuffer;
    _shader.DeleteShaderProgram();
    for (auto &texture : _textures) delete texture;
}

void COBJModel::render(const float *view,
                    const float *projection) {
    glDisable(GL_CULL_FACE);
    _shader.Use();
    _vao.bind();
    _indicesBuffer->bind();

    glUniformMatrix4fv(_shader("model"), 1, GL_FALSE, &_modelMatrix[0][0]);
    glUniformMatrix4fv(_shader("view"), 1, GL_FALSE, view);
    glUniformMatrix4fv(_shader("projection"), 1, GL_FALSE, projection);
    glUniform1iARB(_shader("texture_diffuse"), 3);

    // Attributes
    size_t verticesOffset = 0;
    size_t texCoordOffset = 0;
    size_t indicesOffset = 0;

    for (int i = 0; i < _shapes.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + 3);

        int texIndex = _shapes[i].mesh.material_ids[0];
        _textures[texIndex]->bind();

        /* ----- Attach Vertices(layout = 0) ----- */
        glEnableVertexAttribArray(0);
        _verticesBuffer->bind();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              0, (void *) verticesOffset);

        /* ----- Attach Textures (layout = 1) ----- */
        glEnableVertexAttribArray(1);
        _texCoordBuffer->bind();
        glVertexAttribPointer(1, 2, GL_FLOAT,
                              GL_FALSE,
                              0, (void *) texCoordOffset);

        /* ----- Draw a Shape ----- */
        glDrawElements(GL_TRIANGLES, _shapes[i].mesh.indices.size(),
                       GL_UNSIGNED_INT, (void *) indicesOffset);

        verticesOffset += sizeof(float) * _shapes[i].mesh.positions.size();
        texCoordOffset += sizeof(float) * _shapes[i].mesh.texcoords.size();
        indicesOffset += sizeof(unsigned int) * _shapes[i].mesh.indices.size();

        _textures[texIndex]->unbind();
        checkErrorOpenGL("COBJModel - draw loop");
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    _texCoordBuffer->unbind();
    _verticesBuffer->unbind();
    _indicesBuffer->unbind();
    _vao.unbind();
    _shader.UnUse();
    glEnable(GL_CULL_FACE);
}

void COBJModel::setModelMatrix(mat4 modelMatrix) {
    _modelMatrix = modelMatrix;
}

void COBJModel::_loadShapesAndMaterials() {
    string errorMessage;

    if (!tinyobj::LoadObj(_shapes, _materials, errorMessage, _objName.c_str(),
                          _directory.c_str())) {
        cerr << errorMessage << endl;
    }

    if (_moreThanOneMaterialPerShape(errorMessage)) {
        cerr << errorMessage << endl;
    }
}

bool COBJModel::_moreThanOneMaterialPerShape(string &errorMessage) {
    for (auto &shape : _shapes) {
        if (adjacent_find(shape.mesh.material_ids.begin(),
                          shape.mesh.material_ids.end(),
                          std::not_equal_to<int>())
            != shape.mesh.material_ids.end()) {
            errorMessage +=
                    "There is more than one material assigned to a shape";
            return true;
        }
    }
    return false;
}

void COBJModel::_createTexturesFromImages() {
    for (auto &material : _materials) {
        if(material.diffuse_texname.size() > 0) {
            string path = _directory + "/" + material.diffuse_texname;
            _textures.push_back(new CTexture2D(path));
        }
        else {
            _textures.push_back(new CTexture2D(1,1));
        }
    }
}

void COBJModel::_createBuffers() {
    _vao.bind();
    _verticesBuffer = new CBuffer(GL_ARRAY_BUFFER);
    _indicesBuffer = new CBuffer(GL_ELEMENT_ARRAY_BUFFER);
    _texCoordBuffer = new CBuffer(GL_ARRAY_BUFFER);
}

void  COBJModel::_loadDataToBuffers() {
    _vao.bind();
    int verticesBufferSize = 0;
    int indicesBufferSize = 0;
    int texCoordBufferSize = 0;
    int offset = 0;
    for (int i = 0; i < _shapes.size(); i++) {
        verticesBufferSize += sizeof(float) * _shapes[i].mesh.positions.size();
        indicesBufferSize += sizeof(unsigned int) * _shapes[i].mesh.indices.size();
        texCoordBufferSize += sizeof(float) * _shapes[i].mesh.texcoords.size();
    }

    /* ---- Upload Vertices Data ----- */
    _verticesBuffer->bind();
    _verticesBuffer->setDataStatic(verticesBufferSize, NULL);
    offset = 0;

    for (int i = 0; i < _shapes.size(); i++) {
        int chunkSize = sizeof(float) * _shapes[i].mesh.positions.size();
        _verticesBuffer->setSubData(offset, chunkSize, &_shapes[i].mesh.positions[0]);
        offset += chunkSize;
    }

    _verticesBuffer->unbind();
    checkErrorOpenGL("COBJModel - uploading vertex data");

    /* ----- Upload TexCoord Data ----- */
    _texCoordBuffer->bind();
    _texCoordBuffer->setDataStatic(texCoordBufferSize, NULL);
    offset = 0;

    for (int i = 0; i < _shapes.size(); i++) {
        int chunkSize = sizeof(float) * _shapes[i].mesh.texcoords.size();
        _texCoordBuffer->setSubData(offset, chunkSize, &_shapes[i].mesh.texcoords[0]);
        offset += chunkSize;
    }

    _texCoordBuffer->unbind();
    checkErrorOpenGL("COBJModel - uploading texCoord data");

    /* ----- Upload Indices Data ---- */
    _indicesBuffer->bind();
    _indicesBuffer->setDataStatic(indicesBufferSize, NULL);
    offset = 0;

    for (int i = 0; i < _shapes.size(); i++) {
        int chunkSize = sizeof(unsigned int) * _shapes[i].mesh.indices.size();
        _indicesBuffer->setSubData(offset, chunkSize, &_shapes[i].mesh.indices[0]);
        offset += chunkSize;
    }
    _indicesBuffer->unbind();
    checkErrorOpenGL("COBJModel - uploading indices data2");
}

void COBJModel::_getBuffersSizes(int *verticesSize, int *indicesSize,
                                 int *texCoordSize) {
    for (int i = 0; i < _shapes.size(); i++) {
        *verticesSize += sizeof(float) * _shapes[i].mesh.positions.size();
        *indicesSize += sizeof(unsigned int) * _shapes[i].mesh.indices.size();
        *texCoordSize += sizeof(float) * _shapes[i].mesh.texcoords.size();
    }
}

void COBJModel::_initializeShaderProgram() {
    _shader.LoadFromFile(GL_VERTEX_SHADER, "res/shaders/f15.vert");
    _shader.LoadFromFile(GL_FRAGMENT_SHADER, "res/shaders/f15.frag");
    _shader.CreateAndLinkProgram();

    _shader.Use();
    _shader.AddUniform("texture_diffuse");
    _shader.AddAttribute("position");
    _shader.AddUniform("model");
    _shader.AddUniform("view");
    _shader.AddUniform("projection");
    _shader.UnUse();
}

