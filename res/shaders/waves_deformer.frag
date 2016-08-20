//==============================================================================
// The shader using Euler method calculates next step in shallow water
// equations.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#version 330 core
//precision highp float;

#define NONE                 0
#define UP_NEIGHBOUR         1.0
#define DOWN_NEIGHBOUR      -1.0
#define LEFT_NEIGHBOUR       1.0
#define RIGHT_NEIGHBOUR     -1.0

struct MembraneEqProperties {
    float h;
    float c;
    float dt;
    float dtOverall;
};

//==============================================================================
// In
//------------------------------------------------------------------------------
in vec2                      v_heightFieldTexCoords;

//==============================================================================
// Uniforms
//------------------------------------------------------------------------------
uniform sampler2D            u_heightFieldTexture;
uniform float                u_sideSize;
uniform int                  u_verticesPerSide;
uniform MembraneEqProperties u_membraneProperties;
uniform int                  u_isPerlinNoiseCalculations;
uniform float                u_wavesAmplitude;
uniform float                u_wavesFrequency;
uniform float                u_wavesChoppiness;
uniform float                u_wavesResoulutionX;
uniform float                u_wavesResoulutionY;

/**
 * Calculates damping according to distance between the fragment and closest
 * shore. As a fragment's position, the procedure uses its UV coordinates on
 * heightfield texture.
 *
 * @param position Fragment's UV heightfield texture coordinates.
 */
float calculateDamping(vec2 position) {
    float distShoreX = min(position.x, 1.0 - position.x);
    float distShoreY = min(position.y, 1.0 - position.y);
    float distShore  = max(distShoreX, distShoreY);
    distShore = u_sideSize * distShore;
    return 0.99 * min(1, distShore/(1.5));
}

/**
 * Retrieves height of specified neighbour. All eight neighbors can be
 * access.
 *
 * @param uModifier Left (1.0) or right (-1.0) neighbor. 0 will represent none.
 * @param vModifier Up   (1.0) or down  (-1.0) neighbor. 0 will represent none.
 */
float getNeighbour(float uModifier, float vModifier) {
    float step = 1.0 / float(u_verticesPerSide);
    return texture
           (
           u_heightFieldTexture,
               vec2
               (
                    v_heightFieldTexCoords.x - uModifier * step,
                    v_heightFieldTexCoords.y - vModifier * step
               )
           ).r;
}
float dividedDifferencies(float up, float down, float left, float right,
                         float current, float old) {
    float A = (u_membraneProperties.c * u_membraneProperties.c *
               u_membraneProperties.dt * u_membraneProperties.dt) /
              (u_membraneProperties.h * u_membraneProperties.h);
    float B = 2. - 4. * A;
    return (A * (up + down + left + right)) + (B * current) - old;
}
/**
 * TODO
 */
float hash( vec2 p ) {
    float h = dot(p,vec2(127.1,311.7));
    return fract(sin(h)*43758.5453123);
}

/**
 * TODO
 */
float noise( in vec2 p ) {
    vec2 i = floor( p );
    vec2 f = fract( p );
    vec2 u = f*f*(3.0-2.0*f);
    return -1.0+2.0*mix(
                mix( hash( i + vec2(0.0,0.0) ),
                     hash( i + vec2(1.0,0.0) ),
                        u.x),
                mix( hash( i + vec2(0.0,1.0) ),
                     hash( i + vec2(1.0,1.0) ),
                        u.x),
                u.y);
}

// sea
// bteitler: TLDR is that this passes a low frequency random terrain through a 2D symmetric wave function that looks like this:
// http://www.wolframalpha.com/input/?i=%7B1-%7B%7B%7BAbs%5BCos%5B0.16x%5D%5D+%2B+Abs%5BCos%5B0.16x%5D%5D+%28%281.+-+Abs%5BSin%5B0.16x%5D%5D%29+-+Abs%5BCos%5B0.16x%5D%5D%29%7D+*+%7BAbs%5BCos%5B0.16y%5D%5D+%2B+Abs%5BCos%5B0.16y%5D%5D+%28%281.+-+Abs%5BSin%5B0.16y%5D%5D%29+-+Abs%5BCos%5B0.16y%5D%5D%29%7D%7D%5E0.65%7D%7D%5E4+from+-20+to+20
// The <choppy> parameter affects the wave shape.
float sea_octave(vec2 uv, float choppy) {
    uv += noise(uv);
    vec2 wv = 1.0-abs(sin(uv));
    vec2 swv = abs(cos(uv));
    wv = mix(wv,swv,wv);
    return pow(1.0-pow(wv.x * wv.y,0.65),choppy);
}

float map_detailed() {
    mat2 octave_m = mat2(1.6,1.2,-1.2,1.6);
    float freq = u_wavesFrequency;
    float amp = u_wavesAmplitude;
    float choppy = u_wavesChoppiness;
    vec2 uv = v_heightFieldTexCoords;
    uv.x *= u_wavesResoulutionX;
    uv.y *= u_wavesResoulutionY;

    float d, h = 0.0;
    for(int i = 0; i < 5; i++) {
        // bteitler: start out with our 2D symmetric wave at the current frequency
    	d = sea_octave((uv+u_membraneProperties.dtOverall * 0.01)*freq,choppy);
        // bteitler: stack wave ontop of itself at an offset that varies over time for more height and wave pattern variance
    	d += sea_octave((uv-u_membraneProperties.dtOverall * 0.01)*freq,choppy);

        h += d * amp; // bteitler: Bump our height by the current wave function

        // bteitler: "Twist" our domain input into a different space based on a permutation matrix
        // The scales of the matrix values affect the frequency of the wave at this iteration, but more importantly
        // it is responsible for the realistic assymetry since the domain is shiftly differently.
        // This is likely the most important parameter for wave topology.
    	uv *= octave_m;

        freq *= 1.9; // bteitler: Exponentially increase frequency every iteration (on top of our permutation)
        amp *= 0.22; // bteitler: Lower the amplitude every frequency, since we are adding finer and finer detail
        // bteitler: finally, adjust the choppy parameter which will effect our base 2D sea_octave shape a bit.  This makes
        // the "waves within waves" have different looking shapes, not just frequency and offset
        choppy = mix(choppy,1.0,0.2);
    }
    return h - 0.75;
}

vec4 calculatePerlinNoiseColor(){
    float hei = map_detailed();
    return vec4(hei + getNeighbour(NONE,            NONE), 0.0, 0.0, 0.0);
}

vec4 calculateWaterDisturbance() {
    float up      = getNeighbour(NONE,            UP_NEIGHBOUR);
    float down    = getNeighbour(NONE,            DOWN_NEIGHBOUR);
    float left    = getNeighbour(LEFT_NEIGHBOUR,  NONE);
    float right   = getNeighbour(RIGHT_NEIGHBOUR, NONE);
    float current = getNeighbour(NONE,            NONE);
    float old     = texture2D(u_heightFieldTexture, v_heightFieldTexCoords).g;
    float oldV    = texture2D(u_heightFieldTexture, v_heightFieldTexCoords).b;

    float d       = calculateDamping(v_heightFieldTexCoords);

    float height = d * dividedDifferencies(up, down, left, right, current, old);
    return vec4(height, current, oldV, 0.0);
}

void main()
{
    if(u_isPerlinNoiseCalculations == 1) {
        gl_FragColor = calculatePerlinNoiseColor();
    } else {
        gl_FragColor = calculateWaterDisturbance();
    }
}