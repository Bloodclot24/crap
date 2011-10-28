uniform samplerCube cubeMap;
varying vec3 vTexCoord;
uniform float t;

void main (void)
{
   	gl_FragColor = textureCube(cubeMap, vTexCoord)*t;
}
