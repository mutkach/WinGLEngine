//#pragma once
#include "main.h"
#define map_size 1024

class errain{
	
	GLuint VertexVBID;
	GLuint IndexVBID;
	float x; float z;
	float min_height, max_height;
	float a[map_size][map_size];
    Vertex data[map_size*map_size];
	std :: vector<int> fc;
	//public:
	void Generate(float posx, float posz, int seed);
	void Create(float posx, float posz);
	void Draw();
	void Calculate_Normals();
	errain();
	~errain();
};