void main() {

    vec3 normal, lightDir;
    vec4 diffuse;
    float NdotL;

    normal = normalize(gl_NormalMatrix * gl_Normal);

    lightDir = normalize(vec3(gl_LightSource[0].position));

    NdotL = max(dot(normal, lightDir), 0.0);

    diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
    gl_FrontColor =  NdotL * diffuse;

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}
