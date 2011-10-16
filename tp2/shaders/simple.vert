#version 120
uniform float t;
void main()
{
vec4 position = gl_Vertex;
position += cos(t);
gl_Position = gl_ModelViewProjectionMatrix * position;
}
