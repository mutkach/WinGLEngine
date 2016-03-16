#version 130
uniform mat4 orthMatrix;

in vec3 point;
in vec2 texCoord;

out vec2 TexCoord;

void main(void){

TexCoord = vec2(point.x + 1, point.y + 1)/2.0;
gl_Position = orthMatrix * vec4(point, 1.0);

}