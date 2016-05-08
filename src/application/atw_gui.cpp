// author: dybisz

#include "atw_gui.h"

CAtwGui::CAtwGui(Settings& settings)
        : _settings(settings) {

    _disturbanceHeight = _settings.manualDisturbanceStrength;
    _isRaining = _settings.rain;
    _rainIntensity = _settings.rainIntensity;
    _rainDropSize = _settings.rainStrength;
    _waves = _settings.waves;
    _waterAnimation = _settings.animation;
    _wavesIntensity = _settings.wavesStrength;
    _lightDirection.x = 1.0;
    _lightDirection.y = 1.0;
    _lightDirection.z = 1.0;
}

void CAtwGui::initializeATW() {
    TwInit(TW_OPENGL, NULL);
    TwWindowSize(_settings.windowWidth, _settings.windowHeight);
}

void CAtwGui::initializeWaterBar() {
    _waterBar = CAtwBarBuilder()
            .setLabel("Water")
            .setPosition(10, 10)
            .setContained(true)
            .setColor(0, 128, 128)
            .setSize(240, 220)
            .build();

    CAtwButtonBuilder()
            .setOwner(_waterBar)
            .setLabel("Animation")
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("animationOnOf")
            .setDataType(TW_TYPE_BOOL32)
            .setObservableData(&_waterAnimation)
            .setLabel("On / Off:")
            .build();

    CAtwButtonBuilder()
            .setOwner(_waterBar)
            .setLabel("Manual_Disturbance")
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("disturbanceStrength")
            .setDataType(TW_TYPE_FLOAT)
            .setObservableData(&_disturbanceHeight)
            .setLabel("Strength:")
            .setStep(0.1)
            .build();

    CAtwButtonBuilder()
            .setOwner(_waterBar)
            .setLabel("Waves")
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("wavesOnOf")
            .setDataType(TW_TYPE_BOOL32)
            .setObservableData(&_waves)
            .setLabel("On / Off:")
            .build();

    TwAddVarRW(_waterBar, "wavesHeight", TW_TYPE_FLOAT,
               &_wavesIntensity,
               "label='Strength:' step=0.0001");

    CAtwButtonBuilder()
            .setOwner(_waterBar)
            .setLabel("Rain")
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("isRaining")
            .setDataType(TW_TYPE_BOOL32)
            .setObservableData(&_isRaining)
            .setLabel("On / Off:")
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("rainHeight")
            .setDataType(TW_TYPE_FLOAT)
            .setObservableData(&_rainDropSize)
            .setLabel("Strength:")
            .setStep(0.1)
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("rainIntensity")
            .setDataType(TW_TYPE_INT32)
            .setObservableData(&_rainIntensity)
            .setLabel("Intensity:")
            .setStep(1.0)
            .build();
}

void CAtwGui::initializeSceneBar() {
    ///////////////////////////////////////////////////////////////////
//    _sceneBar = TwNewBar("Scene");
//    TwDefine(" 'Scene' size='240 160' contained=true fontsize=1");
//    TwSetParam(_sceneBar, NULL, "position", TW_PARAM_CSTRING, 1, "545 16");
//    TwAddVarRW(_sceneBar, "Light_Direction", TW_TYPE_DIR3F, &_lightDirection,
//               "showval=true open=true ");


//    TwAddSeparator(_waterBar, "", NULL);
//    TwAddVarRW(_waterBar, "particles/s", TW_TYPE_INT32,
//               &_particlesPerSecond,"step=10");
//    TwAddVarRW(_waterBar, "spread", TW_TYPE_FLOAT, &_particlesSpread,
//               "step=0.01");

//    TwAddVarRW(_waterBar, "smoke color", TW_TYPE_COLOR3F, &_smokeColor, " "
//            "label='smoke color' ");
//
//    TwAddSeparator(_waterBar, "", NULL);
//    TwAddButton(_waterBar, "Spawn Sphere", NULL, NULL, "");
//    TwAddSeparator(_waterBar, "", NULL);
//    TwAddVarRW(_waterBar, "Visible", TW_TYPE_BOOL32,
//               &_spawnSphereVisible,
//               " label='Visible' help='Should spawn sphere be"
//                       " visible?'");
//
//    TwAddVarRW(_waterBar, "Radius", TW_TYPE_FLOAT,
//               &_spawnSphereRadius,
//               "step=0.01");
//    TwAddSeparator(_particlesGUI, "", NULL);
//    TwAddButton(_particlesGUI, "Controls:", NULL, NULL, "");
//    TwAddButton(_particlesGUI, "RMB  - Rotate Camera", NULL, NULL, "");
//    TwAddButton(_particlesGUI, "WSAD - Move Camera", NULL, NULL, "");
}

void CAtwGui::initializeControlsBar() {

    _controlsBar = CAtwBarBuilder()
            .setLabel("Controls")
            .setSize(200, 105)
            .setContained(true)
            .setPosition(625, 510)
            .setAlpha(0)
            .setFontsize(1)
            .setColor(0, 128, 128)
            .build();

    CAtwButtonBuilder()
            .setOwner(_controlsBar)
            .setLabel("W, S, A, D  - move around")
            .build();

    CAtwButtonBuilder()
            .setOwner(_controlsBar)
            .setLabel("Z, X         - move up / down")
            .build();

    CAtwButtonBuilder()
            .setOwner(_controlsBar)
            .setLabel("LMB         - disturb water")
            .build();

    CAtwButtonBuilder()
            .setOwner(_controlsBar)
            .setLabel("RMB         - look around")
            .build();
}

void CAtwGui::terminateATW() {
    TwTerminate();
}

float CAtwGui::getDisturbanceHeight() {
    return _disturbanceHeight;
}

bool CAtwGui::getIsRaining() {
    return _isRaining;
}

int CAtwGui::getRainingIntensity() {
    return _rainIntensity;
}

float CAtwGui::getRainDropSize() {
    return _rainDropSize;
}

bool CAtwGui::getWaves() {
    return _waves;
}

float CAtwGui::getWavesIntensity() {
    return _wavesIntensity;
}

vec3 &CAtwGui::getLightDirection() {
    return _lightDirection;
}

bool CAtwGui::getWaterAnimation() {
    return _waterAnimation;
}