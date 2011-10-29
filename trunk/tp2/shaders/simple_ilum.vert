uniform bool light0, light1;
varying vec3 _normal;
varying vec4 _posicion;
uniform mat4 matriz_mv;

void calcular_iluminacion(vec3 orig_normal, vec4 position){
      _normal = vec3(gl_ModelViewMatrix * vec4(orig_normal,0.0));
      _posicion = gl_ModelViewMatrix * position;
      gl_FrontColor = gl_Color;
      gl_TexCoord[0] = gl_MultiTexCoord0;
}