#include "glfw_renderer.h"
#include "settings_reader.h"

using namespace std;

int main(void) {
    utils::seed();
    Settings settings = utils::readFromINI("config.ini");
    CGLFWRenderer renderer(settings);
    renderer.runMainLoop();
    return 0;
}