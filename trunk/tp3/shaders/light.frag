uniform float ka, kd, ks, shininess;

varying vec4 normal_, posicion_, ojo_;

vec4 computeLight()
{

    int fuente = 0;
    vec4 normal = normalize(normal_);
    vec4 lightDir = normalize(gl_LightSource[fuente].position - posicion_);
    float NdotL = max(dot(normal, lightDir), 0.0);
    vec4 diffuse = kd * gl_LightSource[fuente].diffuse;
    vec4 ambient = ka * gl_LightSource[fuente].ambient;
    
    vec4 s = lightDir;
    vec4 v = normalize(-ojo_);
    vec4 r = reflect( -s, normal );
    float RdotV =  pow( max( dot(r,v), 0.0 ), shininess);
	
    return vec4((RdotV * gl_LightSource[fuente].specular * ks + diffuse * NdotL + ambient).rgb, 1.0);
} 
