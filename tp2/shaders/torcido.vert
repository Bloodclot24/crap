uniform float t;
varying vec3 lightDir,normal;

void main(){

  normal = normalize(gl_NormalMatrix * gl_Normal);

  lightDir = normalize(vec3(gl_LightSource[0].position));
  gl_TexCoord[0] = gl_MultiTexCoord0;

  gl_FrontColor = gl_Color;

  vec4 v = vec4(gl_Vertex);
  float alfa = 3.141592654/2.0;
  float xe = -0.5;
  float ze = -0.5;

  float zmax = 0.5;

  float x0 = xe - v.x;
  float z0 = v.z - ze;

  float th = z0*alfa;

  float xp  = xe - (x0 * cos(th) + z0 * sin(th));
  float zp  = -x0 * sin(th) + z0 * cos(th) + ze;

  v.x = t*xp + (1.0-t)*v.x;
  v.z = t*zp + (1.0-t)*v.z;

  gl_Position = gl_ModelViewProjectionMatrix * v;
}

