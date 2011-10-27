uniform float t;
uniform mat4 matriz_mv;

void calcular_iluminacion(vec3 orig_normal, vec4 posicion);

vec3 ondular(vec3 entrada);

void main(){

  vec4 v = vec4(ondular(vec3(gl_Vertex)),1);

  float escala = 6.0*3.141592654*t;

  float xt = 1.0 + 0.03*escala*cos(v.x*escala);
  float yt = 1.0 + 0.02*escala*cos(v.y*escala);
  float zt = 1.0 + 0.035*escala*cos(v.z*escala);

  vec3 normal = gl_Normal* (1.0-t) + vec3(xt, yt, zt) * t;
  
  calcular_iluminacion(normal, v);

  gl_Position = gl_ProjectionMatrix * matriz_mv * gl_ModelViewMatrix * v;

}

vec3 ondular(vec3 entrada){
  float escala = 6.0*3.141592654*t;
  float x = entrada.x;
  float y = entrada.y;
  float z = entrada.z;
  float px = 0.03;
  float py = 0.02;
  float pz = 0.035;
  entrada.x = x + px*sin(x*escala) + py*cos(y*escala) + pz*sin(z*escala);
  entrada.y = y + px*cos(x*escala) + py*sin(y*escala) + pz*cos(z*escala);
  entrada.z = z + px*sin(x*escala) + py*cos(y*escala) + pz*sin(z*escala);
  return entrada;
}