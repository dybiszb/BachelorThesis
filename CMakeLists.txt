#===============================================================================
# File assures cross-platform compilation. All external libraries are compiled
# in the process. Resources folder is copied to the output directory.
#==============================================================================
# author: dybisz
#-------------------------------------------------------------------------------

#===============================================================================
# General Settings
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8.4)
project(BachelorThesis)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=gnu++0x")


#===============================================================================
# Definitions
#-------------------------------------------------------------------------------
add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)


#===============================================================================
# External Libraries
#-------------------------------------------------------------------------------
add_subdirectory (external)

include_directories(
        external/AntTweakBar-1.16/include/
        external/glew-1.13.0/include/
        external/glfw-3.1.2/include/GLFW/
        external/glm-0.9.7.1/
        external/inih/cpp/
        external/inih/
        external/SOIL_/
        external/tinyobjloader/
        external/PhysX/include/
        external/PhysX/include/characterkinematic/
        external/PhysX/include/cloth/
        external/PhysX/include/common/
        external/PhysX/include/cooking/
        external/PhysX/include/extensions/
        external/PhysX/include/foundation/
        external/PhysX/include/geometry/
        external/PhysX/include/gpu/
        external/PhysX/include/particles/
        external/PhysX/include/physxprofilesdk/
        external/PhysX/include/physxvisualdebuggersdk/
        external/PhysX/include/pvd/
        external/PhysX/include/pxtask/
        external/PhysX/include/vehicle/
)

set(EXTERNAL_LIBS
        ${OPENGL_LIBRARY}
        SOIL
        glfw
        GLEW_1130
        ANTTWEAKBAR_116_OGLCORE_GLFW
        INIH
        tinyobjloader
        )

#===============================================================================
# Project's Includes
#-------------------------------------------------------------------------------
include_directories(
        include/application/builders
        include/application
        include/entities
        include/entities/builders
        include/entities/bounding
        include/geometry
        include/rendering/buffers
        include/rendering/textures
        include/rendering
        include/utils
        res/
)

#===============================================================================
# Project's Sources
#-------------------------------------------------------------------------------
set(
        SOURCE_FILES
        src/application/custom_camera.cpp
        src/application/glfw_io.cpp
        src/application/glfw_renderer.cpp
        src/application/glfw_timer.cpp
        src/entities/builders/water_builder.cpp
        src/entities/builders/skybox_builder.cpp
        src/entities/skybox_cube.cpp
        src/entities/water_grid.cpp
        src/geometry/cube.cpp
        src/geometry/grid.cpp
        src/geometry/quad.cpp
        src/rendering/buffers/buffer.cpp
        src/rendering/buffers/frame_buffer.cpp
        src/rendering/buffers/vertex_array.cpp
        src/rendering/textures/cubemap_texture.cpp
        src/rendering/textures/texture_2D.cpp
        src/rendering/glsl_shader.cpp
        src/rendering/renderable_object.cpp
        src/utils/error_handling.cpp
        src/utils/rand_functions.cpp
        src/utils/rays_functions.cpp
        src/utils/waves_deformer.cpp
        src/main.cpp
        src/application/atw_gui.cpp
        src/application/builders/atw_bar_builder.cpp
        src/application/builders/atw_button_builder.cpp
        src/application/builders/atw_var_builder.cpp
        src/utils/settings_reader.cpp
        src/entities/ship_model.cpp
        src/utils/obj_model.cpp
        src/entities/bounding/computational_cell.cpp
        src/entities/bounding/computational_grid.cpp
        src/utils/physx_simulation.cpp
        src/utils/initialize.cpp)

#===============================================================================
# Executable
#-------------------------------------------------------------------------------
link_directories(${CMAKE_SOURCE_DIR}/external/PhysX/lib/vc15_x86/)
link_directories(${CMAKE_SOURCE_DIR}/external/assimp/lib/)
add_executable(bachelor_water ${SOURCE_FILES})

#===============================================================================
# Linking
#-------------------------------------------------------------------------------
target_link_libraries (bachelor_water ${EXTERNAL_LIBS})

#===============================================================================
# Testing
#-------------------------------------------------------------------------------
enable_testing()
include_directories(
        external/googletest/googletest/include/
        external/googletest/googletest/
        tests/)

set(TEST_SOURCES
        tests/utils_unittest.cpp
        src/utils/settings_reader.cpp
        src/utils/rays_functions.cpp
        src/application/custom_camera.cpp
        src/utils/rand_functions.cpp
        src/utils/error_handling.cpp
        src/utils/initialize.cpp
        src/rendering/textures/cubemap_texture.cpp
        src/utils/obj_model.cpp
        src/rendering/buffers/buffer.cpp
        src/rendering/buffers/frame_buffer.cpp
        src/rendering/buffers/vertex_array.cpp
        src/rendering/textures/texture_2D.cpp
        src/rendering/glsl_shader.cpp
        src/rendering/renderable_object.cpp)

add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests gtest gtest_main)
target_link_libraries(unit_tests ${EXTERNAL_LIBS})
add_test(NAME test COMMAND unit_tests)
set_target_properties(unit_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:bachelor_water>/tests)
add_custom_command(
        TARGET unit_tests
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/tests/run_tests.bat
        $<TARGET_FILE_DIR:bachelor_water>/tests)
# Config Files
add_custom_command(
        TARGET unit_tests
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/tests/test_config.ini
        $<TARGET_FILE_DIR:bachelor_water>/tests)
# Resources
add_custom_command(
        TARGET unit_tests PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory   # Copy resources
        ${CMAKE_SOURCE_DIR}/tests/test_resources
        $<TARGET_FILE_DIR:unit_tests>/resources
)

#===============================================================================
# Copy Installer Sources
#-------------------------------------------------------------------------------
add_custom_command(
        TARGET bachelor_water POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/win_installer
        $<TARGET_FILE_DIR:bachelor_water>/win_installer
)
#===============================================================================
# Copy Resources
#-------------------------------------------------------------------------------
add_custom_command(
        TARGET bachelor_water PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory   # Copy resources
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:bachelor_water>/res
)

#===============================================================================
# Copy Configuration Files
#-------------------------------------------------------------------------------
file(GLOB ConfigFiles ${CMAKE_SOURCE_DIR}/config/*.ini)

foreach(ConfigFiles ${ConfigFiles})
    add_custom_command(
            TARGET bachelor_water PRE_BUILD COMMAND ${CMAKE_COMMAND} -E
            copy  ${ConfigFiles} $<TARGET_FILE_DIR:bachelor_water>
    )
endforeach()

#===============================================================================
# Copy Dlls
#-------------------------------------------------------------------------------
file(GLOB DllFiles
        ${CMAKE_SOURCE_DIR}/external/PhysX/bin/vc15_x86/*.dll
        ${CMAKE_SOURCE_DIR}/external/assimp/bin/*.dll)

foreach(DllFiles ${DllFiles})
    add_custom_command(
            TARGET bachelor_water PRE_BUILD COMMAND ${CMAKE_COMMAND} -E
            copy  ${DllFiles} $<TARGET_FILE_DIR:bachelor_water>
    )
endforeach()