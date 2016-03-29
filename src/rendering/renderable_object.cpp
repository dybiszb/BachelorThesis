// author: dybisz

#include "renderable_object.h"

using namespace rendering;

CRenderableObject::~CRenderableObject() {
    _shader.DeleteShaderProgram();
}
