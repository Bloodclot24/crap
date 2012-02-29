uniform mat4 matriz_camara;
varying vec3 vTexCoord;
uniform float mapZ;
varying vec4 normal_, posicion_;

void main()
{
    gl_FrontColor = gl_Color;

    vec4 inVertex = vec4(gl_Vertex.xy, gl_Vertex.z+mapZ, gl_Vertex.w);

    vec4 vertex = gl_ModelViewMatrix * inVertex;

    vec3 normal = gl_NormalMatrix * gl_Normal;

    vec3 vertexn = normalize(vertex.xyz / vertex.w);

    vec4 vcoords = vec4(reflect(vertexn, normal), 0.0);

    vcoords = gl_ModelViewMatrixInverse * vcoords;

    vTexCoord.xyz = normalize(vcoords.xyz);

    //vTexCoord = normalize(inVertex.xyz);

    normal_ = normalize(vec4(gl_NormalMatrix * gl_Normal,0.0));
    posicion_ = gl_ModelViewMatrix * gl_Vertex;
    posicion_ = posicion_ / posicion_.w;


    gl_FrontColor = vec4(0.2, 0.2, 0.2, 1.0);
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
}
