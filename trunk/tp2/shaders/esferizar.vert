varying vec3 lightDir,normal;
uniform float t;

void calcular_iluminacion(vec3 orig_normal);


void main(){

	normal = gl_Normal;
	vec4 posicion = gl_Vertex;

	float x0 = posicion.x;
	float y0 = posicion.y;
	float z0 = posicion.z;

	float factor = 1.0*t;
	float radio = 0.7;
	
	if(z0!=0.0) {
		float divisor = pow(x0/z0,2.0) + pow(y0/z0,2.0) + 1.0;
		float radicando = pow(radio,2.0) / divisor;
		float ze = pow(radicando,0.5);
			
		if(z0<0.0)
			ze = -ze;
	
		float xe = ze * x0 / z0;
		float ye = ze * y0 / z0;
		
		posicion.x = x0 + factor * (xe - x0);
		posicion.y = y0 + factor * (ye - y0);
		posicion.z = z0 + factor * (ze - z0);
  
		normal.x = normal.x*(1.0 - factor) + xe * factor;
		normal.y = normal.y*(1.0 - factor) + ye * factor;
		normal.z = normal.z*(1.0 - factor) + ze * factor;

	} else if (x0 != 0.0) {
		float divisor = pow(z0/x0,2.0) + pow(y0/x0,2.0) + 1.0;
		float radicando = pow(radio,2.0) / divisor;
		float xe = pow(radicando,0.5);
			
		if(x0<0.0)
			xe = -xe;
	
		float ze = xe * z0 / x0;
		float ye = xe * y0 / x0;
		
		posicion.x = x0 + factor * (xe - x0);
		posicion.y = y0 + factor * (ye - y0);
		posicion.z = z0 + factor * (ze - z0);

		normal.x = normal.x*(1.0 - factor) + xe * factor;
		normal.y = normal.y*(1.0 - factor) + ye * factor;
		normal.z = normal.z*(1.0 - factor) + ze * factor;

	} else if (y0 != 0.0) {
		float divisor = pow(x0/y0,2.0) + pow(z0/y0,2.0) + 1.0;
		float radicando = pow(radio,2.0) / divisor;
		float ye = pow(radicando,0.5);
			
		if(y0<0.0)
			ye = -ye;
	
		float xe = ye * x0 / y0;
		float ze = ye * z0 / y0;
		
		posicion.x = x0 + factor * (xe - x0);
		posicion.y = y0 + factor * (ye - y0);
		posicion.z = z0 + factor * (ze - z0);

		normal.x = normal.x*(1.0 - factor) + xe * factor;
		normal.y = normal.y*(1.0 - factor) + ye * factor;
		normal.z = normal.z*(1.0 - factor) + ze * factor;
	}

	calcular_iluminacion(normal);
	
	gl_Position = gl_ModelViewProjectionMatrix * posicion;
}
