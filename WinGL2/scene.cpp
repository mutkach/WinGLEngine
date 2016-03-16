#include "scene.h"

Scene::Scene(){
	pento = new Pento();
	camera = new CCamera();
	camera->SetCamera( 0,0,0, 1,0,0, 0,1,0);
	btCapsuleShape* capsule;
	cameraMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,-1,0)));
	capsule = new btCapsuleShape(1, 18);
	
	cameraCapsule = new btRigidBody(
		50,
		cameraMotionState,
		capsule,
		btVector3(0,0,0)
		);
	//cameraCapsule->setInvInertiaDiagLocal(btVector3(0,0,0));
	//cameraCapsule->updateInertiaTensor();
	//cameraCapsule->setDamping(0.96,0);
	
	pento->dynamicsWorld->addRigidBody(cameraCapsule);

	
	//cameraCapsule->setAngularFactor(btVector3(0,1,0));
	
}

void Scene :: AddObject(Object* object, vec3 position, float mass){
	
	Entity* newEntity = new Entity();
	newEntity->body = object;
	newEntity->setPosition(position);
	newEntity->setScale(vec3(1.0, 1.0, 1.0) );
	newEntity->setTransform();
	newEntity->setPhysics(mass);

	entities.push_back(newEntity);
	pento->AddObject(newEntity);
	
}

void Scene :: AddLight(Light* light, vec3 position){
	lights.push_back(light);
}

void Scene :: UpdateScene(){
	pento->UpdateSimulation();
	camera->Update();

	btVector3 pos = cameraCapsule->getCenterOfMassPosition();
	camera->m_vView -= camera->m_vPosition;
	camera->m_vPosition = vec3(pos.x(), pos.y(), pos.z());
	camera->m_vView += camera->m_vPosition;
	//cameraCapsule->setLinearVelocity(btVector3(0,0,0));
	for(int i = 0; i < entities.size(); ++i){
		entities[i]->updateTransform();
		//if(!entities[i]->properties->rigidBody->hasContactResponse())
		//	entities[i]->properties->rigidBody->applyCentralImpulse(500*btVector3(1, 0, 0));
	}

	

}

bool SegmentBoxIntersection(vec2 a, vec2 b, vec2 position, float dx){
	int x = 0;
	float a1 = b.y - a.y;
	float b1 = a.x - b.x;
	float c1 = -a1 * a.x - b1 * a.y;
	float k = a1 / (-b1);
	float d = c1/ (-b1);

	//if(k*position.x + d < position.y)
	return true;

}


trool GetIntersection(vec2 position, float dx){
	int x = 0;

	vec2 center(10*11, 10*11);
	float radius = 52.1;

	if(distance(position, center) <= radius)
		++x;
	position.x += dx;

	if(distance(position, center) <= radius)
		++x;			//	Можно улучшить и отсеивать переceчение с самого начала
	position.y += dx;	//  Аналогично и непересечение
					 
	if(distance(position, center) <= radius)
		++x;
	position.x -= dx;
	if(distance(position, center) <= radius)
		++x;

	if(x == 4)
		return INSIDE;
	if(x > 0)
		return INTERSECT;
	else if(x == 0)
		return OUTSIDE;

}


void Scene :: CreateScene(){
	Object* block = new Object("default/cube.obj", true);
	Object* blockMed = new Object("default/cube_m.obj", true);
	Object* blockBig = new Object("default/cube_b.obj", true);
	
	srand( (unsigned)time( NULL ) );
	
	
	float dx = 10;
	
	for(int i = 0; i <= 18; ++i){
		for(int k = 0; k <= 14; ++k){

			if(GetIntersection(vec2(i*dx, k*dx), dx) == OUTSIDE)
				continue;

			if(GetIntersection(vec2(i*dx, k*dx), dx) == INSIDE){
				coin{
					AddObject(blockMed, vec3(i*dx, 0, k*dx), 0);
					AddObject(blockMed, vec3(i*dx, 4, k*dx), 0);
					coin AddObject(blockMed, vec3(i*dx, 8, k*dx), 0);

					AddObject(blockMed, vec3(i*dx + dx/2, 0, k*dx), 0);
					AddObject(blockMed, vec3(i*dx + dx/2, 4, k*dx), 0);
					coin AddObject(blockMed, vec3(i*dx + dx/2, 8, k*dx), 0);

					AddObject(blockMed, vec3(i*dx, 0, k*dx + dx/2), 0);
					AddObject(blockMed, vec3(i*dx, 4, k*dx + dx/2), 0);
					coin AddObject(blockMed, vec3(i*dx, 8, k*dx + dx/2), 0);

					AddObject(blockMed, vec3(i*dx + dx/2, 0, k*dx + dx/2), 0);
					AddObject(blockMed, vec3(i*dx + dx/2, 4, k*dx + dx/2), 0);
					coin AddObject(blockMed, vec3(i*dx + dx/2, 8, k*dx + dx/2), 0);
				}
			else{
				AddObject(blockBig, vec3(i*dx + dx/2, 0, k*dx), 0);
				AddObject(blockBig, vec3(i*dx + dx/2, 4, k*dx), 0); 
				coin AddObject(blockBig, vec3(i*dx + dx/2, 8, k*dx), 0);
			}
			}
			if(GetIntersection(vec2(i*dx, k*dx), dx) == INTERSECT){

				if(GetIntersection(vec2(i*dx, k*dx), dx/2) == INSIDE){
					AddObject(blockMed, vec3(i*dx, 0, k*dx), 0);
					AddObject(blockMed, vec3(i*dx, 4, k*dx), 0);
					coin AddObject(blockMed, vec3(i*dx, 8, k*dx), 0);
				}

				if(GetIntersection(vec2(i*dx + dx/2, k*dx), dx/2) == INSIDE){
					AddObject(blockMed, vec3(i*dx + dx/2, 0, k*dx), 0);
					AddObject(blockMed, vec3(i*dx + dx/2, 4, k*dx), 0);
					coin AddObject(blockMed, vec3(i*dx + dx/2, 8, k*dx), 0);
				}
				
				if(GetIntersection(vec2(i*dx, k*dx + dx/2), dx/2) == INSIDE){
					AddObject(blockMed, vec3(i*dx, 0, k*dx + dx/2), 0);
					AddObject(blockMed, vec3(i*dx, 4, k*dx + dx/2), 0);
					coin AddObject(blockMed, vec3(i*dx, 8, k*dx + dx/2), 0);
				}
				
				if(GetIntersection(vec2(i*dx + dx/2, k*dx + dx/2), dx/2) == INSIDE){
					AddObject(blockMed, vec3(i*dx + dx/2, 0, k*dx + dx/2), 0);
					AddObject(blockMed, vec3(i*dx + dx/2, 4, k*dx + dx/2), 0);
					coin AddObject(blockMed, vec3(i*dx + dx/2, 8, k*dx + dx/2), 0);
				}
				


			}

		}
	}

}
/*
trool Scene :: FrustumCull(vec3* bounds, vec4 *plane){
	
	vec3 p, n;
	int in, out;
	p = bounds[0];
	n = bounds[7];
	int result = INSIDE;

	for(int i = 0; i < 6; ++i){	
						
			p = bounds[0];
			n = bounds[7];
			
			if( plane[i].x >= 0 ){
				p.x = bounds[7].x; //max X
				n.x = bounds[0].x; //min X
			}

			if( plane[i].y >= 0 ){
				p.y = bounds[7].y; //max Y
				n.y = bounds[0].y; //min Y
			}
			
			if( plane[i].z >= 0 ){
				p.z = bounds[7].z; //max Z
				n.z = bounds[0].z; //min Z
			}

			if( glm::dot(vec4(p, 1.0), plane[i] ) < 0 )
				return OUTSIDE;


			if( glm::dot(vec4(n, 1.0), plane[i] ) < 0 )
				result = INTERSECT;
			
			
	}

	return result;
}


void Scene :: OctreeCull(Octree* node){
	
	if( FrustumCull(node->bounds, camera->plane) == INSIDE ){
	
		node->DepthFirst(node, true);

	}
	
	
	if( FrustumCull(node->bounds, camera->plane) == INTERSECT){
	
		if(node->children[0] == NULL){
			node->DepthFirst(node, true);
		}
		else{
			for(int i = 0; i < 8; ++i)
				OctreeCull(node->children[i]);
		}

	}
		
	if( FrustumCull(node->bounds, camera->plane) == OUTSIDE ){
		node->DepthFirst(node, false);
	}
		

}

*/