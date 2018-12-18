#version 130

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;

uniform vec3 lightDirection;
uniform vec3 lightColor;

void main()
{
    //vec3 tmp = dot(-lightDirection, normal0) * color0 ;
    vec3 tmp = color0;
	//gl_FragColor =  clamp(vec4(tmp,1.0), 0.0, 1.0);
    //gl_FragColor = t * texture(texture1,x1) + (1 - t) * texture(texture2,x2) ;
    gl_FragColor =  clamp(vec4(tmp,1.0), 0.0, 1.0);
}
