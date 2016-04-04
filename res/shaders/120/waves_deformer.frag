#version 120

uniform sampler2D oldvalues;
uniform float sideSize;
varying vec2 texUV;

float calculateDamping(vec2 position, float sideSize) {
    float distShoreX = min(position.x, 1-position.x);
    float distShoreY = min(position.y, 1- position.y);
    float distShore = min(distShoreX, distShoreY);
    distShore = sideSize * distShore;
    return 0.99 * min(1, distShore);
}

void main()
{
  // Constants (Temporary)
  float N = sideSize;
  float h = 2. / (N - 1.);
  float c = 1.;
  float d_t = 1./(N);
  float A = (c * c * d_t * d_t) / (h * h);
  float B = 2. - 4. * A;

  // Neighbors
  float step    = 1.0 / N;
  float up      = texture2D(oldvalues, vec2(texUV.x, texUV.y + step)).r;
  float down    = texture2D(oldvalues, vec2(texUV.x, texUV.y - step)).r;
  float right   = texture2D(oldvalues, vec2(texUV.x - step, texUV.y)).r;
  float left    = texture2D(oldvalues, vec2(texUV.x + step, texUV.y)).r;
  float current = texture2D(oldvalues, vec2(texUV.x, texUV.y)).r;
  float old     = texture2D(oldvalues, texUV).g;
  float d       = calculateDamping(texUV, sideSize);
  float height = d*(A * (up + down + left + right) + B * current - old);
  gl_FragColor = vec4(height, current,0.0,0.0);

}