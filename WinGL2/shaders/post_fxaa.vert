#version 130
uniform mat4 orthMatrix;

in vec3 point;
in vec2 texCoord;

out vec2 TexCoord;

void main(void){

TexCoord = texCoord;
gl_Position = orthMatrix * vec4(point, 1.0);

}