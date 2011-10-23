varying vec3 lightDir,normal;

void main()
{
	normal = normalize(gl_NormalMatrix * gl_Normal);

	lightDir = normalize(vec3(gl_LightSource[0].position));
	gl_TexCoord[0] = gl_MultiTexCoord0;

	vec4 posicion = gl_ModelViewProjectionMatrix * gl_Vertex;

	float x = posicion.x;
	float y = posicion.y;
	float z = posicion.z;

	float _sin = sin(z*3.141592654);
	float _cos = cos(z*3.141592654);

	posicion.x = x*_cos-y*_sin;
	posicion.y = x*_sin+y*_cos;

	gl_Position =  posicion;
}
