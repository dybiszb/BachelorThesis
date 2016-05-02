//==============================================================================
// In charge of updating time lapsed. It solely relies on GLFW's procedures.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef TIMER_H
#define TIMER_H

#include <glfw3.h>

class CTimer {
public:

    CTimer();

    /**
     * @return Difference in seconds between current and last call of the
     *         procedure.
     */
    float tick();
private:
    double _lastTime;

};


#endif
