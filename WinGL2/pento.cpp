#include "pento.h"


Pento :: Pento (){

		broadphase = new btDbvtBroadphase();
		timer = new Timer();
		// Set up the collision configuration and dispatcher
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
 
		// The actual physics solver
		solver = new btSequentialImpulseConstraintSolver;
 
		// The world.
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0, -10, 0));


}

Pento :: ~Pento(){

		delete dynamicsWorld;
		delete solver;
		delete dispatcher;
		delete collisionConfiguration;
		delete broadphase;


}

void Pento :: AddObject(Entity* entity){
	
		dynamicsWorld->addRigidBody(entity->properties->rigidBody);
	
}

void Pento ::  UpdateSimulation(){
		timer->StopTimer();
		dynamicsWorld->stepSimulation(1/20.f,2);
		timer->StartTimer();

}