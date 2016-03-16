#version 130


uniform sampler2D depthTex;
uniform sampler2D normalTex;

uniform float lightRadius;
uniform vec3  lightColour;
uniform vec3  lightPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 invMatrix;
uniform mat4 MVPMatrix;
uniform mat3 normalMatrix;

in vec3 point;



void main(void){
	gl_Position = MVPMatrix * vec4(point, 1.0);
	//lightEyePosition =  (vec3( viewMatrix * modelMatrix * vec4(lightPosition, 1.0)  ) ); // 2 ;
	//invMatrix = inverse(projectionMatrix * viewMatrix);
}