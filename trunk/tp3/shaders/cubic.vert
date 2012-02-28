uniform mat4 matriz_camara;
varying vec3 vTexCoord;

void main()
{

    gl_FrontColor = gl_Color;

    vec4 vertex = gl_ModelViewMatrix * gl_Vertex;

    vec3 normal = gl_NormalMatrix * gl_Normal;

    vec3 vertexn = normalize(vertex.xyz / vertex.w);

    vec4 vcoords = vec4(reflect(vertexn, normal), 0.0);

    vcoords = gl_ModelViewMatrixInverse * vcoords;

    vTexCoord.xyz = normalize(vcoords.xyz);

    //vTexCoord = normalize(gl_Vertex.xyz);

    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}
