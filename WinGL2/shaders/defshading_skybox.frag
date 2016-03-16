#version 130


uniform sampler2D skybox;


in vec2 TexCoord;

out vec3 bufferColour;

void main(void){
	bufferColour = texture(skybox, vec2(TexCoord.x, 1.0 - TexCoord.y) ).rgb;
}