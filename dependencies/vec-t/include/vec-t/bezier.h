#ifndef UTILS_BEZIER_H
#define UTILS_BEZIER_H

#include "shape.h"
#include <vector>
#include <array>


void calculate_winding_numbers_quadratic_beziers(shape* _shape);

void calculate_winding_numbers_linear_beziers(shape* _shape);

unsigned int divide_quadratic_beziers(shape* _shape);

std::vector<bezier_t> break_cubic_in_quadratics(point a, point b, point c, point d);

void calculate_normals(shape* _shape);

#endif