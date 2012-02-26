varying vec4 normal_, posicion_;//, ojo_;

void main()
{
    normal_ = gl_ModelViewMatrix * vec4(gl_Normal,0.0);
    posicion_ = gl_ModelViewMatrix * gl_Vertex;

//    ojo_ = gl_ModelViewMatrix * vec4(0.0, 0.0, 0.0, 1.0);

    gl_FrontColor = gl_Color;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    //normal_ = gl_NormalMatrix * gl_Normal;

    gl_Position = ftransform();
}
