#version 130

uniform sampler2D depthTex;
uniform sampler2D normalTex;
uniform sampler2D noiseTex;

uniform mat4 invMatrix;
uniform mat4 VPMatrix;

uniform mat4 projectionMatrix;
uniform mat4 orthMatrix;

uniform vec3 kernel[16];


uniform float screenSizeW;
uniform float screenSizeH;

uniform float zNear;
uniform float zFar;

in vec2 TexCoord;
in vec3 viewRay;


out float occlusion; //Заменить на float



mat3 tbnMatrix(vec3 normal, vec2 texCoord){
	
	vec2 noiseScale = vec2(screenSizeW/4, screenSizeH/4); 
	vec3 rvec = texture(noiseTex, texCoord*noiseScale).xyz * 2.0 - 1.0;
    vec3 tangent = normalize(rvec - normal * dot(rvec, normal));
    vec3 bitangent = cross(normal, tangent);

   return mat3(tangent, bitangent, normal);

}


void main(void){
	
	vec2 projAB = vec2( (zNear + zFar)/(zFar - zNear) , (2*zNear*zFar)/(zFar - zNear) );


	

	vec3 pSphere[8] = vec3[](vec3(0.24710192, 0.6445882, 0.033550154),vec3(0.00991752, -0.21947019, 0.7196721),vec3(0.25109035, -0.1787317, -0.011580509),vec3(-0.08781511, 0.44514698, 0.56647956),vec3(-0.011737816, -0.0643377, 0.16030222),vec3(0.035941467, 0.04990871, -0.46533614),vec3(-0.058801126, 0.7347013, -0.25399926),vec3(-0.24799341, -0.022052078, -0.13399573));
	

	vec2 pixelSize;
	pixelSize.x = 1.0/screenSizeW;
	pixelSize.y = 1.0/screenSizeH;
	vec3 pos = vec3 (( gl_FragCoord.x * pixelSize.x ) , ( gl_FragCoord.y * pixelSize.y ) , 0.0);

	pos.z = texture( depthTex, pos.xy ).r ;	

	float depth = pos.z;
    //float linearDepth = (2 * zNear) / (zFar + zNear - depth * (zFar - zNear));
	float linearDepth = projAB.y / (depth - projAB.x);

    vec3 ray = normalize(viewRay);
    ray = ray / ray.z;
    vec3 reposition = linearDepth * ray;

	vec3 normal =  texture ( normalTex , vec2(pos.x, pos.y) ).xyz *2.0 - 1.0;
	//normal = normalize(normal);
    mat3 tbn = tbnMatrix(normal, pos.xy);

	occlusion = 0;
	
	for(int i = 0; i < 16; i++){
        // Get sample position
        vec3 samplePos = tbn * vec3(kernel[i].x, kernel[i].y, kernel[i].z) ;
        samplePos = samplePos * 2 + reposition; 

        // Project and bias sample position to get its texture coordinates
        vec4 offset = projectionMatrix * vec4(samplePos, 1.0);
        offset.xy /= offset.w;
        offset.xy = offset.xy * 0.5 + 0.5;
        // Get sample depth

        float sample_depth = texture(depthTex, vec2(offset.x, offset.y) ).r;
        //float linearDepth = (2 * zNear) / (zFar + zNear - sample_depth * (zFar - zNear));
		float linearDepth = projAB.y / (sample_depth - projAB.x);
		//float rangeCheck = abs(reposition.z - linearDepth ) < 5 ? 1.0 : 0.0;
        if(abs(reposition.z - linearDepth ) < 10){
            occlusion += ( linearDepth <= samplePos.z ? 0.0 : 1.0);// * rangeCheck ;
        }
		else{
			occlusion += 0.0;
		}
    }
	

	occlusion =  1 -  (occlusion / 16.0);

}



/*
void main (void)
{
    const float attScale  = 0.5;
	float distScale = 1.0;
    vec2 noiseScale = vec2(screenSizeW/4, screenSizeH/4); 
    vec2 pixelSize = vec2(1.0/screenSizeW, 1.0/screenSizeH);
	float radius = 0.1;
	vec3 pos = vec3 (( gl_FragCoord.x * pixelSize.x ) , ( gl_FragCoord.y * pixelSize.y ) , 0.0);

	pos.z = texture( depthTex, pos.xy ).r ;	

    float   zb    = texture ( depthTex, pos.xy ).x;
    float   z     = zFar*zNear/(zb * (zFar - zNear) - zFar);          // get z-eye
    vec3    pe    = pos * z / pos.z;                                  // point in eye coordinates
    float   att   = 0.0;
    vec3    plane = 2.0 * texture ( noiseTex, pos.xy * noiseScale).xyz - vec3 ( 1.0 );
    
    for ( int i = 0; i < 16; i++ )
    {
        vec3    sample  = reflect   ( kernel[i], plane );
        float   zSample = texture ( depthTex, pos.xy + radius*sample.xy / z ).x;

        zSample = zFar * zNear / (zSample * (zFar - zNear) - zFar );
        
        float   dist = max ( zSample - z, 0.0 ) / distScale;    
        float   occl = 15 * max ( dist * (2.0 - dist), 0.0 );
        
        att += -occl;//1.0 / ( 1.0 + occl*occl );
    }
    





    att = clamp ( att / 8.0 + 0.45, 0.0, 1.0 ) * attScale;
    
    occlusion = att ;


}
*/