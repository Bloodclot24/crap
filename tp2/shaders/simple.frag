uniform float t;
varying vec3 _normal;
varying vec4 _posicion;
uniform bool light0, light1;
varying float light0f, light1f;

vec4 calcular_iluminacion_especular(int);

void main(){

    vec4 especular1 = vec4(0.0,0.0,0.0,0.0);
    //if(light0){
      especular1 = calcular_iluminacion_especular(1);
    //}
    //else{
    //  especular1 = vec4(1.0, 0.0, 0.0, 0.0);
    //}
    vec4 especular2 = vec4(0.0,0.0,0.0,0.0);
    //if(light1)
      //especular2 = calcular_iluminacion_especular(1);

  gl_FragColor = (gl_Color+especular1)*t;
}


vec4 calcular_iluminacion_especular(int fuente){
      vec3 normal=_normal, lightDir;
      vec4 diffuse, ambient, globalAmbient, especular;
      float NdotL, RdotV;

      normal = normalize(gl_NormalMatrix * normal);
      lightDir = normalize(vec3(gl_LightSource[fuente].position));
      NdotL = max(dot(normal, lightDir), 0.0);
      diffuse = gl_FrontMaterial.diffuse * gl_LightSource[fuente].diffuse;

      vec4 eyeCoords = gl_ModelViewMatrix * _posicion;
      vec3 s = normalize(vec3(gl_LightSource[fuente].position - _posicion));
      vec3 v = normalize(-eyeCoords.xyz);
      vec3 r = reflect( -s, normal );
      float spec =  pow( max( dot(r,v), 0.0 ), 50.0);

      return spec *gl_LightSource[fuente].specular;
}