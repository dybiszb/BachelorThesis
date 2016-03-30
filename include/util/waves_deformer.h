//==============================================================================
// TODO underline that this is kind of double frame buffer, which renders
// TODO stuff offscreen hence it has to have some association with renderable
// TODO object
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef WAVES_DEFORMER_H
#define WAVES_DEFORMER_H

#include <GL/glew.h>
#include "buffers/frame_buffer.h"
#include "textures/texture2D.h"
#include "glsl_shader.h"
#include "vertex_array.h"
#include "vertex.h"
#include "quad.h"
#include "error_handling.h"

using namespace rendering;
using namespace geometry;
using namespace util;

class CWavesDeformer{

public:
    // input # vertices in row & column !!!
    CWavesDeformer(int width, int height);

    ~CWavesDeformer();
    void renderStep();
private:
    GLsizei _width;
    GLsizei _height;
    CFrameBuffer *_fbo1;
    CFrameBuffer *_fbo2;
    CTexture2D *_tex1;
    CTexture2D *_tex2;
    GLSLShader _shader;
    CVertexArray _vao;
    CQuad _quad;

    void _initShaders();
};


#endif
