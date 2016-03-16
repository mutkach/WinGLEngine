#include "skybox.h"


Skybox :: Skybox(char* textureFront,  char* textureBack,
		   char* textureLeft,   char* textureRight,
		   char* textureBottom, char* textureTop){
			   

			   images[0] = new Texture(textureFront);
			   images[1] = new Texture(textureBack);
			   images[2] = new Texture(textureLeft);
			   images[3] = new Texture(textureRight);
			   images[4] = new Texture(textureBottom);
			   images[5] = new Texture(textureTop);

			   for(int i = 0; i < 6; ++i)
				   textures[i] = images[i]->texID;

}