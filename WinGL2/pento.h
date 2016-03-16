#ifndef PENTO_H
#define PENTO_H

#include "timer.h"
#include "entity.h"
#include "physproperty.h"
#include "object.h"

struct Entity;
class Timer;

class Pento{
public:

	Pento();

	~Pento();
	
	void AddObject(Entity* entity);


	void UpdateSimulation();



	Timer* timer;
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

};



#endif