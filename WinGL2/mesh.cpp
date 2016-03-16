#include "mesh.h"

void Mesh :: RenderStaticMesh(){

		  int CurrentSize1 = numOfFaces;
		  int CurrentSize = numOfVerts;
		  glBindBuffer(GL_ARRAY_BUFFER, VBOid);
		  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*CurrentSize, NULL, GL_STATIC_DRAW);
		  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex)*CurrentSize, &pVerts[0]);
		  glEnableVertexAttribArray(0);
		  glEnableVertexAttribArray(1);
		  glEnableVertexAttribArray(2);
		  //glEnableVertexAttribArray(3);
		  //glEnableVertexAttribArray(4);


		  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); 
		  glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(GLfloat)*3));
		  glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(GLfloat)*6));
		  //glVertexAttribPointer (3, 4, GL_FLOAT, GL_TRUE , sizeof(Vertex), (float*)(sizeof(GLfloat)*8));
		  //glVertexAttribPointer (4, 4, GL_INT,   GL_FALSE, sizeof(Vertex), (float*)(sizeof(GLfloat)*12));

		  

		  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Indexid);
		  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)*CurrentSize1*3, NULL, GL_STATIC_DRAW);
		  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLint)*CurrentSize1*3, &pFaces[0].v1);
		  glDrawElements(GL_TRIANGLES, CurrentSize1*3, GL_UNSIGNED_INT, NULL);

		  glDisableVertexAttribArray(0);
		  glDisableVertexAttribArray(1);
		  glDisableVertexAttribArray(2);
		  //glDisableVertexAttribArray(3);
		  //glDisableVertexAttribArray(4);
};

void Mesh :: RenderMesh(){

		  int CurrentSize1 = numOfFaces;
		  int CurrentSize = numOfVerts;
		  glBindBuffer(GL_ARRAY_BUFFER, VBOid);
		  glEnableVertexAttribArray(0);
		  glEnableVertexAttribArray(1);
		  glEnableVertexAttribArray(2);
		  glEnableVertexAttribArray(3);
		  //glEnableVertexAttribArray(4);


		  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); 
		  glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(GLfloat)*3));
		  glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(GLfloat)*6));
		  glVertexAttribPointer (3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(GLfloat)*8));
		 // glVertexAttribPointer (4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(GLfloat)*11));


		  

		  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Indexid);
		  glDrawElements(GL_TRIANGLES, CurrentSize1*3, GL_UNSIGNED_INT, NULL);

		  glDisableVertexAttribArray(0);
		  glDisableVertexAttribArray(1);
		  glDisableVertexAttribArray(2);
		  glDisableVertexAttribArray(3);
		 // glDisableVertexAttribArray(4);
};

void Mesh :: RenderCheapMesh(){

		  int CurrentSize1 = numOfFaces;
		 
		  glBindBuffer(GL_ARRAY_BUFFER, VBOid);

		  glEnableVertexAttribArray(0);
		  glEnableVertexAttribArray(1);
		  //glEnableVertexAttribArray(2);
		  //glEnableVertexAttribArray(3);
		  //glEnableVertexAttribArray(4);


		  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); 
		  glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)(sizeof(GLfloat)*3));
		  //glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof(XVertex), (float*)(sizeof(GLfloat)*6));
		  //glVertexAttribPointer (3, 4, GL_FLOAT, GL_TRUE , sizeof(XVertex), (float*)(sizeof(GLfloat)*8));
		  //glVertexAttribPointer (4, 4, GL_INT,   GL_FALSE, sizeof(XVertex), (float*)(sizeof(GLfloat)*12));

		  

		  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Indexid);
		  glDrawElements(GL_TRIANGLES, CurrentSize1*3, GL_UNSIGNED_INT, NULL);

		  glDisableVertexAttribArray(0);
		  glDisableVertexAttribArray(1);
		  //glDisableVertexAttribArray(2);
		  //glDisableVertexAttribArray(3);
		  //glDisableVertexAttribArray(4);
};