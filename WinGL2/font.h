#ifndef FONT_H
#define FONT_H


#include "utility.h"
#include "math.h"

#include <gl/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

extern RECT  g_rRect;

using namespace glm;


struct Glyph{
  
  float advanceX; // advance.x
  float advanceY; // advance.y
 
  float bitmapW; // bitmap.width;
  float bitmapH; // bitmap.rows;
 
  float bitmapL; // bitmap_left;
  float bitmapT; // bitmap_top;
 
  float textureOffsetX; // x offset of glyph in texture coordinates
};

class Font{
public:
	

	
	
	Font(char* filename);
	~Font();

	void PushSequence(std :: string);
	void RenderSequence();
	void CombinePushSequence(std:: string text, double number);
	void CombinePushSequence(std:: string text, double number1, double number2);
	void CombinePushSequence(std:: string text, double number1, double number2, double number3);

	void CombinePushSequence(std:: string text, int number);
private:
	
	FT_Library ft;
	FT_Face face;
	FT_GlyphSlot g;
	Glyph chars[128];
	

	GLuint atlasTexture;
	GLuint quadVertexBuffer;
	GLuint quadUVBuffer;
	GLint atlasSizeW;
	GLint atlasSizeH;

	std::deque<std :: string> sequence;
	void FillAtlas();
	void RenderText(char* text, float x, float y, float sx, float sy);
};

#endif