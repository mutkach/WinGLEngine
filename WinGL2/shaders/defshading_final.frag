uniform sampler2D finalTex;
uniform sampler2D colourTex;

in vec2 TexCoord;

void main(void){

vec3 diffuse = texture2D( colourTex , TexCoord ). xyz ;
vec3 light   = texture2D( finalTex, TexCoord).xyz;
gl_FragColor.xyz = diffuse*0.5 + light;
gl_FragColor.a = 1.0;


}