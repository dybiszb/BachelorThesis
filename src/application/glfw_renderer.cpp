// author: dybisz

#include "glfw_renderer.h"

CGLFWRenderer::CGLFWRenderer(int windowWidth, int windowHeight,
                             bool fullscreen) :
        _fullscreen(fullscreen),
        _windowWidth(windowWidth),
        _windowHeight(windowHeight),
        _gui(windowWidth, windowHeight) {
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
    _gui.terminateATW();
    glfwTerminate();
}

void CGLFWRenderer::runMainLoop() {
    do {
        /* ----- Calculate Time ----- */
        float deltaTime = _timer.tick();


        /* ----- Update Time ----- */
        _water->updateTime(deltaTime);
        _inputOutput->updateCamera(deltaTime);

        /* ----- Camera Position ----- */
        _skybox->setCameraPosition(_camera.getPosition());
        _water->setCameraPosition(_camera.getPosition());

        /* ----- Light Direction ----- */
        _water->setLightDirections(_gui.getLightDirection());

        /* ----- Check Disturbance ----- */
        if (_inputOutput->isIntersectionRequested()) {
            vec2 viewportCoordinates =
                    _inputOutput->getIntersectionCoordinates();
            _water->intersect(viewportCoordinates, _camera, _gui.getDisturbanceHeight());
            _inputOutput->setIntersectionRequested(false);
        }

        /* ----- Waves ----- */
        if (_gui.getWaves() && _gui.getWaterAnimation()) {
            for (int i = 0; i < 800; i++) {
                int x = utils::randomInteger(0, _water->getVerticesPerSide()
                                                - 2);
                int y = utils::randomInteger(0, _water->getVerticesPerSide() -
                                                2);
                vec2 quadCoordinates(x, y);
                _water->intersect(quadCoordinates, _gui.getWavesIntensity());
            }
        }

        /* ----- Rain ----- */
        if (_gui.getIsRaining() && _gui.getWaterAnimation()) {
            for (int i = 0; i < _gui.getRainingIntensity(); i++) {
                int x = utils::randomInteger(0, _water->getVerticesPerSide()
                                                - 2);
                int y = utils::randomInteger(0, _water->getVerticesPerSide() -
                                                2);
                vec2 quadCoordinates(x, y);
                _water->intersect(quadCoordinates, _gui.getRainDropSize());
            }
        }

        /* ----- Check Stop Scene ----- */
        if (_gui.getWaterAnimation() != _water->getAnimation()) {
            _water->setAnimation(_gui.getWaterAnimation());
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* ----- Render Scene ----- */
        _skybox->render(&_camera.getViewMatrix()[0][0],
                        &_camera.getProjectionMatrix()[0][0]);
        _water->render(&_camera.getViewMatrix()[0][0],
                       &_camera.getProjectionMatrix()[0][0]);

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
}

void CGLFWRenderer::_initWindow() {
    _window = glfwCreateWindow(_windowWidth, _windowHeight,
                               "Bachelor Thesis - Bartlomiej Dybisz",
                               _fullscreen ? glfwGetPrimaryMonitor() : NULL,
                               NULL);
    if (_window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        getchar();
        glfwTerminate();
    }
    glfwMakeContextCurrent(_window);
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, 1);
}

void CGLFWRenderer::_initInputOutput() {
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
    _gui.initializeATW();
    _gui.initializeWaterBar();
    _gui.initializeSceneBar();
    _gui.initializeControlsBar();
}

void CGLFWRenderer::_initCallbacks() {
    glfwSetMouseButtonCallback(_window, CGLFWInputOutput::mouse_button_callback);
    glfwSetCursorPosCallback(_window, (GLFWcursorposfun) TwEventMousePosGLFW);
    glfwSetScrollCallback(_window, (GLFWscrollfun) TwEventMouseWheelGLFW);
    glfwSetKeyCallback(_window, (GLFWkeyfun) TwEventKeyGLFW);
    glfwSetCharCallback(_window, (GLFWcharfun) TwEventCharGLFW);
}

void CGLFWRenderer::_initRenderableObjects() {
    float sceneLength = 32.0f;
    int quadsPerSide = 256;

    _skybox = CSkyboxBuilder()
            .setSideSize(sceneLength)
            .setModernShaders(false)
            .build();

    _water = CWaterBuilder()
            .setQuadsPerSide(quadsPerSide)
            .setSideSize(sceneLength)
            .setBottomCorner(vec2(-sceneLength / 2.0, -sceneLength / 2.0))
            .setModernShaders(false)
            .setSkyboxId(_skybox->getCubemapId())
            .setViewport(_windowWidth, _windowHeight)
            .build();
}

void CGLFWRenderer::_initGLGlobalSettings() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}