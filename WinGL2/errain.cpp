#include "main.h"
#include "errain.h"


errain::errain(void)
{
}


errain::~errain(void)
{
}



void errain :: Generate(float posx, float posz, int seed){
	min_height =  10000;
	max_height = -10000;
	x = posx;
	z = posz;
	module :: Perlin Cloud;
	module :: RidgedMulti Ridge;
	srand(seed);
	 for(int i = 0; i < map_size; i+=1){
        for(int k = 0; k < map_size; k+=1){
				 a[i][k] = (Ridge.GetValue((i + posx)*0.004f, 5, (k + posz)*0.004f)*40);
				 if(a[i][k] > max_height)
					 max_height = a[i][k];
				 if(a[i][k] < min_height)
					 min_height = a[i][k];
				
        }
    }
}


void errain:: Create(float posx, float posz){
	glGenBuffers(1, &VertexVBID);
	glGenBuffers(1, &IndexVBID);
	int size1;
	int size2;
	int size3;

	for(int i = 0; i < map_size; i+=1){
		for(int k = 0; k < map_size ; k+=1){
			size1 = i*map_size+k;
			data[size1].p.x = i + posx;
			data[size1].p.y = a[i][k]; 
			data[size1].p.z = k + posz; 

		}
	}
	for(int i = 0; i < map_size - 1; i+=1){
		for(int k = 0; k < map_size - 1; k+=1){
			
			//if( ((a[i+1][k+1] > a[i][k] && a[i+1][k+1]>a[i][k+1] && a[i+1][k+1]>a[i+1][k]) || (a[i+1][k+1]<a[i][k] && a[i+1][k+1]<a[i][k+1] && a[i+1][k+1]<a[i+1][k]) || (a[i][k] < a[i+1][k] && a[i][k]<a[i][k+1] && a[i][k]<a[i+1][k+1]) || (a[i][k]>a[i+1][k] && a[i][k]>a[i][k+1] && a[i][k]>a[i+1][k+1])) ){// || a[i][k+1]>a[i+1][k+1] && a[i][k+1]>a[i][k]  && a[i+1][k]<a[i][k] && a[i+1][k]<a[i+1][k+1]  || a[i][k+1]<a[i+1][k+1] && a[i][k+1]<a[i][k]  && a[i+1][k]>a[i+1][k+1] && a[i+1][k]>a[i][k]  ){
				size2 = fc.size();

				size3 = 0 + k + i*map_size;
				fc.resize(size2+3); 
				fc[size2] = size3;				 //0     . .  
												 //      # .

				fc[size2 + 1] = size3 + map_size;//1     # .
												 //      . .		
				
				fc[size2 + 2] = 1 + size3;       //2	 . .
												 //      . #		

				fc.resize(size2 + 6);
				
				fc[size2 + 3] = size3 + map_size;    //1     # .
												     //      . .
				
				fc[size2 + 4] = 1 + size3 + map_size; //3    . #
													  //     . .

				fc[size2 + 5] = 1 + size3 ;			    //2  . .
												        //   . #	
			
			//}
			
			 
			//else{
				size2 = fc.size();

				size3 = 0 + k + i*map_size;
				
				fc.resize(size2+3); 
				fc[size2] = size3 ; //0
				fc[size2 + 1] = size3 + map_size; //1 
				fc[size2 + 2] = 1 + size3 + map_size; //2 

				fc.resize(size2 + 6);
				fc[size2 + 3] = size3 ; //1
				fc[size2 + 4] = 1 + size3 + map_size; //3
				fc[size2 + 5] = 1 + size3 ; //2

			//}
			
		}
	}






}

void errain :: Draw(){

  glBindBuffer(GL_ARRAY_BUFFER, VertexVBID);
  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, sizeof(Vertex), (float*)(sizeof(GLfloat)*3));
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);   

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBID);
  glDrawElements(GL_TRIANGLES, fc.size(), GL_UNSIGNED_INT, NULL);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  
}

void errain :: Calculate_Normals(){
	CVertex3 f1, f2, f3, f4;
	float magnitude;
	int size1;
	for(int i = 0; i < map_size; ++i){
		for(int k = 0;  k < map_size; ++k){
			size1 = i*map_size+k;
			
			
			if(i > 1){
				f1.x =  a[i][k] - a[i-1][k];
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
				f2.z = a[i][k+1] - a[i][k];
			}
			
			else{
				f2.x = 0;
				f2.y = 0;
				f2.z = 0;
			}

			if(i < map_size - 1){
				f3.x = a[i+1][k] - a[i][k];
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
				f4.z = a[i][k-1] - a[i][k];
			}
			else{
				f4.x = 0;
				f4.y = 0;
				f4.z = 0;
			}



			data[size1].n.x = (f1.x + f2.x + f3.x + f4.x)/4;
			data[size1].n.y = (f1.y + f2.y + f3.y + f4.y)/4;
			data[size1].n.z = (f1.z + f2.z + f3.z + f4.z)/4;
			magnitude = (float)sqrt( (data[size1].n.x * data[size1].n.x) +
            (data[size1].n.y * data[size1].n.y) +
            (data[size1].n.z * data[size1].n.z) );
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
	