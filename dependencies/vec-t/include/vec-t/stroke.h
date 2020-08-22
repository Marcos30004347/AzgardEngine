#ifndef UTILS_STROKE_H
#define UTILS_STROKE_H

#include "shape.h"
#include <vector>

/**
 * Convert a path to a shape of a stroke.
 **/
std::vector<path> build_stroke_path(path contour, float width, stroke_linejoin join = JOIN_ROUND);

#endif