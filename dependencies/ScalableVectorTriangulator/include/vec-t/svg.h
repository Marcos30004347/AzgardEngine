#ifndef UTILS_SVG_H
#define UTILS_SVG_H

#include "triangulation.h"

std::vector<shape_triangulation_data> parse_svg(const char* svg_path);

#endif