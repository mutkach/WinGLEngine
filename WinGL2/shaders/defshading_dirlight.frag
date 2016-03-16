#version 130

uniform sampler2D normalTex;
uniform sampler2D depthTex;
uniform sampler2DArray shadowDepthTex;

uniform vec3  lightDirection;
uniform vec3  lightColour;

uniform float screenSizeW;
uniform float screenSizeH;

uniform float zNear;
uniform float zFar;


uniform mat4 invMatrix;
uniform mat4 shadowMVPMatrix;
uniform mat4 shadowNearMVPMatrix;
uniform mat4 shadowMediumMVPMatrix;
uniform mat4 shadowFarMVPMatrix;
	
out vec4 lightAccTex;




void main(void){

	vec2 pixelSize;


	pixelSize.x = 1.0/screenSizeW;
	pixelSize.y = 1.0/screenSizeH;

	vec3 pos = vec3 (( gl_FragCoord.x * pixelSize.x ) , ( gl_FragCoord.y * pixelSize.y ) , 0.0);
	vec3 shit;

	pos.z = texture( depthTex, pos.xy ).r ;

	vec3 normal =  texture ( normalTex , pos.xy ). xyz *2.0 - 1.0;
	if(normal == vec3(-1.0, -1.0, -1.0) )
	discard;
	
	vec4 clip = invMatrix * vec4 ( pos * 2.0 - 1.0 , 1.0);

	shit = clip . xyz / clip . w ;
	float visibility = 1;
	vec4 shadowCoord;

	//shadowCoord = shadowNearMVPMatrix * vec4(shit, 1);
	//shadowCoord.w = shadowCoord.z;
	//shadowCoord.w += 0.001;
	//shadowCoord.z = float(0);

	
	if(pos.z < 0.995){
		shadowCoord = shadowNearMVPMatrix * vec4(shit, 1);
		shadowCoord.w = shadowCoord.z;
		shadowCoord.w -= 0.0006;
		shadowCoord.z = float(0);
	}
	else if(pos.z < 0.998){
	  shadowCoord = shadowMediumMVPMatrix * vec4(shit, 1);
	  shadowCoord.w = shadowCoord.z;
	  shadowCoord.w -= 0.0006;
		shadowCoord.z = float(1);
	}
	else{
		shadowCoord = shadowFarMVPMatrix * vec4(shit, 1);
		shadowCoord.w = shadowCoord.z;
		shadowCoord.w -= 0.0006;
		shadowCoord.z = float(2);
	}
	
	visibility = 1.0;

	if ( texture( shadowDepthTex, vec3(shadowCoord.x, shadowCoord.y, shadowCoord.z) ).z  <  shadowCoord.w  && shadowCoord.x > 0 && shadowCoord.x < 1 && shadowCoord.y > 0 && shadowCoord.y < 1)
				visibility = 0.0;


	

	
	float lambert;
	lambert = clamp ( dot ( -normalize(lightDirection) , normal ) ,0.0 ,1.0);

	//visibility = 0.0;

	lightAccTex = vec4 ( lightColour.xyz * lambert * visibility * 0.5, 1.0);


}