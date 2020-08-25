#ifndef GLES3_GLYPH_H
#define GLES3_GLYPH_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftoutln.h>

#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>
#include "glm/glm.hpp"

#include "camera.h"
#include "shader.h"

struct bounding_box_t {
	glm::vec2 p0;
	glm::vec2 p1;
};

class Glyph {
	private:
	unsigned long _glyph;


	unsigned int num_indices;
	unsigned int num_beziers;
	unsigned int num_triangles;

	GLES3_Shader* program0;
	GLES3_Shader* program1;

	GLuint base_vao;
	GLuint base_ibo;
	GLuint bezier_vao;

	float advance_x;
	float advance_y;
	float hori_bearing_x;
	float hori_bearing_y;
	float vert_bearing_x;
	float vert_bearing_y;

	bounding_box_t bounding_box;

	public:
	Glyph(FT_Face face, FT_UInt glyph_id);
	void draw(GLES3_Camera* camera, glm::mat4 model, std::vector<std::vector<glm::vec2>> positions_packs, std::vector<std::vector<glm::vec2>> scales_packs);


	inline unsigned long get_glyph_id() { return this->_glyph; }

	// inline float get_advance_x() { return this->bounding_box.p1.x; }
	// inline float get_advance_y() { return this->bounding_box.p1.y - this->bounding_box.p0.y; }

	// inline float get_hori_bearing_x() { return this->hori_bearing_x; }
	// inline float get_hori_bearing_y() { return this->hori_bearing_y; }
	// inline float get_vert_bearing_x() { return this->vert_bearing_x; }
	// inline float get_vert_bearing_y() { return this->vert_bearing_y; }
	inline float get_height() { return this->bounding_box.p1.y - this->bounding_box.p0.y; }
	inline float get_width() { return this->bounding_box.p1.x - this->bounding_box.p0.x; }

	inline bounding_box_t get_bounding_box() { return this->bounding_box; }
};

#endif