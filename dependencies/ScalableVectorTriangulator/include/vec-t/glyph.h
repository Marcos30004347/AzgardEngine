#ifndef UTILS_GLYPH_H
#define UTILS_GLYPH_H


#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftoutln.h>
#include "triangulation.h"

shape_triangulation_data parse_glyph(FT_Face face, FT_UInt glyph_id);

shape_triangulation_data parse_glyph(const char* font_file, FT_UInt glyph_id);


#endif