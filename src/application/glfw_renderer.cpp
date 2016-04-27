// author: dybisz

#include "GLFW_renderer.h"

CGLFWRenderer::CGLFWRenderer(int windowWidth, int windowHeight) :
        _windowWidth(windowWidth),
        _windowHeight(windowHeight) {
    _initGLFW();
    _initWindow();
    _initInputOutput();
    _initGLEW();
    _initATWBar();
    _initCallbacks();
    _initRenderableObjects();
    _initGLGlobalSettings();
}

CGLFWRenderer::~CGLFWRenderer() {
    delete _inputOutput;
    delete _water;
    delete _skybox;
    TwTerminate();
    glfwTerminate();
}

void CGLFWRenderer::runMainLoop() {
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        TwDraw();
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
    while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(_window) == 0);
}

void CGLFWRenderer::_initGLFW() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
}

void CGLFWRenderer::_initWindow() {
    _window = glfwCreateWindow(_windowWidth, _windowHeight, "Smoke Trails "
            "Editor", NULL /*glfwGetPrimaryMonitor()*/, NULL);
    if (_window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        getchar();
        glfwTerminate();
    }
    glfwMakeContextCurrent(_window);
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, 1);
}

void CGLFWRenderer::_initInputOutput() {
    if (_window == NULL) {
        fprintf(stderr, "Initiaqlize _window in CGLFWRenderer first.\n");
        getchar();
        glfwTerminate();
    }
    _inputOutput = new CGLFWInputOutput(_window);
    _inputOutput->setCamera(&_camera);
}

void CGLFWRenderer::_initGLEW() {
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
    }
}

void CGLFWRenderer::_initATWBar() {
    TwInit(TW_OPENGL, NULL);
    TwWindowSize(_windowWidth, _windowHeight);
    _waterBar = TwNewBar("Smoke Emitter Settings");
    TwDefine(" 'Smoke Emitter Settings' size='240 500' ");
    TwSetParam(_waterBar, NULL, "refresh", TW_PARAM_CSTRING, 1, "0.1");

    TwAddSeparator(_waterBar, "", NULL);
    TwAddButton(_waterBar, "Particle", NULL, NULL, "");
    TwAddSeparator(_waterBar, "", NULL);

//    TwAddVarRW(_waterBar, "lifetime", TW_TYPE_FLOAT, &_particleLifetime,
//               "step=0.1");
//
//    TwAddSeparator(_waterBar, "", NULL);
//    TwAddButton(_waterBar, "Emitter", NULL, NULL, "");
//    TwAddSeparator(_waterBar, "", NULL);
//    TwAddVarRW(_waterBar, "particles/s", TW_TYPE_INT32,
//               &_particlesPerSecond,"step=10");
//    TwAddVarRW(_waterBar, "spread", TW_TYPE_FLOAT, &_particlesSpread,
//               "step=0.01");
//    TwAddVarRW(_waterBar, "random color", TW_TYPE_BOOL32, &_randomColor,
//               " label='random color' help='Should smoke be generated using "
//                       "random colors?'"
//                       " ");
//    TwAddVarRW(_waterBar, "smoke color", TW_TYPE_COLOR3F, &_smokeColor, " "
//            "label='smoke color' ");
//
//    TwAddSeparator(_waterBar, "", NULL);
//    TwAddButton(_waterBar, "Spawn Sphere", NULL, NULL, "");
//    TwAddSeparator(_waterBar, "", NULL);
//    TwAddVarRW(_waterBar, "Visible", TW_TYPE_BOOL32,
//               &_spawnSphereVisible,
//               " label='Visible' help='Should spawn sphere be"
//                       " visible?'");
//
//    TwAddVarRW(_waterBar, "Radius", TW_TYPE_FLOAT,
//               &_spawnSphereRadius,
//               "step=0.01");
//    TwAddSeparator(_particlesGUI, "", NULL);
//    TwAddButton(_particlesGUI, "Controls:", NULL, NULL, "");
//    TwAddButton(_particlesGUI, "RMB  - Rotate Camera", NULL, NULL, "");
//    TwAddButton(_particlesGUI, "WSAD - Move Camera", NULL, NULL, "");
}

void CGLFWRenderer::_initCallbacks() {
    glfwSetMouseButtonCallback(_window, CGLFWInputOutput::mouse_button_callback);
    glfwSetCursorPosCallback(_window, (GLFWcursorposfun)TwEventMousePosGLFW);
    glfwSetScrollCallback(_window, (GLFWscrollfun)TwEventMouseWheelGLFW);
    glfwSetKeyCallback(_window, (GLFWkeyfun)TwEventKeyGLFW);
//    glfwSetKeyCallback(_window, CGLFWInputOutput::key_callback);

    glfwSetCharCallback(_window, (GLFWcharfun)TwEventCharGLFW);
}

void CGLFWRenderer::_initRenderableObjects() {
//    _skybox = CSkyboxBuilder().setSideSize(32).setModernShaders(false).build();
    _water = CWaterBuilder().setQuadsPerSide(256).setSideSize(32)
            .setBottomCorner(vec2(-16,-16)).setModernShaders(false)
            .setSkyboxId(_skybox->getCubemapId()).build();
}

void CGLFWRenderer::_initGLGlobalSettings() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}