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

    /* ----- Light ----- */
    settings.lightOn =
            reader.GetBoolean("Light", "on", false);
    settings.lightDirectionX =
            reader.GetReal("Light", "direction_x", -1);
    settings.lightDirectionY =
            reader.GetReal("Light", "direction_y", -1);
    settings.lightDirectionZ =
            reader.GetReal("Light", "direction_z", -1);

    /* ----- GUI ----- */
    settings.guiMargin =
            reader.GetReal("GUI", "margin", 10.0);

    /* ----- Camera ----- */
    settings.cameraStartPositionX =
            reader.GetReal("Camera", "start_position_x", 0.0);
    settings.cameraStartPositionY =
            reader.GetReal("Camera", "start_position_y", 0.0);
    settings.cameraStartPositionZ =
            reader.GetReal("Camera", "start_position_z", 0.0);
    settings.cameraHorizontalAngle =
            reader.GetReal("Camera", "horizontal_angle", 0.0);
    settings.cameraVerticalAngle =
            reader.GetReal("Camera", "vertical_angle", 0.0);
    settings.cameraFov =
            reader.GetReal("Camera", "fov", 45.0);
    settings.cameraMovementSpeed =
            reader.GetReal("Camera", "movement_speed", 10.0);
    settings.cameraAngularSpeed =
            reader.GetReal("Camera", "angular_speed", 0.5);

    /* ----- Water ----- */
    settings.animation =
            reader.GetBoolean("Water", "animation", true);
    settings.manualDisturbanceStrength =
            reader.GetReal("Water", "manual_disturbance_strength", 0.1);
    settings.rain =
            reader.GetBoolean("Water", "rain", false);
    settings.rainStrength =
            reader.GetReal("Water", "rain_strength", 1.0);
    settings.rainIntensity =
            reader.GetInteger("Water", "rain_intensity", 1);

    return settings;
}
