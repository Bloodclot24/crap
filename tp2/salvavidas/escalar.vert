uniform float t;
uniform mat4 matriz_mv;

void main(void){
	
	gl_FrontColor = gl_Color;
	vec4 v = vec4(gl_Vertex);
	v = gl_ModelViewMatrix * v;
	v.x /= 2.0;

	gl_Position = gl_ProjectionMatrix * matriz_mv * v;
}     