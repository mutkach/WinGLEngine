#version 130

uniform mat4 MVPMatrix;

in vec3 point;
in vec3 normal;

void main(void){
	gl_Position =  MVPMatrix * vec4(point, 1.0) ;
}
