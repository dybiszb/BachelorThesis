// author: dybisz

#include "settings_reader.h"

using namespace utils;

Settings utils::readFromINI(string pathToINI) {
    INIReader reader(pathToINI);
    Settings settings;

    if (reader.ParseError() < 0) {
        cout << "Can't load " + pathToINI << endl;
        return settings;
    }

    /* ----- Scene ----- */
    settings.fullScreen =
            reader.GetBoolean("Scene", "full_screen", false);
    settings.windowWidth =
            reader.GetInteger("Scene", "window_width", 800);
    settings.windowHeight =
            reader.GetInteger("Scene", "window_height", 600);
    settings.edgeSize =
            reader.GetReal("Scene", "edge_size", 32.0);
    settings.quads =
            reader.GetInteger("Scene", "quads", 256);

    /* ----- Water ----- */
    settings.animation =
            reader.GetBoolean("Water", "animation", true);
    settings.manualDisturbanceStrength =
            reader.GetReal("Water", "manual_disturbance_strength", 0.1);
    settings.waves =
            reader.GetBoolean("Water", "waves", false);
    settings.wavesStrength =
            reader.GetReal("Water", "waves_strength", 0.01);
    settings.rain =
            reader.GetBoolean("Water", "rain", false);
    settings.rainStrength =
            reader.GetReal("Water", "rain_strength", 1.0);
    settings.rainIntensity =
            reader.GetInteger("Water", "rain_intensity", 1);

    return settings;
}
