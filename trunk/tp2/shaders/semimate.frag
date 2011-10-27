uniform float t;
varying vec3 _normal;
varying vec4 _posicion;
uniform bool light0, light1;

vec4 calcular_iluminacion(int);

void main(){

      vec4 globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;      

      vec4 iluminacion0 = vec4(0.0,0.0,0.0,0.0);
//    if(light0)
        iluminacion0 = calcular_iluminacion(0);
      
      vec4 iluminacion1 = vec4(0.0,0.0,0.0,0.0);
//    if(light1)
        iluminacion1 = calcular_iluminacion(1);

      gl_FragColor = (iluminacion0 + iluminacion1 + globalAmbient)*t;
}


vec4 calcular_iluminacion(int fuente){
      
      vec3 normal = normalize( _normal);
      vec3 lightDir = normalize(vec3(gl_LightSource[fuente].position - _posicion));
      float NdotL = max(dot(normal, lightDir), 0.0);
      vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[fuente].diffuse;
      vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[fuente].ambient;
    
      return diffuse * NdotL * 0.5 + ambient;
}