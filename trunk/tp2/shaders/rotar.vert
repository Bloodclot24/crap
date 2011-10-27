uniform float t;

void calcular_iluminacion(vec3 orig_normal);

void calcular_iluminacion_especular(vec3 orig_normal, vec4 posicion);


void main()
{
	
	vec4 posicion = gl_Vertex;

	float x = posicion.x;
	float y = posicion.y;
	float z = posicion.z;

	float angulo = z*3.141592654*t;

	float _sin = sin(angulo);
	float _cos = cos(angulo);

	posicion.x = x*_cos-y*_sin;
	posicion.y = x*_sin+y*_cos;

	vec3 normal = gl_Normal;
	x = normal.x;
	y = normal.y;
	z = normal.z;

	normal.x = x*_cos-y*_sin;
	normal.y = x*_sin+y*_cos;


	calcular_iluminacion(normal);
	calcular_iluminacion_especular(normal,posicion);


	gl_Position = gl_ModelViewProjectionMatrix * posicion;
}
