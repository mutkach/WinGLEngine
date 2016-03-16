#version 130


in vec3 point;
in vec2 texCoord;

out vec2 TexCoord;

void main(void){

TexCoord = texCoord;
gl_Position = vec4(point.xy, 0.0, 1.0);




}