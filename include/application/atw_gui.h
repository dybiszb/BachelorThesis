//==============================================================================
// Creates UI using Ant Tweak Bar library. In addition all variables modifiable
// by the interface are stored and managed.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef ATW_GUI_H
#define ATW_GUI_H

#include <AntTweakBar.h>
#include <glm/glm.hpp>
#include "builders/atw_bar_builder.h"
#include "builders/atw_button_builder.h"
#include "builders/atw_var_builder.h"
#include "settings_struct.h"
#include "custom_camera.h"

using namespace glm;
using namespace utils;



class CAtwGui {
public:
    /**
     * For initializing the interface, height and width are essential
     * information.
     *
     * @param settings  Set of settings.
     * @param camera    Pointer to the scene's camera. Resources will not be
     *                  freed after deleting the class.
     */
    CAtwGui(Settings& settings, CCustomCamera* camera);

    /**
     * Creates Ant Tweak Bar library's context.
     */
    void initializeATW();

    /**
     * Creates a window within the interface, which will be used to manage
     * water simulation.
     */
    void initializeWaterBar();

    /**
     * Creates a window within the interface, which will be used to manage
     * ship simulation.
     */
    void initializeShipBar();

    /**
     * Creates a window, withing the interface context, which will be in charge
     * of the scene settings.
     */
    void initializeSceneBar();

    /**
     * Initializes simpel window, withing the interface context, that will
     * display information about the application's controls.
     */
    void initializeControlsBar();

    /**
     * Must be called at the end of the interface usage. Releases all
     * resources related to the gui context and terminates Ant Tweak Bar
     * library.
     */
    void terminateATW();

//==============================================================================
// Access Functions
//------------------------------------------------------------------------------
    float getDisturbanceHeight();
    int   getKernelSize();
    float getFlatness();
    bool  getIsRaining();
    int   getRainingIntensity();
    float getRainDropSize();
    vec3& getLightDirection();
    bool  getWaterAnimation();
    bool  getLightOn();
    int   getRainKernel();
    float getRainFlatness();
    bool  getWavesOn();
    float getWavesAmplitude();
    float getWavesFrequency();
    float getWavesChoppiness();
    float getWavesResolutionX();
    float getWavesResolutionY();
    float getLinearDamping();
    float getAngularDamping();
    vec3& getModelLocalTranslation();
    float getModelScale();
    bool getGridVisibility();

//==============================================================================
// Update Functions
//------------------------------------------------------------------------------
    void setMovementForce(const vec3& force);

private:
//==============================================================================
// Interface Properties
//------------------------------------------------------------------------------
    TwBar *        _waterBar;
    TwBar *        _shipBar;
    TwBar *        _sceneBar;
    TwBar *        _controlsBar;
    Settings       _settings;
    CCustomCamera* _camera;

//==============================================================================
// Water Properties
//------------------------------------------------------------------------------
    float    _disturbanceHeight;
    int      _kernelSize;
    float    _flatness;
    bool     _isRaining;
    int      _rainIntensity;
    float    _rainDropSize;
    bool     _waterAnimation;
    int      _rainKernel;
    float    _rainFlatness;
    bool     _wavesOn;
    float    _wavesFrequency;
    float    _wavesAmplitude;
    float    _wavesChoppiness;
    float    _wavesResolutionX;
    float    _wavesResolutionY;

//==============================================================================
// Scene Properties
//------------------------------------------------------------------------------
    bool     _lightOn;
    vec3     _lightDirection;
    vec3     _cameraPosition;

//==============================================================================
// Simulation Properties
//------------------------------------------------------------------------------
    float    _linearDamping;
    float    _angularDamping;
    vec3     _modelLocalTranslation;
    float    _modelScale;
    bool     _gridVisibility;
    vec3     _movementForce;
    vec3     _enginesPosition;
};

#endif
