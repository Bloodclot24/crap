uniform sampler2D tex;

vec4 mapearTextura()
{
	vec4 color = texture2D(tex,gl_TexCoord[0].st);
        return color;
}

