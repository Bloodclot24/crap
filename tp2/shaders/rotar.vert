uniform float t;
varying vec3 lightDir,normal;

void calcular_iluminacion(vec3 orig_normal);

void main()
{
	
	calcular_iluminacion(gl_Normal);

	vec4 posicion = gl_Vertex;

	float x = posicion.x;
	float y = posicion.y;
	float z = posicion.z;

	float angulo = z*3.141592654*t;

	float _sin = sin(angulo);
	float _cos = cos(angulo);

	posicion.x = x*_cos-y*_sin;
	posicion.y = x*_sin+y*_cos;
	gl_Position = gl_ModelViewProjectionMatrix * posicion;
}
