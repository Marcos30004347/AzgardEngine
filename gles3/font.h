#ifndef GLES3_FONT_H
#define GLES3_FONT_H

#include <vector>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "glyph.h"

class Font {
	private:
	FT_Library ft_library;
	FT_Face ft_face;

	unsigned int num_glyphs;
	std::map<FT_UInt, Glyph*> glyphs;


	public:
	Font(const char* filepath);

	inline unsigned int get_num_glyphs() { return this->num_glyphs; }

	inline FT_Library get_library() { return this->ft_library; }
	inline FT_Face get_face() { return this->ft_face; }

	inline Glyph* get_glyph(FT_UInt glyph) {
		if(!this->glyphs.count(glyph)) {
			this->glyphs[glyph] = new Glyph(this->ft_face, glyph);
		}
		return this->glyphs[glyph];
	}
	// inline std::map<unsigned int, Glyph*> get_glyphs() { return this->glyphs; }
};


#endif