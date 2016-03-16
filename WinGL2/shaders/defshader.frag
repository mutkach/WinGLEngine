
uniform sampler2D baseImage;
//uniform sampler2D normalMap;
//uniform sampler2DShadow depthMap;

varying float diffuse_value;
                                          
in vec2 TexCoord;
in vec3 Normal;
//varying vec3 vertex_light_position;
//varying vec3 lightDir;
//varying vec4 shit;
void main (void)
{
   //float shadow = 1.0;
   //vec3 ShadowCoords = shit.xyz;
   //ShadowCoords.z -= 0.08;
   //ShadowCoords = ShadowCoords / shit.w;

   //if(ShadowCoords.x > 0 && ShadowCoords.y > 0 && ShadowCoords.x <=1 && ShadowCoords.y <= 1){
	//shadow = texture( depthMap, ShadowCoords ).x + 0.1;
   //}

   //float value = max(dot(Normal, lightDir), 0.0);
   gl_FragColor = texture2D( baseImage, TexCoord );// * value;// * shadow
   //gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	
}