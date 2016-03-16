#ifndef SCENE_H
#define SCENE_H


#include "utility.h"
#include "math.h"

#include "pento.h"
#include "camera.h"
#include "light.h"
#include "entity.h"

class Pento;
class Object;
class Light;
struct Entity;

#define INSIDE 0
#define INTERSECT 1
#define OUTSIDE 2

typedef int trool;

class Scene{
	public:
	//std::vector <Object*> objects;
	std::vector <Entity*> entities;
	std::vector <Light*> lights;
	Pento* pento;
	CCamera* camera;
	btCollisionWorld::ClosestRayResultCallback *RayCallback;
	btVector3 start;
	btVector3 end;
	btRigidBody *cameraCapsule;
	btMotionState *cameraMotionState;

	Scene();
	~Scene();
	void AddObject(Object* object, vec3 position, float mass); // -1 для декора, 0 - для статики, >0 - динамика
	void AddLight(Light* light, vec3 position);
	void CreateScene();
	void UpdateScene();


};





#endif
