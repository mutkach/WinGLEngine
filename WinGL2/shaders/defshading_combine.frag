#version 130

uniform sampler2D colourTex;
uniform sampler2D lightAccTex;
uniform sampler2D bloomTex;
uniform sampler2D ssaoTex;


in vec2 TexCoord;

out vec4 finalTex;

void main(void){

vec3 diffuse = texture( colourTex , TexCoord ).xyz ;
vec3 light   = texture( lightAccTex, TexCoord).xyz;
vec3 bloom   = texture( bloomTex, TexCoord).xyz;
float ssao	 = texture( ssaoTex, TexCoord).r;

finalTex.xyz =   diffuse*0.2 + light*(ssao-0.5);// + bloom;//vec3(diffuse, diffuse, diffuse);//*0.2 + light*0.5 - bloom*3 ;
finalTex.a = 1.0;
}