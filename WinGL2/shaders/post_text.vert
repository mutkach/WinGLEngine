#version 130
uniform mat4 orthMatrix;

in vec2 point;
in vec2 texCoord;

uniform float  screenSizeW;
uniform float  screenSizeH;

out vec2 TexCoord;

void main(void){
vec4 Point = vec4(point, 0, 1.0);
vec2 screenSize = vec2(screenSizeW, screenSizeH);
TexCoord = vec2(texCoord.x, texCoord.y);//vec2(coord.z + 1, coord.w + 1)/2.0;
gl_Position = Point;

}