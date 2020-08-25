#ifndef NODES_CORE_SQUARE_H
#define NODES_CORE_SQUARE_H

#include "desc.h"

math_shape_desc_t* get_box_desc(float width, float height) {
    shape_triangulation_data d = {};

    d.advance_x = 0.1f;
    d.advance_y = 0.0f;

    d.hori_bearing_x = 0.0f;
    d.hori_bearing_y = 0.0f;
    d.vert_bearing_x = 0.0f;
    d.vert_bearing_y = 0.0f;

    d.curves_vertex_array_data = std::vector<float>();
    d.path_vertex_array_data = std::vector<float>();
    d.stroke_curves_vertex_array_data = std::vector<float>();
    d.stroke_path_vertex_array_data = std::vector<float>();

    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);

    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(1.0f);

    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(height);
    d.path_vertex_array_data.push_back(0.0f);

    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(1.0f);

    d.path_vertex_array_data.push_back(width);
    d.path_vertex_array_data.push_back(height);
    d.path_vertex_array_data.push_back(0.0f);

    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(1.0f);

    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);

    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(1.0f);

    d.path_vertex_array_data.push_back(width);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);

    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(1.0f);


    d.path_vertex_array_data.push_back(width);
    d.path_vertex_array_data.push_back(height);
    d.path_vertex_array_data.push_back(0.0f);

    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(0.0f);
    d.path_vertex_array_data.push_back(1.0f);

    d.boundings = {};

    d.boundings.p0 = point(0,0);
    d.boundings.p1 = point(width,height);

    math_shape_desc_t* over_bar_desc = init_shape_desc();
    math_shape_params_t* over_bar = init_shape_param();

    // hb_codepoint_t gid; 
    // hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);
    // //u221a
    // std::string s("0000");
    // int num = std::stoi(s, 0, 16);
    // hb_font_get_nominal_glyph(harf_font, num, &gid);

    over_bar->custom_shapes = new Shape(&d);
    over_bar->n_custom_shapes = 1;
    over_bar->p0_x = 0.0f;
    over_bar->p1_x = width;
    over_bar->p1_y = height;
    over_bar->p0_y = 0.0f;
    over_bar->advance_y = 0.0f;
    over_bar->advance_x = 0.1f;
    over_bar->x = 0.0f;
    over_bar->y = 0.0f;
    over_bar->stretch_x = 1.0f;
    over_bar->stretch_y = 1.0f;

    over_bar->codepoint = 1;

    add_param_to_desc(over_bar_desc, over_bar);
    // over_bar_desc->first_param = over_bar;
    // over_bar_desc->last_param = over_bar;

    over_bar_desc->n_params = 1;
    over_bar_desc->advance_x = 0.1f;
    over_bar_desc->advance_y = 0.0f;
    over_bar_desc->x = 0.0f;
    over_bar_desc->y = 0.0f;
    over_bar_desc->p0_x = over_bar->p0_x;
    over_bar_desc->p1_x = over_bar->p1_x;
    over_bar_desc->p0_y = over_bar->p0_y;
    over_bar_desc->p1_y = over_bar->p1_y;
    over_bar_desc->height = height;
    over_bar_desc->width = width;
    over_bar_desc->operations = 0;
    return over_bar_desc;
}

#endif