#version 330 core

in vec2 TexCoords;
in vec3 v_normal;
in vec3 v_position;
out vec4 color;

uniform sampler2D texture_diffuse;
uniform vec3      u_directionalLight;
uniform vec3 u_cameraPosition;

void phongDirectionalLight(float shiny,
                           float specular,
                           float diffuse,
                           vec3 sourceColor,
                           inout vec3 diffuseColor,
                           inout vec3 specularColor) {
    vec3 reflection = normalize(reflect(normalize(u_directionalLight), v_normal));
    vec3 toCamera = normalize(u_cameraPosition - v_position);
    float direction = max(0.0, dot(toCamera, reflection));

    specularColor += pow(direction, shiny) * sourceColor * specular;
    diffuseColor += max(0.0, dot(-u_directionalLight, v_normal)) * sourceColor *
                    diffuse;
}

void main()
{
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    vec3 moonColor = vec3(0.7, 0.7, 0.7);
    phongDirectionalLight(100.0, 2.0, 0.5, moonColor, diffuse, specular);
    vec3 finalColor = (vec3(0.1f, 0.1f, 0.1f) + diffuse) * vec3(texture
    (texture_diffuse,
    TexCoords));
    color = vec4(finalColor, 1.0f);
}