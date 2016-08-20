// author: dybisz

#include "glfw_renderer.h"
#include <time.h>
#include <unistd.h>

CGLFWRenderer::CGLFWRenderer(Settings& settings) :
        _settings(settings),
        _camera(settings),
        _gui(settings, &_camera) {
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
    delete _ship;
    _gui.terminateATW();
    glfwTerminate();
}

void CGLFWRenderer::runMainLoop() {
    do {
        /* ----- Calculate Time ----- */
        float deltaTime = _timer.tick();
        float renderTimeStart = glfwGetTime();
        /* ----- Update Time ----- */
        _water->updateTime(deltaTime);
        _inputOutput->updateTime(deltaTime);

        /* ----- Update Waves ----- */
        _water->setWavesOn(_gui.getWavesOn());
        _water->setWavesAmplitude(_gui.getWavesAmplitude());
        _water->setWavesFrequency(_gui.getWavesFrequency());
        _water->setWavesChoppiness(_gui.getWavesChoppiness());
        _water->setWavesResolutionX(_gui.getWavesResolutionX());
        _water->setWavesResolutionY(_gui.getWavesResolutionY());

        /* ----- Camera Position ----- */
        _skybox->setCameraPosition(_camera.getPosition());
        _water->setCameraPosition(_camera.getPosition());

        /* ----- Light Direction ----- */
        _water->setLightDirections(_gui.getLightDirection());

        /* ----- Check Disturbance ----- */
        if (_inputOutput->isIntersectionRequested()) {
            vec2 viewportCoordinates =
                    _inputOutput->getIntersectionCoordinates();
            _water->areaIntersect(viewportCoordinates, _camera,
                                  _gui.getDisturbanceHeight(), _gui
                                          .getKernelSize(), _gui.getFlatness());
            _inputOutput->setIntersectionRequested(false);
        }

        /* ----- Check if Lights are On ----- */
        if(_gui.getLightOn() != _water->getLightOn()) {
            _water->setLightOn(_gui.getLightOn());
        }

        /* ----- Rain ----- */
        if (_gui.getIsRaining() && _gui.getWaterAnimation()) {
            for (int i = 0; i < _gui.getRainingIntensity(); i++) {
                int x = (int)
                        utils::randomInteger(50,
                                             _water->getVerticesPerSide() - 50);
                int y = (int) utils::randomInteger(50, _water->getVerticesPerSide() -
                                                       50);
                vec2 quadCoordinates(x, y);
                _water->pointIntersect(quadCoordinates, _gui.getRainDropSize()
                        ,_gui.getRainKernel(), _gui.getRainFlatness());

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
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        _water->render(&_camera.getViewMatrix()[0][0],
                       &_camera.getProjectionMatrix()[0][0]);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        _ship->updateComputationalGrid(_water->getHeightfieldAsArray(),
                                       _settings.quads,
                                       _settings.quads, _settings.edgeSize);
        _ship->render(&_camera.getViewMatrix()[0][0],
                      &_camera.getProjectionMatrix()[0][0]);

        TwDraw();
        glfwSwapBuffers(_window);
        glfwPollEvents();

        float renderTimeEnd = glfwGetTime();
        float waitTime = (1000.0/ 60.0 - (renderTimeEnd - renderTimeStart));
//        cout << waitTime << endl;
//        sleep(waitTime * 0.1);
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
    _window = glfwCreateWindow(_settings.windowWidth, _settings.windowHeight,
                               "Bachelor Thesis - Bartlomiej Dybisz",
                               _settings.fullScreen ? glfwGetPrimaryMonitor() : NULL,
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
    _skybox = CSkyboxBuilder()
            .setSideSize(_settings.edgeSize)
            .build();

    _water = CWaterBuilder()
            .setQuadsPerSide(_settings.quads)
            .setSideSize(_settings.edgeSize)
            .setBottomCorner(vec2(-_settings.edgeSize / 2.0,
                                  -_settings.edgeSize / 2.0))
            .setModernShaders(false)
            .setSkyboxId(_skybox->getCubemapId())
            .setViewport(_settings.windowWidth, _settings.windowHeight)
            .setAnimation(true)
            .setLightOn(false)
            .build();

    _ship = new CShipModel(_settings);
}

void CGLFWRenderer::_initGLGlobalSettings() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}