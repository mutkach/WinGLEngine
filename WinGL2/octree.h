#ifndef OCTREE_H
#define OCTREE_H

#include <vector>
#include "math.h"
#include "object.h"
#include "entity.h"


class Mesh;
class Object;
struct Entity;
//Чинить. Позже
class Octree{
public:
	Octree *children[8];

	vec3 position;
	vec3 bounds[8];
	int objThreshold;
	int depthThreshold;
	int depth;
	float length;
	
	Octree(int _objThreshold, int _depthThreshold, int _depth, float _length, vec3 _position);

	void add(Octree* node, Entity* object);
	void DepthFirst(Octree* node, bool flag);
	std :: vector <Entity*> entities; 


};


#endif