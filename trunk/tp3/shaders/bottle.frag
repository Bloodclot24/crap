uniform sampler2D tex;
uniform float level;

vec4 mapTexture()
{
    vec2 texCoordinates = gl_TexCoord[0].st;
    vec4 color = texture2D(tex,texCoordinates);

    if(gl_TexCoord[0].t < 0.42 || gl_TexCoord[0].t > 0.64)
        color = vec4(0.6,0.6,0.6,0.15);

    return color;
}
