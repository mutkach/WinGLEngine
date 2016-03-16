#version 130



uniform mat4 MVPMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

in vec3 point;
in vec3 normal;
in vec2 texCoord;
in vec3 tangent;
//in vec3 bitangent;




out vec2 TexCoord;
out vec3 N;
out vec3 T;
out vec3 B;




void main ( void ) {
	TexCoord = texCoord;
	N = normalize( vec3( normalMatrix * normal ) )  ;
	//T = normalize( vec3( normalMatrix * tangent ) )  ;
	//B = cross(N, T);

	gl_Position =  MVPMatrix * vec4(point, 1.0) ;

}