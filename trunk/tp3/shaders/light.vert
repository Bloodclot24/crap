varying vec4 normal_, posicion_;

void main()
{
    normal_ = normalize(vec4(gl_NormalMatrix * gl_Normal,0.0));
    posicion_ = gl_ModelViewMatrix * gl_Vertex;
    posicion_ = posicion_ / posicion_.w;

    gl_FrontColor = gl_Color;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}
