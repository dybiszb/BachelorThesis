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

using namespace rendering;

class CWavesDeformer {

public:
    CWavesDeformer(int width, int height);

    ~CWavesDeformer();

private:
    GLsizei _width;
    GLsizei _height;
    CFrameBuffer *_fbo1;
    CFrameBuffer *_fbo2;
    CTexture2D *_tex1;
    CTexture2D *_tex2;
};


#endif
