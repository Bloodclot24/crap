varying vec3 _lightDir1,_lightDir2,_normalFinal;

uniform bool light0, light1;

vec4 procesar_luz(int numero, vec3 normal);

void calcular_iluminacion(vec3 orig_normal){
	vec3 normal;
	vec4 globalAmbient;
	normal = normalize(gl_NormalMatrix * orig_normal);
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	
	vec4 l1=vec4(0,0,0,0),l2=vec4(0,0,0,0);
	if(light0)
	  l1 = procesar_luz(0,normal);
	if(light1)
	  l2 = procesar_luz(1,normal);
  
	gl_FrontColor =   l1 + l2 + globalAmbient;

	_normalFinal = normal;

	gl_TexCoord[0] = gl_MultiTexCoord0;
}

vec4 procesar_luz(int numero, vec3 normal){
  vec3 lightDir;
  vec4 diffuse, ambient;
  float NdotL;

  lightDir = normalize(vec3(gl_LightSource[numero].position));
  NdotL = max(dot(normal, lightDir), 0.0);
  diffuse = gl_FrontMaterial.diffuse * gl_LightSource[numero].diffuse;
  /* Compute the ambient and globalAmbient terms */

  ambient = gl_FrontMaterial.ambient * gl_LightSource[numero].ambient;

  if(numero == 0)
     _lightDir1 = lightDir;
  if(numero == 1)
     _lightDir2 = lightDir;

  return NdotL * diffuse +  ambient;
}