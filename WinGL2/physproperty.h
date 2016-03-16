#ifndef PHYSPROPERTY_H
#define PHYSPROPERTY_H

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>

struct PhysProperty{

public:
	

	


	//btCollisionShape* shape;
	btDefaultMotionState* motionState;
	btRigidBody* rigidBody;
	btScalar mass;
	btVector3 inertia;
	btTransform transform;

	PhysProperty(){


	}
	
	
};


#endif