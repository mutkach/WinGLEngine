#version 130
uniform sampler2D text;




in vec2 TexCoord;

//out vec4 final;

void main(void){
vec3 color = vec3(0.9, 0.9, 1.0);
gl_FragColor.rgb = color;
gl_FragColor.a =  texture(text, TexCoord).r;//vec4(TexCoord.x, 0.0, TexCoord.y, 1.0);
}