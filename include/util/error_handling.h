//==============================================================================
// Set of auxiliary methods for error checking.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <iostream>
#include <src/SOIL.h>
#include <GL/glew.h>
#include <string>

using namespace std;

namespace util {
    /**
     * In many SOIL's function error indication is in form of some specific
     * returned value. Providing this value as an argument to the function
     * will case checking source of the error and displaying it in stdout
     * stream.
     *
     * @param TODO
     */
    void checkErrorSOIL(int errorId);

    /**
     * Basic error check in OpenGL context. If something unwanted occured
     * appropriate message with error number will be displayed in stdout stream.
     *
     * @param errorSource Represents name of the place that caused an error.
     *                    One can supply everything that suits his/her needs.
     */
    void checkErrorOpenGL(string errorSource);

    /**
     * TODO
     */
    void checkErrorFrameBuffer(string errorSource);

    /**
     * TODO
     */
    void checkErrorCubemapId(string errorSource, int cubemapId);
}

#endif
