varying vec3 lightDir,normal;

void main()
{
	normal = normalize(gl_NormalMatrix * gl_Normal);

	lightDir = normalize(vec3(gl_LightSource[0].position));
	gl_TexCoord[0] = gl_MultiTexCoord0;

	vec4 posicion = gl_Vertex;
	//posicion = gl_ModelViewMatrix * posicion;
//	float x = posicion.x;
//	float y = posicion.y;
//	float z = posicion.z;

//	float _sin = sin(z*3.141592654);
//	float _cos = cos(z*3.141592654);
	

	posicion.x = posicion.x*2.0;
	posicion.y = posicion.y/2.0;
	posicion.z = posicion.z/2.0;


	gl_Position = gl_ModelViewProjectionMatrix * posicion;
	//gl_Position = ftransform();
}
