cmake_minimum_required(VERSION 2.8.4)
project(BachelorWater)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#
#if (NOT WIN32)
#    set(CMAKE_MODULE_PATH /usr/local/lib/cmake /usr/local/lib/x86_64-linux-gnu/cmake)
#    set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw)
#endif (NOT WIN32)
#
#find_package (OpenGL REQUIRED)
#if (WIN32)
#include_directories("D:/Libs/GLFW/include" "D:/Libs/GLM" "D:/Libs/GLEW/include")
#link_directories("D:/Libs/GLEW/lib/Release/x64" "D:/Libs/GLFW/lib-mingw" )
#else (WIN32)
#    find_package (glfw3 REQUIRED)
#    find_package (GLM REQUIRED)
#    find_package (GLEW REQUIRED STATIC)
#endif (WIN32)

###################################################
#                EXTERNAL LIBS                    #
###################################################
add_subdirectory (external)

include_directories(
        external/glew-1.13.0/include/
        external/glfw-3.1.2/include/GLFW/
        external/glm-0.9.7.1/
        external/soil/
)

set(EXTERNAL_LIBS
        ${OPENGL_LIBRARY}
        SOIL
        glfw
        GLEW_1130
)

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

include_directories(
        include/util
        include/entities
        include/rendering
        include/rendering/buffers
        include/rendering/textures
        include/geometry
        include/camera
        res/
)

set(SOURCE_FILES
        src/main.cpp
        src/util/error_handling.cpp                 #done
        src/rendering/renderable_object.cpp         #done
        src/rendering/buffers/vertex_array.cpp              #done
        src/rendering/buffers/buffer.cpp                    #done
        src/rendering/textures/cubemap_texture.cpp           #done
        src/rendering/glsl_shader.cpp
        src/camera/fps_camera.cpp
        src/entities/water_grid.cpp
        src/entities/skybox.cpp                     #done
        src/geometry/grid.cpp                       #done
        src/geometry/cube.cpp
        src/rendering/textures/texture2D.cpp
        src/rendering/buffers/frame_buffer.cpp
        src/util/waves_deformer.cpp
        src/geometry/quad.cpp include/geometry/quad.h)

## "sample" is the name of the executable
add_executable(bachelor_water ${SOURCE_FILES})
target_link_libraries (bachelor_water
        ${EXTERNAL_LIBS})

if (WIN32)
    target_link_libraries (bachelor_water
            ${EXTERNAL_LIBS})
endif (WIN32)

if (UNIX)
    target_link_libraries (bachelor_water
            ${OPENGL_LIBRARIES}
            ${GLFW3_LIBRARY}
            ${GLEW_LIBRARY}
            Xxf86vm pthread Xrandr Xinerama Xi Xcursor)
endif (UNIX)

# Copy resources
add_custom_command(TARGET bachelor_water PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:bachelor_water>/res)