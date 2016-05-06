// author: dybisz

#include "glfw_renderer.h"

CGLFWRenderer::CGLFWRenderer(int windowWidth, int windowHeight,
                             bool fullscreen) :
        _windowWidth(windowWidth),
        _windowHeight(windowHeight),
        _fullscreen(fullscreen) {
    _initGLFW();
    _initWindow();
    _initInputOutput();
    _initGLEW();
    _initWaterProperties();
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
//    _initATWBar();
//    _initCallbacks();
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
        _water->setLightDirections(_lightDirection);

        /* ----- Check Disturbance ----- */
        if (_inputOutput->isIntersectionRequested()) {
            vec2 viewportCoordinates =
                    _inputOutput->getIntersectionCoordinates();
            _water->intersect(viewportCoordinates, _camera, _disturbanceHeight);
            _inputOutput->setIntersectionRequested(false);
        }

        /* ----- Waves ----- */
        if(_waves && _waterAnimation) {
            for(int i = 0; i < 800; i++) {
                int x = utils::randomInteger(0, _water->getVerticesPerSide()
                                                - 2);
                int y = utils::randomInteger(0, _water->getVerticesPerSide() -
                                                2);
                vec2 quadCoordinates(x,y);
                _water->intersect(quadCoordinates, _wavesIntensity);
            }
        }

        /* ----- Rain ----- */
        if(_isRaining && _waterAnimation) {
            for(int i = 0; i < _rainIntensity; i++) {
                int x = utils::randomInteger(0, _water->getVerticesPerSide()
                                                - 2);
                int y = utils::randomInteger(0, _water->getVerticesPerSide() -
                        2);
                vec2 quadCoordinates(x,y);
                _water->intersect(quadCoordinates, _rainDropSize);
            }
        }

        /* ----- Check Stop Scene ----- */
//        if(_inputOutput->isStopAnimationRequested()) {
//            _waterAnimation = !_waterAnimation;
//            _inputOutput->setStopAnimationRequested(false);
//        }
        if(_waterAnimation != _water->getAnimation()) {
            _water->setAnimation(_waterAnimation);
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

    glfwWindowHint(GLFW_SAMPLES, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
}

void CGLFWRenderer::_initWaterProperties() {
    _disturbanceHeight = 2.0;
    _isRaining         = true;
    _rainIntensity     = 1;
    _rainDropSize      = 1.0;
    _waves             = false;
    _waterAnimation    = true;
    _wavesIntensity    = 0.01;
    _lightDirection.x  = 1.0;
    _lightDirection.y  = 1.0;
    _lightDirection.z  = 1.0;
}

void CGLFWRenderer::_initWindow() {
    _window = glfwCreateWindow(_windowWidth, _windowHeight,
                               "Bachelor Thesis - Bartlomiej Dybisz",
            _fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
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
//    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
    }
}

void CGLFWRenderer::_initATWBar() {
    TwInit(TW_OPENGL, NULL);
    TwWindowSize(_windowWidth, _windowHeight);
    _waterBar = TwNewBar("Water");
    TwDefine(" 'Water' size='240 220' contained=true fontsize=1");

//
//    TwAddSeparator(_waterBar, "", NULL);
    TwAddButton(_waterBar, "Animation", NULL, NULL, "");
    TwAddVarRW(_waterBar, "animation:", TW_TYPE_BOOL32, &_waterAnimation,
               " label='On / Off:' help='Animate water or not' ");

    TwAddButton(_waterBar, "Manual_Disturbance", NULL, NULL, "");
    TwAddVarRW(_waterBar, "Height: ", TW_TYPE_FLOAT,
               &_disturbanceHeight,
               "label='Strength:' step=0.1");

    TwAddButton(_waterBar, "Waves", NULL, NULL, "");
    TwAddVarRW(_waterBar, "On / Off:", TW_TYPE_BOOL32, &_waves,
               " label='On / Off:' help='Should smoke be generated using "
                       "random colors?'"
                       " ");
    TwAddVarRW(_waterBar, "wavesHeight", TW_TYPE_FLOAT,
               &_wavesIntensity,
               "label='Strength:' step=0.0001");

    TwAddButton(_waterBar, "Rain", NULL, NULL, "");
    TwAddVarRW(_waterBar, "isRaining", TW_TYPE_BOOL32, &_isRaining,
               " label='On / Off:' help='Should smoke be generated using "
                       "random colors?'"
                       " ");
    TwAddVarRW(_waterBar, "Height_: ", TW_TYPE_FLOAT,
               &_rainDropSize,
               "label='Strength:' step=0.01");

    TwAddVarRW(_waterBar, "Intensity: ", TW_TYPE_INT32,
               &_rainIntensity,
               "step=1");

    _controlsBar = TwNewBar("Controls");
    TwDefine(" 'Controls' size='170 85' contained=true position='625 510' "
                     "alpha=0 fontsize=1");
    TwAddButton(_controlsBar, "W, S, A, D  - move around", NULL, NULL, "");
    TwAddButton(_controlsBar, "Z, X         - move up / down", NULL, NULL, "");
    TwAddButton(_controlsBar, "LMB         - disturb water", NULL, NULL, "");
    TwAddButton(_controlsBar, "RMB         - look around", NULL, NULL, "");
    ///////////////////////////////////////////////////////////////////
//    _sceneBar = TwNewBar("Scene");
//    TwDefine(" 'Scene' size='240 160' contained=true fontsize=1");
//    TwSetParam(_sceneBar, NULL, "position", TW_PARAM_CSTRING, 1, "545 16");
//    TwAddVarRW(_sceneBar, "Light_Direction", TW_TYPE_DIR3F, &_lightDirection,
//               "showval=true open=true ");


//    TwAddSeparator(_waterBar, "", NULL);
//    TwAddVarRW(_waterBar, "particles/s", TW_TYPE_INT32,
//               &_particlesPerSecond,"step=10");
//    TwAddVarRW(_waterBar, "spread", TW_TYPE_FLOAT, &_particlesSpread,
//               "step=0.01");

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
    glfwSetMouseButtonCallback(_window,
                               CGLFWInputOutput::mouse_button_callback);
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