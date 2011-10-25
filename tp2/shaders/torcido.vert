uniform float t;
varying vec3 lightDir,normal;

void main(){

  normal = normalize(gl_NormalMatrix * gl_Normal);

  lightDir = normalize(vec3(gl_LightSource[0].position));
  gl_TexCoord[0] = gl_MultiTexCoord0;

  gl_FrontColor = gl_Color;

  vec4 v = vec4(gl_Vertex);
  float alfa = 3.141592654/4.0;
  float xe = 1.0;
  float ze = -0.5;

  float x0 = xe - v.x;
  float z0 = v.z - ze;

  float th = z0*alfa;
	
  float xp  = xe - cos(th)*x0;
  float zp  = sin(th)*x0 + ze;
  
  v.x = t*xp + (1.0-t)*v.x;
  v.z = t*zp + (1.0-t)*v.z;

  gl_Position = gl_ModelViewProjectionMatrix * v;
}

