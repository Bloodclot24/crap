uniform float ka, kd, ks, shininess;

varying vec3 Normal;
varying vec4 Position;

vec3 ads(int index)
{
    vec4 LightPosition = gl_LightSource[index].position;

    vec3 n = normalize(Normal);

    vec4 ambient = gl_LightSource[index].ambient * ka;

    vec3 s;
    if( LightPosition.w == 0.0 )
        s = normalize(vec3(LightPosition));
    
    else
        s = normalize(vec3(LightPosition - Position)); 

    vec3 v = normalize(vec3(-Position));
    vec3 r = reflect(-s, n); 

    float sDotN = max(dot(s,n), 0.0);

    vec4 diffuse = gl_LightSource[index].diffuse * kd * sDotN;

    vec4 spec = vec4(0.0);
    if( sDotN > 0.0 )
    spec = gl_LightSource[index].specular * ks * 
        pow( max( dot(r,v), 0.0 ), shininess ); 

    return (ambient + diffuse + spec).rgb;
}

vec4 computeLight()
{
    vec4 color = vec4(ads(0), 1);
    return color;
}
