#version 130
uniform sampler2D colourTex;

#define FXAA_REDUCE_MIN (1.0 / 128.0) 
#define FXAA_REDUCE_MUL (1.0 / 8.0) 
#define FXAA_SPAN_MAX 8.0

uniform float screenSizeW;
uniform float screenSizeH;

in vec2 TexCoord;

out vec4 endTex;

void main(void){

	vec2 resolution;
	resolution.x = 1.0/screenSizeW;
	resolution.y = 1.0/screenSizeH;

	vec3 rgbNW = texture(colourTex, (TexCoord.xy  + vec2(-1.0, -1.0) * resolution) ).xyz;
	vec3 rgbNE = texture(colourTex, (TexCoord.xy  + vec2(1.0, -1.0) * resolution) ).xyz;
	vec3 rgbSW = texture(colourTex, (TexCoord.xy  + vec2(-1.0, 1.0) * resolution) ).xyz;
	vec3 rgbSE = texture(colourTex, (TexCoord.xy  + vec2(1.0, 1.0) * resolution) ).xyz;
	vec3 rgbM = texture(colourTex, TexCoord.xy ).xyz;
	vec3 luma = vec3(0.299, 0.587, 0.114);

	float lumaNW = dot(rgbNW, luma);
	float lumaNE = dot(rgbNE, luma);
	float lumaSW = dot(rgbSW, luma);
	float lumaSE = dot(rgbSE, luma);
	float lumaM  = dot(rgbM, luma);
	float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
	float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

	vec2 dir;
	dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
	dir.y = ((lumaNW + lumaSW) - (lumaNE + lumaSE));

	float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * FXAA_REDUCE_MUL), FXAA_REDUCE_MIN);

	float rcpDirMin = 1.0 / (min(abs(dir.x), abs(dir.y)) + dirReduce);

	dir = min(vec2(FXAA_SPAN_MAX, FXAA_SPAN_MAX), max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX), dir * rcpDirMin)) * resolution;

	vec3 rgbA = 0.5 * ( 
		//texture(colourTex, TexCoord.xy * resolution + dir * (1.0 / 3.0 - 0.5)).xyz 
		//+ texture(colourTex, TexCoord.xy * resolution + dir * (2.0 / 3.0 - 0.5)).xyz);
		texture(colourTex, TexCoord.xy  + dir * (1.0 / 3.0 - 0.5)).xyz 
		+ texture(colourTex, TexCoord.xy  + dir * (2.0 / 3.0 - 0.5)).xyz);
	vec3 rgbB = rgbA * 0.5 + 0.25 * (
		//texture(colourTex, TexCoord.xy * resolution + dir * -0.5).xyz 
		//+ texture(colourTex, TexCoord.xy * resolution + dir * 0.5).xyz);
		texture(colourTex, TexCoord.xy + dir * -0.5).xyz 
		+ texture(colourTex, TexCoord.xy  + dir * 0.5).xyz);

	float lumaB = dot(rgbB, luma);

	if ((lumaB < lumaMin) || (lumaB > lumaMax)) {
		endTex = vec4(rgbA, 1.0);
	} else {
		endTex = vec4(rgbB, 1.0);
	}
	
}