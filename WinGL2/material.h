#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "texture.h"

class Texture;

struct Material{
	Texture*  textureDiffuse;
	Texture*  textureAmbient;
	Texture*  textureSpecular;
	Texture*  textureNormal;
	bool isSkinned;
	bool isShadowed;
};

#endif