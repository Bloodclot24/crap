varying vec3 Normal;
varying vec4 Position;

void main()
{
    int lights = 1;

    Normal = vec3(gl_ModelViewMatrix * vec4(gl_Normal,0.0));
    Position = gl_ModelViewMatrix * gl_Vertex;

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
    gl_FrontColor = gl_Color;
}
