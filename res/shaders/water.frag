//==============================================================================
// Shader in charge of coloring the water surface. Based on sent position
// and its normal, refracted and reflected beams are calculated. Next, their
// intersctions with the skybox's textures are found. Using fresnel
// coefficient one acquires appropriate ratio to mix them. Such blended
// colors are assigned to the pixel.
//==============================================================================
// author: dybisz
//------------------------------------------------------------------------------
#version 330 core

struct BoundingBox{
    vec3 boxMin;
    vec3 boxMax;
};

//==============================================================================
// In
//------------------------------------------------------------------------------
in vec3             v_position;
in vec3             v_normal;
in vec2             v_textureCoords;

//==============================================================================
// Uniforms
//------------------------------------------------------------------------------
uniform sampler2D   u_heightFieldTexture;
uniform samplerCube u_skyboxTexture;
uniform BoundingBox u_box;
uniform vec3        u_cameraPosition;
uniform float       u_sideSize;
uniform vec3        u_lightDirection;
uniform bool        u_lightOn;

/**
 * Given parameters describing box and a ray, procedure finds their
 * intersections and returns the one, which lies on the directed ray.
 * Bounding box is represented by two points symbolizing its maximal and
 * minimal corner e.g. for unit cube centralized in the origin it wil be
 * (- 0.5, -0.5, -0.5) and (0.5, 0.5, 0.5), respectively.
 *
 * @param origin    The ray's origin.
 * @param direction The ray's direction. Will be normalized.
 * @param boxMax    3 dimensional point with box minimum corner.
 * @param boxMin    3 dimensional point with box maximum corner.
 *
 * @return Appropriate intersection point with bounding box.
 */
vec3 intersection(vec3 origin, vec3 direction, vec3 boxMax, vec3 boxMin) {
   direction = normalize(direction);
   vec3 tmin = (boxMin - origin)/direction;
   vec3 tmax = (boxMax - origin)/direction;

   vec3 real_min = min(tmin, tmax);
   vec3 real_max = max(tmin, tmax);

   float minmax = min( min(real_max.x, real_max.y), real_max.z);
   float maxmin = max( max(real_min.x, real_min.y), real_min.z);

   vec3 intersection = origin + (minmax * direction);
   return intersection;
}


/**
 * Using Schlick's approximation, the procedure calculates the contribution
 * of the Fresnel factor in the specular reflection of light from a
 * non-conducting interface (surface) between two media.
 *
 * @param cameraPosition   Position of the camera in world space.
 * @param fragmentPosition Position of the fragment in world space.
 * @param vertexNormal     Fragment's normal in world space.
 *
 * @return Approximated Fresnel's coefficient.
 */
float fresnel(vec3 cameraPosition, vec3 fragmentPosition, vec3 vertexNormal)
{
    vec3 toCamera = normalize(cameraPosition - fragmentPosition);
    float cosfi     = max(0.0, 1.0 - dot(toCamera, vertexNormal));
    float rzero     = pow((1.33 - 1.0) / (1.33 + 1.0), 2.0);

    return rzero + (1.0 - rzero) * pow(1.0 - cosfi, 5.0);
}

void sunLight(float shiny, float specular, float diffuse, vec3 sunColor,
              inout vec3 diffuseColor, inout vec3 specularColor) {
    vec3 reflection = normalize(reflect(normalize(u_lightDirection), v_normal));
    vec3 toCamera = normalize(u_cameraPosition - v_position);
    float direction = max(0.0, dot(toCamera, reflection));

    specularColor += pow(direction, shiny) * sunColor * specular;
    diffuseColor += max(0.0, dot(-u_lightDirection, v_normal)) * sunColor *
                    diffuse;
}

void main()
{
    // Reflected / refracted rays
    vec3  toPosition      = v_position - u_cameraPosition;
    float indicesRatio    = 1.0 / 1.33;
    vec3  reflectedVector = reflect(toPosition, v_normal);
    vec3  refractedVector = refract(toPosition, v_normal, indicesRatio);

    // Intersections with the skybox
    vec3 reflectedIntersection = intersection(v_position, reflectedVector,
                                              u_box.boxMax, u_box.boxMin);
    vec3 refractedIntersection = intersection(v_position, refractedVector,
                                              u_box.boxMax, u_box.boxMin);

    // Colors at the intersections
    vec3 reflectedColor = vec3(texture(u_skyboxTexture, reflectedIntersection));
    vec3 refractedColor = vec3(texture(u_skyboxTexture, refractedIntersection));

    // Fresnel's coefficient
    float w = fresnel(u_cameraPosition, v_position, v_normal);

    // Sun Light
    if(u_lightOn) {
        vec3 diffuse = vec3(0.0);
        vec3 specular = vec3(0.0);
        vec3 sunColor = vec3(1.0, 1.0, 1.0);
        sunLight(100.0, 2.0, 0.5, sunColor, diffuse, specular);
        vec3 mixed = mix(reflectedColor * 0.9 + specular, diffuse * refractedColor, w);
        mixed = mixed + specular;
        gl_FragColor = vec4(mixed, 1.0);

    // Plane Skybox Check
    } else {
        gl_FragColor = vec4(mix(reflectedColor, refractedColor, w), 1.0);
    }

}