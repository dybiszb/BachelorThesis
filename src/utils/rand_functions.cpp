// author: dybisz

#include "rand_functions.h"

bool utils::seeded = false;

void utils::seed() {
    if (!seeded) {
        srand(static_cast <unsigned> (time(0)));
        seeded = true;
    }
}
float utils::randomInteger(int lBoundary, int rBoundary) {
    return rand() % rBoundary + lBoundary;

}

// TODO swap to template
float utils::randomFloat(float lBoundary, float rBoundary) {
    return lBoundary +
           static_cast <float> (rand()) / (static_cast <float>
           (RAND_MAX / (rBoundary - lBoundary)));
}

vec3 utils::randomPointInSphere(vec3 center, float R) {
    float pi = 3.14159265;
    vec3 randomPoint(0.0f, 0.0f, 0.0f);

    /* ----- Randomize Parameters ----- */
    float phi      = utils::randomFloat(0.0f, 2.0f * pi);
    float cosTheta = utils::randomFloat(-1.0f, 1.0f);
    float u        = utils::randomFloat(0.0f, 1.0f);
    float theta    = acos(cosTheta);
    float r        = R * cbrt(u);

    /* ----- Convert to Cartesian ----- */
    randomPoint.x = r * sin(theta) * cos(phi);
    randomPoint.y = r * sin(theta) * sin(phi);
    randomPoint.z = r * cos(theta);

    return randomPoint;
}



