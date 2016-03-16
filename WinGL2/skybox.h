#ifndef _SKYBOX_H
#define _SKYBOX_H

#include "texture.h"
#include <gl/glew.h>


class Texture;

class Skybox{
public:

	Texture* images[6];
	GLuint textures[6];

	Skybox(char* textureFront,  char* textureBack,
		   char* textureLeft,   char* textureRight,
		   char* textureBottom, char* textureTop);
	
	
};

#endif