uniform sampler2D tex;
uniform float displacement;

void main()
{
    vec2 texCoordinates = vec2(gl_TexCoord[0].s, gl_TexCoord[0].t-displacement);
    vec4 color = texture2D(tex,texCoordinates);
    gl_FragColor = color*gl_Color;
}

