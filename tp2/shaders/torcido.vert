uniform float t;
uniform mat4 matriz_mv;

void calcular_iluminacion(vec3 orig_normal, vec4 posicion);

vec3 torcer(vec3 original);

void main(){

  vec4 v = vec4(torcer(vec3(gl_Vertex)),1);
  
  vec3 normal = torcer(gl_Normal);

  calcular_iluminacion(normal,v);

  gl_Position = gl_ProjectionMatrix * matriz_mv * gl_ModelViewMatrix* v;
}

vec3 torcer(vec3 original){
  float alfa = 3.141592654/4.0;
  float xe = 1.0;
  float ze = -0.5;

  float x0 = xe - original.x;
  float z0 = original.z - ze;

  float th = z0*alfa;
	
  float xp  = xe - cos(th)*x0;
  float zp  = sin(th)*x0 + ze;
  
  original.x = t*xp + (1.0-t)*original.x;
  original.z = t*zp + (1.0-t)*original.z;
  return original;
}
