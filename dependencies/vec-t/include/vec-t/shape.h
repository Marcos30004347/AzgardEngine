#ifndef UTILS_SHAPE_H
#define UTILS_SHAPE_H

#include <vector>
#include <array>
#include "math.h"


struct point{
	float x, y;
	int winding_number;

	std::array<float, 2> normal;
	std::array<float, 4> color;

	point(float _x, float _y ) {
		x = _x;
		y = _y;
		winding_number = 0;
		normal = {0.0f, 0.0f};
		color = {0.0f, 0.0f, 0.0f, 1.0f};
	}

	point() {
		x = 0; y = 0; winding_number = 0;
		normal = {0.0f, 0.0f};
		color = {0.0f, 0.0f, 0.0f, 1.0f};
	}

	point& operator =(const point& a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}

	point operator+(const point& a)
	{
		return point(a.x+x, a.y+y );
	}
	bool operator==(const point& a)
	{
		return (a.x == x && a.y == y);
		// return ((abs(a.x - x) <= 0.00001 ) && abs(a.y - y) <= 0.00001 );
	}
	bool operator!=(const point& a)
	{
		// 0.000001 >= a.x - x+ a.y - y &&  -0.000001 <= a.x - x+ a.y - y)=
		return (a.x != x || a.y != y);
		// return !(0.00000001 >= a.x - x + a.y - y &&  -0.00000001 <= a.x - x + a.y - y);
	}
	point operator-(const point& a)
	{
		return point( x-a.x, y-a.y);
	}
	point operator/(const float& a)
	{
		return point( x/a, y/a);
	}
	point operator*(const float& a)
	{
		return point( x*a, y*a);
	}
	bool operator > (const point& a)
	{
		return (sqrt(pow(x,2)+pow(y,2)) > sqrt(pow(a.x,2)+pow(a.y,2)));
	}
	bool operator >= (const point& a)
	{
		return (sqrt(pow(x,2)+pow(y,2)) >= sqrt(pow(a.x,2)+pow(a.y,2)));
	}
	bool operator < (const point& a)
	{
		return (sqrt(pow(x,2)+pow(y,2)) < sqrt(pow(a.x,2)+pow(a.y,2)));
	}
	bool operator <= (const point& a)
	{
		return (sqrt(pow(x,2)+pow(y,2)) <= sqrt(pow(a.x,2)+pow(a.y,2)));
	}

	bool operator > (const point& a) const
	{
		return (sqrt(pow(x,2)+pow(y,2)) > sqrt(pow(a.x,2)+pow(a.y,2)));
	}
	bool operator >= (const point& a) const
	{
		return (sqrt(pow(x,2)+pow(y,2)) >= sqrt(pow(a.x,2)+pow(a.y,2)));
	}
	bool operator < (const point& a) const
	{
		return (sqrt(pow(x,2)+pow(y,2)) < sqrt(pow(a.x,2)+pow(a.y,2)));
	}
	bool operator <= (const point& a) const
	{
		return (sqrt(pow(x,2)+pow(y,2)) <= sqrt(pow(a.x,2)+pow(a.y,2)));
	}
};

enum path_fill_type {
	NONE = 0,
	COLOR = 1,
	GRADIENT_LINEAR = 2,
	GRADIENT_RADIAL = 3,
};

enum stroke_linecap {
	CAP_BUTT = 0,
	CAP_ROUND = 1,
	CAP_SQUARE = 2,
};

enum stroke_linejoin {
	JOIN_MITER = 0,
	JOIN_ROUND = 1,
	JOIN_BEVEL = 2,
};



struct bezier_t {
	bool is_quadratic;
	point off0;
	point control;
	point off1;

	bezier_t(point _off0, point _off1) {
		off0 = _off0;
		off1 = _off1;
		control = (off0 + off1)*0.5f;
		is_quadratic = false;
	}

	bezier_t(point _off0, point _control ,point _off1) {
		off0 = _off0;
		control = _control;
		off1 = _off1;
		is_quadratic = true;
	}

	bezier_t(point _off0, point _control ,point _off1, bool _is_quadratic) {
		off0 = _off0;
		control = _control;
		off1 = _off1;
		is_quadratic = _is_quadratic;
	}
};

struct path {
	std::vector<bezier_t> beziers;

	int orientation;
    
	bool closed;

    // internal use
	point _last;

	path() {
		closed = true;
		beziers = std::vector<bezier_t>();
		orientation = 0;
	}
};

struct gradient_stop {
	std::array<float, 4> color;
	float offset;
	gradient_stop(std::array<float, 4> _color, float _offset) {
		color = _color;
		offset = _offset;
	}
};

struct shape
{
	float w,h;
	float advance_x, advance_y;

	std::vector<path> paths;

	float stroke_width;
	stroke_linecap _stroke_linecap;
	stroke_linejoin _stroke_linejoin;

	bool fill;
	path_fill_type fill_type;
	std::array<float, 4> color;
	float fx, fy;
	float* form;
	char spread;
	std::vector<gradient_stop> stops;

	shape() {
		w = 0.0f;
		h = 0.0f;
		advance_x = 0.0f;
		advance_y = 0.0f;
		paths = std::vector<path>();
	}
};


struct bezier_point_coordinates {
	int path;
	int bezier;
	int point;
	bezier_point_coordinates(int _outline_index, int _bezier_index, int _point_index) {
		path = _outline_index;
		bezier = _bezier_index;
		point = _point_index;
	}
};

struct line_intercection_params{
	float t,u;
	line_intercection_params(float _t, float _u) {
		t = _t;
		u = _u;
	}
};

line_intercection_params line_intercept_params(point p1, point p2, point p3, point p4);

int do_line_intercept(point p1, point p2, point p3, point p4);
float lenght(point v);
float dot(point a, point b);
point vectors_projection(point v1,point v2 );
point point_line_projection(point v1, point v2, point v3);
bool colinear(point p1, point p2, point p3);
point normal(point p1, point p2, int orientation = 1);
void calculate_normals(shape* _shape);
void calculate_path_directions(shape* _shape);
float triangle_area(point p1, point p2, point p3);
// bezier_point_coordinates find_quadratic_bezier(point current, shape _shape, unsigned int = 0);
// bezier_point_coordinates find_quadratic_bezier(point current, path path, unsigned int point_index);
#endif