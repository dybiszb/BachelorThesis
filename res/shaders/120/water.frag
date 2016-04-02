#version 120

varying vec2 vTexCoords;
varying vec3 vPosition;

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

void main()
{
    // Boundary calculations. Should be passed as a uniform.
    vec3 box[2];
    float halfSide = sideSize/2;
    box[0] = vec3(-halfSide,-halfSide,-halfSide);
    box[1] = vec3(halfSide,halfSide,halfSide);

    float ratio = 1.00 / 1.52;
    vec3 normal = vec3(0,-1,0);
    vec3 I = normalize(vPosition - cameraPos);
    vec3 Reflection = reflect(I, normalize(normal));
    vec3 Refraction = refract(I, normalize(-normal), ratio);

    vec3 reflecionTex = inter(vPosition, -Reflection, box[1], box[0]);
    vec3 refractionTex = inter(vPosition, -Refraction, box[1], box[0]);

    vec4 colorReflection = textureCube(skyBoxTex,reflecionTex);
    vec4 colorRefraction = textureCube(skyBoxTex,refractionTex);

    gl_FragColor = mix(colorReflection, colorRefraction, 0.5);
//gl_FragColor = texture2D(heightFieldTex, vTexCoords);
}