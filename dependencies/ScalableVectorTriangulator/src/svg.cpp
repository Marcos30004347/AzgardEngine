#include "vec-t/svg.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#define NANOSVG_IMPLEMENTATION	// Expands implementation
#include "nanosvg.h"

#include "vec-t/bezier.h"
#include "vec-t/shape.h"
#include "vec-t/stroke.h"
#include "vec-t/color.h"
#include "math.h"


bool validate_shape(shape* _shape) {
    bool _t = false;
    for(int p=0; p<_shape->paths.size(); p++) {
        std::vector<bezier_t> linears;
        for(int i=0; i<_shape->paths[p].beziers.size(); i++) {
            int t = _shape->paths[p].beziers.size();
            int prev = i ==0 ? t-1: i-1;
            int next = i ==t-1 ? 0: i+1;
            bezier_t A = _shape->paths[p].beziers[prev];
            bezier_t B = _shape->paths[p].beziers[i];
            bezier_t C = _shape->paths[p].beziers[next];


            if(do_line_intercept(A.off0, A.off1, C.off0, C.off1)) {
                _t = true;

                // bezier_point_coordinates coord0 = find_quadratic_bezier(A[0], _shape->paths[p], 0);
                // bezier_point_coordinates coord1 = find_quadratic_bezier(C[0], _shape->paths[p], 0);

                // if(_shape->paths[p].beziers[prev].is_quadratic) {
                //     linears.push_back(bezier_t(
                //        _shape->paths[p].beziers[prev].off0,
                //        _shape->paths[p].beziers[prev].off1,
                //         (C.off0 + A.off0)*0.5f
                //     ));
                // }


                // if(_shape->paths[p].beziers[next].is_quadratic) {
                //     linears.push_back({
                //         (C.off0 + A.off0)*0.5f,
                //         _shape->paths[p].beziers[next].off1,
                //         _shape->paths[p].beziers[next].control
                //     });
                // }

                linears.push_back(bezier_t(
                    A.off0,
                    B.off1
                ));

                if(i!= t-1) {
                    linears.push_back(bezier_t(
                        B.off1,
                        C.off1
                    ));
                }
    
                i++;
            } else
            {
                linears.push_back(B);
                // bezier_point_coordinates coord0 = find_quadratic_bezier(B[0], _shape->paths[p], 0);
                // if(coord0.bezier != -1) {
                //     quadratics.push_back({
                //         _shape->paths[p].quadratic_bezier_curves[coord0.bezier][0],
                //         _shape->paths[p].quadratic_bezier_curves[coord0.bezier][1],
                //         _shape->paths[p].quadratic_bezier_curves[coord0.bezier][2]
                //     });
                // }
            }
            
        }
        _shape->paths[p].beziers = linears;
        // _shape->paths[p].quadratic_bezier_curves = quadratics;
    }
    return _t;
}




shape_triangulation_data triangulate_svg_shape(shape* _shape) {
    shape_triangulation_data triangulation_data = shape_triangulation_data();

    printf("Parsing shape ...\n");
    printf("Calculating winding numbers of quadratic beziers\n");
    printf("Dividing quadratic beziers of %lu paths\n", _shape->paths.size());


    while(divide_quadratic_beziers(_shape));

    // for(path p : _shape->paths) {
    //     printf("path\n");
    //     for(linear_bezier l: p.linear_bezier_curves) {
    //         printf("(%f, %f)\n", l[0].x, l[0].y);
    //         printf("(%f, %f)\n", l[1].x, l[1].y);
    //         // printf("(%f, %f)\n", l[2].x, l[2].y);
    //     }
    //     printf("quadratics of path\n");

    //     for(quadratic_bezier l: p.quadratic_bezier_curves) {
    //         printf("(%f, %f)\n", l[0].x, l[0].y);
    //         printf("(%f, %f)\n", l[1].x, l[1].y);
    //         printf("(%f, %f)\n", l[2].x, l[2].y);
    //     }
    // }

    calculate_winding_numbers_quadratic_beziers(_shape);
    printf("Calculating winding numbers of linear beziers\n");
    calculate_winding_numbers_linear_beziers(_shape);
    printf("Calculating path directions\n");
    calculate_path_directions(_shape);

    printf("Calculating normal of points\n");
    calculate_normals(_shape);

    printf("Stroke width=%f\n", _shape->stroke_width);


    // stroke disable for now.
    if(false && _shape->stroke_width) {
        // build stroke
        printf("Creating Strokes...\n");
        // TODO: Set attributes like color and others.
        std::vector<float> vao_paths;
        std::vector<float> vao_curves;
        printf("Generating Paths:\n");
        for(int p=0; p<_shape->paths.size(); p++) {
            std::vector<path> paths = build_stroke_path(_shape->paths[p], _shape->stroke_width, JOIN_BEVEL);
            printf("stroke paths: %li\n", paths.size());
            for(path stroke_segment: paths) {
                shape _stroke_shape = shape();

                _stroke_shape.fill = true;

                _stroke_shape.paths = { stroke_segment };

                printf("Dividing quadratic beziers of stroke\n");
                while(divide_quadratic_beziers(&_stroke_shape));
                printf("Calculating winding numbers of quadratic beziers of stroke\n");
                calculate_winding_numbers_quadratic_beziers(&_stroke_shape);
                printf("Calculating winding numbers of linear beziers of stroke\n");
                calculate_winding_numbers_linear_beziers(&_stroke_shape);

                printf("Calculating path directions of stroke=%i\n", p);
                calculate_path_directions(&_stroke_shape);

                std::vector<float> stroke_vao_beziers = build_curves_vertices(_stroke_shape);

                std::vector<float> stroke_vao_paths = build_paths_vertices(_stroke_shape);
                std::vector<float> vao_path_with_colors;
                std::vector<float> vao_curves_with_colors;

                for(int i=0; i<stroke_vao_paths.size()/6; i++) {
                    std::array<float,4> color = calculate_color(stroke_vao_paths[i*6+0], stroke_vao_paths[i*6+1], *_shape);
                    for(int j=0; j<6; j++) vao_path_with_colors.push_back(stroke_vao_paths[(i*6)+j]);
                    for(int j=0; j<4; j++) vao_path_with_colors.push_back(color[j]);
                }

                for(int i=0; i<stroke_vao_beziers.size()/6; i++) {
                    std::array<float,4> color = calculate_color(stroke_vao_beziers[i*6+0], stroke_vao_beziers[i*6+1], *_shape);
                    for(int j=0; j<6; j++) vao_curves_with_colors.push_back(stroke_vao_beziers[(i*6)+j]);
                    for(int j=0; j<4; j++) vao_curves_with_colors.push_back(color[j]);
                }

                for(float v: vao_curves_with_colors) {
                    vao_curves.push_back(v);
                }
                for(float v: vao_path_with_colors) {
                    vao_paths.push_back(v);
                }
            }

        }


        triangulation_data.stroke_curves_vertex_array_data = vao_curves;
        triangulation_data.stroke_path_vertex_array_data = vao_paths;

        printf("Done!\n");
    }


    if(_shape->fill) {
        printf("Building path vertices\n");

        // printf("=================================== \n");
        // printf("=================================== \n");
        // printf("=================================== \n");
        // printf("=================================== \n");
        // printf("=================================== \n");
        // printf("=================================== \n");
        // printf("=================================== \n");
        // printf("=================================== \n");

        // for(int i=0; i<_shape->paths.size(); i++) {
        //     _shape->paths[i].quadratic_bezier_curves = std::vector<quadratic_bezier>();
        // }
        std::vector<float> vao_paths = build_paths_vertices(*_shape);
    
        printf("Building curves vertices\n");
        std::vector<float> vao_beziers = build_curves_vertices(*_shape);
    
        std::vector<float> vao_path_with_colors;
        std::vector<float> vao_curves_with_colors;

        for(int i=0; i<vao_paths.size()/6; i++) {
            std::array<float,4> color = calculate_color(vao_paths[i*6+0], vao_paths[i*6+1], *_shape);
            for(int j=0; j<6; j++) vao_path_with_colors.push_back(vao_paths[(i*6)+j]);
            for(int j=0; j<4; j++) vao_path_with_colors.push_back(color[j]);
        }

        for(int i=0; i<vao_beziers.size()/6; i++) {
            std::array<float,4> color = calculate_color(vao_beziers[i*6+0], vao_beziers[i*6+1], *_shape);
            for(int j=0; j<6; j++) vao_curves_with_colors.push_back(vao_beziers[(i*6)+j]);
            for(int j=0; j<4; j++) vao_curves_with_colors.push_back(color[j]);
        }
        triangulation_data.path_vertex_array_data = vao_path_with_colors;
        triangulation_data.curves_vertex_array_data = vao_curves_with_colors;

    }
    printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    // printf("\n");
    return triangulation_data;

}



std::vector<shape_triangulation_data> parse_svg(const char* svg_path) {
    printf("PARSING SVG...\n");

    struct NSVGimage* image;
    image = nsvgParseFromFile(svg_path, "px", 96);

    printf("size: %f x %f\n", image->width, image->height);

    std::vector<shape*> shapes;
    std::vector<shape_triangulation_data> triangulation_datas;

    for (NSVGshape *nvgshape = image->shapes; nvgshape != NULL; nvgshape = nvgshape->next) {
        printf("adding shape...\n");

        shape* path_data = new shape();

        printf("stroke width: %f\n", nvgshape->strokeWidth);

        bool redefine_first_point = true;
        path_data->stroke_width = nvgshape->strokeWidth;

        switch (nvgshape->strokeLineCap)
        {
            case NSVG_CAP_BUTT:
                path_data->_stroke_linecap = CAP_BUTT;
                break;
            case NSVG_CAP_ROUND:
                path_data->_stroke_linecap = CAP_ROUND;
                break;
            case NSVG_CAP_SQUARE:
                path_data->_stroke_linecap = CAP_SQUARE;
                break;
            default:
                break;
        }


        switch (nvgshape->strokeLineJoin)
        {
            case NSVG_JOIN_MITER:
                path_data->_stroke_linejoin = JOIN_MITER;
                break;
            case NSVG_JOIN_ROUND:
                path_data->_stroke_linejoin = JOIN_ROUND;
                break;
            case NSVG_JOIN_BEVEL:
                path_data->_stroke_linejoin = JOIN_BEVEL;
                break;
            default:
                break;
        }

        path_data->color = parse_nsvg_color(nvgshape->fill.color);
        switch (nvgshape->fill.type)
        {
            case NSVG_PAINT_COLOR:
                path_data->fill_type = COLOR;
                path_data->fill = true;
                break;
            case NSVG_PAINT_LINEAR_GRADIENT:
                path_data->fill_type = GRADIENT_LINEAR;
                path_data->fill = true;
                path_data->form = nvgshape->fill.gradient->xform;
                path_data->spread = nvgshape->fill.gradient->spread;
                for(auto s : nvgshape->fill.gradient->stops) path_data->stops.push_back(gradient_stop(parse_nsvg_color(s.color), s.offset));

                break;
            case NSVG_PAINT_RADIAL_GRADIENT:
                path_data->fx = nvgshape->fill.gradient->fx;
                path_data->fy = nvgshape->fill.gradient->fy;
                path_data->form = nvgshape->fill.gradient->xform;
                path_data->spread = nvgshape->fill.gradient->spread;
                for(auto s : nvgshape->fill.gradient->stops) path_data->stops.push_back(gradient_stop(parse_nsvg_color(s.color), s.offset));
                path_data->fill_type = GRADIENT_RADIAL;
                path_data->fill = true;
                break;
            case NSVG_PAINT_NONE:
                path_data->fill_type = NONE;
                path_data->fill = false;
                break;
            default:
                path_data->fill_type = COLOR;
                path_data->fill = true;
                break;
        }


        for (NSVGpath * svg_path = nvgshape->paths; svg_path != NULL; svg_path = svg_path->next) {
            point first_point(-10000.f, -10000.f);
            point last_point_current_bezier(-10000.f, -10000.f);

            for (int i = 0; i < svg_path->npts-1; i += 3) {
                float* p = &svg_path->pts[i*2];

                if((first_point.x == -10000.f && first_point.y == -10000.f )|| redefine_first_point) {
                    redefine_first_point = false;
                    first_point = point(p[0],p[1]);


                    path_data->paths.push_back(path());

                    if(!svg_path->closed) {
                        path_data->paths[path_data->paths.size() - 1].closed = false;
                    } else {
                        path_data->paths[path_data->paths.size() - 1].closed = true;
                    }

                }
                last_point_current_bezier = point(p[6],p[7]);

                // printf("nanovg points\n");
                // printf("(%f, %f)\n", p[0], p[1]);
                // printf("(%f, %f)\n", p[2], p[3]);
                // printf("(%f, %f)\n", p[4], p[5]);
                // printf("(%f, %f)\n", p[6], p[7]);
                // if(false && lenght(point(p[0], p[1]) - point(p[6], p[7])) < 0.0001f) {
                //     path_data->paths[path_data->paths.size() - 1].linear_bezier_curves.push_back({
                //         point(p[6], p[7]),
                //         point(p[0], p[1])
                //     });
                // }else {
                printf("breaking cubic...\n");
                if(lenght(point(p[0],p[1]) - point(p[6],p[7])) < 0.001f ) {
                    path_data->paths[path_data->paths.size() - 1].beziers.push_back(bezier_t(
                        point(p[0],p[1]),
                        point(p[6],p[7])
                    ));
                } else {
                    std::vector<bezier_t> beziers = break_cubic_in_quadratics(
                        point(p[0],p[1]),
                        point(p[2],p[3]),
                        point(p[4],p[5]),
                        point(p[6],p[7])
                    );
                
                    for(bezier_t b : beziers) {
                        // printf("resulting bez\n");
                        // printf("(%f, %f)\n", b[0].x, b[0].y);
                        // printf("(%f, %f)\n", b[1].x, b[1].y);
                        // printf("(%f, %f)\n", b[2].x, b[2].y);
                        // path_data->paths[path_data->paths.size() - 1].beziers.push_back({
                        //     b,
                        // });
                        if(triangle_area(b.off0, b.control, b.off1) > 0.000001f) {
                            path_data->paths[path_data->paths.size() - 1].beziers.push_back(b);
                        } else {
                            path_data->paths[path_data->paths.size() - 1].beziers.push_back(bezier_t(b.off0, b.off1));
                        }
                    }

                }


                
                if(last_point_current_bezier == first_point) {
                    redefine_first_point = true;
                    printf("end of outline %lu!\n", path_data->paths.size() - 1);

                    break;
                }
            }
        }

        shapes.push_back(path_data);
        // while(validate_shape(path_data));
        validate_shape(path_data);
        
        triangulation_datas.push_back(triangulate_svg_shape(path_data));
        printf("shape added!\n");
    }


    nsvgDelete(image);
    return triangulation_datas;

}

