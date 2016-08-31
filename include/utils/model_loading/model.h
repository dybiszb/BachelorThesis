//==============================================================================
// TODO
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
#include "assimp_texture.h"
#include <src/SOIL.h>

#pragma comment(lib, "assimp-vc140-mt.lib")

using namespace std;

class CModel
{
public:
    CModel(GLchar* path);
    void render(const float *view, const float *projection);
private:
    vector<CMesh> _meshes;
    string _directory;
    vector<AssimpTexture> _texturesLoaded;

    void _loadModel(string path);
    void _processNode(aiNode* node, const aiScene* scene);
    CMesh _processMesh(aiMesh* mesh, const aiScene* scene);
    vector<AssimpTexture> _loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                                string typeName);
    GLint _textureFromFile(const char* path, string directory);
};


#endif
