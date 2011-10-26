uniform float t;
varying vec3 lightDir,normal;

void calcular_iluminacion(vec3 orig_normal);

void main(){

	calcular_iluminacion(gl_Normal);
  
	gl_Position = ftransform();
}

