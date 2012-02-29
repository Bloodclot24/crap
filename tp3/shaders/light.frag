uniform float ka, kd, ks, shininess;
varying vec4 normal_, posicion_;

vec4 computeLight()
{
    vec4 light = vec4(0.0, 0.0, 0.0, 1.0);

    for(int fuente = 0; fuente < 6; fuente++) {
        vec4 lightDir = normalize(gl_ModelViewMatrix * gl_LightSource[fuente].position - posicion_);
        vec4 ambient = ka * gl_LightSource[fuente].ambient;

        float angle = acos(dot(-lightDir, normalize(gl_ModelViewMatrix * vec4(gl_LightSource[fuente].spotDirection,0.0))));
        float cutoff = radians(clamp(gl_LightSource[fuente].spotCutoff, 0.0, 90.0));
   
        if(angle < cutoff) {
      
            float spotFactor = pow(dot(-lightDir, normalize(gl_ModelViewMatrix * vec4(gl_LightSource[fuente].spotDirection,0.0))), 10.0);//gl_LightSource[fuente].spotExponent);
       
        	float NdotL = max(dot(normal_, lightDir), 0.0);
        	vec4 diffuse = kd * gl_LightSource[fuente].diffuse;
        	vec4 v = normalize(-posicion_);
      		vec4 r = reflect(-lightDir, normal_);
        	float RdotV =  pow( max( dot(r,v), 0.0 ), shininess);

        	light += spotFactor*(RdotV * gl_LightSource[fuente].specular * ks + diffuse * NdotL);
        }
        light += ambient;
    }

    return light;
} 