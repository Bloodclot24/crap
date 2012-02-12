uniform float displacement;
uniform sampler2D tex;

vec4 mapTexture()
{
    vec2 texCoordinates = vec2(gl_TexCoord[0].s, gl_TexCoord[0].t-displacement);
    vec4 color = texture2D(tex,texCoordinates);
    if(displacement == 0.0)
        color=vec4(0,1,0,0);
    return color;
}

vec4 computeLight()
{
    return gl_Color;
}
