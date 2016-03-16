#ifndef __OBJECT_H
#define __OBJECT_H

#include "math.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "material.h"
#include "physproperty.h"

class Mesh;
struct Material;
struct PhysProperty;

using namespace glm;

class Object
{	
public:


	Object(const std :: string location, bool _static);

	//void Render();
	void LoadTextures();
	void InitMesh(const aiMesh* _mesh, Mesh &mesh, int numOfVertices);


	//vec3 bounds[8];

	const aiScene* sc;
	bool isLeftHanded;

	btCollisionShape* shape; 

    int numOfMeshes;           // Число обьектов в модели
    int numOfMaterials;         // Число материалов модели

	std :: vector<Material> materials;
    std :: vector<Mesh> mesh;      // Список обьектов в модели
	std :: string upper_location;
	std :: string lower_location;


};


#endif