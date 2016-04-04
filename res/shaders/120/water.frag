#version 120

varying vec2 vTexCoords;
varying vec3 vPosition;

uniform vec3 lightPos;
uniform sampler2D heightFieldTex;
uniform samplerCube skyBoxTex;
uniform vec3 cameraPos;
uniform float sideSize;

vec3 inter(vec3 orig, vec3 dir, vec3 box_max, vec3 box_min) {
   vec3 tmin = (box_min - orig)/dir;
   vec3 tmax = (box_max - orig)/dir;

   vec3 real_min = min(tmin, tmax);
   vec3 real_max = max(tmin, tmax);

   float minmax = min( min(real_max.x, real_max.y), real_max.z);
   float maxmin = max( max(real_min.x, real_min.y), real_min.z);

   vec3 intersection = orig + (maxmin * dir);
   return intersection;
}

float phongShading(vec3 normal, vec3 lightPos, vec3 cameraPos) {
    vec4 outputColor = vec4(0.0, 0.0, 0.0, 0.0);

    vec3 L = normalize(lightPos - vPosition);
    vec3 E = normalize(-cameraPos);
    // we are in Eye Coordinates, so EyePos is (0,0,0)
    vec3 R = normalize(-reflect(L,normal));
//    vec4 Kd = vec4(0.0f, 0.5f, 0.5f, 1.0f);
//    vec4 diffuse = Kd * max(dot(normal,L),0.0);
//    diffuse = clamp(diffuse, 0.0, 1.0);
//
//    outputColor += diffuse;
//    return outputColor;
return  max(dot(normal,L),0.0);
}

const float rzero = pow((1.33 - 1.0)/(1.33 + 1.0), 2.0);
float fresnel(float cosfi)
{
    return rzero + (1.0-rzero) * pow(1.0-cosfi, 5.0);
}

vec3 calculateNormal() {
  float current = texture2D(heightFieldTex, vec2(vTexCoords.x, vTexCoords.y)).r;
  if(current < 0.1) {
    return vec3(0,-1,0);
  }
  float step    = 1. / sideSize;
  float up      = texture2D(heightFieldTex, vec2(vTexCoords.x, vTexCoords.y + step)).r;
  float down    = texture2D(heightFieldTex, vec2(vTexCoords.x, vTexCoords.y - step)).r;
  float right   = texture2D(heightFieldTex, vec2(vTexCoords.x - step, vTexCoords.y)).r;
  float left    = texture2D(heightFieldTex, vec2(vTexCoords.x + step, vTexCoords.y)).r;

  vec3 n1 = normalize(vec3(1.0, down- up,0.0));
  vec3 n2 = normalize(vec3(0.0, left - right,1.0));

  return normalize(cross(n2, n1));
}

void main()
{
    // Boundary calculations. Should be passed as a uniform.
    vec3 box[2];
    float halfSide = sideSize/2;
    box[0] = vec3(-halfSide,-halfSide,-halfSide);
    box[1] = vec3(halfSide,halfSide,halfSide);

    float ratio = 1.00 / 1.52;
    vec3 normal = calculateNormal();
    vec3 I = normalize(vPosition - cameraPos);
    vec3 Reflection = reflect(-I, normalize(normal));
    vec3 Refraction = refract(-I, normalize(normal), ratio);

    vec3 reflecionTex = inter(vPosition, Reflection, box[1], box[0]);
    vec3 refractionTex = inter(vPosition, Refraction, box[1], box[0]);

    vec4 colorReflection = textureCube(skyBoxTex,reflecionTex);
    vec4 colorRefraction = textureCube(skyBoxTex,refractionTex);
    float colorPhong      = phongShading(normal, lightPos, I);
    float w = fresnel(abs(normalize(I).y));

    gl_FragColor =  mix(colorReflection, colorRefraction, w);
//     gl_FragColor = colorPhong;

    //gl_FragColor = texture2D(heightFieldTex, vTexCoords);
}