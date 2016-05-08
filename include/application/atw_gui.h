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

using namespace glm;

class CAtwGui {
public:
    /**
     * For initializing the interface, height and width are essential
     * information.
     *
     * @param windowWidth  Width of the scene window.
     * @param windowHeight Height of the scene window.
     */
    CAtwGui(int windowWidth, int windowHeight);

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
    TwBar *_waterBar;
    TwBar *_sceneBar;
    TwBar *_controlsBar;
    int    _windowWidth;
    int    _windowHeight;

//==============================================================================
// Water Properties
//------------------------------------------------------------------------------
    float  _disturbanceHeight;
    bool   _isRaining;
    int    _rainIntensity;
    float  _rainDropSize;
    bool   _waves;
    float  _wavesIntensity;
    vec3   _lightDirection;
    bool   _waterAnimation;

};

#endif
