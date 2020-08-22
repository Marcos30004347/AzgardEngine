#ifndef UTILS_TRIANGULATION_H
#define UTILS_TRIANGULATION_H

#include <vector>

#include "shape.h"
#include "bezier.h"

struct bounding_box {
	point p0;
	point p1;
};

struct shape_triangulation_data {
	std::vector<float> path_vertex_array_data;
	std::vector<float> curves_vertex_array_data;

	std::vector<float> stroke_path_vertex_array_data;
	std::vector<float> stroke_curves_vertex_array_data;
	
	bounding_box boundings;

	float advance_y;
	float advance_x;
	float hori_bearing_y;
	float hori_bearing_x;
	float vert_bearing_y;
	float vert_bearing_x;

	shape_triangulation_data(std::vector<float> _vertex_array_data) {
		path_vertex_array_data = _vertex_array_data;
	}

	shape_triangulation_data() {
		path_vertex_array_data = std::vector<float>();
		curves_vertex_array_data = std::vector<float>();
	}
};


std::vector<float> build_paths_vertices(
	shape &shape
);
std::vector<float> build_curves_vertices(
	shape _shape
);


#endif