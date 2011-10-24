varying vec3 lightDir,normal;
uniform float t;

void main()
{
    normal = normalize(gl_NormalMatrix * gl_Normal);

    lightDir = normalize(vec3(gl_LightSource[0].position));
    gl_TexCoord[0] = gl_MultiTexCoord0;

    vec4 posicion = gl_Vertex;

    

    gl_Position = gl_ModelViewProjectionMatrix * posicion;
    gl_FrontColor = gl_Color;

}
