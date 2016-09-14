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

namespace utils {
    /**
     * In many SOIL's function error indication is in form of some specific
     * returned value. Providing this value as an argument to the function
     * will case checking source of the error and displaying it in stdout
     * stream.
     *
     * @param errorId Number of SOIL's error to check. Normally it is
     *                returned by the library functions
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
     * Checks status of OpenGL's frame buffer object. It will display an
     * appropriate message in case of any errors.
     *
     * @param errorSource In order to efficiently localizing bugs, one can
     *                    specify method (or other source) that is using the
     *                    following procedure. In that case it will be
     *                    displayed on the screen along any error that will
     *                    occur.
     */
    void checkErrorFrameBuffer(string errorSource);

    /**
     * Encapsulates the process of checking a cubemap id correctness.
     * Appropriate message is displayed in case of an error.
     *
     * @param errorSource In order to efficiently localizing bugs, one can
     *                    specify method (or other source) that is using the
     *                    following procedure. In that case it will be
     *                    displayed on the screen along any error that will
     *                    occur.
     * @param cubemapId   If of a cubemap in OpenGL's context.
     */
    void checkErrorCubemapId(string errorSource, int cubemapId);
}

#endif
