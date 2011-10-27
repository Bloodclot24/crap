uniform bool light0, light1;
varying vec3 _normal;
varying vec4 _posicion;

void calcular_iluminacion(vec3 orig_normal, vec4 position){
      _normal = orig_normal;
      _posicion = position;
      gl_FrontColor =  gl_Color;
      gl_TexCoord[0] = gl_MultiTexCoord0;
}