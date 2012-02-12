uniform float displacement;
uniform sampler2D tex;

vec4 mapTexture()
{
    vec2 texCoordinates = vec2(gl_TexCoord[0].s, gl_TexCoord[0].t-displacement);
    vec4 color = texture2D(tex,texCoordinates);
    color.a = 1.0;
    return color;
}
