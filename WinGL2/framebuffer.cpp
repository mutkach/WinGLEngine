#include "framebuffer.h"

Framebuffer :: Framebuffer(GLint _width, GLint _height, unsigned int _numOfColorAttachments, GLenum _format, unsigned int _numOfDepthAttachments){
	width = _width;
	height = _height;
	numOfColorAttachments = _numOfColorAttachments;
	numOfDepthAttachments = _numOfDepthAttachments;

	format = _format;
	textures = NULL;
	colorAttachments = NULL;
}



Framebuffer :: ~Framebuffer(){	
	if(numOfDepthAttachments)
		glDeleteTextures(numOfColorAttachments + 1, textures);
	else
		glDeleteTextures(numOfColorAttachments, textures);

	glDeleteFramebuffers(1, &handle);

}

void Framebuffer ::Init(){

	glGenFramebuffers(1, &handle);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, handle);
		if(numOfDepthAttachments){

			textures = new GLuint [numOfColorAttachments + 1];
			glGenTextures(numOfColorAttachments + 1, textures);

		}
		else{

			textures = new GLuint [numOfColorAttachments];
			glGenTextures(numOfColorAttachments, textures);

		}

		if(numOfColorAttachments)
			colorAttachments = new GLenum [numOfColorAttachments];

		int i = 0;
		while(i < numOfColorAttachments){

			colorAttachments[i] = GL_COLOR_ATTACHMENT0 + i;
			glBindTexture(GL_TEXTURE_2D, textures[i]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,  GL_RGB, GL_FLOAT, NULL);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i], 0);
			++i;
		}

		if(numOfDepthAttachments > 1){

			glBindTexture(GL_TEXTURE_2D_ARRAY, textures[numOfColorAttachments]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
			glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT24, width, height, numOfDepthAttachments, 0,  GL_DEPTH_COMPONENT, GL_INT, NULL);
			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				//glFramebufferTexture3D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textures[numOfColorAttachments], 0);

		}
		else if(numOfDepthAttachments > 0){

			glBindTexture(GL_TEXTURE_2D, textures[numOfColorAttachments]);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0,  GL_DEPTH_COMPONENT, GL_INT, NULL); 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textures[numOfColorAttachments], 0);
		}

		

	GLenum Status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

     if (Status != GL_FRAMEBUFFER_COMPLETE) {
         //printf("FB error, status: 0x%x\n", Status);
		 MessageBox(NULL, "shit fuck", "Buffer crapped", MB_OK);
     }

	 glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

}

void Framebuffer::Bind(){
	glViewport(0,0, width, height);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, handle);

}

void Framebuffer ::Unbind(){

	glViewport(0,0, 640, 480);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

}

void Framebuffer :: BindAttachments(GLint size, GLenum* attachments){
	glViewport(0,0, width, height);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, handle);
	glDrawBuffers(size, attachments);

}

void Framebuffer :: BindAttachment(GLenum attachment){
	glViewport(0,0, width, height);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, handle);
	glDrawBuffer(attachment);

}

void Framebuffer :: BindDepthAttachment(GLenum attachment){
	glViewport(0,0, width, height);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, handle);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textures[numOfColorAttachments], 0, attachment);

}

void Framebuffer::Clear(GLbitfield clearMask){
	glClear(clearMask);
}

//GBuffer :: GBuffer() : Framebuffer( g_rRect.right, g_rRect.bottom, 2, GL_RGBA8, 1){
//
//}
/*
ShadowBuffer :: ShadowBuffer(GLuint _width, GLuint _height, GLenum _format){
	width = _width;
	height = _height;
	format = _format;
	textureArray = NULL;
	colorTexture = NULL;
}

void ShadowBuffer :: Init(){

	glGenFramebuffers(1, &handle);
	glBindFramebuffer(GL_FRAMEBUFFER, handle);

	glGenTextures(1, &colorTexture);
	glGenTextures(1, &textureArray);

	glBindTexture(GL_TEXTURE_2D, colorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

	glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT24, width, height, MAX_SPLITS,  0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

     if (Status != GL_FRAMEBUFFER_COMPLETE) {
         printf("FB error, status: 0x%x\n", Status);
     }

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void ShadowBuffer :: Bind(){
	glViewport(0,0, width, height);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, handle);
	glDrawBuffer(GL_NONE);
}

void ShadowBuffer :: BindAttachment(GLuint level){
	glViewport(0,0, width, height);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, handle);
	glFramebufferTextureLayer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureArray, 0, level);

}

void ShadowBuffer :: Clear(){


}
*/