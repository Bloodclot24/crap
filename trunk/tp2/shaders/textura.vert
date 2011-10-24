uniform float t;
varying vec3 lightDir,normal;

void main()
{
	normal = normalize(gl_NormalMatrix * gl_Normal);

	lightDir = normalize(vec3(gl_LightSource[0].position));
	gl_TexCoord[0] = gl_MultiTexCoord0;

	vec4 posicion = gl_Vertex;

	float x = posicion.x;
	float y = posicion.y;
	float z = posicion.z;

	float angulo = z*3.141592654;

	float _sin = sin(angulo);
	float _cos = cos(angulo);

	posicion.x = x*_cos-y*_sin;
	posicion.y = x*_sin+y*_cos;

	gl_Position = gl_ModelViewProjectionMatrix * posicion;
}
