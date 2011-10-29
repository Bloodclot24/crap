uniform float t;
varying vec3 _normal;
varying vec4 _posicion;
uniform bool light0, light1;
uniform mat4 matriz_mv;

vec4 calcular_iluminacion(int);

void main(){

      vec4 globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;      

      vec4 iluminacion0 = vec4(0.0,0.0,0.0,0.0);
//      if(light0)  //Según el driver de video puede funcionar o causar errores gráficos
	iluminacion0 = calcular_iluminacion(0);
      
      vec4 iluminacion1 = vec4(0.0,0.0,0.0,0.0);
//    if(light1)
	iluminacion1 = calcular_iluminacion(1);

      gl_FragColor = (iluminacion0 + iluminacion1 + globalAmbient)*t;
}


vec4 calcular_iluminacion(int fuente){
      
      vec3 normal = normalize(_normal);
      vec3 lightDir = normalize(vec3(gl_LightSource[fuente].position - _posicion));
      float NdotL = max(dot(normal, lightDir), 0.0);
      vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[fuente].diffuse;
      vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[fuente].ambient;
    
      vec4 eyeCoords = matriz_mv * vec4(0.0,0.0,0.0,1.0);
      vec3 s = lightDir;
      vec3 v = normalize(-eyeCoords.xyz);
      vec3 r = reflect( -s, normal );
      float RdotV =  pow( max( dot(r,v), 0.0 ), 50.0);
	
      return RdotV * gl_LightSource[fuente].specular + diffuse * NdotL + ambient;
}