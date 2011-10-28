varying vec3 vTexCoord;
uniform mat4 matriz_mv;

uniform bool light0, light1;
varying vec3 _normal;
varying vec4 _posicion;

void calcular_iluminacion(vec3 orig_normal, vec4 position){
      _normal = vec3(gl_ModelViewMatrix * vec4(orig_normal,1.0));
      
      _posicion = gl_ModelViewMatrix * position;
      gl_FrontColor =  gl_Color;
      gl_TexCoord[0] = gl_MultiTexCoord0;

      vTexCoord.xyz = reflect(vec3(matriz_mv * _posicion), _normal);
}
