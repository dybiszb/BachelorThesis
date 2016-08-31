//==============================================================================
// In case of loading models using assimp library one does not want to carry
// sophisticated objects of texture between render calls. Instead following
// simple struct has been created. It includes only id type and path.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef TEXTURE_STRUCT_H
#define TEXTURE_STRUCT_H

#include<string>
#include <GL/glew.h>
#include "assimp/types.h"

using namespace std;

struct AssimpTexture {
    GLuint id;
    string type;
    aiString path;
};

#endif
