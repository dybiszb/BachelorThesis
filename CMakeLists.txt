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
# External Libraries
#-------------------------------------------------------------------------------
add_subdirectory (external)

include_directories(
        external/AntTweakBar-1.16/include/
        external/glew-1.13.0/include/
        external/glfw-3.1.2/include/GLFW/
        external/glm-0.9.7.1/
        external/SOIL_/
)

set(EXTERNAL_LIBS
        ${OPENGL_LIBRARY}
        SOIL
        glfw
        GLEW_1130
        ANTTWEAKBAR_116_OGLCORE_GLFW
)

#===============================================================================
# Project's Includes
#-------------------------------------------------------------------------------
include_directories(
        include/application
        include/entities
        include/entities/builders
        include/geometry
        include/rendering/buffers
        include/rendering/textures
        include/rendering
        include/util
        res/
)

#===============================================================================
# Project's Sources
#-------------------------------------------------------------------------------
set(
        SOURCE_FILES
        src/application/camera.cpp
        src/application/glfw_io.cpp
        src/application/glfw_renderer.cpp
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
        src/rendering/textures/texture2D.cpp
        src/rendering/glsl_shader.cpp
        src/rendering/renderable_object.cpp
        src/util/error_handling.cpp
        src/util/rand_functions.cpp
        src/util/waves_deformer.cpp
        src/main.cpp
)

#===============================================================================
# Executable
#-------------------------------------------------------------------------------
add_executable(bachelor_water ${SOURCE_FILES})

#===============================================================================
# Linking
#-------------------------------------------------------------------------------
target_link_libraries (bachelor_water ${EXTERNAL_LIBS})

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
# Custom Commands
#-------------------------------------------------------------------------------
add_custom_command(
        TARGET bachelor_water PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory   # Copy resources
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:bachelor_water>/res
)