#version 130
uniform sampler2D lightAccTex;

uniform float screenSizeW;
uniform float screenSizeH;


in vec2 TexCoord;

out vec4 downsampledTex;

void main(void){

		
    vec2 dx   = vec2 ( 1.0 / screenSizeW, 0.0 );
    vec2 dy   = vec2 ( 0.0, 1.0 / screenSizeH );
    vec4 base = texture ( lightAccTex, TexCoord ) +
                texture ( lightAccTex, TexCoord + dx ) +
                texture ( lightAccTex, TexCoord + dy ) +
                texture ( lightAccTex, TexCoord + dx + dy );

    base *= 0.25;

    if ( length ( base.rgb ) < 0.4 )
        base.rgb = vec3 ( 0.0 );

    downsampledTex = base;//vec4(TexCoord.x, TexCoord.y, 1, 1.0);
}