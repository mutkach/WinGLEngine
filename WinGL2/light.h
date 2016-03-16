#ifndef LIGHT_H
#define LIGHT_H


#include <glm/glm/glm.hpp>
#include "object.h"



#define MAX_SPLITS 3


class Object;

class Light{
public:
	Object *type;
	std :: string name;

	float radius;
	vec3 colour;
	vec3 position;
	mat4 transform;
	
	
	void SetPosition(vec3 _position){
		position = _position;
		translate = glm :: translate(_position);
	}

	void SetColour(vec3 _colour){
		colour = _colour;
	}

	void SetRotation(float _angle, vec3 _axis){
		rotation = glm::rotate(_angle, _axis);
	}

	void SetRotation(vec3 _position, vec3 _direction){
		float RotZ = atan(_direction.x, _direction.y);
		float RotX = atan(_direction.z, _direction.y);
		float RotY = atan(_direction.z, _direction.x);
		
		float x = (_direction.x-1)/2;
		float y = (_direction.y)/2;
		float z = (_direction.z)/2;

		rotation = rotate(180.0f, x, y, z) ;
		
	}
	
	void SetScale(vec3 _scale){
		scale = glm ::scale(_scale);
	}

	void SetTransform(){
		transform =  translate * rotation * scale;
	}

	void SetRadius(float _radius){
		radius = _radius;
		scale = glm :: scale(vec3(2, 2, 2)) * glm :: scale(vec3(radius, radius, radius)) ;
	}


	mat4 translate;
	mat4 rotation;
	mat4 scale;
};

class DirLight{
public:
	std :: string name;
	vec3 colour;
	vec3 direction;

	void SetDirection(vec3 &_direction){
		direction = _direction;
	}

	void SetColour(vec3 _colour){
		colour = _colour;
	}
	mat4 viewMatrix[MAX_SPLITS];
	mat4 projectionMatrix[MAX_SPLITS];
	mat4 MVP[MAX_SPLITS];
	mat4 clipMatrix[MAX_SPLITS];
	vec4 plane[MAX_SPLITS][6];
	void UpdateShadowMatrix(mat4& invMatrix, int& splitNum);
	void ExtractShadowPlanes(int& splitNum);

};




#endif