uniform float t;

void calcular_iluminacion(vec3 orig_normal);

void main(){
	calcular_iluminacion(gl_Normal);
  
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

