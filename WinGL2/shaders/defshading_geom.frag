#version 130 


uniform  sampler2D baseImage;
uniform  sampler2D normalMap;



in vec2 TexCoord;
in vec3 N;
in vec3 B;
in vec3 T;




out vec3 bufferColour;
out vec3 bufferNormal;


void main(void){

bufferColour =  texture( baseImage , TexCoord ).xyz;
//vec3 nmap = 2.0 * texture(normalMap, TexCoord).xyz - 1.0;//vec3(2.0*texture(normalMap, TexCoord).rg - 1.0, texture(normalMap, TexCoord).b);
//vec3 _Normal = normalize( (T*nmap.x) + (B*nmap.y) + (N*nmap.z) );
//_Normal = vec3(_Normal.x, (_Normal.y), (_Normal.z));
bufferNormal  = vec3( N*0.5 + 0.5);

}