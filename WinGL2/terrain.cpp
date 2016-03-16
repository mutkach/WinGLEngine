#include "terrain.h"

Terrain::Terrain(float posx, float posz, int seed, std :: string location){
	x = posx;
	Generate(posx, posz, seed);
	Create(posx, posz);
	CalculateNormals();
	//Texture tex;
	//CTexture *Texture;
	//Texture = new CTexture();
	//Texture->LoadTexture(&location[0], &tex);
	//textures = &tex;
	//textureID = textures->texID;

}


void Terrain :: Generate(float posx, float posz, int seed){
	
	min_height =  FLT_MAX;
	max_height = -FLT_MAX;
	x = posx;
	z = posz;
	module :: Perlin Cloud;
	module :: RidgedMulti Ridge;
	srand(seed);
	 for(int i = 0; i < map_size; i+=1){
        for(int k = 0; k < map_size; k+=1){
			//float current = (Ridge.GetValue((i + posx)*0.009f, -18428, (k + posz)*0.009f)*10);

					heightmap[i][k] = 0;

				 if(heightmap[i][k] > max_height)
					 max_height = heightmap[i][k];
				 if(heightmap[i][k] < min_height)
					 min_height = heightmap[i][k];
				
        }
    }
}


void Terrain:: Create(float posx, float posz){
	glGenBuffers(1, &TerrainMesh.VBOid);
	glGenBuffers(1, &TerrainMesh.Indexid);
	Mesh* mesh = &TerrainMesh;
	int size1;
	int size2;
	int size3;

	for(int i = 0; i < map_size; i+=1){
		for(int k = 0; k < map_size ; k+=1){
			size1 = i*map_size+k;
			mesh->pVerts[size1].p.x = i + posx;
			mesh->pVerts[size1].p.y = heightmap[i][k]; 
			mesh->pVerts[size1].p.z = k + posz; 

				mesh->pVerts[size1].t.x = i/float(map_size);

				mesh->pVerts[size1].t.y = k/float(map_size);



		}
	}
	for(int i = 0; i < map_size - 1; i+=1){
		for(int k = 0; k < map_size - 1; k+=1){
			
			/*
			size2 = mesh->pFaces.size();

				size3 = 0 + k + i*map_size;
				mesh->pFaces.resize(size2+1); 
				mesh->pFaces[size2].v1 = size3;				 //0     . .  
												             //      # .

				mesh->pFaces[size2].v2 = size3 + map_size; //1     # .
						 								   //      . .		
				
				mesh->pFaces[size2].v3 = 1 + size3;       //2	 . .
												          //     . #		

				mesh->pFaces.resize(size2 + 2);
				
				mesh->pFaces[size2].v1 = size3 + map_size;    //1     # .
												     //      . .
				
				mesh->pFaces[size2].v2 = 1 + size3 + map_size; //3    . #
													  //     . .

				mesh->pFaces[size2 + 1].v3 = 1 + size3 ;			    //2  . .
												        //   . #	
			
			//}
			
			*/
			//else{
				size2 = mesh->pFaces.size();

				size3 = 0 + k + i*map_size;
				
				mesh->pFaces.resize(size2 + 1); 
				mesh->pFaces[size2].v1 = size3 ; //0
				mesh->pFaces[size2].v2 = size3 + map_size; //1 
				mesh->pFaces[size2].v3 = 1 + size3; //2 

				mesh->pFaces.resize(size2 + 2);
				mesh->pFaces[size2 + 1].v1 = size3 + map_size; //1
				mesh->pFaces[size2 + 1].v2 = 1 + size3 + map_size; //3
				mesh->pFaces[size2 + 1].v3 = 1 + size3 ; //2

			//}
			
		}
	}






}

void Terrain :: Draw(){
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glBindBuffer(GL_ARRAY_BUFFER, VertexVBID);
  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, sizeof(Vertex), (float*)(sizeof(GLfloat)*3));
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);   
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glTexCoordPointer(2, GL_FLOAT,sizeof(Vertex),(float*)(sizeof(GLfloat)*6));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBID);
  glDrawElements(GL_TRIANGLES, fc.size(), GL_UNSIGNED_INT, NULL);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  
}

void Terrain :: CalculateNormals(){
	CVertex3 f1, f2, f3, f4;
	float magnitude;
	int size1;
	for(int i = 0; i < map_size; ++i){
		for(int k = 0;  k < map_size; ++k){
			size1 = i*map_size+k;
			
			
			if(i > 1){
				f1.x =  heightmap[i][k] - heightmap[i-1][k];
				f1.y = 1;
				f1.z = 0;
			}
			else{
				f1.x = 0;
				f1.y = 0;
				f1.z = 0;
			}
			
			if(k < map_size - 1){
				f2.x = 0;
				f2.y = 1;
				f2.z = heightmap[i][k+1] - heightmap[i][k];
			}
			
			else{
				f2.x = 0;
				f2.y = 0;
				f2.z = 0;
			}

			if(i < map_size - 1){
				f3.x = heightmap[i+1][k] - heightmap[i][k];
				f3.y = 1;
				f3.z = 0;
			}

			else{
				f3.x = 0;
				f3.y = 0;
				f3.z = 0;
			}

			if(k > 1){
				f4.x = 0;
				f4.y = 1;
				f4.z = heightmap[i][k-1] - heightmap[i][k];
			}
			else{
				f4.x = 0;
				f4.y = 0;
				f4.z = 0;
			}



			data[size1].n.x = (f1.x + f2.x + f3.x + f4.x)/4;
			data[size1].n.y = (f1.y + f2.y + f3.y + f4.y)/4;
			data[size1].n.z = (f1.z + f2.z + f3.z + f4.z)/4;
			magnitude = (float)sqrt( (data[size1].n.x * data[size1].n.x) + (data[size1].n.y * data[size1].n.y) + (data[size1].n.z * data[size1].n.z) );
			data[size1].n.x /= magnitude;
			data[size1].n.y /= magnitude;
			data[size1].n.z /= magnitude;
			
		}
	}

    glBindBuffer(GL_ARRAY_BUFFER, VertexVBID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*map_size*map_size, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex)*map_size*map_size, data);

	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)*fc.size(), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLint)*fc.size(), &fc[0]);
}
	
void Terrain :: LoadTextures(std :: string location){

}
	