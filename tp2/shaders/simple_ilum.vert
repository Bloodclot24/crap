void calcular_iluminacion(vec3 orig_normal){

	vec3 normal, lightDir;
	vec4 diffuse, ambient, globalAmbient;
	float NdotL;

	normal = normalize(gl_NormalMatrix * orig_normal);
	lightDir = normalize(vec3(gl_LightSource[0].position));
	NdotL = max(dot(normal, lightDir), 0.0);
	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	/* Compute the ambient and globalAmbient terms */

	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	gl_FrontColor =  NdotL * diffuse + globalAmbient + ambient;
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