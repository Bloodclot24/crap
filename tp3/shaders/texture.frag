uniform sampler2D tex;

vec4 mapTexture()
{
    vec4 color = texture2D(tex,gl_TexCoord[0].st);
    return color;
}

