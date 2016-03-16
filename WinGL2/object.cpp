#include "object.h"
#define BONE_AFFINITY 4




bool exists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}


void Object::LoadTextures(){

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
			if(!exists(&myname[0])){
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
			if(!exists(&myname[0])){
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
			if(!exists(&myname[0])){
				materials[i].textureNormal = new Texture("default/textures/normal.tga");
				materials[i].textureNormal->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
			}
			else{
				materials[i].textureNormal = new Texture(&myname[0]);
				materials[i].textureNormal->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
			}
		}
		else{
			materials[i].textureNormal= new Texture("default/textures/normal.tga");
			materials[i].textureNormal->SetFiltering(true, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
		}
		
	
		
	}

}

void Object::InitMesh(const aiMesh* _mesh, Mesh &mesh, int numOfVertices){

	CVertex3 maxes, mins;
	maxes.x = -1000; maxes.y = -1000; maxes.z = -1000;
	mins.x = 1000; mins.y = 1000; mins.z = 1000;
	mesh.numOfVerts = _mesh->mNumVertices;
			mesh.numOfFaces = _mesh->mNumFaces;
			mesh.pVerts.resize(_mesh->mNumVertices);
			mesh.pFaces.resize(_mesh->mNumFaces);
			mesh.materialID = _mesh->mMaterialIndex;
			mesh.baseVertex = numOfVertices;
			numOfVertices += _mesh->mNumVertices;
			
			for(unsigned int i1 = 0; i1 < _mesh->mNumVertices; ++i1){
				Vertex* currentVertex = &mesh.pVerts[i1];

				
					currentVertex->p.x = _mesh->mVertices[i1].x;
					currentVertex->p.y = _mesh->mVertices[i1].y;
					currentVertex->p.z = _mesh->mVertices[i1].z;
				
					currentVertex->n.x = _mesh->mNormals[i1].x;
					currentVertex->n.y = _mesh->mNormals[i1].y;	
					currentVertex->n.z = _mesh->mNormals[i1].z;

		
				if(_mesh->mTextureCoords[0]){
					currentVertex->t.x = _mesh->mTextureCoords[0][i1].x;
					currentVertex->t.y = _mesh->mTextureCoords[0][i1].y;
				}

				if(_mesh->HasTangentsAndBitangents() ){
					currentVertex->tan.x = _mesh->mTangents[i1].x;
					currentVertex->tan.y = _mesh->mTangents[i1].y;
					currentVertex->tan.z = _mesh->mTangents[i1].z;
				}

				
				if(currentVertex->p.x > maxes.x) maxes.x = currentVertex->p.x; if(currentVertex->p.x < mins.x) mins.x = currentVertex->p.x;
				if(currentVertex->p.y > maxes.y) maxes.y = currentVertex->p.y; if(currentVertex->p.y < mins.y) mins.y = currentVertex->p.y;
				if(currentVertex->p.z > maxes.z) maxes.z = currentVertex->p.z; if(currentVertex->p.z < mins.z) mins.z = currentVertex->p.z;
				
			}

			for(unsigned int i1 = 0; i1 < _mesh->mNumFaces; ++i1){
				mesh.pFaces[i1].v1 = _mesh->mFaces[i1].mIndices[0];
				mesh.pFaces[i1].v2 = _mesh->mFaces[i1].mIndices[1];
				mesh.pFaces[i1].v3 = _mesh->mFaces[i1].mIndices[2];
			}


			//mesh.bounds[8] = vec3(0.0, 0.0, 0.0);

			/*
			for(unsigned int i = 0; i < 8; ++i){
				mesh.bounds[i].x = mins.x;
				mesh.bounds[i].y = mins.y;
				mesh.bounds[i].z = mins.z;
				if(i & 1) mesh.bounds[i].x = maxes.x;
				if(i & 2) mesh.bounds[i].y = maxes.y;
				if(i & 4) mesh.bounds[i].z = maxes.z;
				mesh.bounds[i] = mesh.bounds[i];
				mesh.bounds[8] += mesh.bounds[i];
			}
			mesh.bounds[8] /= 8;
			*/

}



Object :: Object(const std:: string location, bool _static)
{	
	upper_location = location;
	lower_location =  upper_location.substr(0,upper_location.find_last_of('/')+1);

	sc = aiImportFile( &upper_location[0],aiProcessPreset_TargetRealtime_Quality | aiProcess_GenNormals);
	
	if(!sc)
		return;


	int CurrentSize, CurrentSize1;
	numOfMeshes = sc->mNumMeshes;	
	numOfMaterials = sc->mNumMaterials;
	mesh.resize(sc->mNumMeshes);
	

	if(sc->HasMaterials() ){
		LoadTextures();
	}
	

	int numOfVertices = 0;

	for (unsigned int i = 0; i < sc->mNumMeshes; ++i)
	{				
				const struct aiMesh* _mesh = sc->mMeshes[i];
				InitMesh(_mesh, mesh[i], numOfVertices);

				glGenBuffers(1, &mesh[i].VBOid);
				glGenBuffers(1, &mesh[i].Indexid);

				CurrentSize = mesh[i].numOfVerts;
				glBindBuffer(GL_ARRAY_BUFFER, mesh[i].VBOid);
				glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*CurrentSize, NULL, GL_STATIC_DRAW);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex)*CurrentSize, &mesh[i].pVerts[0]);

				CurrentSize1 = mesh[i].numOfFaces;
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh[i].Indexid);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)*CurrentSize1*3, NULL, GL_STATIC_DRAW);
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLint)*CurrentSize1*3, &mesh[i].pFaces[0].v1);

	}

	

	btTriangleMesh* tmpMesh = new btTriangleMesh();

	for(int i = 0; i < numOfMeshes; ++i){
		for(int k = 0; k < mesh[i].numOfFaces; ++k){

			int index1 = mesh[i].pFaces[k].v1;
			int index2 = mesh[i].pFaces[k].v2;
			int index3 = mesh[i].pFaces[k].v3;

			

			btVector3 v1(-mesh[i].pVerts[index1].p.x,  -mesh[i].pVerts[index1].p.y,  mesh[i].pVerts[index1].p.z );
			btVector3 v2(-mesh[i].pVerts[index2].p.x,  -mesh[i].pVerts[index2].p.y,  mesh[i].pVerts[index2].p.z );
			btVector3 v3(-mesh[i].pVerts[index3].p.x,  -mesh[i].pVerts[index3].p.y,  mesh[i].pVerts[index3].p.z );

			tmpMesh->addTriangle(v1, v2, v3);

		}
	}

	if(_static){//Static
		shape = new btBvhTriangleMeshShape(tmpMesh, true);
		
	}
	else{
		btConvexShape* originalConvexShape = new btConvexTriangleMeshShape(tmpMesh, true);// is the original convexHullShape
		btShapeHull hull(originalConvexShape);//create a hull approximation
		btScalar margin = originalConvexShape->getMargin(); //Где-то в стеке, где-то в куче. Потом проверить
	
		hull.buildHull(margin);

		btConvexHullShape* tmpShape = new btConvexHullShape();

		for (int i = 0; i < hull.numVertices(); i++){

			tmpShape->addPoint(hull.getVertexPointer()[i]);	

		}

		shape = tmpShape;
		
		delete originalConvexShape;
	}

	
	
	
}

