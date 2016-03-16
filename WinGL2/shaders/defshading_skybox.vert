#version 130

uniform mat4 MVPMatrix;

in vec3 point;
in vec2 texCoord;

out vec2 TexCoord;

void main(void){
	TexCoord = texCoord;
	gl_Position =  MVPMatrix * vec4(point, 1.0) ;
}
