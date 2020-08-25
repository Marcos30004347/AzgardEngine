#include"font.h"

Font::Font(const char* filename) {
	FT_Library ft_library;
	FT_Outline  outline;
	FT_Face ft_face;

	if (FT_Init_FreeType( &ft_library )) { 
		printf("error loading font\n");
	}


	if( FT_New_Face(ft_library, filename, 0, &ft_face) )
		printf("Error: loading Font Face from %s\n", filename);


	this->ft_library = ft_library;
	this->ft_face = ft_face;
	this->num_glyphs =  ft_face->num_glyphs;

	this->glyphs = std::map<unsigned int, Glyph*>();


	// FT_UInt charcode;
	// FT_ULong character = FT_Get_First_Char(this->ft_face, &charcode);

	// this->glyphs.insert({FT_Get_Char_Index(this->ft_face, 's'), new Glyph(this->ft_face, 's')});
	// for(int i=0; i<this->num_glyphs; i++) {
	// 	this->glyphs.insert({i, new Glyph(this->ft_face, i)});

	// }
	printf ("num glyphs: %lu\n", ft_face->num_glyphs);
	// for (FT_UInt glyph_index=0; glyph_index<=ft_face->num_glyphs; glyph_index++)
	// {
	// 	/* 0 = .notdef */
	// 	this->glyphs.insert({glyph_index, new Glyph(this->ft_face, glyph_index)});
	// 	printf ("%u\n", glyph_index);
	// }






	// for(int i=0; i<this->ft_face->num_charmaps, i++) {
		
	// }
	// do {
	// 	printf("charcode: %u\n", charcode);
	// 	if(charcode == 1301) throw 20;
	// 	this->glyphs[charcode] = new Glyph(this->ft_face, character);
	// 	character = FT_Get_Next_Char(this->ft_face, character, &charcode);
	// } while(charcode);


	printf("charmaps: %u\n", ft_face->num_charmaps);
	// for(auto i = this->glyphs.begin();  i != this->glyphs.end(); i++) {
	// 	printf("KKKKKKKKKKKKK %u\n", i->first);
	// 	// i->second->draw(camera, model, {{ pos }}, {{1.f}});
	// }

	// for(int i='A'; i<='A'; i++) {
	// }
}