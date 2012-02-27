uniform float ka, kd, ks, shininess;
uniform mat4 matriz_camara;
uniform vec3 eye; 
uniform float spectator;
varying vec4 normal_, posicion_;

vec4 computeLight()
{
	vec4 light = vec4(0.0, 0.0, 0.0, 1.0);
	for(int fuente = 0; fuente < 6; fuente++) {
      	vec4 lightDir = normalize(gl_LightSource[fuente].position - posicion_);
      	float NdotL = max(dot(normal_, lightDir), 0.0);
      	vec4 diffuse = kd * gl_LightSource[fuente].diffuse;
      	vec4 ambient = ka * gl_LightSource[fuente].ambient;//*intensidad spot
    
      	vec4 s = lightDir;    
      	float angle = acos(dot(-s.xyz, gl_LightSource[fuente].spotDirection));
      	float cutoff = radians(clamp(gl_LightSource[fuente].spotCutoff, 0.0, 90.0));
	
	if(angle < cutoff) {
		float spotFactor =pow(dot(-s.xyz, gl_LightSource[fuente].spotDirection), 10.0);//gl_LightSource[fuente].spotExponent);
        vec4 eyeCoords = matriz_camara * vec4(0.0,0.0,0.0,1.0);

      	vec4 v = normalize(-eyeCoords);
      	vec4 r = reflect( -s, normal_ );
      	float RdotV =  pow( max( dot(r,v), 0.0 ), shininess);
      	light += spotFactor* (RdotV * gl_LightSource[fuente].specular * ks + diffuse * NdotL);	     
  	}
  	light+=ambient;
  	
  	}
  	
    return light;
} 
