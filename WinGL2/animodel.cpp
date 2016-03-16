#include "animodel.h"
#define BONE_AFFINITY 4



BoneInfo AddBoneData(int BoneIndex, float Weight, BoneInfo& b){
	for(unsigned int i = 0; i < BONE_AFFINITY; ++i){
		if (b.weight[i] == 0.0) {
			b.BoneID[i] = BoneIndex;
            b.weight[i] = Weight;
            return b;
        }     
	}
	assert(0);
}

bool exists1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

void Animodel::LoadTextures(){


	aiString Path;
	bool read;
	materials.resize(sc->mNumMaterials);  

	std:: string myname;
	std :: string extension;
	for(unsigned int i = 0; i < sc->mNumMaterials; ++i){

		if(AI_SUCCESS == sc->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &Path)){
			myname = Path.data;
			myname = lower_location + myname.substr( myname.find_last_of( '/' ) +1 );
			extension = myname.substr( myname.find_last_of( '.' ) +1 );
			if(!exists1(&myname[0])){
				materials[i].textureDiffuse= new Texture("default/textures/diffuse.tga");
				materials[i].textureDiffuse->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
			}
			else{
				materials[i].textureDiffuse= new Texture(&myname[0]);
				materials[i].textureDiffuse->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
			}
		}
		else{
				materials[i].textureDiffuse= new Texture("default/textures/diffuse.tga");
				materials[i].textureDiffuse->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
		}
		
		if(AI_SUCCESS == sc->mMaterials[i]->GetTexture(aiTextureType_SPECULAR, 0, &Path)){
			myname = Path.data;
			myname = lower_location + myname.substr( myname.find_last_of( '/' ) +1 );
			extension = myname.substr( myname.find_last_of( '.' ) +1 );
			if(!exists1(&myname[0])){
				materials[i].textureSpecular = new Texture("default/textures/specular.tga");
				materials[i].textureSpecular->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
			}
			else{
				materials[i].textureSpecular = new Texture(&myname[0]);
				materials[i].textureSpecular->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
			}
		}
		else{
				materials[i].textureSpecular = new Texture("default/textures/specular.tga");
				materials[i].textureSpecular->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
		}


		if(AI_SUCCESS == sc->mMaterials[i]->GetTexture(aiTextureType_NORMALS, 0, &Path)){
			myname = Path.data;
			myname = lower_location + myname.substr( myname.find_last_of( '/' ) +1 );
			extension = myname.substr( myname.find_last_of( '.' ) +1 );
			if(!exists1(&myname[0])){
				materials[i].textureNormal = new Texture("default/textures/normal.tga");
				materials[i].textureNormal->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
			}
			else{
				materials[i].textureNormal = new Texture(&myname[0]);
				materials[i].textureNormal->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
			}
		}
		else{
			materials[i].textureNormal = new Texture("default/textures/normal.tga");
			materials[i].textureNormal->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
		}
		
	
		
	}

}

void Animodel::InitMesh(const aiMesh* _mesh, Mesh &mesh, int numOfVertices){
	
	mesh.numOfVerts = _mesh->mNumVertices;
			mesh.numOfFaces = _mesh->mNumFaces;
			mesh.pVerts.resize(_mesh->mNumVertices);
			mesh.pFaces.resize(_mesh->mNumFaces);
			mesh.materialID = _mesh->mMaterialIndex;
			mesh.baseVertex = numOfVertices;
			numOfVertices += _mesh->mNumVertices;

			for(unsigned int i1 = 0; i1 < _mesh->mNumVertices; ++i1){
				switch(isLeftHanded){

				case 0:
					{
					mesh.pVerts[i1].p.x = _mesh->mVertices[i1].x;
					mesh.pVerts[i1].p.y = _mesh->mVertices[i1].y;
					mesh.pVerts[i1].p.z = _mesh->mVertices[i1].z;
				
					mesh.pVerts[i1].n.x = _mesh->mNormals[i1].x;
					mesh.pVerts[i1].n.y = _mesh->mNormals[i1].y;	
					mesh.pVerts[i1].n.z = _mesh->mNormals[i1].z;
					break;
					}

				case 1:
					{
					mesh.pVerts[i1].p.x = _mesh->mVertices[i1].x;
					mesh.pVerts[i1].p.z = _mesh->mVertices[i1].y;
					mesh.pVerts[i1].p.y = _mesh->mVertices[i1].z;
				
					mesh.pVerts[i1].n.x = _mesh->mNormals[i1].x;
					mesh.pVerts[i1].n.z = _mesh->mNormals[i1].y;	
					mesh.pVerts[i1].n.y = _mesh->mNormals[i1].z;
					break;
					}

				}
				if(sc->HasMaterials() ){
					mesh.pVerts[i1].t.x = _mesh->mTextureCoords[0][i1].x;
					mesh.pVerts[i1].t.y = 1 - _mesh->mTextureCoords[0][i1].y;
				}

			}
			for(unsigned int i1 = 0; i1 < _mesh->mNumFaces; ++i1){
				mesh.pFaces[i1].v1 = _mesh->mFaces[i1].mIndices[0];
				mesh.pFaces[i1].v2 = _mesh->mFaces[i1].mIndices[1];
				mesh.pFaces[i1].v3 = _mesh->mFaces[i1].mIndices[2];
			}

			for(unsigned int i = 0; i < _mesh->mNumBones; ++i){
					std :: string boneName = _mesh->mBones[i]->mName.data;
					int BoneIndex = 0;
							if (boneMapping.find(boneName) == boneMapping.end()) {
								BoneIndex = numOfBones;
								numOfBones++; 
								aiMatrix4x4 boneOffset = _mesh->mBones[i]->mOffsetMatrix;
								boneOffsets.push_back(boneOffset);
								boneFinals.resize(boneFinals.size()+1);
								boneMapping[boneName] = BoneIndex;
							}
							else{
								BoneIndex = boneMapping[boneName];
							}
							unsigned int VertexID;
							for (unsigned int j = 0 ; j < _mesh->mBones[i]->mNumWeights; j++) {
							
								VertexID = _mesh->mBones[i]->mWeights[j].mVertexId;

								float Weight = _mesh->mBones[i]->mWeights[j].mWeight; 	

								//AddBoneData(BoneIndex, Weight, mesh.pVerts[VertexID].b);
							}
				}
			

}

Animodel :: Animodel(std:: string location, int left)
{	
	upper_location = location;
	lower_location =  upper_location.substr(0,upper_location.find_last_of('/')+1);
	isLeftHanded = left;

	sc = aiImportFile( &upper_location[0],aiProcessPreset_TargetRealtime_MaxQuality);

	baseTransform = sc->mRootNode->mTransformation;
	
	baseTransform.Inverse();


	numOfBones = 0;

	int CurrentSize, CurrentSize1;

	numOfMeshes = sc->mNumMeshes;	
	numOfMaterials = sc->mNumMaterials;
	mesh.resize(sc->mNumMeshes);

	if(sc->HasMaterials() ){
		LoadTextures();
	}
	

	int numOfVertices = 0;
		for (unsigned int n = 0; n < sc->mNumMeshes; ++n)
		{				
				const struct aiMesh* _mesh = sc->mMeshes[n];
				InitMesh(_mesh, mesh[n], numOfVertices);
				
		}


	for(int i = 0; i < numOfMeshes; ++i){
		glGenBuffers(1, &mesh[i].VBOid);
		glGenBuffers(1, &mesh[i].Indexid);

		CurrentSize = mesh[i].numOfVerts;
		glBindBuffer(GL_ARRAY_BUFFER, mesh[i].VBOid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(XVertex)*CurrentSize, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(XVertex)*CurrentSize, &mesh[i].pVerts[0]);

		CurrentSize1 = mesh[i].numOfFaces;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh[i].Indexid);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)*CurrentSize1*3, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLint)*CurrentSize1*3, &mesh[i].pFaces[0].v1);

	}
	
}

/*
void Animodel :: Render(){
	
	for(int i = 0; i < numOfMeshes; ++i){
	      int diffuse;
		  diffuse = materials[mesh[i].materialID].textureDiffuse->texID;
		  glActiveTexture(GL_TEXTURE0);
		  glBindTexture( GL_TEXTURE_2D, diffuse);
		  if(materials[mesh[i].materialID].isSkinned){
			  glUseProgram(Skinning.programHandle);
					mesh[i].RenderMesh();
				glUseProgram(0);
		  }
    }
 
}
*/


void Animodel::ReadNode(float AnimationTime, const aiNode* pNode, const aiMatrix4x4 ParentTransform)
{ 
    std :: string NodeName(pNode->mName.data);

    const aiAnimation* pAnimation = sc->mAnimations[0];

	aiMatrix4x4 NodeTransformation = pNode->mTransformation;

    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
	
    if (pNodeAnim) {
        // Interpolate scaling and generate scaling transformation matrix
        aiVector3D Scaling;
        CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
        aiMatrix4x4 ScalingM;
        ScalingM.Scaling(Scaling, ScalingM);
        
        // Interpolate rotation and generate rotation transformation matrix
        aiQuaternion RotationQ;
        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);        
        aiMatrix4x4 RotationM = aiMatrix4x4(RotationQ.GetMatrix());

        // Interpolate translation and generate translation transformation matrix
        aiVector3D Translation;
        CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
        aiMatrix4x4 TranslationM;
        TranslationM.Translation(Translation, TranslationM);
        
        // Combine the above transformations
        NodeTransformation = TranslationM * RotationM * ScalingM;
    }
	

   aiMatrix4x4 GlobalTransformation = ParentTransform * NodeTransformation;

    if (boneMapping.find(NodeName) != boneMapping.end()) {
        unsigned int BoneIndex = boneMapping[NodeName];
		boneFinals[BoneIndex] = baseTransform * GlobalTransformation * boneOffsets[BoneIndex];
    }

    for (unsigned int i = 0 ; i < pNode->mNumChildren ; i++) {
        ReadNode(AnimationTime, pNode->mChildren[i], GlobalTransformation);
    }

}

//Черный ящик

void Animodel::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumScalingKeys == 1) {
        Out = pNodeAnim->mScalingKeys[0].mValue;
        return;
    }

    unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
    unsigned int NextScalingIndex = (ScalingIndex + 1);
    assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
    float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
    const aiVector3D& End   = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}

unsigned int Animodel::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumScalingKeys > 0);
    
    for (unsigned int i = 0 ; i < pNodeAnim->mNumScalingKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
            return i;
        }
    }

    return 0;
}

const aiNodeAnim* Animodel::FindNodeAnim(const aiAnimation* pAnimation, const std :: string NodeName)
{
    for (unsigned int i = 0 ; i < pAnimation->mNumChannels ; i++) {
        const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
        
        if (std :: string(pNodeAnim->mNodeName.data) == NodeName) {
            return pNodeAnim;
        }
    }
    
    return NULL;
}

void Animodel::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	// we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1) {
        Out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }
    
    unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
    unsigned int NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
    float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ   = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;    
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    Out = Out.Normalize();
}

unsigned int Animodel::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumRotationKeys > 0);

    for (unsigned int i = 0 ; i < pNodeAnim->mNumRotationKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);

    return 0;
}

void Animodel::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumPositionKeys == 1) {
        Out = pNodeAnim->mPositionKeys[0].mValue;
        return;
    }
            
    unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
    unsigned int NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
    float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}

unsigned int Animodel::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{    
    for (unsigned int i = 0 ; i < pNodeAnim->mNumPositionKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);

    return 0;
}

void Animodel::BoneTransform(float TimeInSeconds)
{
    aiMatrix4x4 Identity;
	aiVector3t<float> tempValue(0, 0, 0);
	Identity.Translation(aiVector3t<float>(0,0,0), Identity);

    
    
    float TicksPerSecond = (float)(sc->mAnimations[0]->mTicksPerSecond != 0 ? sc->mAnimations[0]->mTicksPerSecond : 25.0f);
    float TimeInTicks = TimeInSeconds * TicksPerSecond;
    float AnimationTime = fmod(TimeInTicks, (float)sc->mAnimations[0]->mDuration);

	ReadNode(AnimationTime, sc->mRootNode, Identity);

	transforms.resize(numOfBones);

    for (unsigned int i = 0 ; i < numOfBones; i++) {
		transforms[i]= boneFinals[i];
		
    }
}
