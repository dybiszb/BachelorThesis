//==============================================================================
// All parameters of the application are assumed to be passed via one object.
// Following structure fulfils this assumption, encapsulating all values that
// can be tweaked either dynamically, or before application run.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef SETTINGS_STRUCT_H
#define SETTINGS_STRUCT_H

namespace utils {
    struct Settings {

//==============================================================================
// Scene Properties
//------------------------------------------------------------------------------
        bool fullScreen;
        int windowWidth;
        int windowHeight;
        float edgeSize;
        int quads;

//==============================================================================
// Water Properties
//------------------------------------------------------------------------------
        bool animation;
        float manualDisturbanceStrength;
        bool waves;
        float wavesStrength;
        bool rain;
        float rainStrength;
        int rainIntensity;
    };
}

#endif
