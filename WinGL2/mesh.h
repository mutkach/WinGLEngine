#ifndef MESH_H
#define MESH_H

#include <gl/glew.h>
#include <vector>
#include "vertex.h"

class Mesh{
public:
	GLuint VBOid;
	GLuint Indexid;
    int  numOfVerts;            
    int  numOfFaces;            
	int	 baseVertex;
    int  materialID;      
    std :: vector<Vertex>  pVerts;         
    std :: vector<CFace> pFaces;  
	void RenderMesh();
	void RenderStaticMesh();
	void RenderCheapMesh();
};

class SkinnedMesh{
public:
	GLuint VBOid;
	GLuint Indexid;
    int  numOfVerts;           
    int  numOfFaces;          
    int  numTexVertex;        
	int	 baseVertex;
    int  materialID;            
    std :: vector<XVertex>  pVerts;         
    std :: vector<CFace> pFaces;             
	void RenderMesh();
	void RenderCheapMesh();
};


#endif