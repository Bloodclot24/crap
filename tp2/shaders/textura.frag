uniform float t;
varying vec3 lightDir,normal;
uniform sampler2D tex;
uniform float usar_textura;

void main()
{
	vec3 ct,cf;
	vec4 texel;
	float intensity,at,af;
	intensity = max(dot(lightDir,normalize(normal)),0.0);
	cf = intensity * (gl_FrontMaterial.diffuse).rgb +
		          gl_FrontMaterial.ambient.rgb;
	af = gl_FrontMaterial.diffuse.a;
	texel = texture2D(tex,gl_TexCoord[0].st);

	if(usar_textura == 0.0){
	   ct = gl_Color.rgb;
	   at = gl_Color.a;
	}
	else{
	  ct = mix(vec3(texel), vec3(gl_Color), 0);
	  at = texel.a;
	}
	
	gl_FragColor = vec4(ct * cf, at * af);

}
