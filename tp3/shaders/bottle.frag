uniform sampler2D tex;
uniform float fillLevel;
uniform float label;

vec4 mapTexture()
{
    vec2 texCoordinates = gl_TexCoord[0].st;
    vec4 color = texture2D(tex,texCoordinates);
    
    vec4 contentsColor = vec4(0.6,0.6,0.6,0.2);

    if(gl_TexCoord[0].t < fillLevel)
        contentsColor = vec4(0.1,0.05,0.0,0.9);

    if(gl_TexCoord[0].t < 0.42 || gl_TexCoord[0].t > 0.64 || label == 0.0)
        color = contentsColor;

    return color;
}
