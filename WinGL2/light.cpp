#include "light.h"

void DirLight :: ExtractShadowPlanes(int& splitNum){
	mat4 v = viewMatrix[splitNum];
	mat4 p = projectionMatrix[splitNum];
	mat4 _clipMatrix;
	_clipMatrix[0][0] = v[0][0]*p[0][0]+v[0][1]*p[1][0]+v[0][2]*p[2][0]+v[0][3]*p[3][0];
	_clipMatrix[1][0] = v[0][0]*p[0][1]+v[0][1]*p[1][1]+v[0][2]*p[2][1]+v[0][3]*p[3][1];
	_clipMatrix[2][0] = v[0][0]*p[0][2]+v[0][1]*p[1][2]+v[0][2]*p[2][2]+v[0][3]*p[3][2];
	_clipMatrix[3][0] = v[0][0]*p[0][3]+v[0][1]*p[1][3]+v[0][2]*p[2][3]+v[0][3]*p[3][3];
	_clipMatrix[0][1] = v[1][0]*p[0][0]+v[1][1]*p[1][0]+v[1][2]*p[2][0]+v[1][3]*p[3][0];
	_clipMatrix[1][1] = v[1][0]*p[0][1]+v[1][1]*p[1][1]+v[1][2]*p[2][1]+v[1][3]*p[3][1];
	_clipMatrix[2][1] = v[1][0]*p[0][2]+v[1][1]*p[1][2]+v[1][2]*p[2][2]+v[1][3]*p[3][2];
	_clipMatrix[3][1] = v[1][0]*p[0][3]+v[1][1]*p[1][3]+v[1][2]*p[2][3]+v[1][3]*p[3][3];
	_clipMatrix[0][2] = v[2][0]*p[0][0]+v[2][1]*p[1][0]+v[2][2]*p[2][0]+v[2][3]*p[3][0];
	_clipMatrix[1][2] = v[2][0]*p[0][1]+v[2][1]*p[1][1]+v[2][2]*p[2][1]+v[2][3]*p[3][1];
	_clipMatrix[2][2] = v[2][0]*p[0][2]+v[2][1]*p[1][2]+v[2][2]*p[2][2]+v[2][3]*p[3][2];
	_clipMatrix[3][2] = v[2][0]*p[0][3]+v[2][1]*p[1][3]+v[2][2]*p[2][3]+v[2][3]*p[3][3];
	_clipMatrix[0][3] = v[3][0]*p[0][0]+v[3][1]*p[1][0]+v[3][2]*p[2][0]+v[3][3]*p[3][0];
	_clipMatrix[1][3] = v[3][0]*p[0][1]+v[3][1]*p[1][1]+v[3][2]*p[2][1]+v[3][3]*p[3][1];
	_clipMatrix[2][3] = v[3][0]*p[0][2]+v[3][1]*p[1][2]+v[3][2]*p[2][2]+v[3][3]*p[3][2];
	_clipMatrix[3][3] = v[3][0]*p[0][3]+v[3][1]*p[1][3]+v[3][2]*p[2][3]+v[3][3]*p[3][3];

	clipMatrix[splitNum] = _clipMatrix;

	mat4 VP1 =  clipMatrix[splitNum];
	//left
	plane[splitNum][0].x = VP1[3][0] + VP1[0][0];
	plane[splitNum][0].y = VP1[3][1] + VP1[0][1];
	plane[splitNum][0].z = VP1[3][2] + VP1[0][2];
	plane[splitNum][0].w = VP1[3][3] + VP1[0][3];

	//right
	plane[splitNum][1].x = VP1[3][0] - VP1[0][0];
	plane[splitNum][1].y = VP1[3][1] - VP1[0][1];
	plane[splitNum][1].z = VP1[3][2] - VP1[0][2];
	plane[splitNum][1].w = VP1[3][3] - VP1[0][3];

	//bottom
	plane[splitNum][2].x = VP1[3][0] + VP1[1][0];
	plane[splitNum][2].y = VP1[3][1] + VP1[1][1];
	plane[splitNum][2].z = VP1[3][2] + VP1[1][2];
	plane[splitNum][2].w = VP1[3][3] + VP1[1][3];

	//upper
	plane[splitNum][3].x = VP1[3][0] - VP1[1][0];
	plane[splitNum][3].y = VP1[3][1] - VP1[1][1];
	plane[splitNum][3].z = VP1[3][2] - VP1[1][2];
	plane[splitNum][3].w = VP1[3][3] - VP1[1][3];

	//near
	plane[splitNum][4].x = VP1[3][0] + VP1[2][0];
	plane[splitNum][4].y = VP1[3][1] + VP1[2][1];
	plane[splitNum][4].z = VP1[3][2] + VP1[2][2];
	plane[splitNum][4].w = VP1[3][3] + VP1[2][3];

	//far
	plane[splitNum][5].x = VP1[3][0] - VP1[2][0];
	plane[splitNum][5].y = VP1[3][1] - VP1[2][1];
	plane[splitNum][5].z = VP1[3][2] - VP1[2][2];
	plane[splitNum][5].w = VP1[3][3] - VP1[2][3];


}

void DirLight :: UpdateShadowMatrix(mat4& invMatrix, int& splitNum){

	vec4 clip;
	vec3 mask;
	vec3 centroid;
	vec3 corners[8];
	
	for(int i = 0; i < 8; ++i){
		mask.x = (i%2)*2 - 1; mask.y = (i&2) - 1; 
		mask.z = (i&4)/4 * 0.995;
		if(splitNum == 1) mask.z = (i&4)/4 * 0.998;
		if(splitNum == 2) mask.z = (i&4)/4 * 1;

		clip  = invMatrix * vec4(mask, 1) ;
		corners[i] = vec3(clip)/clip.w;
		centroid += corners[i];
	}

	centroid /= 8;
	
	
	float dist = 600;
	vec3 dir = direction;

	mat4 _sunView = lookAt(centroid - (dir * dist), centroid, vec3(0,1,0) );

	vec3 dots[8];
	vec3 max(corners[0]), min(corners[0]);

	for(int i = 0; i < 8; ++i){
		dots[i] = vec3(_sunView * vec4(corners[i], 1) );
		if(max.x < dots[i].x) max.x = dots[i].x; if(min.x > dots[i].x) min.x = dots[i].x;
		if(max.y < dots[i].y) max.y = dots[i].y; if(min.y > dots[i].y) min.y = dots[i].y;
		if(max.z < dots[i].z) max.z = dots[i].z; if(min.z > dots[i].z) min.z = dots[i].z;
	}

	projectionMatrix[splitNum] = ortho(min.x, max.x, min.y, max.y, -max.z, -min.z);
	
	viewMatrix[splitNum] = _sunView;

	ExtractShadowPlanes(splitNum);


}



