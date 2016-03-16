#version 130
uniform mat4 orthMatrix;

uniform mat4 invMatrix;
uniform mat4 invProjectionMatrix;
uniform mat4 VPMatrix;



in vec3 point;
in vec2 texCoord;

out vec2 TexCoord;
out vec3 viewRay;

void main(void){

TexCoord = vec2(point.x + 1, point.y + 1)/2.0;

viewRay = (invProjectionMatrix * vec4(point, 1.0)).xyz;
gl_Position = vec4(point.xy, 0.0, 1.0);

}