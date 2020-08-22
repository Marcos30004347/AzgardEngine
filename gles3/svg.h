#ifndef GLES3_SVG_H
#define GLES3_SVG_H

#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>
#include "glm/glm.hpp"

#include "camera.h"

#include "shape.h"

class SVG {
	private:
	std::vector<Shape*> shapes;
	// bezier data dont have indices yet.	

	public:
	SVG(const char* path);
	void draw(GLES3_Camera* camera, glm::mat4 model, std::vector<std::vector<glm::vec2>> positions_packs, std::vector<std::vector<glm::vec2>> scales_packs);
};

#endif