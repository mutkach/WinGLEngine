#ifndef __ANIMODEL_H
#define __ANIMODEL_H
#include "main.h"


class Mesh;

struct Material;



class Animodel
{	
public:


	Animodel(std :: string location, int left);

	//void Render();
	void LoadTextures();
	void InitMesh(const aiMesh* _mesh, Mesh &mesh, int numOfVertices);
	void LoadBones(std :: string location, int left);
	
	void BoneTransform(float TimeInSeconds);
	const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const std :: string NodeName);
	unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
	unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
	unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
	void ReadNode(float AnimationTime, const aiNode* pNode, const aiMatrix4x4 ParentTransform);
	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

	const aiScene* sc;
	bool isLeftHanded;
	 
    int numOfMeshes;           // Число обьектов в модели
    int numOfMaterials;         // Число материалов модели
	int numOfBones;

	std :: vector<Material> materials;
    std :: vector<Mesh> mesh;      // Список обьектов в модели
	std :: string upper_location;
	std :: string lower_location;
	

	std :: vector<aiMatrix4x4> transforms;
	std :: vector<aiMatrix4x4> boneOffsets;
	std :: vector<aiMatrix4x4> boneFinals;

	glm :: mat4 transform; 
	aiMatrix4x4 baseTransform;
	std :: map<std :: string, int> boneMapping;
};


#endif