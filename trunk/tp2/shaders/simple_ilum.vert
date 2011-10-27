uniform bool light0, light1;
varying vec4 pos;
varying float light0f, light1f;

varying vec3 _normal;
varying vec4 _posicion;

vec4 procesar_luz(int numero, vec3 normal);

void calcular_iluminacion(vec3 orig_normal){
	pos = gl_ModelViewMatrix * gl_Vertex;

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

  return NdotL * diffuse +  ambient;
}

void calcular_iluminacion_especular(vec3 orig_normal, vec4 position){
      _normal = orig_normal;
      _posicion = position;
      light0f = 1.0;
      //light1f = float(light1);
}