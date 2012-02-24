vec4 mapTexture();
vec4 computeLight();

void main()
{
    vec4 textureColor = mapTexture();

    vec4 lightColor = computeLight();

    gl_FragColor = textureColor*lightColor;
}

