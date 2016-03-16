#version 130
uniform sampler2D blurredWTex;

uniform float screenSizeW;
uniform float screenSizeH;


in vec2 TexCoord;

out vec4 blurredHTex;

void main(void){

		
   vec4 sum = vec4(0.0);
   vec2 texCoord = TexCoord;
   float blurSize = 1 /screenSizeH;

   sum += texture(blurredWTex, vec2(texCoord.x, texCoord.y - 4.0*blurSize)) * 0.05;
   sum += texture(blurredWTex, vec2(texCoord.x, texCoord.y - 3.0*blurSize)) * 0.09;
   sum += texture(blurredWTex, vec2(texCoord.x, texCoord.y - 2.0*blurSize)) * 0.12;
   sum += texture(blurredWTex, vec2(texCoord.x, texCoord.y - 1.0*blurSize)) * 0.15;
   sum += texture(blurredWTex, vec2(texCoord.x, texCoord.y               )) * 0.16;
   sum += texture(blurredWTex, vec2(texCoord.x, texCoord.y + 1.0*blurSize)) * 0.15;
   sum += texture(blurredWTex, vec2(texCoord.x, texCoord.y + 2.0*blurSize)) * 0.12;
   sum += texture(blurredWTex, vec2(texCoord.x, texCoord.y + 3.0*blurSize)) * 0.09;
   sum += texture(blurredWTex, vec2(texCoord.x, texCoord.y + 4.0*blurSize)) * 0.05;
 
   blurredHTex = sum;
}