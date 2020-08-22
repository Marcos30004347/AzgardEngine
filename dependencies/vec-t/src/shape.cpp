#include "vec-t/shape.h"
#include "stdio.h"

void calculate_path_directions(shape* _shape) {
	for(int path=0; path<_shape->paths.size(); path++) {
		float _sum = 0.0f;
		for(int segment=0; segment < _shape->paths[path].beziers.size(); segment++) {
			point b = _shape->paths[path].beziers[segment].off0;
			point c = _shape->paths[path].beziers[segment].off1;
			
			_sum += b.x * c.y - c.x * b.y;
			// _sum += (c.x - b.x)*((b.y+c.y)/2.0f);
		}
		_shape->paths[path].orientation = _sum > 0 ? 1 : -1;
	}
}

// bezier_point_coordinates find_quadratic_bezier(point current, shape _shape, unsigned int point_index) {
// 	for(int c=0; c<_shape.paths.size(); c++) {
// 		for(int b=0; b<_shape.paths[c].beziers.size(); b++) {
// 			point off0 = _shape.paths[c].beziers[b].off0;

// 			if(current.x == off0.x && current.y == off0.y) return bezier_point_coordinates(c,b,point_index);
// 		}
// 	}

// 	return bezier_point_coordinates(-1,-1,-1);
// }


// bezier_point_coordinates find_quadratic_bezier(point current, path path, unsigned int point_index) {
// 	for(int b=0; b< path.quadratic_bezier_curves.size(); b++) {
// 		point off0 =  path.quadratic_bezier_curves[b][point_index];

// 		if(current.x == off0.x && current.y == off0.y) return bezier_point_coordinates(-1, b, point_index);
// 	}

// 	return bezier_point_coordinates(-1,-1,-1);
// }

line_intercection_params line_intercept_params(point p1, point p2, point p3, point p4) {
	float denominator = ((p1.x - p2.x)*(p3.y - p4.y)) - ((p1.y - p2.y)*(p3.x - p4.x));
	
	if(denominator == 0.0f) {
		return line_intercection_params(-1.0f,-1.0f);
	} 

	float t = (((p1.x - p3.x)*(p3.y - p4.y)) - ((p1.y-p3.y)*(p3.x - p4.x)))/denominator;
	float u = -1.0f * (((p1.x - p2.x)*(p1.y - p3.y)) - ((p1.y-p2.y)*(p1.x - p3.x)))/denominator;

	return line_intercection_params(t,u);
}

int do_line_intercept(point p1, point p2, point p3, point p4) {
	line_intercection_params interception_params = line_intercept_params(p1, p2, p3, p4);


	if(interception_params.t >= 0.0f && interception_params.t<=1.0f && interception_params.u<=1.0f && interception_params.u >= 0.0f) {
		return 1;
	}

	return 0;
}


float lenght(point v) {
	return sqrt(pow(v.x,2) + pow(v.y,2));
}

float dot(point a, point b) {
   
   return (a.x*b.x + b.y*a.y);
}

point vectors_projection(point v1,point v2 ) {
    float v2_ls = lenght(v2) * lenght(v2);
	float t = (dot( v2, v1 )/v2_ls );
	return point(v2.x*t, v2.y*t);

}

point point_line_projection(point v1, point v2, point v3) {
	point line = v3 - v2;
	point p = v1 - v2;
	point _p = vectors_projection(p, line);
	return _p + v2;
}

bool colinear(point p1, point p2, point p3) {
	float area = 0.5 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
	return (area == 0 ? true : false);
}

point normal(point p1, point p2, int orientation) {
	// printf("P1=(%f, %f)\n", p1.x, p1.y);
	// printf("P2=(%f, %f)\n", p2.x, p2.y);
	// printf("orientation=%i\n", orientation);

	point normal_point = point(p1.y-p2.y, p2.x - p1.x)*orientation;
	// printf("N=(%f, %f)\n", normal_point.x, normal_point.y);
	// printf("Lenght=%f\n", lenght(normal_point));
	point N = (normal_point/lenght(normal_point));

	return N + ((p1+p2)*0.5f);
}

point calculate_point_normal(point B0, point A, point B1, int orientation = 1) {
	point C = normal(B0, A, orientation);
	point D = normal(A, B1, orientation);

	point K = (C - ((A+B0)*0.5f)) + (D - ((A+B1)*0.5f));
	point T = K/(lenght(K));

	point J = T + A;
	return J;
}

void calculate_normals(shape* _shape) {
	for(int path=0; path<_shape->paths.size(); path++) {
		printf("calculating normals of path %i!\n", path);
		for(int segment=0; segment < _shape->paths[path].beziers.size(); segment++) {

			if(!_shape->paths[path].closed && (segment == 0 || segment == _shape->paths[path].beziers.size() - 1)) {
				point B0 = _shape->paths[path].beziers[segment].off0;
				point A0 = _shape->paths[path].beziers[segment].off1;

				point _normal = normal(B0, A0 , -1*_shape->paths[path].orientation);
				
				if(segment == 0) _shape->paths[path].beziers[segment].off0.normal = {_normal.x, _normal.y};
				else if(segment == _shape->paths[path].beziers.size() - 1) _shape->paths[path].beziers[segment].off1.normal = {_normal.x, _normal.y};

				continue;
			}

			int next_segment = (segment == _shape->paths[path].beziers.size() - 1 ? 0 : segment + 1);
	
			point B0 = _shape->paths[path].beziers[segment].off0;
			point A0 = _shape->paths[path].beziers[segment].off1;
			// A0 == A1
			point A1 = _shape->paths[path].beziers[next_segment].off0;
			point B1 = _shape->paths[path].beziers[next_segment].off1;

			point K = calculate_point_normal(B0, A0, B1, -1*_shape->paths[path].orientation);

			_shape->paths[path].beziers[segment].off1.normal = { K.x, K.y };
			_shape->paths[path].beziers[next_segment].off0.normal = { K.x, K.y };

			// bezier_point_coordinates coordsP0 = find_quadratic_bezier(A0, *_shape, 0);
			// bezier_point_coordinates coordsP1 = find_quadratic_bezier(A0, *_shape, 2);
	
			// if(_shape->paths[path].beziers[segment].is_quadratic) {
			// 	// bezier found
			// 	// _shape->paths[path].beziers[coordsP0.bezier][0].normal = { K.x, K.y };
			// }
			// if(coordsP1.path != -1) {
			// 	// bezier found
			// 	_shape->paths[path].quadratic_bezier_curves[coordsP1.bezier][2].normal = { K.x, K.y };
			// }
		}

		for(int bezier=0; bezier < _shape->paths[path].beziers.size() && _shape->paths[path].beziers[bezier].is_quadratic; bezier++) {

			point K = normal(
				_shape->paths[path].beziers[bezier].off0,
				_shape->paths[path].beziers[bezier].off1,
				-1*_shape->paths[path].orientation
			);
		
			K = K - (_shape->paths[path].beziers[bezier].off0 + _shape->paths[path].beziers[bezier].off1)*0.5f;
			K = K/(lenght(K));
			K = K + _shape->paths[path].beziers[bezier].off1;
			_shape->paths[path].beziers[bezier].control.normal = { K.x, K.y };
		}
	}
}

float triangle_area(point p1, point p2, point p3) {
	return abs((p1.x*(p2.y-p3.y) + p2.x*(p3.y - p1.y) + p3.x*(p1.y-p2.y))/2.f);
}