// author: dybisz

#include "skybox_builder.h"

using namespace entities;

const float CSkyboxBuilder::defaultSideSize = 32.0f;

//const char* CSkyboxBuilder::defaultFaces[6]= {
//        "./res/textures/skybox/front.jpg",
//        "./res/textures/skybox/back.jpg",
//        "./res/textures/skybox/up.jpg",
//        "./res/textures/skybox/down.jpg",
//        "./res/textures/skybox/right.jpg",
//        "./res/textures/skybox/left.jpg"
//};
const char* CSkyboxBuilder::defaultFaces[6]= {
        "./res/textures/hip_miramar/miramar_ft.tga",
        "./res/textures/hip_miramar/miramar_bk.tga",
        "./res/textures/hip_miramar/miramar_up.tga",
        "./res/textures/hip_miramar/miramar_dn.tga",
        "./res/textures/hip_miramar/miramar_rt.tga",
        "./res/textures/hip_miramar/miramar_lf.tga"
};


CSkyboxBuilder::CSkyboxBuilder() {
    _sideSize = defaultSideSize;
    _faces[0] = defaultFaces[0];
    _faces[1] = defaultFaces[1];
    _faces[2] = defaultFaces[2];
    _faces[3] = defaultFaces[3];
    _faces[4] = defaultFaces[4];
    _faces[5] = defaultFaces[5];
};

CSkyboxBuilder::~CSkyboxBuilder() {

}

CSkybox *CSkyboxBuilder::build() {
    return new CSkybox(this->_sideSize, this->_faces);
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