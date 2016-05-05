//==============================================================================
// Set of functions, which perform randomization of different sorts. It
// includes seeding procedure.
// =============================================================================
// author: dybisz
//------------------------------------------------------------------------------

#ifndef RAND_FUNCTIONS_H
#define RAND_FUNCTIONS_H

#include <glm/glm.hpp>
#include <cstdlib>
#include <math.h>
#include <ctime>

using namespace glm;

namespace utils {

        /**
         * Protects against multiple seeding.
         */
        extern bool seeded;

        /**
         * Seeds random numbers. Must be called one time, preferably at the
         * beginning of the application.
         */
        void seed();

        /**
         * Generates random integer from [lBoundary, rBoundary] interval
         * (inclusively). Implementation follows: http://stackoverflow.com/
         * questions/686353/c-random-float-number-generation
         *
         * @param lBoundary Minimum number that can be randomly chosen.
         * @param rBoundary Maximum number that can be randomly chosen.
        */
        float randomInteger(int lBoundary, int rBoundary);

        /**
         * Generates random number from [lBoundary, rBoundary] interval
         * (inclusively). Implementation follows: http://stackoverflow.com/
         * questions/686353/c-random-float-number-generation
         *
         * @param lBoundary Minimum number that can be randomly chosen.
         * @param rBoundary Maximum number that can be randomly chosen.
         */
        float randomFloat(float lBoundary, float rBoundary);

        /**
         * Randomly generates point within a specified sphere. Procedure
         * based on python implementation presented under following link:
         * http://stackoverflow.com/questions/5408276/sampling-uniformly-
         * distributed-random-points-inside-a-spherical-volume
         *
         * @param center Point, which represents center of the spawn sphere.
         * @param R      Radius of the spawn sphere.
         */
        vec3 randomPointInSphere(vec3 center, float R);
}

#endif
