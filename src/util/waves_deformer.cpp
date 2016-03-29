// author: dybisz

#include "waves_deformer.h"

CWavesDeformer::CWavesDeformer(int width, int height) : _width(width),
                                                        _height(height) {
    _fbo1 = new CFrameBuffer();
    _fbo2 = new CFrameBuffer();
    _tex1 = new CTexture2D(width, height);
    _tex2 = new CTexture2D(width, height);

    _fbo1->bind();
    _fbo1->setColorAttachement(*_tex1);
    _fbo1->unbind();

    _fbo1->bind();
    _fbo2->setColorAttachement(*_tex2);
    _fbo2->unbind();
}

CWavesDeformer::~CWavesDeformer() {
    delete _fbo1;
    delete _fbo2;
    delete _tex1;
    delete _tex2;
}