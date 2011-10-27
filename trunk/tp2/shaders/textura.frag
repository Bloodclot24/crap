uniform float t;
varying vec3 _lightDir1, _lightDir2,_normalFinal;
uniform sampler2D tex;
uniform float usar_textura;
uniform bool light0, light1;

void main()
{
	vec3 ct,cf1,cf2;
	vec4 texel;
	float intensity1=0.0,intensity2=0.0,at,af;

	if(light0)
	  intensity1 = max(dot(_lightDir1,normalize(_normalFinal)),0.0);
	if(light1)
	  intensity2 = max(dot(_lightDir2,normalize(_normalFinal)),0.0);

	cf1 = intensity1 * (gl_FrontMaterial.diffuse).rgb;
		          
	cf2 = intensity2 * (gl_FrontMaterial.diffuse).rgb;

	af = gl_FrontMaterial.diffuse.a;
	texel = texture2D(tex,gl_TexCoord[0].st);


	if(usar_textura == 0.0){
	   ct = gl_Color.rgb;
	   at = gl_Color.a;
	}
	else{
	  ct = texel.rgb;//mix(vec3(texel), vec3(gl_Color), 0);
	  at = texel.a;
	}
	
	gl_FragColor = vec4(ct * cf1 + ct * cf2 , at * af);

}
