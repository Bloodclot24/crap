uniform float t;
uniform mat4 matriz_mv;

void calcular_iluminacion(vec3 orig_normal, vec4 posicion);

void main(){

	vec4 posicion =  gl_Vertex;

	calcular_iluminacion(gl_Normal, posicion);
  
	gl_Position = gl_ProjectionMatrix * matriz_mv * gl_ModelViewMatrix * posicion;
}

