#include "vec-t/glyph.h"
#include "vec-t/triangulation.h"
#include "vec-t/shape.h"
#include "vec-t/bezier.h"

// #include <freetype/ftoutln.h>

#include <vector>
#include <array>

int cubicTo(const FT_Vector*  control1, const FT_Vector*  control2, const FT_Vector*  to, shape* user) {
	unsigned int current_outline_index = user->paths.size() - 1;
	point _to = point(((to->x)/user->w), ((to->y)/user->h));
	point _control0 = point(((control1->x)/user->w), ((control1->y)/user->h));
	point _control1 = point(((control2->x)/user->w), ((control2->y)/user->h));

	std::vector<bezier_t> bezs = break_cubic_in_quadratics(user->paths[current_outline_index]._last, _control0, _control1, _to);
	for(bezier_t bez: bezs) {
		user->paths[current_outline_index].beziers.push_back(bez);
	}
	user->paths[current_outline_index]._last = _to;

	return 0;
}

int moveTo(const FT_Vector* to, shape* user) {

	point _to = point(((to->x)/user->w), ((to->y)/user->h));

	user->paths.push_back(path());
	user->paths[user->paths.size() - 1]._last = _to;

	return 0;
}

int lineTo(const FT_Vector* to, shape* user) {

	unsigned int current_outline_index = user->paths.size() - 1;

	point lastPoint = user->paths[current_outline_index]._last;

	point _to = point(((to->x)/user->w), ((to->y)/user->h));
	user->paths[current_outline_index].beziers.push_back(bezier_t(lastPoint, _to));
	user->paths[current_outline_index]._last = _to;

	return 0;
}

int conicTo(const FT_Vector* control,const FT_Vector* to, shape* user) {

	unsigned int current_outline_index = user->paths.size() - 1;

	point lastPoint = user->paths[current_outline_index]._last;

	point _to(((to->x)/user->w), ((to->y)/user->h));
	point _control(((control->x)/user->w), ((control->y)/user->h));
	
	// user->paths[current_outline_index].beziers.push_back(bezier_t(lastPoint, _to));
	user->paths[current_outline_index].beziers.push_back(bezier_t(lastPoint, _control , _to));
	user->paths[current_outline_index]._last = _to;

	return 0;
}


shape_triangulation_data parse_glyph(FT_Face face, FT_UInt glyph_id) {
	// printf("Triangulating %i\n", glyph_id);

 	FT_Set_Char_Size (face, 1*64, 1*64, 0, 0);
	// FT_Set_Pixel_Sizes(face, 1, 1);
	FT_Error err;
	err = FT_Load_Glyph(face, glyph_id, FT_LOAD_NO_SCALE );
	if(err) {
		printf("cant load char, err: %i\n", err);
	}
	shape _shape = shape();

	_shape.h = face->units_per_EM;
	_shape.w = face->units_per_EM;
	_shape.advance_x = face->glyph->advance.x;
	_shape.advance_y = face->glyph->advance.y;

	FT_Outline_Funcs funcs;
	funcs.move_to = (FT_Outline_MoveToFunc)&moveTo;
	funcs.line_to = (FT_Outline_LineTo_Func)&lineTo;
	funcs.cubic_to = (FT_Outline_CubicTo_Func)&cubicTo;
	funcs.conic_to = (FT_Outline_ConicTo_Func)&conicTo;
	funcs.shift = 0;
	funcs.delta = 0;


	FT_Outline outline = face->glyph->outline;
	// printf("Decomposing Glyph Outline\n");
	FT_Error error = FT_Outline_Decompose(&outline, &funcs, &_shape);

	if (error) printf("Couldn't extract the outline: FT_Outline_Decompose() failed\n");

	// // Not in use
	// FT_Orientation orientation = FT_Outline_Get_Orientation(&face->glyph->outline);

	if(!face->glyph->outline.n_contours) return shape_triangulation_data();

	// printf("Calculating path directions\n");
	calculate_path_directions(&_shape);

	// printf("Dividing quadratic beziers\n");
	
	while(divide_quadratic_beziers(&_shape));
	calculate_path_directions(&_shape);

	// printf("Calculating winding numbers of quadratic beziers\n");
    calculate_winding_numbers_quadratic_beziers(&_shape);

	// printf("Calculating winding numbers of linear beziers\n");
	calculate_winding_numbers_linear_beziers(&_shape);


	// for(path p : _shape.paths) {
	// 	for(bezier_t b : p.beziers) {
	// 		printf("bez====\n");
	// 		printf("(%f, %f)\n", b.off0.x, b.off0.y);
	// 		if(b.is_quadratic) { 
	// 			printf("(%f, %f)\n", b.control.x, b.control.y);
	// 			printf("winding=%i\n", b.control.winding_number);
	// 		}
	// 		printf("(%f, %f)\n", b.off1.x, b.off1.y);
	// 	}
	// }

	// printf("Building path vertices\n");
	std::vector<float> vao_paths = build_paths_vertices(_shape);

	// printf("Building curves vertices\n");
	std::vector<float> vao_beziers = build_curves_vertices(_shape);

	shape_triangulation_data triangulation_data = shape_triangulation_data();

	triangulation_data.path_vertex_array_data = vao_paths;
	triangulation_data.curves_vertex_array_data = vao_beziers;

	if(false) {
		printf("Path VAO\n");

		for(int i=0; i<triangulation_data.path_vertex_array_data.size()/6; i++) {
			printf("(%f, %f)\n", 
				triangulation_data.path_vertex_array_data[(i*6) + 0],
				triangulation_data.path_vertex_array_data[(i*6) + 1]
			);
		}

		// printf("Path VAO\n");

		// for(int i=0; i<triangulation_data.curves_vertex_array_data.size()/6; i++) {
		// 	printf("(%f, %f)\n", 
		// 		triangulation_data.curves_vertex_array_data[(i*6) + 0],
		// 		triangulation_data.curves_vertex_array_data[(i*6) + 1]
		// 	);
		// }
	}

	triangulation_data.advance_x = 0;
	triangulation_data.advance_y = 0;
	triangulation_data.hori_bearing_x = 0;
	triangulation_data.hori_bearing_y = 0;
	triangulation_data.vert_bearing_x = 0;
	triangulation_data.vert_bearing_y = 0;

	if(!triangulation_data.path_vertex_array_data.size()) {
		return triangulation_data;
	}

	triangulation_data.boundings.p0 = point(
		triangulation_data.path_vertex_array_data[0],
		triangulation_data.path_vertex_array_data[1]
	);

	triangulation_data.boundings.p1 = point(
		triangulation_data.path_vertex_array_data[0],
		triangulation_data.path_vertex_array_data[1]
	);

	for(int i=0; i<triangulation_data.path_vertex_array_data.size()/6; i++) {
			point p = point(
				triangulation_data.path_vertex_array_data[(i*6) + 0],
				triangulation_data.path_vertex_array_data[(i*6) + 1]
			);


			
			triangulation_data.boundings.p0 = point(
				std::min(triangulation_data.boundings.p0.x, p.x),
				std::min(triangulation_data.boundings.p0.y, p.y)
			);

			triangulation_data.boundings.p1 = point(
				std::max(triangulation_data.boundings.p1.x, p.x),
				std::max(triangulation_data.boundings.p1.y, p.y)
			);
	}
	
	triangulation_data.advance_x = triangulation_data.boundings.p1.x;
	triangulation_data.advance_y = triangulation_data.boundings.p0.x;
	triangulation_data.hori_bearing_x = face->glyph->metrics.horiBearingX/64.f;
	triangulation_data.hori_bearing_y = face->glyph->metrics.horiBearingY/64.f;
	triangulation_data.vert_bearing_x = face->glyph->metrics.vertBearingX/64.f;
	triangulation_data.vert_bearing_y = face->glyph->metrics.vertBearingY/64.f;

	FT_Size_RequestRec req = { FT_SIZE_REQUEST_TYPE_BBOX , 0 , 3450 , 0 , 0 };
	FT_Request_Size( face , &req );

	// printf("(%f, %f)\n",  face->glyph->metrics.horiBearingX/64.f, face->glyph->metrics.horiBearingY/64.f);
	// printf("(%f, %f)\n",  face->glyph->metrics.vertBearingX/64.f, face->glyph->metrics.vertBearingY/64.f);
	// printf("(%f, %f)\n",  face->glyph->metrics.horiAdvance/64.f, face->glyph->metrics.vertAdvance/64.f);

	//same
	// printf("(%f, %f)\n",  triangulation_data.boundings.p0.x, triangulation_data.boundings.p1.x);
	// printf("(%f, %f)\n",  req.width, req.height);
	// printf("(%f, %f)\n",  req.horiResolution, req.vertResolution);

	// if(glyph_id == 1301) throw 20;

	return triangulation_data;
}



shape_triangulation_data parse_glyph(const char* font_file, FT_UInt glyph_id) {
	FT_Library ft_library;
	FT_Outline  outline;
	FT_Face ft_face;

	if (FT_Init_FreeType( &ft_library )) { 
		printf("error loading font\n");
	}


	if( FT_New_Face(ft_library, font_file, 0, &ft_face) )
		printf("Error: loading Font Face from %s\n", font_file);


	return parse_glyph(ft_face, glyph_id);
}