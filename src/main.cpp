#include "glfw_renderer.h"
#include "rand_functions.h"

CGLFWRenderer renderer(800, 600);

int main(void) {
    //utils::seed();
    renderer.runMainLoop();
    return 0;
}