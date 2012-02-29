varying vec3 vTexCoord;

uniform samplerCube cubeMap;

vec4 mapTexture()
{
    //return  textureCube(cubeMap, vTexCoord);
    return mix(vec4(0.05,0.05,0.05,1.0),textureCube(cubeMap, vTexCoord) , 0.25);
} 
