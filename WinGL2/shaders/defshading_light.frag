#version 130


uniform sampler2D normalTex;
uniform sampler2D depthTex;

uniform float lightRadius;
uniform vec3  lightColour;
uniform vec3  lightPosition;

uniform float screenSizeW;
uniform float screenSizeH;

uniform mat3 normalMatrix;
uniform mat4 invMatrix;


out vec3 lightAccTex;

void main(void){

vec2 pixelSize;

pixelSize.x = 1.0/screenSizeW;
pixelSize.y = 1.0/screenSizeH;

vec3 pos = vec3 (( gl_FragCoord.x * pixelSize.x ) , ( gl_FragCoord.y * pixelSize.y ) , 0.0);

pos.z = texture( depthTex, pos.xy ).r ;
vec3 shit = pos;

vec3 normal =  texture ( normalTex , pos.xy ). xyz *2.0 - 1.0;

vec4 clip = invMatrix * vec4 ( pos * 2.0 - 1.0 , 1.0);

pos = clip . xyz / clip . w ;

float dist = length (  pos - lightPosition);
float atten = 1 - clamp ( dist / lightRadius , 0.0 , 1.0);

vec3 incident = normalize (normalMatrix * (lightPosition - pos)  );
float lambert = max( dot( normal, incident ), 0.0 );

if( atten == 0.0) {
//discard;
//finalTex = vec4(1,0,1,1);
}
//else{
//lightAccTex = vec4(0,1, 1,1);
//}

lightAccTex = vec3(lightColour.xyz * atten * lambert);

}