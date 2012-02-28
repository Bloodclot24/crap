varying vec3 vTexCoord;

uniform samplerCube cubeMap;

vec4 computeLight()
{
    return  textureCube(cubeMap, vTexCoord);
    //return mix(gl_Color,textureCube(cubeMap, vTexCoord) , 0.25);
} 
