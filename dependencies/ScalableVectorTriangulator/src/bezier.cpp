#include "vec-t/bezier.h"
#include "stdio.h"

void calculate_winding_numbers_quadratic_beziers(shape* _shape) {

	for(int outline0_index=0; outline0_index<_shape->paths.size(); outline0_index++) {
		for(int seg_index=0; seg_index<_shape->paths[outline0_index].beziers.size(); seg_index++ ) {
			_shape->paths[outline0_index].beziers[seg_index].control.winding_number = 0;
		}
	}

	for(int outline0_index=0; outline0_index<_shape->paths.size(); outline0_index++) {
		for(int bezier=0; bezier<_shape->paths[outline0_index].beziers.size(); bezier++ ) {
		if(!_shape->paths[outline0_index].beziers[bezier].is_quadratic) continue;
	
			for(int outline1_index=0; outline1_index<_shape->paths.size(); outline1_index++) {
				for(int seg_index=0; seg_index<_shape->paths[outline1_index].beziers.size(); seg_index++ ) {

					bezier_t bezier_points = _shape->paths[outline0_index].beziers[bezier];
					point caster = point((bezier_points.off0.x + bezier_points.control.x + bezier_points.off1.x)/3.0f, (bezier_points.off0.y + bezier_points.control.y + bezier_points.off1.y)/3.0f);

					point linea = _shape->paths[outline1_index].beziers[seg_index].off0;
					point lineb = _shape->paths[outline1_index].beziers[seg_index].off1;
			
					line_intercection_params interception_params = line_intercept_params(caster, point(1000.0f, caster.y), linea, lineb);

					if(interception_params.t > 0.0f && interception_params.t<=1.0f && interception_params.u<1.0f && interception_params.u >= 0.0f) {
						_shape->paths[outline0_index].beziers[bezier].control.winding_number++;
					}
				}
			}

		}
	}
}

bool is_point_inside_triangle(point P, point A, point B, point C) {
	float w1 = (A.x*(C.y-A.y) + (P.y - A.y)*(C.x - A.x) - P.x*(C.y-A.y));
	w1 /= 		((B.y-A.y)*(C.x - A.x) - (B.x-A.x)*(C.y-A.y));

	float w2 = P.y - A.y - w1*(B.y-A.y);
	w2 /= C.y - A.y;
	
	return (w1 >= 0 && w2 >= 0 && (w1+w2) <= 1);
}

void calculate_winding_numbers_linear_beziers(shape* _shape) {

	for(int outline0_index=0; outline0_index<_shape->paths.size(); outline0_index++) {
		for(int outline1_index=0; outline1_index<_shape->paths.size(); outline1_index++) {

			for(int seg0_index=0; seg0_index<_shape->paths[outline0_index].beziers.size(); seg0_index++ ) {
				for(int seg1_index=0; seg1_index<_shape->paths[outline1_index].beziers.size(); seg1_index++ ) {

					point caster = _shape->paths[outline0_index].beziers[seg0_index].off0;
					point linea = _shape->paths[outline1_index].beziers[seg1_index].off0;
					point lineb = _shape->paths[outline1_index].beziers[seg1_index].off1;
			
					if(caster.x == linea.x && caster.y == linea.y) continue;
					if(caster.x == lineb.x && caster.y == lineb.y) continue;

					line_intercection_params interception_params = line_intercept_params(caster, point(1000.0f, caster.y), linea, lineb);

					if(interception_params.t > 0.0f && interception_params.t<=1.0f && interception_params.u<=1.0f && interception_params.u >= 0.0f) {
						_shape->paths[outline0_index].beziers[seg0_index].off0.winding_number++;
					}

				}
			}

		}
	}
}



std::vector<bezier_t> split_quadratic_bezier(bezier_t bez) {
	if(!bez.is_quadratic) {
		return {
			bez,
		};
	}

	point off0 = bez.off0;
	point control = bez.control;
	point off1 = bez.off1;

	point sideA;
	sideA.x = off0.x + control.x;
	sideA.x = sideA.x/2.f;

	sideA.y = off0.y + control.y;
	sideA.y = sideA.y/2.f;

	point sideB;
	sideB.x = off1.x + control.x;
	sideB.x = sideB.x/2.f;

	sideB.y = off1.y + control.y;
	sideB.y = sideB.y/2.f;

	point midle;
	midle.x = sideA.x + sideB.x;
	midle.x = midle.x/2.f;

	midle.y = sideA.y + sideB.y;
	midle.y = midle.y/2.f;

	std::vector<bezier_t> bezs;

	if(triangle_area(off0, sideA, midle) > 0.000001f) {
		bezs.push_back(bezier_t(off0, sideA, midle));
	}

	if(triangle_area(midle, sideB, off1) > 0.000001f) {
		bezs.push_back(bezier_t(midle, sideB, off1));
	}

	return bezs;
}


// unsigned int _divide_quadratic_beziers(shape* _shape) {
// 	unsigned int ammount = 0;
// 	std::vector<std::vector<quadratic_bezier>> quadratics;
// 	std::vector<std::vector<linear_bezier>> linears;
// 	for(int path=0; path< _shape->paths.size(); path++) {
// 		std::vector<std::vector<linear_bezier>> fonte_linears = _shape->paths[path].linear_bezier_curves;
// 		std::vector<std::vector<quadratic_bezier>> fonte_quadratics = _shape->paths[path].quadratic_bezier_curves;
// 		for(linear_bezier l: fonte_linears) {
// 			bezier_point_coordinates coord = find_quadratic_bezier(_shape->paths[path].linear_bezier_curves[linear_bez][0], *_shape, 0);

// 		}
// 	}

// }

// float triangle_area(point A, point B, point C) {
// 	return (A.x*(B.y - C.y) + B.x*(C.y-A.y) + C.x*(A.y - B.y))/2.f;
// }


unsigned int divide_quadratic_beziers(shape* _shape) {
	unsigned int ammount = 0;
	std::vector<std::vector<bezier_t>> beizers;

	for(int path=0; path< _shape->paths.size(); path++) {

		std::vector<bezier_t> linear_bezier_curves;

		for(int linear_bez=0; linear_bez < _shape->paths[path].beziers.size(); linear_bez++) {
			
			// bezier_point_coordinates coord = find_quadratic_bezier(_shape->paths[path].linear_bezier_curves[linear_bez][0], *_shape, 0);
	
			if(_shape->paths[path].beziers[linear_bez].is_quadratic) { // point found.
				bool was_divided = false;


	
				for(int bezi_path = 0; bezi_path<_shape->paths.size() && !was_divided; bezi_path++) {
					for(int bezier=0; bezier < _shape->paths[bezi_path].beziers.size()  && !was_divided; bezier++) {

						point A =_shape->paths[path].beziers[linear_bez].off0;
						point B =_shape->paths[path].beziers[linear_bez].control;
						point C =_shape->paths[path].beziers[linear_bez].off1;

						
						point E = _shape->paths[bezi_path].beziers[bezier].off0;
						point P = _shape->paths[bezi_path].beziers[bezier].control;
						point F = _shape->paths[bezi_path].beziers[bezier].off1;

						if(bezier == linear_bez && path == bezi_path) continue;


						if(
							is_point_inside_triangle(P, A, B, C)
							|| is_point_inside_triangle(B, E, P, F)
						) {
							if(triangle_area(A,B,C) >= triangle_area(E,P,F)) {
								ammount++;
								std::vector<bezier_t> beziers = split_quadratic_bezier(_shape->paths[path].beziers[linear_bez]);

								was_divided = true;

								for(bezier_t bez : beziers) {
									linear_bezier_curves.push_back(bez);
								}
							}
						} 
					}
				}



	
				if(!was_divided) {
					linear_bezier_curves.push_back(_shape->paths[path].beziers[linear_bez]);
				}

			} else {
				linear_bezier_curves.push_back(_shape->paths[path].beziers[linear_bez]);
			}
		}



		beizers.push_back(linear_bezier_curves);

		// printf("divided quadratic size: %li\n", quadratic_bezier_curves.size());
		// printf("divided linear size: %li\n", linear_bezier_curves.size());
	}

	for(int i=0; i< beizers.size(); i++) {
		_shape->paths[i].beziers = beizers[i];
	}

	// printf("divided %u beziers!\n", ammount);

	return ammount;
}







std::vector<bezier_t> break_cubic_in_quadratics(point a, point b, point c, point d) {
	std::vector<bezier_t> beziers;
	point p1 = (b+c)/2.f;
	point p2 = (a+b)/2.f;
	point p3 = (c+d)/2.f;

	point m0 = (p1+p2)/2.f;
	point m1 = (p1+p3)/2.f;

	point m = (m0+m1)/2.f;



	
	line_intercection_params params0 = line_intercept_params(m, m0, a, b);
	line_intercection_params params1 = line_intercept_params(m, m1, d, c);


	if((params0.t == -1.f || params1.t == -1.f) 
	|| ((params0.u >= 1.f || params0.u <= 0.f))
	|| ((params1.u >= 1.f || params1.u <= 0.f))
	) {
		// printf("returning A\n");
		// printf("%f %f\n", params0.t, params0.u);
		// printf("%f %f\n", params1.t, params1.u);

		beziers.push_back(bezier_t( a, p2, m ));
		beziers.push_back(bezier_t( m, p3, d ));

		//point_line_projection(m, d, c);	
		return beziers;

	}
	point A = m0 - m;
	A = A*params0.t;
	A = A + m;
	point B = m0 - m;
	B = B * -1.f*params1.t;
	B = B + m;

	// printf("returning B\n");
	// printf("%f %f\n", params0.t, params0.u);
	// printf("%f %f\n", params1.t, params1.u);
	if(a == A) {
		if(a == m) {
			throw 20;
		}
		A = (a+m)*0.5f;
	}
	if(m == A) {
		if(a == m) {
			throw 20;
		}
		A = (a+m)*0.5f;
	}

	if(m == B) {
		if(d == m) {
			throw 20;
		}
		B = (d+m)*0.5f;
	}
	if(d == A) {
		if(d == m) {
			throw 20;
		}
		B = (d+m)*0.5f;
	}

	beziers.push_back(bezier_t( a, A, m ));
	beziers.push_back(bezier_t( m, B, d ));

	//point_line_projection(m, d, c);	
	return beziers;
}

