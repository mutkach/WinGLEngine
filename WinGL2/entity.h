#ifndef ENTITY_H
#define ENTITY_H



#include "object.h"
#include "pento.h"




using namespace glm;

class Object;
struct PhysProperty;



struct Entity{

	Object* body;



	vec3 bounds[8];
	vec3 position;
	vec3 _scale;
	quat rotationQuat;
	mat4 transform;

	mat4 translate;
	mat4 rotation;
	mat4 scale;

	PhysProperty *properties;

	void setPosition(vec3 _position);

	void setRotation(float _angle, vec3 _axis);

	void setScale(vec3 __scale);

	void setTransform();
	void updateTransform();
	void setPhysics(float mass);


	
	Entity* parent;
	std :: vector <Entity*> children;
};

#endif
