// author: dybisz

#include "builders/water_builder.h"

using namespace entities;

const int   CWaterBuilder::defaultQuadsPerSide = 256;
const float CWaterBuilder::defaultSideSize = 32.0f;
const vec2  CWaterBuilder::defaultBottomCorner(-defaultSideSize / 2.0,
                                               -defaultSideSize / 2.0);
const int   CWaterBuilder::defaultSkyboxId = -1;
const bool  CWaterBuilder::defaultModernShaders = false;


CWaterBuilder::CWaterBuilder() {
    _quadsPerSide = defaultQuadsPerSide;
    _sideSize = defaultSideSize;
    _bottomCorner = defaultBottomCorner;
    _modernShaders = defaultModernShaders;
};

CWaterGrid *CWaterBuilder::build() {
    return new CWaterGrid(this->_quadsPerSide, this->_sideSize,
                      this->_bottomCorner, this->_skyboxId,
                          this->_modernShaders);
}

CWaterBuilder &CWaterBuilder::setQuadsPerSide(const int quadsPerSide) {
    this->_quadsPerSide = quadsPerSide;
    return *this;
}

CWaterBuilder &CWaterBuilder::setSideSize(const float sideSize) {
    this->_sideSize = sideSize;
    return *this;
}

CWaterBuilder &CWaterBuilder::setBottomCorner(const vec2 bottomCorner) {
    this->_bottomCorner = bottomCorner;
    return *this;
}

CWaterBuilder& CWaterBuilder::setSkyboxId(int skyboxId) {
    this->_skyboxId = skyboxId;
    return *this;
}

CWaterBuilder &CWaterBuilder::setModernShaders(const bool modernShaders) {
    this->_modernShaders = modernShaders;
    return *this;
}