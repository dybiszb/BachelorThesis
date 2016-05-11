// author: dybisz

#include "atw_gui.h"

CAtwGui::CAtwGui(Settings& settings, CCustomCamera* camera)
        : _settings(settings), _camera(camera) {

    _disturbanceHeight = _settings.manualDisturbanceStrength;
    _isRaining = _settings.rain;
    _rainIntensity = _settings.rainIntensity;
    _rainDropSize = _settings.rainStrength;
    _waves = _settings.waves;
    _waterAnimation = _settings.animation;
    _wavesIntensity = _settings.wavesStrength;

    _lightDirection = vec3
            {
                _settings.lightDirectionX,
                _settings.lightDirectionY,
                _settings.lightDirectionZ
            };
}

void CAtwGui::initializeATW() {
    TwInit(TW_OPENGL, NULL);
    TwWindowSize(_settings.windowWidth, _settings.windowHeight);
}

void CAtwGui::initializeWaterBar() {
    _waterBar = CAtwBarBuilder()
            .setLabel("Water")
            .setPosition(_settings.guiMargin, _settings.guiMargin)
            .setContained(true)
            .setColor(0, 128, 128)
            .setSize(240, 210)
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("animationOnOf")
            .setDataType(TW_TYPE_BOOL32)
            .setObservableData(&_waterAnimation)
            .setLabel("On / Off:")
            .setGroup("Animation")
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("disturbanceStrength")
            .setDataType(TW_TYPE_FLOAT)
            .setObservableData(&_disturbanceHeight)
            .setLabel("Strength:")
            .setStep(0.1)
            .setGroup("Manual_Disturbance")
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("wavesOnOf")
            .setDataType(TW_TYPE_BOOL32)
            .setObservableData(&_waves)
            .setLabel("On / Off:")
            .setGroup("Waves")
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("wavesHeight")
            .setDataType(TW_TYPE_FLOAT)
            .setObservableData(&_wavesIntensity)
            .setLabel("Strength:")
            .setStep(0.0001)
            .setGroup("Waves")
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("isRaining")
            .setDataType(TW_TYPE_BOOL32)
            .setObservableData(&_isRaining)
            .setLabel("On / Off:")
            .setGroup("Rain")
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("rainHeight")
            .setDataType(TW_TYPE_FLOAT)
            .setObservableData(&_rainDropSize)
            .setLabel("Strength:")
            .setStep(0.1)
            .setGroup("Rain")
            .build();

    CAtwVarBuilder()
            .setOwner(_waterBar)
            .setId("rainIntensity")
            .setDataType(TW_TYPE_INT32)
            .setObservableData(&_rainIntensity)
            .setLabel("Intensity:")
            .setStep(1.0)
            .setGroup("Rain")
            .build();
}

void CAtwGui::initializeSceneBar() {
    _sceneBar = CAtwBarBuilder()
            .setLabel("Scene")
            .setPosition
                    (
                            _settings.windowWidth- 195 - _settings.guiMargin,
                            0 + _settings.guiMargin
                    )
            .setContained(true)
            .setColor(0, 128, 128)
            .setSize(240, 450)
            .setRefresh(0.1)
            .build();

    CAtwVarBuilder()
            .setOwner(_sceneBar)
            .setId("windowWidth")
            .setDataType(TW_TYPE_INT32)
            .setObservableData(&_settings.windowWidth)
            .setLabel("Width")
            .setGroup("Window")
            .setReadOnly(true)
            .build();

    CAtwVarBuilder()
            .setOwner(_sceneBar)
            .setId("windowHeight")
            .setDataType(TW_TYPE_INT32)
            .setObservableData(&_settings.windowHeight)
            .setLabel("Height")
            .setGroup("Window")
            .setReadOnly(true)
            .build();

    TwAddVarRW(_sceneBar, "Direction", TW_TYPE_DIR3F, &_lightDirection,
               "opened=true axisz=-z showval=true group=Light");


    TwStructMember pointMembers[] = {
            { "X", TW_TYPE_FLOAT, offsetof(vec3, x), "step=0.1"},
            { "Y", TW_TYPE_FLOAT, offsetof(vec3, y), "step=0.1"},
            { "Z", TW_TYPE_FLOAT, offsetof(vec3, z), "step=0.1"}
    };
    TwType pointType = TwDefineStruct("POINT", pointMembers, 3, sizeof(vec3),
                                      NULL, NULL);

    CAtwVarBuilder()
            .setOwner(_sceneBar)
            .setId("cameraPosX")
            .setDataType(pointType)
            .setObservableData(&_camera->_position)
            .setLabel("Position")
            .setGroup("Position")
            .build();

    CAtwVarBuilder()
            .setOwner(_sceneBar)
            .setId("horizontalAngle")
            .setDataType(TW_TYPE_FLOAT)
            .setObservableData(&_camera->_horizontalAngle)
            .setLabel("Horizontal")
            .setGroup("Angle")
            .build();

    CAtwVarBuilder()
            .setOwner(_sceneBar)
            .setId("verticalAngle")
            .setDataType(TW_TYPE_FLOAT)
            .setObservableData(&_camera->_verticalAngle)
            .setLabel("Vertical")
            .setGroup("Angle")
            .build();

    CAtwVarBuilder()
            .setOwner(_sceneBar)
            .setId("fovAngle")
            .setDataType(TW_TYPE_FLOAT)
            .setObservableData(&_camera->_fov)
            .setLabel("FoV")
            .setGroup("Angle")
            .build();

    CAtwVarBuilder()
            .setOwner(_sceneBar)
            .setId("movementSpeed")
            .setDataType(TW_TYPE_FLOAT)
            .setObservableData(&_camera->_movementSpeed)
            .setLabel("Movement")
            .setGroup("Speed")
            .build();

    CAtwVarBuilder()
            .setOwner(_sceneBar)
            .setId("angularSpeed")
            .setDataType(TW_TYPE_FLOAT)
            .setObservableData(&_camera->_angularSpeed)
            .setLabel("Angular")
            .setStep(0.01)
            .setGroup("Speed")
            .build();

    TwDefine("Scene/cameraPosX opened=true");
    TwDefine("Scene/cameraPosX group=Camera");
    TwDefine("Scene/Angle group=Camera");
    TwDefine("Scene/Speed group=Camera");
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