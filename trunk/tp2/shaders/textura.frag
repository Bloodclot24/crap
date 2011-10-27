uniform float t;
varying vec3 _lightDir1, _lightDir2,_normalFinal;
uniform sampler2D tex;
uniform float usar_textura;
uniform bool light0, light1;
varying vec4 pos;

void main()
{
	vec3 ct,cf1,cf2;
	vec4 texel;
	float intensity1=0.0,intensity2=0.0,at,af;

	if(light0){
	  intensity1 = max(dot(_lightDir1,normalize(_normalFinal)),0.0);
	}
	if(light1){
	  intensity2 = max(dot(_lightDir2,normalize(_normalFinal)),0.0);
	}

	af = gl_FrontMaterial.diffuse.a;
	texel = texture2D(tex,gl_TexCoord[0].st);

	ct = texel.rgb*t;
	at = texel.a;

	vec4 specular = vec4(0.0,0.0,0.0,0.0);
	//if(light0){
	  vec4 lightspec = vec4(1.0, 1.0, 1.0, 1.0); //gl_LightSource[0].specular;
	  vec4 matspec = vec4(1.0, 1.0, 1.0, 1.0); //gl_FrontMaterial.specular;
	  float shininess = 5.0; //gl_FrontMaterial.shininess;

	  vec4 lpos = gl_LightSource[0].position;
	  vec4 s = -normalize(pos-lpos); 
	  vec3 light = s.xyz;

	  vec3 r = -reflect(light, _normalFinal);
	  r = normalize(r);
	  vec3 v = -pos.xyz;
	  v = normalize(v);
	  specular= vec4(0.0,0.0,0.0,0.0);
	  
	  //if(dot(r,v) <= 0.0)
	  //   float nada=0.0;
	    

	  //specular = lightspec * matspec * pow(max(0.0, dot(r, v)), shininess);
	//}

	gl_FragColor = vec4(ct * intensity1 + ct * intensity2 , at * af);	
	//gl_FragColor = specular;


	//cf1 = intensity1; * (gl_FrontMaterial.diffuse).rgb;
	//cf2 = intensity2; * (gl_FrontMaterial.diffuse).rgb;
	//gl_FragColor = vec4(ct * cf1 + ct * cf2 , at * af);

}
