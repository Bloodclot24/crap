uniform float t;
uniform mat4 matriz_mv;

float escala = 3.0*3.141592654*t;
float px = 0.05;
float py = 0.05;
float pz = 0.05;


void calcular_iluminacion(vec3 orig_normal, vec4 posicion);

vec3 ondular(vec3 entrada);

void main(){

  vec4 v = vec4(ondular(vec3(gl_Vertex)),1);

  float x = gl_Vertex.x;
  float y = gl_Vertex.y;
  float z = gl_Vertex.z;

  vec3 nuevaNormal;
  
  vec3 nuevaNormalx = vec3(-px*sin(z*escala)*escala,0,1);
  vec3 nuevaNormaly = vec3(1, -py*sin(x*escala)*escala,0);
  vec3 nuevaNormalz = vec3(0, 1 ,-pz*sin(y*escala)*escala);

  nuevaNormal = normalize(nuevaNormalx+nuevaNormaly+nuevaNormalz);

  if(dot(nuevaNormal,gl_Normal) < 0.0) //si apunta hacia el otro lado que la original la invierto
    nuevaNormal = -nuevaNormal;

  vec3 normal = gl_Normal* (1.0-t) + nuevaNormal * t;
  
  calcular_iluminacion(normal, v);

  gl_Position = gl_ProjectionMatrix * matriz_mv * gl_ModelViewMatrix * v;

}

vec3 ondular(vec3 entrada){
  float x = entrada.x;
  float y = entrada.y;
  float z = entrada.z;

  entrada.x = x + px*cos(z*escala);
  entrada.y = y + py*cos(x*escala);
  entrada.z = z + pz*cos(y*escala);

  return entrada;
}