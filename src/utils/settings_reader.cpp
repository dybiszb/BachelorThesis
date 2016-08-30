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
            (float) reader.GetReal("Scene", "edge_size", 32.0);
    settings.quads =
            reader.GetInteger("Scene", "quads", 256);

    /* ----- Ship ----- */
    settings.linearDamping =
            (float) reader.GetReal("Ship", "linear_damping", 2.0);
    settings.angularDamping =
            (float) reader.GetReal("Ship", "angular_damping", 6.0);
    settings.modelLocalTranslationX =
            (float) reader.GetReal("Ship", "model_local_translation_x", 13.0);
    settings.modelLocalTranslationY =
            (float) reader.GetReal("Ship", "model_local_translation_y", 2.5);
    settings.modelLocalTranslationZ =
            (float) reader.GetReal("Ship", "model_local_translation_z", 3.0);
    settings.modelScale =
            (float) reader.GetReal("Ship", "model_scale", 0.2);
    settings.gridVisibility =
            reader.GetBoolean("Ship", "grid_visibility", true);
    settings.enginesPointX =
            (float) reader.GetReal("Ship", "engines_point_x", 10.0);
    settings.enginesPointY =
            (float) reader.GetReal("Ship", "engines_point_y", 0.0);
    settings.enginesPointZ =
            (float) reader.GetReal("Ship", "engines_point_z", 0.0);

    /* ----- Light ----- */
    settings.lightOn =
            reader.GetBoolean("Light", "on", false);
    settings.lightDirectionX =
            (float) reader.GetReal("Light", "direction_x", -0.1);
    settings.lightDirectionY =
            (float) reader.GetReal("Light", "direction_y", -1.7);
    settings.lightDirectionZ =
            (float) reader.GetReal("Light", "direction_z", -0.3);

    /* ----- GUI ----- */
    settings.guiMargin =
            (float) reader.GetReal("GUI", "margin", 10.0);

    /* ----- Camera ----- */
    settings.cameraStartPositionX =
            (float) reader.GetReal("Camera", "start_position_x", 0.0);
    settings.cameraStartPositionY =
            (float) reader.GetReal("Camera", "start_position_y", 0.0);
    settings.cameraStartPositionZ =
            (float) reader.GetReal("Camera", "start_position_z", 0.0);
    settings.cameraHorizontalAngle =
            (float) reader.GetReal("Camera", "horizontal_angle", 0.0);
    settings.cameraVerticalAngle =
            (float) reader.GetReal("Camera", "vertical_angle", 0.0);
    settings.cameraFov =
            (float) reader.GetReal("Camera", "fov", 45.0);
    settings.cameraMovementSpeed =
            (float) reader.GetReal("Camera", "movement_speed", 10.0);
    settings.cameraAngularSpeed =
            (float) reader.GetReal("Camera", "angular_speed", 0.5);

    /* ----- Water ----- */
    settings.animation =
            reader.GetBoolean("Water", "animation", true);
    settings.manualDisturbanceStrength =
            (float) reader.GetReal("Water", "manual_disturbance_strength", 0.3);
    settings.manualDisturbanceKernel =
            reader.GetInteger("Water", "manual_disturbance_kernel", 4);
    settings.manualDisturbanceFlatness =
            (float) reader.GetReal("Water", "manual_disturbance_flatness", 0.2);

    settings.rain =
            reader.GetBoolean("Water", "rain", false);
    settings.rainStrength =
            (float) reader.GetReal("Water", "rain_strength", 1.0);
    settings.rainIntensity =
            reader.GetInteger("Water", "rain_intensity", 1);
    settings.rainKernelSize =
            reader.GetInteger("Water", "rain_kernel", 1);
    settings.rainFlatness =
            (float) reader.GetReal("Water", "rain_flatness", 0.2);

    settings.waves =
            reader.GetBoolean("Water", "waves", true);
    settings.wavesAmplitude =
            (float) reader.GetReal("Water", "waves_amplitude", 0.6);
    settings.wavesFrequency =
            (float) reader.GetReal("Water", "waves_frequency", 10.16);
    settings.wavesChoppiness =
            (float) reader.GetReal("Water", "waves_choppiness", 2.0);
    settings.wavesResolutionX =
            (float) reader.GetReal("Water", "waves_resolution_x", 0.75);
    settings.wavesResolutionY =
            (float) reader.GetReal("Water", "waves_resolution_y", 1.0);

    return settings;
}
