varying vec3 Normal;
varying vec4 Position;

void main()
{
    int lights = 1;

    Normal = gl_Normal;

    Position = ftransform();
    Position = vec4(gl_ModelViewMatrix * gl_Position);

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
    gl_FrontColor = gl_Color;
}
