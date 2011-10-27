uniform float t;
varying vec3 _normal;
varying vec4 _posicion;
uniform bool light0, light1;
uniform sampler2D tex;
uniform mat4 matriz_mv;

vec4 calcular_iluminacion(int);

void main(){

      vec4 globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;      
      vec4 color_textura0 = vec4(0.0,0.0,0.0,0.0);
      vec4 color_textura1 = vec4(0.0,0.0,0.0,0.0);

      vec4 iluminacion0 = vec4(0.0,0.0,0.0,0.0);
      //if(light0)
            iluminacion0 = calcular_iluminacion(0);


      vec4 iluminacion1 = vec4(0.0,0.0,0.0,0.0);
      //if(light1)
            iluminacion1 = calcular_iluminacion(1);


      gl_FragColor = (iluminacion0 + iluminacion1 + globalAmbient)*t;
}

vec4 calcular_iluminacion(int fuente){
      vec3 ct;
      vec3 normal = normalize( _normal);
      vec4 texel;
      float at,af;

      vec3 lightDir = normalize(vec3(gl_LightSource[fuente].position - _posicion));
      float NdotL = max(dot(normal, lightDir), 0.0);
      vec4 diffuse = gl_FrontMaterial.diffuse * gl_LightSource[fuente].diffuse;
      vec4 ambient = gl_FrontMaterial.ambient * gl_LightSource[fuente].ambient;

      vec4 eyeCoords = matriz_mv * _posicion;
      vec3 s = normalize(vec3(gl_LightSource[fuente].position - _posicion));
      vec3 v = normalize(-eyeCoords.xyz);
      vec3 r = reflect( -s, normal );
      float RdotV =  pow( max( dot(r,v), 0.0 ), 50.0);

/*      return RdotV * gl_LightSource[fuente].specular + 
	      diffuse  * NdotL + 
	      texture2D(tex, gl_TexCoord[0].st) * NdotL + ambient;*/

        return (RdotV * gl_LightSource[fuente].specular + 
	      diffuse  * NdotL + 
	      NdotL + ambient) *texture2D(tex, gl_TexCoord[0].st);

}
