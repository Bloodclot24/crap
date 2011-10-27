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

	vec3 normal, lightDir, posCamara;
	vec4 diffuse, ambient, globalAmbient, especular;
	float NdotL, RdotV;

	normal = normalize(gl_NormalMatrix * orig_normal);
	lightDir = normalize(vec3(gl_LightSource[0].position));
	NdotL = max(dot(normal, lightDir), 0.0);
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	/* Compute the ambient and globalAmbient terms */
	//r = normalize(-lightDir + 2.0 * max(dot(normal, lightDir)) * normal);


vec4 eyeCoords = gl_ModelViewMatrix * position;
vec3 s = normalize(vec3(gl_LightSource[0].position - eyeCoords));
vec3 v = normalize(-eyeCoords.xyz);
vec3 r = reflect( -s, normal );
float spec =  pow( max( dot(r,v), 0.0 ), 5.0);

/*

	vec3 rp = normalize(reflect( -lightDir, normal ));
	vec4 r = vec4(rp,0.0);
	vec4 v = (0.0, 0.0, 0.2, 0.0);//normalize(gl_ModelViewMatrix * position);
	RdotV = max(dot(r, v),0.0);
	especular = gl_FrontMaterial.specular * gl_LightSource[0].specular;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
*/
	gl_FrontColor =  spec *gl_LightSource[0].specular * gl_FrontMaterial.specular + NdotL * diffuse + globalAmbient + ambient;
}