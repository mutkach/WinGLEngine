#include "entity.h"


void Entity :: updateTransform(){

		btTransform trans;
		btVector3 tmpVec3Min;
		btVector3 tmpVec3Max;
		//properties->motionState->setWorldTransform
		properties->motionState->getWorldTransform(trans);
		
		/*
		properties->rigidBody->getAabb(tmpVec3Min, tmpVec3Max);
		
		bounds[0] = vec3((float)tmpVec3Min.getX(), (float)tmpVec3Min.getY(), (float)tmpVec3Min.getZ());
		bounds[1] = vec3((float)tmpVec3Max.getX(), (float)tmpVec3Min.getY(), (float)tmpVec3Min.getZ());
		bounds[2] = vec3((float)tmpVec3Min.getX(), (float)tmpVec3Min.getY(), (float)tmpVec3Max.getZ());
		bounds[3] = vec3((float)tmpVec3Max.getX(), (float)tmpVec3Min.getY(), (float)tmpVec3Max.getZ());
		bounds[4] = vec3((float)tmpVec3Min.getX(), (float)tmpVec3Max.getY(), (float)tmpVec3Min.getZ());
		bounds[5] = vec3((float)tmpVec3Max.getX(), (float)tmpVec3Max.getY(), (float)tmpVec3Min.getZ());
		bounds[6] = vec3((float)tmpVec3Min.getX(), (float)tmpVec3Max.getY(), (float)tmpVec3Max.getZ());
		bounds[7] = vec3((float)tmpVec3Max.getX(), (float)tmpVec3Max.getY(), (float)tmpVec3Max.getZ());
		*/
		vec3 _position = vec3( (float)trans.getOrigin().getX(), (float)trans.getOrigin().getY() , (float)trans.getOrigin().getZ() );
		
		setPosition(_position);

		btQuaternion tmpQuat = trans.getRotation();
		
		vec4 s = vec4(tmpQuat.getX(), tmpQuat.getY(), tmpQuat.getZ(), tmpQuat.getW() );

		rotation = toMat4( quat(s.x, s.y, s.z, s.w) );
		transform = translate * rotation * scale;

}


void Entity :: setPosition(vec3 _position){
		position = _position;
		translate = glm::translate(_position);

}

void Entity :: setRotation(float _angle, vec3 _axis){
		
			rotation = glm::rotate(_angle, _axis);
			rotationQuat = glm::quat_cast(rotation);
}

void Entity :: setScale(vec3 __scale){
			_scale = __scale;
			scale = glm ::scale(_scale);
}

void Entity :: setTransform(){
			transform = translate * rotation * scale;
}

void Entity :: setPhysics(float mass){
	properties = new PhysProperty();
	properties->motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,-1,0)));

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
	mass,                  // mass
	properties->motionState,        // initial position
	body->shape,              // collision shape of body
	btVector3(0,0,0)    // local inertia
	);
	properties->rigidBody = new btRigidBody(rigidBodyCI);
}