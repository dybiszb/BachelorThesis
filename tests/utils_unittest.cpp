//==============================================================================
// Following source file contains all tests related to functions located in
// [Project Dir]\src\utilities. Google tests framework used.
// Be careful with error handling functions tests - its order has meaning and
// it should be changed only when needed. What is more, because some of the
// tests require GLFW's window to be set up, during tests execution dummy
// windows may appear.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#include <settings_reader.h>
#include <glm/glm.hpp>
#include <src/SOIL.h>
#include "custom_camera.h"
#include "gtest/gtest.h"
#include "rays_functions.h"
#include "rand_functions.h"
#include "error_handling.h"
#include "initialize.h"
#include "cubemap_texture.h"

// TEMPORARY: for vectors/matrices print outs
#include <iostream>
#include "glm/ext.hpp"
// ---------------------------

using namespace utils;
using namespace glm;
using namespace std;
using namespace rendering;

// =============================================================================
// Tests Setup
// =============================================================================
class UtilitiesTest : public ::testing::Test {
protected:
    Settings settings = utils::readFromINI("test_config.ini");
    CCustomCamera camera;
    GLFWwindow* window;
    UtilitiesTest() : camera(settings) {
        if(!utils::initGLFW()) return;
        window = initGLFWWindow(settings.windowWidth, settings.windowHeight,
                                "Bachelor Thesis - Unit Tests");
        if (!utils::initGLEW()) return;
    }
};

// =============================================================================
// Settings Reader Tests
// =============================================================================
TEST_F(UtilitiesTest, SettingsReader_readFromINI) {
    EXPECT_EQ(false, settings.fullScreen);
    EXPECT_EQ(800, settings.windowWidth);
    EXPECT_EQ(600, settings.windowHeight);
    EXPECT_EQ(16.0f, settings.edgeSize);
    EXPECT_EQ(32, settings.quads);
}

// =============================================================================
// Rays Functions Tests
// =============================================================================
TEST_F(UtilitiesTest, RaysFunctions_toNormalizedDeviceCoordinates) {
    vec2 viewportCoordinates = vec2(400.0f, 400.0f);
    vec3 normalizedDeviceCoordinates = toNormalizedDeviceCoordinates
            (viewportCoordinates, settings.windowWidth, settings.windowHeight);
    EXPECT_EQ(0.0f, normalizedDeviceCoordinates.x);
    EXPECT_LT(-0.34f, normalizedDeviceCoordinates.y);
    EXPECT_GT(-0.3f, normalizedDeviceCoordinates.y);
    EXPECT_EQ(1.0f, normalizedDeviceCoordinates.z);
}

TEST_F(UtilitiesTest, RaysFunctions_toCameraCoordinates) {
    vec4 rayClipSpace = vec4(2.0f, 3.5f, -1.0, 1.0);
    mat4 projectionMatrix = camera.getProjectionMatrix();
    vec4 rayCameraSpace = toCameraCoordinates(rayClipSpace, projectionMatrix);
    EXPECT_GT(1.49, rayCameraSpace.x);
    EXPECT_LT(1.48, rayCameraSpace.x);
    EXPECT_GT(1.96, rayCameraSpace.y);
    EXPECT_LT(1.95, rayCameraSpace.y);
    EXPECT_EQ(-1.0f, rayCameraSpace.z);
    EXPECT_EQ(0.0f, rayCameraSpace.w);
}

TEST_F(UtilitiesTest, RaysFunctions_toWorldCoordinates) {
    vec4 rayCameraSpace = vec4(1.5f, 2.0f, -1.0, 0.0);
    mat4 viewMatrix = camera.getViewMatrix();
    vec3 rayWorldSpace = toWorldCoordinates(rayCameraSpace, viewMatrix);
    EXPECT_GT(-0.73, rayWorldSpace.x);
    EXPECT_LT(-0.74, rayWorldSpace.x);
    EXPECT_GT(0.43, rayWorldSpace.y);
    EXPECT_LT(0.42, rayWorldSpace.y);
    EXPECT_GT(0.53, rayWorldSpace.z);
    EXPECT_LT(0.52, rayWorldSpace.z);
}

TEST_F(UtilitiesTest, RaysFunctions_rayIntersectsPlane) {
    vec3 planeNormal = vec3(0.0, 1.0, 0.0);
    vec4 rayCameraSpace = vec4(1.5f, 2.0f, -1.0, 0.0);
    mat4 viewMatrix = camera.getViewMatrix();
    vec3 rayWorldSpace = toWorldCoordinates(rayCameraSpace, viewMatrix);
    vec3 cameraPosition = camera.getPosition();
    vec3 intersectionPoint = vec3(-1.0, -1.0, -1.0);
    EXPECT_EQ(false, rayIntersectsPlane(rayWorldSpace, planeNormal,
                                        cameraPosition,
                                        intersectionPoint));
    vec3 rayWorldSpace2 = vec3(0.0, -1.0f, 0.0);
    EXPECT_EQ(true, rayIntersectsPlane(rayWorldSpace2, planeNormal,
                                       cameraPosition,
                                       intersectionPoint));
}

// =============================================================================
// Rand Functions Tests
// =============================================================================
TEST_F(UtilitiesTest, RandFunctions_randomInteger) {
    int leftBoundary = -1;
    int rightBoundary = 5;
    int randInt = (int) utils::randomInteger(leftBoundary, rightBoundary);
    EXPECT_GT(rightBoundary, randInt);
    EXPECT_LT(leftBoundary - 1, randInt);
}

TEST_F(UtilitiesTest, RandFunctions_randomFloat) {
    float leftBoundary = -1.5f;
    float rightBoundary = 5.5f;
    float randInt = utils::randomFloat(leftBoundary, rightBoundary);
    EXPECT_GT(rightBoundary, randInt);
    EXPECT_LT(leftBoundary - 1.0f, randInt);
}

TEST_F(UtilitiesTest, RandFunctions_randomPointInSphere) {
    vec3 center = vec3(0.0f, 0.0f, 0.0f);
    float radius = 5.0f;
    vec3 pointInSphere = randomPointInSphere(center, radius);
    float centerPointDistance = sqrt(pow(pointInSphere.x - center.x, 2.0)
                                     + pow(pointInSphere.x - center.x, 2.0)
                                     + pow(pointInSphere.x - center.x, 2.0));

    EXPECT_GT(centerPointDistance, 0.0f);
    EXPECT_LT(centerPointDistance, radius);
}

// =============================================================================
// Error Handling Functions Tests
// =============================================================================
TEST_F(UtilitiesTest, ErrorHandling_checkErrorSOIL_Error) {
    testing::internal::CaptureStdout();
    checkErrorSOIL(0);
    std::string outputError = testing::internal::GetCapturedStdout();
    EXPECT_GT(outputError.size(), (unsigned int) 0);
}

TEST_F(UtilitiesTest, ErrorHandling_checkErrorSOIL_NoError) {
    testing::internal::CaptureStdout();
    checkErrorSOIL(1);
    std::string outputCorrect = testing::internal::GetCapturedStdout();
    EXPECT_EQ(outputCorrect.size(), (unsigned int) 0);
}

TEST_F(UtilitiesTest, ErrorHandling_checkErrorOpenGL_NoError) {
    testing::internal::CaptureStdout();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    checkErrorOpenGL("unit-tests");
    std::string outputCorrect = testing::internal::GetCapturedStdout();
    EXPECT_EQ(outputCorrect.size(), (unsigned int) 0);
}

TEST_F(UtilitiesTest, ErrorHandling_checkErrorOpenGL_Error) {
    testing::internal::CaptureStdout();
    glBindTexture(GL_TEXTURE0, (GLuint) -1);
    checkErrorOpenGL("unit-tests");
    std::string outputError = testing::internal::GetCapturedStdout();
    EXPECT_GT(outputError.size(), (unsigned int) 0);
}

TEST_F(UtilitiesTest, ErrorHandling_checkErrorCubemapId_NoError) {
    const char* testFaces[6]= {
            "./res/textures/hw_nightsky/nightsky_ft.tga",
            "./res/textures/hw_nightsky/nightsky_bk.tga",
            "./res/textures/hw_nightsky/nightsky_up.tga",
            "./res/textures/hw_nightsky/nightsky_dn.tga",
            "./res/textures/hw_nightsky/nightsky_rt.tga",
            "./res/textures/hw_nightsky/nightsky_lf.tga"
    };
    testing::internal::CaptureStdout();
    CCubemapTexture cubemapTexture(testFaces);
    checkErrorCubemapId("unit-tests", cubemapTexture.getId());
    std::string outputCorrect = testing::internal::GetCapturedStdout();
    EXPECT_EQ(outputCorrect.size(), (unsigned int) 0);
}