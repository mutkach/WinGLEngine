#version 130


uniform mat3 normalMatrix;

uniform vec3 lightColour;
uniform vec3 lightDirection;



in vec3 point;
in vec3 normal;

void main(void){
	gl_Position =  vec4(point.xy, 0.0, 1.0) ;
	
}
