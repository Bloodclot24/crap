uniform float t;
varying vec3 lightDir,normal;

void main(){

  normal = normalize(gl_NormalMatrix * gl_Normal);

  lightDir = normalize(vec3(gl_LightSource[0].position));
  gl_TexCoord[0] = gl_MultiTexCoord0;

  gl_FrontColor = gl_Color;
  vec4 v = vec4(gl_Vertex);
  v.z = 0.9*t*(sin(5.0*v.x * t )*0.25)+(0.9-t)*v.z;

  gl_Position = gl_ModelViewProjectionMatrix * v;
}

