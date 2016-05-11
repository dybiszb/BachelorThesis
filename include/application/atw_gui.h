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
#include "camera.h"

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
    bool  getIsRaining();
    int   getRainingIntensity();
    float getRainDropSize();
    bool  getWaves();
    float getWavesIntensity();
    vec3& getLightDirection();
    bool  getWaterAnimation();

private:
//==============================================================================
// Interface Properties
//------------------------------------------------------------------------------
    TwBar *        _waterBar;
    TwBar *        _sceneBar;
    TwBar *        _controlsBar;
    Settings       _settings;
    CCustomCamera* _camera;

//==============================================================================
// Water Properties
//------------------------------------------------------------------------------
    float    _disturbanceHeight;
    bool     _isRaining;
    int      _rainIntensity;
    float    _rainDropSize;
    bool     _waves;
    float    _wavesIntensity;
    bool     _waterAnimation;


//==============================================================================
// Scene Properties
//------------------------------------------------------------------------------
    vec3     _lightDirection;
    vec3     _cameraPosition;
};

#endif
