

uniform sampler2D baseImage;
uniform sampler2D normalMap;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

uniform mat4 customMatrix;

uniform vec3 lightPosition;


in vec3 point;
in vec3 normal;
in vec2 texCoord;

out vec3 Normal;
out vec2 TexCoord;


varying vec4 shit;

void main( void )
{	

   gl_TexCoord[0] = gl_MultiTexCoord0;
   TexCoord    = texCoord;

   mat4 bias = mat4( 0.5, 0.0, 0.0, 0.0,

					 0.0, 0.5, 0.0, 0.0,
					  
					 0.0, 0.0, 0.5, 0.0,

                     0.5, 0.5, 0.5, 1.0 );

   mat3 NormalMatrix = transpose( inverse( mat3(viewMatrix) ) );	
				                        
    
   Normal = normalize(NormalMatrix  * normal ) ;  

 
 
   gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vec4(point, 1.0) ;
   

 
}

