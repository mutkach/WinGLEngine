#version 130
uniform sampler2D downsampledTex;

uniform float screenSizeW;
uniform float screenSizeH;


in vec2 TexCoord;

out vec4 blurredWTex;

void main(void){

	
	
		vec2 texCoord = TexCoord;
      float blurSize = 1/screenSizeW;
     vec4 sum = vec4(0.0, 0.0, 0.0, 0.0);
     sum += texture(downsampledTex, vec2(texCoord.x  - 4.0*blurSize, texCoord.y)) * 0.05;
     sum += texture(downsampledTex, vec2(texCoord.x  - 3.0*blurSize, texCoord.y)) * 0.09;
     sum += texture(downsampledTex, vec2(texCoord.x  - 2.0*blurSize, texCoord.y)) * 0.12;
     sum += texture(downsampledTex, vec2(texCoord.x  - 1.0*blurSize, texCoord.y)) * 0.15;
     sum += texture(downsampledTex, vec2(texCoord.x , texCoord.y)) * 0.16;
     sum += texture(downsampledTex, vec2(texCoord.x  + 1.0*blurSize, texCoord.y)) * 0.15;
     sum += texture(downsampledTex, vec2(texCoord.x  + 2.0*blurSize, texCoord.y)) * 0.12;
     sum += texture(downsampledTex, vec2(texCoord.x  + 3.0*blurSize, texCoord.y)) * 0.09;
     sum += texture(downsampledTex, vec2(texCoord.x  + 4.0*blurSize, texCoord.y)) * 0.05;

    blurredWTex = sum;
}