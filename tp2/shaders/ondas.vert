uniform float t;

void calcular_iluminacion(vec3 orig_normal);

vec3 ondular(vec3 entrada);

void main(){

  vec4 v = vec4(ondular(vec3(gl_Vertex)),1);

  vec3 normal = gl_Normal;
  float inc = 0.01;
  
  vec3 normalx1 = vec3(normal.x + inc, normal.y, normal.z);
  vec3 normalx2 = vec3(normal.x - inc, normal.y, normal.z);

  normalx1 = ondular(normalx1);
  normalx2 = ondular(normalx2);

  float xn = (normalx1.x-normalx2.x)/(2.0*inc);

  calcular_iluminacion(vec3(xn, normal.y, normal.z));

  gl_Position = gl_ModelViewProjectionMatrix * v;
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
  entrada.z = z + px*sin(x*escala) + py*sin(y*escala) + pz*sin(z*escala);
  return entrada;
}