// author: dybisz

#include "model.h"

CModel::CModel(GLchar *path) {
    _loadModel(path);
}

void CModel::render(const float *view, const float *projection) {
    for (GLuint i = 0; i < _meshes.size(); i++)
        this->_meshes[i].render(view, projection);
}

void CModel::_loadModel(string path) {
    // Read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    // Check for errors
    if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    // Retrieve the directory path of the filepath
    _directory = path.substr(0, path.find_last_of('/'));

    // Process ASSIMP's root node recursively
    _processNode(scene->mRootNode, scene);
}

void CModel::_processNode(aiNode *node, const aiScene *scene) {
    // Process each mesh located at the current node
    for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
        // The node object only contains indices to index the actual objects in the scene.
        // The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->_meshes.push_back(this->_processMesh(mesh, scene));
    }
    // After we've processed all of the meshes (if any) we then recursively process each of the children nodes
//    for(GLuint i = 0; i < node->mNumChildren; i++)
//    {
//        this->_processNode(node->mChildren[i], scene);
//    }
}

CMesh CModel::_processMesh(aiMesh *mesh, const aiScene *scene) {
    // Data to fill
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<AssimpTexture> textures;

    // Walk through each of the mesh's vertices
    for (GLuint i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        // Positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // Normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        // Texture Coordinates
        if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoord = vec;
        }
        else
            vertex.texCoord = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }
    // Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // Retrieve all indices of the face and store them in the indices vector
        for (GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // Process materials
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        // We assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'u_textureDiffuseN' where N is a sequential number ranging from 1
        // to MAX_SAMPLER_NUMBER.
        // Same applies to other texture as the following list summarizes:
        // Diffuse: u_textureDiffuseN
        // Specular: u_textureSpecularN
        // Normal: u_textureNormalN

        // 1. Diffuse maps
        vector<AssimpTexture> diffuseMaps = this->_loadMaterialTextures
                (material, aiTextureType_DIFFUSE, "u_textureDiffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. Specular maps
        vector<AssimpTexture> specularMaps = this->_loadMaterialTextures
                (material, aiTextureType_SPECULAR, "u_textureSpecular");
        textures.insert(textures.end(), specularMaps.begin(),
                        specularMaps.end());
    }

    // Return a mesh object created from the extracted mesh data
    return CMesh(vertices, indices, textures);
}

vector<AssimpTexture> CModel::_loadMaterialTextures(aiMaterial *mat,
                                                    aiTextureType type,
                                                    string typeName) {
    vector<AssimpTexture> textures;
    for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        GLboolean skip = (GLboolean) false;
        for (GLuint j = 0; j < _texturesLoaded.size(); j++) {
            if (_texturesLoaded[j].path == str) {
                textures.push_back(_texturesLoaded[j]);
                skip = (GLboolean) true;
                break;
            }
        }
        if (!skip) {
            AssimpTexture texture;
            texture.id = (GLuint) _textureFromFile(str.C_Str(), _directory);
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
            this->_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}


GLint CModel::_textureFromFile(const char *path, string directory) {
    //Generate texture ID and load texture data
    string filename = string(path);
    filename = directory + '/' + filename;
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width, height;
    unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0,
                                           SOIL_LOAD_RGB);
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    return textureID;
}