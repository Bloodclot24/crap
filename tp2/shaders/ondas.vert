uniform float t;
varying vec3 lightDir,normal;

void main(){

  normal = normalize(gl_NormalMatrix * gl_Normal);

  lightDir = normalize(vec3(gl_LightSource[0].position));
  gl_TexCoord[0] = gl_MultiTexCoord0;

  gl_FrontColor = gl_Color;
  vec4 v = vec4(gl_Vertex);

  float escala = 6.0*3.141592654*t;
  float x = v.x;
  float y = v.y;
  float z = v.z;
  float px = 0.03;
  float py = 0.02;
  float pz = 0.035;
  v.x = x + px*sin(x*escala) + py*cos(y*escala) + pz*sin(z*escala);
  v.y = y + px*cos(x*escala) + py*sin(y*escala) + pz*cos(z*escala);
  v.z = z + px*sin(x*escala) + py*sin(y*escala) + pz*sin(z*escala);

  gl_Position = gl_ModelViewProjectionMatrix * v;
}

