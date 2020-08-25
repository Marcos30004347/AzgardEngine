#ifndef GLES3_SHAPE_H
#define GLES3_SHAPE_H

#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>
#include "glm/glm.hpp"

#include "camera.h"
#include "shader.h"

#include "vec-t/triangulation.h"

class Shape {
	private:

	unsigned int num_beziers;
	unsigned int num_triangles;

	unsigned int stroke_num_beziers;
	unsigned int stroke_num_triangles;


	GLES3_Shader* base_path_sh;
	GLES3_Shader* base_curve_sh;
	GLES3_Shader* stroke_path_sh;
	GLES3_Shader* stroke_curve_sh;

	GLuint base_vao;
	GLuint bezier_vao;

	GLuint stroke_base_vao;
	GLuint stroke_bezier_vao;
	// bezier data dont have indices yet.	

	public:
	Shape(shape_triangulation_data* triangulation_data);
	void draw(GLES3_Camera* camera, glm::mat4 model, std::vector<std::vector<glm::vec2>> positions_packs, std::vector<std::vector<glm::vec2>> scales_packs);
};

#endif