#version 120

varying vec2 vTexCoords;
varying vec3 vPosition;
varying vec4 vColor;
varying vec3 vLightDirection;
varying vec3 vNormal;
varying vec3 vVertexCameraspace;

uniform vec3 lightPos;
uniform sampler2D heightFieldTex;
uniform samplerCube skyBoxTex;
uniform vec3 cameraPos;
uniform float sideSize;
uniform int verticesPerSide;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;



vec3 inter(vec3 orig, vec3 dir, vec3 box_max, vec3 box_min) {
   vec3 tmin = (box_min - orig)/dir;
   vec3 tmax = (box_max - orig)/dir;

   vec3 real_min = min(tmin, tmax);
   vec3 real_max = max(tmin, tmax);

   float minmax = min( min(real_max.x, real_max.y), real_max.z);
   float maxmin = max( max(real_min.x, real_min.y), real_min.z);

   vec3 intersection = orig + (minmax * dir);
   return intersection;
}

const float rzero = pow((1.33 - 1.0)/(1.33 + 1.0), 2.0);
// Schlicks aproximation
float fresnel(float cosfi)
{
    return rzero + (1.0-rzero) * pow(1.0-cosfi, 5.0);
}

void main()
{
    // Boundary calculations. Should be passed as a uniform.
    vec3 box[2];
    float halfSide = sideSize/2;
    box[0] = vec3(-halfSide,-halfSide,-halfSide);
    box[1] = vec3(halfSide,halfSide,halfSide);

    // Color calculation
    vec3 n = vec3(0.0, 1.0, 0.0);
    vec3 l = normalize(vLightDirection);
    vec3 reflectedVector = reflect(vPosition - cameraPos, vNormal);
    vec3 refractedVector = refract(vPosition - cameraPos, vNormal, 1.0 / 1.53);

    vec3 reflectedIntersection = inter(vPosition, reflectedVector, box[1], box[0]);
    vec3 refractedIntersection = inter(vPosition, refractedVector, box[1], box[0]);

    vec4 reflectedColor = textureCube(skyBoxTex, reflectedIntersection);
    vec4 refractedColor =  textureCube(skyBoxTex, refractedIntersection);

    float cosTheta = clamp(dot(n,l), 0.0, 1.0);


    //float cosPhi = doat(normalize(cameraPos - vPosition), );
    float w = fresnel(abs(normalize(vPosition - cameraPos).y));
     gl_FragColor = mix(reflectedColor, refractedColor, 0.3);
}