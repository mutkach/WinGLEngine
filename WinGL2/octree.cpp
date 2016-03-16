#include "octree.h"


bool BoxIntersection(vec3 *aabb, vec3 position, float length);




Octree :: Octree(int _objThreshold, int _depthThreshold, int _depth, float _length, vec3 _position){

	depth = _depth;
	length = _length;
	position = _position;
	objThreshold = _objThreshold;
	depthThreshold = _depthThreshold;


	for(int i = 0; i < 8; ++i){
		children[i] = NULL;
		bounds[i] = position;
		if( i & 1 ) bounds[i].x += length;
		if( i & 2 ) bounds[i].y += length;
		if( i & 4 ) bounds[i].z += length;
	}

}

void Octree :: add(Octree *node, Entity* entity){

	if( node->children[0] != 0 ){

		int x = 255;
			if(entity->bounds[0].x > node->position.x + node->length/2) //Bit Mask
			x &= 170; // 10101010 -> {0, 1, 0, 1, 0, 1, 0, 1} 
			if(entity->bounds[0].y > node->position.y + node->length/2)
			x &= 204; // 11001100 -> {0, 0, 1, 1, 0, 0, 1, 1} 
 			if(entity->bounds[0].z > node->position.z + node->length/2)
			x &= 240; // 11110000 -> {0, 0, 0, 0, 1, 1, 1, 1} 
			
			
			for(int i = 0; i < 8; ++i){
			
				//if(x & int( pow<float>(2.0, float(i) ) ) ){ 
					vec3 _position = node->position;
					if( i & 1 ) _position.x += node->length/2;
					if( i & 2 ) _position.y += node->length/2;
					if( i & 4 ) _position.z += node->length/2;
				
					if( BoxIntersection(entity->bounds, _position, node->length/2) )
						add(node->children[i], entity);	
				//}
			
			}
					
			return;

	}

	if( node->children[0] == NULL ){


		if(node->depth >= node->depthThreshold){
		
			
			node->entities.push_back(entity);
			++entity->octreeVisibility;
			return;
		
		}

		if(node->entities.size() <= node->objThreshold){
		
			
			node->entities.push_back(entity);
			++entity->octreeVisibility;
			return;
		
		}

		else{

			//Init new children
			for(int i = 0; i < 8; ++i){
				vec3 newPos = position;
				if( i & 1 ) newPos.x += node->length/2;
				if( i & 2 ) newPos.y += node->length/2;
				if( i & 4 ) newPos.z += node->length/2;

				node->children[i] = new Octree(node->objThreshold, node->depthThreshold, node->depth + 1, node->length/2, newPos);
			}
			//Reset points
			std :: vector <Entity*> temp;
			temp = node->entities;
			node->entities.resize(0);

			for(int i = 0 ; i < temp.size(); ++i){

				temp[i]->octreeVisibility  = 0;
				add(node, temp[i]);	
				
			}

			temp.resize(0);
			//Main object insertion
			add(node, entity);
			return;
		}
	
	
	
	}

}


bool BoxIntersection(vec3 *aabb, vec3 position, float length){
	vec3 center2 = position;
	center2.x += length/2;
	center2.y += length/2;
	center2.z += length/2;

	float distX1 = fabs(aabb[1].x - aabb[0].x)/2;
	float distY1 = fabs(aabb[2].y - aabb[0].y)/2;
	float distZ1 = fabs(aabb[4].z - aabb[0].z)/2;
	
	float distX2 = length/2;
	float distY2 = length/2;
	float distZ2 = length/2;
	
	int result = 0;
	if( fabs( aabb[8].x - center2.x ) < distX1 + distX2 ) //8-ого элемента сейчас нет. Заменить чуть позже
		result++;
	
	if( fabs( aabb[8].y - center2.y ) < distY1 + distY2 )
		result++;

	if( fabs( aabb[8].z - center2.z ) < distZ1 + distZ2 )
		result++;
	

	if(result >= 2)
		return true;
	///Если целиком внутри(result == 3), то break поиск в строке 41

	return false;

}

void Octree ::DepthFirst(Octree* node, bool flag){

	if(node->children[0] == NULL){

		for(int i = 0; i < node->entities.size(); ++i){
			if(!flag)
				--node->entities[i]->currentOctreeVisibility;

		}
	}

	if(node->children[0]!= NULL){

		for(int i = 0; i < 8; ++i){

			DepthFirst(node->children[i], flag);


		}


	}


}



