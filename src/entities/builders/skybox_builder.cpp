// author: dybisz

#include "skybox_builder.h"

using namespace entities;

const float CSkyboxBuilder::defaultSideSize = 32.0f;

//const char* CSkyboxBuilder::defaultFaces[6]= {
//"./res/textures/skybox/alt2/front.tga",
//"./res/textures/skybox/alt2/back.tga",
//"./res/textures/skybox/alt2/up.tga",
//"./res/textures/skybox/alt2/down.tga",
//"./res/textures/skybox/alt2/right.tga",
//"./res/textures/skybox/alt2/left.tga"
//};

const char* CSkyboxBuilder::defaultFaces[6]= {
        "./res/textures/skybox/mountains/front.jpg",
        "./res/textures/skybox/mountains/back.jpg",
        "./res/textures/skybox/mountains/up.jpg",
        "./res/textures/skybox/mountains/down.jpg",
        "./res/textures/skybox/mountains/right.jpg",
        "./res/textures/skybox/mountains/left.jpg"
};

const bool CSkyboxBuilder::defaultModernShaders = false;


CSkyboxBuilder::CSkyboxBuilder() {
    _sideSize = defaultSideSize;
    _faces[0] = defaultFaces[0];
    _faces[1] = defaultFaces[1];
    _faces[2] = defaultFaces[2];
    _faces[3] = defaultFaces[3];
    _faces[4] = defaultFaces[4];
    _faces[5] = defaultFaces[5];

    _modernShaders = defaultModernShaders;
};

CSkyboxBuilder::~CSkyboxBuilder() {

}

CSkybox *CSkyboxBuilder::build() {
    return new CSkybox(this->_sideSize, this->_faces, this->_modernShaders);
}

CSkyboxBuilder &CSkyboxBuilder::setSideSize(const float sideSize) {
    this->_sideSize = sideSize;
    return *this;
}

CSkyboxBuilder &CSkyboxBuilder::setFaces(const char* faces[6]) {
    this->_faces[0] = faces[0];
    this->_faces[1] = faces[1];
    this->_faces[2] = faces[2];
    this->_faces[3] = faces[3];
    this->_faces[4] = faces[4];
    this->_faces[5] = faces[5];
    return *this;
}

CSkyboxBuilder &CSkyboxBuilder::setModernShaders(const bool modernShaders) {
    this->_modernShaders = modernShaders;
    return *this;
}