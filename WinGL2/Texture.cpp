#include "texture.h"
 
 
Texture::Texture(char *filename)
{
    ilLoadImage(filename);
 
    //нет ли ошибок при открытии файла
    int err=ilGetError();
	while ((err = ilGetError()) != IL_NO_ERROR) { 
		const char* strError =  filename;
		//MessageBox(NULL, strError, "Missing texture", MB_OK);
        //exit(1);
	} 
	
	
        

    width = ilGetInteger(IL_IMAGE_WIDTH);          // Ширина
    height = ilGetInteger(IL_IMAGE_HEIGHT);        // Высота
    bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);      // Байт на пиксель
 
    imageData = ilGetData();
 
    ilEnable(IL_CONV_PAL);


    type = ilGetInteger(IL_IMAGE_FORMAT);
 

    glGenTextures(1, &texID);

   
    glBindTexture(GL_TEXTURE_2D,texID);


    //gluBuild2DMipmaps(GL_TEXTURE_2D, texture->bpp, texture->width,texture->height, type, GL_UNSIGNED_BYTE, texture->imageData);
	//glTexImage2D(GL_TEXTURE_2D, 0, texture->bpp, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->imageData);
	//gluBuild2DMipmaps( GL_TEXTURE_2D, texture->bpp, texture->width, texture->height, texture->type, GL_UNSIGNED_BYTE,  (const GLvoid *)texture->imageData );
	glTexImage2D(GL_TEXTURE_2D, 0, bpp, width, height, 0, type, GL_UNSIGNED_BYTE, (const GLvoid *)imageData);
    // Устанавливаем качество текстур
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
}
 
void Texture::SetFiltering(bool hasMipmap, GLenum minification, GLenum magnification){
	glBindTexture(GL_TEXTURE_2D, texID);
	if(hasMipmap)
		gluBuild2DMipmaps(GL_TEXTURE_2D, bpp, width, height, type, GL_UNSIGNED_BYTE,  (const GLvoid *)imageData );
	else
		glTexImage2D(GL_TEXTURE_2D, 0, bpp, width, height, 0, type, GL_UNSIGNED_BYTE, (const GLvoid *)imageData);
	
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minification);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnification );
}

void Texture::FreeTexture()
{
	glDeleteTextures(1, &texID);
}