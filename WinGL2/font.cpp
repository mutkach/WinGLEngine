#include "font.h"

Font :: Font(char* filename){


	FT_Init_FreeType(&ft);
	FT_New_Face(ft, filename, 0, &face);
	FT_Set_Pixel_Sizes(face, 0, 13);
	
	FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL );
	atlasSizeW = 0;
	atlasSizeH = 0;

	g = face->glyph; 
	for(int i = 32; i < 128; i++) {
		if(FT_Load_Char(face, i, FT_LOAD_RENDER)) 
			continue;
 
		atlasSizeW += g->bitmap.width;
		atlasSizeH = max(atlasSizeH, g->bitmap.rows);
 
	}

	

	glGenBuffers(1, &quadVertexBuffer);
	glGenBuffers(1, &quadUVBuffer);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &atlasTexture);
	glBindTexture(GL_TEXTURE_2D, atlasTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, atlasSizeW, atlasSizeH, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	FillAtlas();


}

void Font :: FillAtlas(){
	int x = 0;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, atlasTexture);
 
	for(int i = 32; i < 128; i++) {
		if(FT_Load_Char(face, i, FT_LOAD_RENDER))
			continue;


		glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

		chars[i].advanceX = g->advance.x >> 6;
		chars[i].advanceY = g->advance.y >> 6;
 
		chars[i].bitmapW = g->bitmap.width;
		chars[i].bitmapH = g->bitmap.rows;
 
		chars[i].bitmapL = g->bitmap_left;
		chars[i].bitmapT = g->bitmap_top;
	  
		chars[i].textureOffsetX = (float) x / (float) atlasSizeW;
		x += g->bitmap.width;
	}


}

void Font :: RenderText(char* text, float x, float y, float sx, float sy){

	unsigned int length = strlen(text);

	// Fill buffers
	std::vector<vec2> vertices;
	std::vector<vec2> UVs;


	int n = 0;
 
	  for(const char *p = text; *p; p++) { 
		  float x2 =  x + chars[*p].bitmapL * sx;
		  float y2 =  -y - chars[*p].bitmapT * sy;
		  float w = chars[*p].bitmapW * sx;
		  float h = chars[*p].bitmapH * sy;
 
		  /* Advance the cursor to the start of the next character */
		  x += chars[*p].advanceX * sx;
		  y += chars[*p].advanceY * sy;
 
		  /* Skip glyphs that have no pixels */
		  if(!w || !h)
		    continue;

		    vec2 vertex_up_left    = vec2( x2    , -y2 );
			vec2 vertex_up_right   = vec2( x2 + w, -y2 );
			vec2 vertex_down_right = vec2( x2 + w, -y2 - h);
			vec2 vertex_down_left  = vec2( x2    , -y2 - h);
		    //vec2 vertex_up_left    = vec2( -1, 1 );
			//vec2 vertex_up_right   = vec2( 1, 1 );
			//vec2 vertex_down_right = vec2( 1, -1);
			//vec2 vertex_down_left  = vec2( -1, -1);

			vertices.push_back(vertex_up_left   );
			vertices.push_back(vertex_down_left );
			vertices.push_back(vertex_up_right  );

			vertices.push_back(vertex_down_right);
			vertices.push_back(vertex_up_right  );
			vertices.push_back(vertex_down_left );

			float uv_x = chars[*p].textureOffsetX;
			float uv_w = chars[*p].bitmapW/(float)atlasSizeW;
			float uv_y = chars[*p].bitmapH/(float)atlasSizeH;

			vec2 uv_up_left    = vec2( uv_x       , 0 );
			vec2 uv_up_right   = vec2( uv_x + uv_w, 0 );
			vec2 uv_down_right = vec2( uv_x + uv_w, uv_y );
			vec2 uv_down_left  = vec2( uv_x       , uv_y );

			//vec2 uv_up_left    = vec2( 0, 1 );
			//vec2 uv_up_right   = vec2( 1, 1 );
			//vec2 uv_down_right = vec2( 1, 0 );
			//vec2 uv_down_left  = vec2( 0, 0 );

			UVs.push_back(uv_up_left   );
			UVs.push_back(uv_down_left );
			UVs.push_back(uv_up_right  );

			UVs.push_back(uv_down_right);
			UVs.push_back(uv_up_right);
			UVs.push_back(uv_down_left);

	 }


	glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), &vertices[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, quadUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(vec2), &UVs[0], GL_DYNAMIC_DRAW);


	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
	glBindTexture(GL_TEXTURE_2D, atlasTexture);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, quadUVBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw call
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

	glDisable(GL_BLEND);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


}


void Font :: RenderSequence(){
	std :: string currentText;

	for(int i = 0; i < sequence.size(); ++i){
	
		currentText = sequence[i];
		RenderText(&currentText[0], -0.95, 0.9 - i*0.05, 2.0/g_rRect.right, 2.0/g_rRect.bottom); 	
	}
	sequence.resize(0);

}


void Font :: PushSequence(std :: string text){
	if(sequence.size() > 10){
		sequence.pop_back();
		sequence.push_front( text );
	}
	else{
		sequence.push_front( text );
	}

}

void Font::CombinePushSequence(std::string text, double number){
	
	char buffer[128];
	sprintf(buffer, &text[0], number );
	text = buffer; 
	PushSequence(text);

}

void Font::CombinePushSequence(std::string text, double number1, double number2){
	
	char buffer[128];
	sprintf(buffer, &text[0], number1, number2);
	text = buffer; 
	PushSequence(text);

}

void Font::CombinePushSequence(std::string text, double number1, double number2, double number3){
	
	char buffer[128];
	sprintf_s(buffer, &text[0], number1, number2, number3 );
	text = buffer; 
	PushSequence(text);

}

void Font::CombinePushSequence(std::string text, int number){
	
	char buffer[128];
	sprintf_s(buffer, &text[0], number );
	text = buffer; 
	PushSequence(text);

}