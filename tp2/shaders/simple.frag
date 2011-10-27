uniform float t;
varying vec3 _normal;
varying vec4 _posicion;
uniform bool light0, light1;
uniform float usar_textura;
uniform sampler2D tex;

vec4 calcular_color_textura(int);
vec4 calcular_iluminacion(int);

void main(){

      vec4 globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;      

      vec4 color_base = gl_Color;
      if(usar_textura == 0.0)
	color_base=vec4(1.0,1.0,1.0,1.0);

      vec4 iluminacion0 = vec4(0.0,0.0,0.0,0.0);
      if(light0)
            iluminacion0 = calcular_iluminacion(0);
      
      vec4 iluminacion1 = vec4(0.0,0.0,0.0,0.0);
      if(light1)
            iluminacion1 = calcular_iluminacion(1);

      vec4 color_textura0 = vec4(0.0,0.0,0.0,0.0);
      if(usar_textura == 0.0 && light0)
	  color_textura0 = calcular_color_textura(0);

      vec4 color_textura1 = vec4(0.0,0.0,0.0,0.0);
      if(usar_textura == 0.0 && light1)
	  color_textura1 = calcular_color_textura(1);

      gl_FragColor = (color_base + iluminacion0 + iluminacion1 + globalAmbient + color_textura0 + color_textura1)*t;
}


vec4 calcular_iluminacion(int fuente){
      
      vec3 normal = normalize(gl_NormalMatrix * _normal);
      vec3 lightDir = normalize(vec3(gl_LightSource[fuente].position - _posicion)); //ver si influye la posicion
      float NdotL = max(dot(normal, lightDir), 0.0);
      vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[fuente].diffuse;
      vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[fuente].ambient;
    
      vec4 eyeCoords = gl_ModelViewMatrix * _posicion;
      vec3 s = normalize(vec3(gl_LightSource[fuente].position - _posicion));
      vec3 v = normalize(-eyeCoords.xyz);
      vec3 r = reflect( -s, normal );
      float RdotV =  pow( max( dot(r,v), 0.0 ), 50.0);

      return RdotV * gl_LightSource[fuente].specular + diffuse * NdotL + ambient;
}

vec4 calcular_color_textura(int fuente){
	vec3 ct,cf1,cf2;
	vec4 texel;
	float intensity=0.0, at,af;
	vec3 lightDir = normalize(vec3(gl_LightSource[fuente].position - _posicion));
	intensity = max(dot(lightDir,normalize(_normal)),0.0);

	af = gl_FrontMaterial.diffuse.a;
	texel = texture2D(tex,gl_TexCoord[0].st);

	ct = texel.rgb*t;
	at = texel.a;

	return vec4(ct * intensity, at * af);
}