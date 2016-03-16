#ifndef __TERRAIN_H
#define __TERRAIN_H

#include "main.h"
#include <noise/noise.h>
#define map_size 256


using namespace noise;


class Terrain{
	public:
	GLuint VertexVBID;
	GLuint IndexVBID;
	GLuint textureID;
	float min_height, max_height;
	float x, z;
	Terrain(float posx, float posz, int seed, std :: string location);
	void Draw();
//private:
	void LoadTextures(std :: string location);
	void Generate(float posx, float posz, int seed);
	void Create(float posx, float posz);
	void CalculateNormals();
	Texture *textures;
	Mesh TerrainMesh;
	float heightmap[map_size][map_size];
	Vertex data[map_size*map_size];
	std :: vector<int> fc;
	
	
	//~Terrain();
};
#endif