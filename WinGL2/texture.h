#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "IL/il.h"
#include "IL/ilu.h"

#include <gl/glew.h>



class Texture
{
public:
    GLubyte *imageData;     
    GLuint  bpp;   
    GLuint width,height;   
    GLuint texID;    
	unsigned int type;

	Texture(char *filename);

	void SetFiltering(bool hasMipmap, GLenum minification, GLenum magnification);
    void FreeTexture();
};

 
#endif