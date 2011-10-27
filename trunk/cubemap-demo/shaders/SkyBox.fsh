uniform samplerCube cubeMap;
varying vec3 vTexCoord;

void main (void)
{
   	gl_FragColor = textureCube(cubeMap, vTexCoord) * 1.0;
}
