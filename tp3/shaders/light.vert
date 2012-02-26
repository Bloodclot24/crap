varying vec4 normal_, posicion_;
uniform mat4 matriz_camara;

void main()
{
    normal_ = normalize(vec4(gl_Normal,0.0));
    posicion_ = gl_Vertex;

    gl_FrontColor = gl_Color;
    gl_TexCoord[0] = gl_MultiTexCoord0;

	gl_Position = gl_ProjectionMatrix * matriz_camara * gl_ModelViewMatrix * posicion_;
    //gl_Position = ftransform();
}
