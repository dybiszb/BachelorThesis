#version 330 core

precision highp float;

in vec2 vTexCoords;
in vec3 vPosition;

uniform sampler2D heightFieldTex;
uniform samplerCube skyBoxTex;
uniform vec3 cameraPos;

void main()
{
    float ratio = 1.00 / 1.52;
    vec3 normal = vec3(0,-1,0);
    vec3 I = normalize(vPosition - cameraPos);
    vec3 Reflection = reflect(I, normalize(normal));
//    vec3 Refraction = refract(I, normalize(normal), ratio);

    vec4 colorReflection = texture(skyBoxTex,Reflection);
//    vec4 colorRefaction = texture(skyBoxTex,Refraction);

//    gl_FragColor = mix(colorReflection,colorRefaction,0.6);
    gl_FragColor = colorReflection;
}