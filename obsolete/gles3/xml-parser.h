#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <harfbuzz/hb.h>
#include <harfbuzz/hb-ot.h>
#include <harfbuzz/hb-ft.h>
#include FT_FREETYPE_H
#include "rapidxml.hpp"
#include <fstream>
#include "font.h"
#include "shape.h"
#include <string>
#include <locale>
#include <codecvt>
#include <cassert>


#define NULL_GLYPH UINT64_MAX


struct math_shape_params_t {
    uint32_t codepoint = 0;
    float stretch_x = 1.0f;
    float stretch_y = 1.0f;

    float advance_x = 0.0f;
    float advance_y = 0.0f;

    float p0_x = FLT_MAX;
    float p0_y = FLT_MAX;
    float p1_x = FLT_MIN;
    float p1_y = FLT_MIN;

    float x = 0.0f;
    float y = 0.0f;

    Shape* custom_shapes = nullptr;
    unsigned int n_custom_shapes = 0;
};


struct math_shape_desc_t {
    math_shape_params_t* params = nullptr;
    size_t n_params = 0;

    unsigned int operations = 0;
    float p0_x = 0.0f;
    float p0_y = 0.0f;
    float p1_x = 0.0f;
    float p1_y = 0.0f;
    float advance_x = 0.0f;
    float advance_y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    float x = 0.0f;
    float y = 0.0f;
};




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
    printf("malloc frac\n");

    math_shape_desc_t* over_bar_desc = (math_shape_desc_t*)malloc(sizeof(math_shape_desc_t));
    math_shape_params_t* over_bar = (math_shape_params_t*)malloc(sizeof(math_shape_params_t));

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

    over_bar_desc->params = over_bar;
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
void translate_math_shape_params(math_shape_desc_t* params, float x, float y) {
    if(!params) return;
    float max_x = FLT_MIN;
    float max_y = FLT_MIN;
    float min_x = FLT_MAX;
    float min_y = FLT_MAX;

    for(int i=0; i<params->n_params; i++) {
        params->params[i].x += x;
        params->params[i].y += y;

        params->params[i].p0_x += x;
        params->params[i].p0_y += y;

        params->params[i].p1_x += x;
        params->params[i].p1_y += y;

        min_y = std::min(min_y, params->params[i].p0_y);
        max_y = std::max(max_y, params->params[i].p1_y);

        min_x = std::min(min_x, params->params[i].p0_x);
        max_x = std::max(max_x, params->params[i].p1_x);
    }

    params->x += x;
    params->y += y;

    params->p1_x = max_x;
    params->p0_x = min_x;

    params->p1_y = max_y;
    params->p0_y = min_y;

    params->width = (params->p1_x - params->p0_x);
    params->height = params->p1_y - params->p0_y;
}

void stretch_math_shape_params(math_shape_desc_t* params, float x, float y) {
    if(!params) return;

    float previous_p1_x = 0;
    float previous_p1_y = 0;

    float max_y = FLT_MIN;
    float min_y = FLT_MAX;
    float max_x = FLT_MIN;
    float min_x = FLT_MAX;
    
    float center_x = (params->p0_x + params->p1_x)/2.f;
    float center_y = (params->p0_y + params->p1_y)/2.f;
    
    for(int i=0; i<params->n_params; i++) {
        float p_center_x = (params->params[i].p1_x + params->params[i].p0_x)/2.f;
        float p_center_y = (params->params[i].p1_y + params->params[i].p0_y)/2.f;

        float anchor_x = params->params[i].x;
        float anchor_y = params->params[i].y;
    

        previous_p1_x = params->params[i].p1_x;
        previous_p1_y = params->params[i].p1_y;
    
        float diff_y = (center_y - params->params[i].y) * (1-y);
        
        params->params[i].stretch_x *= x;
        params->params[i].stretch_y *= y;

        params->params[i].p0_x -= anchor_x;
        params->params[i].p0_x *= x;
        params->params[i].p0_x += anchor_x;

        params->params[i].p0_y -= anchor_y;
        params->params[i].p0_y *= y;
        params->params[i].p0_y += anchor_y + diff_y;

        params->params[i].p1_x -= anchor_x;
        params->params[i].p1_x *= x;
        params->params[i].p1_x += anchor_x;

        params->params[i].p1_y -= anchor_y;
        params->params[i].p1_y *= y;
        params->params[i].p1_y += anchor_y + diff_y;
        params->params[i].y += diff_y;

        params->advance_y *= y;
        params->advance_x *= x;

        float diff_x = p_center_x - (params->params[i].p1_x + params->params[i].p0_x)/2.f;
        params->params[i].x     += diff_x;
        params->params[i].p1_x  += diff_x;
        params->params[i].p0_x  += diff_x;

    }

    // int p = 0;
    for(int i=0; i<params->n_params; i++) {

        float diff_x = ((params->p1_x + params->p0_x)/2.f - (params->params[i].p1_x + params->params[i].p0_x)/2.f)*(1 - x);
        // float diff_y = ((params->p0_y)/2.f - (params->params[i].p1_y + params->params[i].p0_y)/2.f)*(1 - y);

        params->params[i].x     += diff_x;
        params->params[i].p1_x  += diff_x;
        params->params[i].p0_x  += diff_x;
        
        // params->params[i].y     += diff_y;
        // params->params[i].p1_y  += diff_y;
        // params->params[i].p0_y  += diff_y;
        min_y = std::min(min_y, params->params[i].p0_y);
        max_y = std::max(max_y, params->params[i].p1_y);

        min_x = std::min(min_x, params->params[i].p0_x);
        max_x = std::max(max_x, params->params[i].p1_x);
    
    }

    params->width = max_x - min_x;
    params->height = max_y - min_y;

    params->p1_x = max_x;
    params->p0_x = min_x;

    params->p1_y = max_y;
    params->p0_y = min_y;

    params->advance_x *= x;
    params->advance_y *= y;
}

math_shape_desc_t* get_math_shape_desc_stretchy(hb_codepoint_t glyph_index, hb_direction_t direction, float desired_size, Font* font, float extra_width = 0.0f) {

    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);

    Glyph* g = font->get_glyph(glyph_index);
    unsigned int variants = 30;
    hb_ot_math_glyph_variant_t variant[30];

    hb_ot_math_get_glyph_variants (
        harf_font,
        glyph_index,
        direction,
        0,
        &variants,
        variant
    );

    printf("glyph_index: %u\n", glyph_index);
    printf("variants: %u\n", variants);
    unsigned int parts = 30;
    hb_ot_math_glyph_part_t part[30];
    // hb_position_t italics_correction[30];

    hb_codepoint_t best = glyph_index;

    for(int i=0; i<variants; i++) {
        printf("glyph variant:%u\n", variant[i].glyph);
        printf("best variant:%u\n", best);
        printf("height: %f\n", font->get_glyph(variant[i].glyph)->get_height());
        if((std::abs(font->get_glyph(variant[i].glyph)->get_height() - desired_size) <= std::abs(font->get_glyph(best)->get_height() - desired_size))) {
            best = variant[i].glyph;
        }
        printf("kkkkkkkkkkkkkkkk\n");

        // hb_ot_math_get_glyph_assembly(harf_font, variant[i].glyph, HB_DIRECTION_TTB, 0,&parts, part, italics_correction);
        // printf("parts: %i\n", parts);
        // for(int j=0; j<parts; j++) {
        //     printf("glyph: %u\n", part[j].glyph);
        //     printf("end_connector_length: %u\n", part[j].end_connector_length);
        //     printf("start_connector_length: %u\n", part[j].start_connector_length);
        //     printf("full_advance: %u\n", part[j].full_advance);
        // }
    }

    printf("glyph_index: %u\n", best);
    printf("malloc shape stretchy\n");

    math_shape_desc_t* desc = (math_shape_desc_t*)malloc(sizeof(math_shape_desc_t));
    math_shape_params_t* param = (math_shape_params_t*)malloc(sizeof(math_shape_params_t));
    Glyph* gs = font->get_glyph(best);
    param->advance_x = 0.1f;
    param->advance_y = 0.1f;
    param->x = 0.0f;
    param->y = 0.0f;
    param->codepoint = best;
    param->stretch_x = 1.0f;
    param->stretch_y = 1.0f;
    param->p0_x = gs->get_bounding_box().p0.x;
    param->p0_y = gs->get_bounding_box().p0.y;
    param->p1_x = gs->get_bounding_box().p1.x;
    param->p1_y = gs->get_bounding_box().p1.y;
    param->n_custom_shapes = 0;
    param->custom_shapes = nullptr;

    desc->params = param;
    desc->n_params = 1;
    desc->p0_x = param->p0_x;
    desc->p0_y = param->p0_y;
    desc->p1_x = param->p1_x;
    desc->p1_y = param->p1_y; 
    desc->advance_x = 0.0f;
    desc->advance_y = 0.0f;
    desc->height = desc->p1_y - desc->p0_y;
    desc->width = desc->p1_x - desc->p0_x;
    desc->x = param->x;
    desc->y = param->y;
    desc->operations = 0;
    
    stretch_math_shape_params(
        desc,
        HB_DIRECTION_IS_HORIZONTAL(direction) ?  extra_width + desired_size/gs->get_width() : 1.0f,
        HB_DIRECTION_IS_HORIZONTAL(direction) ?  1.0f : extra_width + desired_size/gs->get_height()
    );
    printf("iUAHDIUSAHDIASID\n");
    return desc;
}

math_shape_desc_t* concat_math_shape_descs(math_shape_desc_t* a, math_shape_desc_t*b, float x = 0, float y = 0) {
    printf("malloc concat\n");

    math_shape_desc_t* result = (math_shape_desc_t*)malloc(sizeof(math_shape_desc_t));

    printf("<<<<<\n");

    math_shape_params_t* params = (math_shape_params_t*)malloc(sizeof(math_shape_params_t)* ((a? a->n_params : 0) + (b ? b->n_params : 0)));
    for(int i=0; i < (a ? a->n_params : 0); i++) {
        params[i] = a->params[i];
    }
    if(b) {
        translate_math_shape_params(b, x, y);
    }

    for(int i=0; i < (b ? b->n_params : 0); i++) {
        params[i+a->n_params] = b->params[i];
    }

    result->p0_x = std::min(a ? a->p0_x : FLT_MAX, b ? b->p0_x : FLT_MAX);
    result->p0_y = std::min(a ? a->p0_y : FLT_MAX, b ? b->p0_y : FLT_MAX);
    result->p1_x = std::max(a ? a->p1_x : FLT_MIN, b ? b->p1_x : FLT_MIN);
    result->p1_y = std::max(a ? a->p1_y : FLT_MIN, b ? b->p1_y : FLT_MIN);

    result->params = params;
    result->n_params = (a? a->n_params : 0) + (b? b->n_params : 0);
    result->advance_x = b->advance_x;
    result->advance_y = 0.0f;

    result->x = a->x;
    result->y = a->y;

    result->height = result->p1_y - result->p0_y;
    result->width = result->p1_x - result->p0_x;

    result->operations = a->operations + b->operations;
    printf("<<<<<\n");
    if(a) {
        if(a->params) free(a->params);
        free(a);
    }
    if(b) {
        if(b->params) free(b->params);
        free(b);
    }

    return result;
}

math_shape_desc_t* surround_shape_desc_horizontal(unsigned int left_codepoint, unsigned int right_codepoint, math_shape_desc_t* desc, Font* font, float extra_width = 0.4f) {
    math_shape_desc_t* ldesc = get_math_shape_desc_stretchy(left_codepoint, HB_DIRECTION_TTB, (desc->p1_y - desc->p0_y), font, extra_width);
    math_shape_desc_t* rdesc = get_math_shape_desc_stretchy(right_codepoint, HB_DIRECTION_TTB, (desc->p1_y - desc->p0_y), font, extra_width);

    math_shape_desc_t* tmp = concat_math_shape_descs(
        ldesc,
        desc,
        ldesc->p1_x - desc->p0_x,
        ldesc->y
        // (ldesc->p1_y + ldesc->p0_y)/2.f - (desc->p1_y + desc->p0_y)/2.f + extra_width/2.f
    );
    tmp = concat_math_shape_descs(
        tmp,
        rdesc,
        tmp->p1_x - rdesc->p0_x,
        tmp->y
        // (tmp->p1_y + tmp->p0_y)/2.f - (rdesc->p1_y + rdesc->p0_y)/2.f
    );
    return tmp;
}

math_shape_desc_t* parse_xml_node(const rapidxml::xml_node<> *node, Font* font);

math_shape_desc_t* parse_fraction_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr;

    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);

    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), nullptr);

    const rapidxml::xml_node<>* numerator_node = node->first_node();
    const rapidxml::xml_node<>* denominator_node = numerator_node->next_sibling();

    math_shape_desc_t* numerator_shaped_desc = parse_xml_node(numerator_node, font);
    math_shape_desc_t* denominator_shaped_desc = parse_xml_node(denominator_node, font);

    stretch_math_shape_params(
        numerator_shaped_desc,
        0.9f,
        0.9f
    );

    stretch_math_shape_params(
        denominator_shaped_desc,
        0.9f,
        0.9f
    );


    int num_size = numerator_shaped_desc->n_params;
    int den_size = denominator_shaped_desc->n_params;


    float far_midle_point = std::max((numerator_shaped_desc->p0_x + numerator_shaped_desc->p1_x)/2.f, (denominator_shaped_desc->p0_x + denominator_shaped_desc->p1_x)/2.f);
    float bigger_width = std::max(numerator_shaped_desc->width, denominator_shaped_desc->width);

    // float bigger_p0_x = denominator_shaped_desc->p0_x, bigger_p1_x = denominator_shaped_desc->p1_x;

    // if(numerator_shaped_desc->width > denominator_shaped_desc->width) {
    //     bigger_p0_x = numerator_shaped_desc->p0_x;
    //     bigger_p1_x = numerator_shaped_desc->p1_x;
    // }


    unsigned int num_bars = 1;//(unsigned int)std::ceil(far_midle_point/g->get_width());
    // math_shape_params_t* bars_shaped = (math_shape_params_t*)malloc(sizeof(math_shape_params_t));
    // bars_shaped->codepoint = glyph_index;
    float fraction_bar_extra_width = 1.f;


    float bar_tickness = hb_ot_math_get_constant(harf_font, HB_OT_MATH_CONSTANT_FRACTION_RULE_THICKNESS)/64.f;

    printf("\n\n\n\n\nbar tickness : %f\n", bar_tickness);
    printf("bar tickness : %u\n\n\n\n\n\n", hb_ot_math_get_constant(harf_font, HB_OT_MATH_CONSTANT_FRACTION_RULE_THICKNESS));

    math_shape_desc_t* fraction_bar = get_box_desc(fraction_bar_extra_width + bigger_width, bar_tickness);

    translate_math_shape_params(fraction_bar, 0.0f, 0.25f);
    fraction_bar->y -= 0.25f;

    float numerator_margin = hb_ot_math_get_constant(harf_font, HB_OT_MATH_CONSTANT_FRACTION_NUMERATOR_SHIFT_UP)/64.f;
    float denominator_margin = hb_ot_math_get_constant(harf_font, HB_OT_MATH_CONSTANT_FRACTION_DENOMINATOR_SHIFT_DOWN)/64.f;

    float frac_b_p1_x = fraction_bar->p1_x;
    float frac_b_p1_y = fraction_bar->p1_y;
    float frac_b_p0_x = fraction_bar->p0_x;
    float frac_b_p0_y = fraction_bar->p0_y;

    // translate_math_shape_params(fraction_bar, -fraction_bar->width*(fraction_bar_extra_width/2.f), 0.0f);
    unsigned int numerator_operations = numerator_shaped_desc->operations;
    unsigned int denominator_operationss = denominator_shaped_desc->operations;


    math_shape_desc_t* tmp = concat_math_shape_descs(
        fraction_bar,
        numerator_shaped_desc,
        (frac_b_p1_x + frac_b_p0_x)/2.f - (numerator_shaped_desc->p0_x + numerator_shaped_desc->p1_x)/2.f,
        frac_b_p1_y - numerator_shaped_desc->p0_y + numerator_margin
    );

    tmp = concat_math_shape_descs(
        tmp,
        denominator_shaped_desc,
        (frac_b_p1_x + frac_b_p0_x)/2.f - (denominator_shaped_desc->p0_x + denominator_shaped_desc->p1_x)/2.f,
        -1.f*(denominator_shaped_desc->p1_y - frac_b_p0_y + denominator_margin)
    );

    tmp->operations = 1 + numerator_operations + denominator_operationss;

    hb_font_destroy(harf_font);

    return tmp;

}


math_shape_desc_t* parse_utf8(std::string text, Font* font) {

    FT_Set_Char_Size (font->get_face(), 1*64, 1*64, 0, 0);
    
    hb_font_t* hb_font = hb_ft_font_create (font->get_face(), NULL);

    /* Create hb-buffer and populate. */
    hb_buffer_t *hb_buffer;
    hb_buffer = hb_buffer_create ();
    hb_buffer_reset(hb_buffer);

    hb_buffer_set_direction(hb_buffer, HB_DIRECTION_LTR);
    hb_buffer_set_script(hb_buffer, HB_SCRIPT_LATIN);
    hb_buffer_set_language(hb_buffer, hb_language_from_string("en", -1));    hb_buffer_set_content_type(hb_buffer, HB_BUFFER_CONTENT_TYPE_UNICODE);
    hb_buffer_add_utf8 (hb_buffer, text.c_str(), text.size(), 0,text.size());
    // hb_buffer_add_utf32(hb_buffer, text.c_str(), text.size(), 0,text.size());
    // hb_buffer_guess_segment_properties (this->hb_buffer);

    /* Shape it! */
    unsigned int n_feat = 19;
    printf("malloc features\n");

    hb_feature_t* userfeatures = (hb_feature_t*)malloc(sizeof(hb_feature_t)*n_feat);
    userfeatures[0].tag = HB_TAG('d','l','i','g');
    userfeatures[0].value = 1;
    userfeatures[0].start = HB_FEATURE_GLOBAL_START;
    userfeatures[0].end = HB_FEATURE_GLOBAL_END;

    userfeatures[1].tag = HB_TAG('k','e','r','n');
    userfeatures[1].value = 1;
    userfeatures[1].start = HB_FEATURE_GLOBAL_START;
    userfeatures[1].end = HB_FEATURE_GLOBAL_END;

    userfeatures[2].tag = HB_TAG('l','i','g','a');
    userfeatures[2].value = 1;
    userfeatures[2].start = HB_FEATURE_GLOBAL_START;
    userfeatures[2].end = HB_FEATURE_GLOBAL_END;

    userfeatures[3].tag = HB_TAG('c','l','i','g');
    userfeatures[3].value = 1;
    userfeatures[3].start = HB_FEATURE_GLOBAL_START;
    userfeatures[3].end = HB_FEATURE_GLOBAL_END;

    userfeatures[4].tag = HB_TAG('f','r','a','c');
    userfeatures[4].value = 1;
    userfeatures[4].start = HB_FEATURE_GLOBAL_START;
    userfeatures[4].end = HB_FEATURE_GLOBAL_END;

    userfeatures[5].tag = HB_TAG('d','i','s','t');
    userfeatures[5].value = 1;
    userfeatures[5].start = HB_FEATURE_GLOBAL_START;
    userfeatures[5].end = HB_FEATURE_GLOBAL_END;

    userfeatures[6].tag = HB_TAG('d','n','o','m');
    userfeatures[6].value = 0;
    userfeatures[6].start = HB_FEATURE_GLOBAL_START;
    userfeatures[6].end = HB_FEATURE_GLOBAL_END;

    userfeatures[7].tag = HB_TAG('c','u','r','s');
    userfeatures[7].value = 1;
    userfeatures[7].start = HB_FEATURE_GLOBAL_START;
    userfeatures[7].end = HB_FEATURE_GLOBAL_END;

    userfeatures[8].tag = HB_TAG('c','c','m','p');
    userfeatures[8].value = 1;
    userfeatures[8].start = HB_FEATURE_GLOBAL_START;
    userfeatures[8].end = HB_FEATURE_GLOBAL_END;

    userfeatures[9].tag = HB_TAG('a','f','r','c');
    userfeatures[9].value = 0;
    userfeatures[9].start = HB_FEATURE_GLOBAL_START;
    userfeatures[9].end = HB_FEATURE_GLOBAL_END;

    userfeatures[10].tag = HB_TAG('o','r','d','n');
    userfeatures[10].value = 1;
    userfeatures[10].start = HB_FEATURE_GLOBAL_START;
    userfeatures[10].end = HB_FEATURE_GLOBAL_END;


    userfeatures[11].tag = HB_TAG('s','a','l','t');
    userfeatures[11].value = 1;
    userfeatures[11].start = HB_FEATURE_GLOBAL_START;
    userfeatures[11].end = HB_FEATURE_GLOBAL_END;

    userfeatures[12].tag = HB_TAG('n','u','m','r');
    userfeatures[12].value = 0;
    userfeatures[12].start = HB_FEATURE_GLOBAL_START;
    userfeatures[12].end = HB_FEATURE_GLOBAL_END;

    userfeatures[13].tag = HB_TAG('s','s','t','y');
    userfeatures[13].value = 2;
    userfeatures[13].start = HB_FEATURE_GLOBAL_START;
    userfeatures[13].end = HB_FEATURE_GLOBAL_END;

    userfeatures[14].tag = HB_TAG('m','a','t','h');
    userfeatures[14].value = 1;
    userfeatures[14].start = HB_FEATURE_GLOBAL_START;
    userfeatures[14].end = HB_FEATURE_GLOBAL_END;

    userfeatures[15].tag = HB_TAG('c','a','l','t');
    userfeatures[15].value = 1;
    userfeatures[15].start = HB_FEATURE_GLOBAL_START;
    userfeatures[15].end = HB_FEATURE_GLOBAL_END;

    userfeatures[16].tag = HB_TAG('s','u','b','s');
    userfeatures[16].value = 1;
    userfeatures[16].start = HB_FEATURE_GLOBAL_START;
    userfeatures[16].end = HB_FEATURE_GLOBAL_END;

    userfeatures[17].tag = HB_TAG('i','t','a','l');
    userfeatures[17].value = 1;
    userfeatures[17].start = HB_FEATURE_GLOBAL_START;
    userfeatures[17].end = HB_FEATURE_GLOBAL_END;

    userfeatures[18].tag = HB_TAG('s','i','n','f');
    userfeatures[18].value = 1;
    userfeatures[18].start = HB_FEATURE_GLOBAL_START;
    userfeatures[18].end = HB_FEATURE_GLOBAL_END;

    char *shaperprefs[3] = {"ot", "default", "aat"};

    // hb_shape(hb_font, hb_buffer, userfeatures, 15);
    hb_shape_full (hb_font, hb_buffer, userfeatures, n_feat, shaperprefs);

    /* Get glyph information and positions out of the buffer. */
    unsigned int len = hb_buffer_get_length (hb_buffer);
    hb_glyph_info_t *info = hb_buffer_get_glyph_infos (hb_buffer, NULL);
    hb_glyph_position_t *pos = hb_buffer_get_glyph_positions (hb_buffer, NULL);

    float current_x = 0;
    float current_y = 0;
    printf("malloc here %ui\n", len);
    math_shape_params_t* params = (math_shape_params_t*)malloc(sizeof(math_shape_params_t) * len);
    printf("malloc==\n");
    
    float height = 0;
    float width = 0;
    float p0_x = FLT_MAX, p0_y = FLT_MAX, p1_x = FLT_MIN, p1_y = FLT_MIN;

    float advance_x;
    hb_face_t* harf_face = hb_ft_face_create(font->get_face(), nullptr);

    unsigned lookup_count = hb_ot_layout_table_get_lookup_count (harf_face, HB_OT_TAG_GSUB);
    unsigned int variants_count = 30;
    hb_codepoint_t variants[30];        

    for (unsigned int i = 0; i < len; i++){
        unsigned int cluster = info[i].cluster;
        // for (unsigned lookup = 0; lookup < lookup_count; ++lookup){
        //     printf("lookup: %u\n", lookup);
        
        //     hb_ot_layout_lookup_get_glyph_alternates (
        //         harf_face,
        //         lookup,
        //         info[i].codepoint,
        //         0,
        //         &variants_count,
        //         variants
        //     );
        //     printf("variants_count: %u\n", variants_count);

        //     for(int k=0; k<variants_count; k++) {
        //         printf("variant: %u\n", variants[k]);
        //     }
        // }
        Glyph* g = font->get_glyph(info[i].codepoint);

        current_x += pos[i].x_offset / 64.f;
        current_y += pos[i].y_offset / 64.f;

        params[i].codepoint = info[i].codepoint;
        params[i].x = current_x;
        params[i].y = current_y;
        params[i].p0_x = current_x + g->get_bounding_box().p0.x;
        params[i].p0_y = current_y + g->get_bounding_box().p0.y;
        params[i].p1_x = current_x + g->get_bounding_box().p1.x;
        params[i].p1_y = current_y + g->get_bounding_box().p1.y;
        params[i].n_custom_shapes = 0;
        params[i].custom_shapes = nullptr;
    
        if(g->get_bounding_box().p1.x == 0.f) {
            params[i].p1_x += pos[i].x_advance / 64.f;
        }
    
        params[i].stretch_x = 1.f;
        params[i].stretch_y = 1.f;

        params[i].advance_x = pos[i].x_advance / 64.f;
        params[i].advance_y = pos[i].y_advance / 64.f;

        // if(i == 0) {
        //     p0_x = params[i].p0_x;
        //     p0_y = params[i].p0_y;

        //     p1_x = params[i].p1_x;
        //     p1_y = params[i].p1_y;
        // }

        p0_x = std::min(p0_x, params[i].p0_x);
        p0_y = std::min(p0_y, params[i].p0_y);

        p1_x = std::max(p1_x, params[i].p1_x);
        p1_y = std::max(p1_y, params[i].p1_y);

        current_x += pos[i].x_advance / 64.f;
        current_y += pos[i].y_advance / 64.f;
        advance_x = pos[i].x_advance / 64.f;
        width = current_x;
        height = std::max(g->get_height(), height);

    }
    printf("malloc here\n");

    math_shape_desc_t* desc = (math_shape_desc_t*)malloc(sizeof(math_shape_desc_t));
    printf("malloc here\n");

    desc->params = params;
    desc->x = 0.f;
    desc->y = 0.f;
    desc->operations = 1;
    desc->p0_x = p0_x;
    desc->p0_y = p0_y;
    desc->p1_x = p1_x;
    desc->p1_y = p1_y;
    desc->width = desc->p1_x - desc->p0_x;
    desc->height = desc->p1_y - desc->p0_y;
    desc->n_params = len;

    desc->advance_x = 0.1f;
    desc->advance_y = 0.0f;

    printf("end parsing utf8\n");
    return desc;
}





math_shape_desc_t* parse_utf16(uint16_t * text, unsigned int lenght, Font* font) {

    FT_Set_Char_Size (font->get_face(), 1*64, 1*64, 0, 0);
    
    hb_font_t* hb_font = hb_ft_font_create (font->get_face(), NULL);

    /* Create hb-buffer and populate. */
    hb_buffer_t *hb_buffer;
    hb_buffer = hb_buffer_create ();
    hb_buffer_reset(hb_buffer);

    hb_buffer_set_direction(hb_buffer, HB_DIRECTION_LTR);
    hb_buffer_set_script(hb_buffer, HB_SCRIPT_LATIN);
    hb_buffer_set_language(hb_buffer, hb_language_from_string("en", -1));    hb_buffer_set_content_type(hb_buffer, HB_BUFFER_CONTENT_TYPE_UNICODE);
    hb_buffer_add_utf16 (hb_buffer, text, lenght, 0, lenght);
    // hb_buffer_add_utf32(hb_buffer, text.c_str(), text.size(), 0,text.size());
    // hb_buffer_guess_segment_properties (this->hb_buffer);

    /* Shape it! */

    char *shaperprefs[3] = {"ot", "default", "aat"};

    // hb_shape(hb_font, hb_buffer, userfeatures, 15);
    hb_shape_full (hb_font, hb_buffer, nullptr, 0, shaperprefs);

    /* Get glyph information and positions out of the buffer. */
    unsigned int len = hb_buffer_get_length (hb_buffer);
    hb_glyph_info_t *info = hb_buffer_get_glyph_infos (hb_buffer, NULL);
    hb_glyph_position_t *pos = hb_buffer_get_glyph_positions (hb_buffer, NULL);

    float current_x = 0;
    float current_y = 0;
    printf("malloc here %ui\n", len);
    math_shape_params_t* params = (math_shape_params_t*)malloc(sizeof(math_shape_params_t) * len);
    printf("malloc==\n");
    
    float height = 0;
    float width = 0;
    float p0_x = FLT_MAX, p0_y = FLT_MAX, p1_x = FLT_MIN, p1_y = FLT_MIN;

    float advance_x;
    hb_face_t* harf_face = hb_ft_face_create(font->get_face(), nullptr);

    unsigned lookup_count = hb_ot_layout_table_get_lookup_count (harf_face, HB_OT_TAG_GSUB);
    unsigned int variants_count = 30;
    hb_codepoint_t variants[30];        

    for (unsigned int i = 0; i < len; i++){
        unsigned int cluster = info[i].cluster;
        // for (unsigned lookup = 0; lookup < lookup_count; ++lookup){
        //     printf("lookup: %u\n", lookup);
        
        //     hb_ot_layout_lookup_get_glyph_alternates (
        //         harf_face,
        //         lookup,
        //         info[i].codepoint,
        //         0,
        //         &variants_count,
        //         variants
        //     );
        //     printf("variants_count: %u\n", variants_count);

        //     for(int k=0; k<variants_count; k++) {
        //         printf("variant: %u\n", variants[k]);
        //     }
        // }
        Glyph* g = font->get_glyph(info[i].codepoint);

        current_x += pos[i].x_offset / 64.f;
        current_y += pos[i].y_offset / 64.f;

        params[i].codepoint = info[i].codepoint;
        params[i].x = current_x;
        params[i].y = current_y;
        params[i].p0_x = current_x + g->get_bounding_box().p0.x;
        params[i].p0_y = current_y + g->get_bounding_box().p0.y;
        params[i].p1_x = current_x + g->get_bounding_box().p1.x;
        params[i].p1_y = current_y + g->get_bounding_box().p1.y;
        params[i].n_custom_shapes = 0;
        params[i].custom_shapes = nullptr;
    
        if(g->get_bounding_box().p1.x == 0.f) {
            params[i].p1_x += pos[i].x_advance / 64.f;
        }
    
        params[i].stretch_x = 1.f;
        params[i].stretch_y = 1.f;

        params[i].advance_x = pos[i].x_advance / 64.f;
        params[i].advance_y = pos[i].y_advance / 64.f;

        // if(i == 0) {
        //     p0_x = params[i].p0_x;
        //     p0_y = params[i].p0_y;

        //     p1_x = params[i].p1_x;
        //     p1_y = params[i].p1_y;
        // }

        p0_x = std::min(p0_x, params[i].p0_x);
        p0_y = std::min(p0_y, params[i].p0_y);

        p1_x = std::max(p1_x, params[i].p1_x);
        p1_y = std::max(p1_y, params[i].p1_y);

        current_x += pos[i].x_advance / 64.f;
        current_y += pos[i].y_advance / 64.f;
        advance_x = pos[i].x_advance / 64.f;
        width = current_x;
        height = std::max(g->get_height(), height);

    }
    printf("malloc here\n");

    math_shape_desc_t* desc = (math_shape_desc_t*)malloc(sizeof(math_shape_desc_t));
    printf("malloc here\n");

    desc->params = params;
    desc->x = 0.f;
    desc->y = 0.f;
    desc->operations = 1;
    desc->p0_x = p0_x;
    desc->p0_y = p0_y;
    desc->p1_x = p1_x;
    desc->p1_y = p1_y;
    desc->width = desc->p1_x - desc->p0_x;
    desc->height = desc->p1_y - desc->p0_y;
    desc->n_params = len;

    desc->advance_x = 0.1f;
    desc->advance_y = 0.0f;

    printf("end parsing utf16\n");
    return desc;
}



math_shape_desc_t* parse_utf32(uint32_t * text, unsigned int lenght, Font* font) {

    FT_Set_Char_Size (font->get_face(), 1*64, 1*64, 0, 0);
    
    hb_font_t* hb_font = hb_ft_font_create (font->get_face(), NULL);

    /* Create hb-buffer and populate. */
    hb_buffer_t *hb_buffer;
    hb_buffer = hb_buffer_create ();
    hb_buffer_reset(hb_buffer);

    hb_buffer_set_direction(hb_buffer, HB_DIRECTION_LTR);
    hb_buffer_set_script(hb_buffer, HB_SCRIPT_LATIN);
    hb_buffer_set_language(hb_buffer, hb_language_from_string("en", -1));    hb_buffer_set_content_type(hb_buffer, HB_BUFFER_CONTENT_TYPE_UNICODE);
    hb_buffer_add_utf32 (hb_buffer, text, lenght, 0, lenght);
    // hb_buffer_add_utf32(hb_buffer, text.c_str(), text.size(), 0,text.size());
    // hb_buffer_guess_segment_properties (this->hb_buffer);

    /* Shape it! */
    unsigned int n_feat = 19;
    printf("malloc features\n");

    hb_feature_t* userfeatures = (hb_feature_t*)malloc(sizeof(hb_feature_t)*n_feat);
    userfeatures[0].tag = HB_TAG('d','l','i','g');
    userfeatures[0].value = 1;
    userfeatures[0].start = HB_FEATURE_GLOBAL_START;
    userfeatures[0].end = HB_FEATURE_GLOBAL_END;

    userfeatures[1].tag = HB_TAG('k','e','r','n');
    userfeatures[1].value = 1;
    userfeatures[1].start = HB_FEATURE_GLOBAL_START;
    userfeatures[1].end = HB_FEATURE_GLOBAL_END;

    userfeatures[2].tag = HB_TAG('l','i','g','a');
    userfeatures[2].value = 1;
    userfeatures[2].start = HB_FEATURE_GLOBAL_START;
    userfeatures[2].end = HB_FEATURE_GLOBAL_END;

    userfeatures[3].tag = HB_TAG('c','l','i','g');
    userfeatures[3].value = 1;
    userfeatures[3].start = HB_FEATURE_GLOBAL_START;
    userfeatures[3].end = HB_FEATURE_GLOBAL_END;

    userfeatures[4].tag = HB_TAG('f','r','a','c');
    userfeatures[4].value = 1;
    userfeatures[4].start = HB_FEATURE_GLOBAL_START;
    userfeatures[4].end = HB_FEATURE_GLOBAL_END;

    userfeatures[5].tag = HB_TAG('d','i','s','t');
    userfeatures[5].value = 1;
    userfeatures[5].start = HB_FEATURE_GLOBAL_START;
    userfeatures[5].end = HB_FEATURE_GLOBAL_END;

    userfeatures[6].tag = HB_TAG('d','n','o','m');
    userfeatures[6].value = 0;
    userfeatures[6].start = HB_FEATURE_GLOBAL_START;
    userfeatures[6].end = HB_FEATURE_GLOBAL_END;

    userfeatures[7].tag = HB_TAG('c','u','r','s');
    userfeatures[7].value = 1;
    userfeatures[7].start = HB_FEATURE_GLOBAL_START;
    userfeatures[7].end = HB_FEATURE_GLOBAL_END;

    userfeatures[8].tag = HB_TAG('c','c','m','p');
    userfeatures[8].value = 1;
    userfeatures[8].start = HB_FEATURE_GLOBAL_START;
    userfeatures[8].end = HB_FEATURE_GLOBAL_END;

    userfeatures[9].tag = HB_TAG('a','f','r','c');
    userfeatures[9].value = 0;
    userfeatures[9].start = HB_FEATURE_GLOBAL_START;
    userfeatures[9].end = HB_FEATURE_GLOBAL_END;

    userfeatures[10].tag = HB_TAG('o','r','d','n');
    userfeatures[10].value = 1;
    userfeatures[10].start = HB_FEATURE_GLOBAL_START;
    userfeatures[10].end = HB_FEATURE_GLOBAL_END;


    userfeatures[11].tag = HB_TAG('s','a','l','t');
    userfeatures[11].value = 1;
    userfeatures[11].start = HB_FEATURE_GLOBAL_START;
    userfeatures[11].end = HB_FEATURE_GLOBAL_END;

    userfeatures[12].tag = HB_TAG('n','u','m','r');
    userfeatures[12].value = 0;
    userfeatures[12].start = HB_FEATURE_GLOBAL_START;
    userfeatures[12].end = HB_FEATURE_GLOBAL_END;

    userfeatures[13].tag = HB_TAG('s','s','t','y');
    userfeatures[13].value = 2;
    userfeatures[13].start = HB_FEATURE_GLOBAL_START;
    userfeatures[13].end = HB_FEATURE_GLOBAL_END;

    userfeatures[14].tag = HB_TAG('m','a','t','h');
    userfeatures[14].value = 1;
    userfeatures[14].start = HB_FEATURE_GLOBAL_START;
    userfeatures[14].end = HB_FEATURE_GLOBAL_END;

    userfeatures[15].tag = HB_TAG('c','a','l','t');
    userfeatures[15].value = 1;
    userfeatures[15].start = HB_FEATURE_GLOBAL_START;
    userfeatures[15].end = HB_FEATURE_GLOBAL_END;

    userfeatures[16].tag = HB_TAG('s','u','b','s');
    userfeatures[16].value = 1;
    userfeatures[16].start = HB_FEATURE_GLOBAL_START;
    userfeatures[16].end = HB_FEATURE_GLOBAL_END;

    userfeatures[17].tag = HB_TAG('i','t','a','l');
    userfeatures[17].value = 1;
    userfeatures[17].start = HB_FEATURE_GLOBAL_START;
    userfeatures[17].end = HB_FEATURE_GLOBAL_END;

    userfeatures[18].tag = HB_TAG('s','i','n','f');
    userfeatures[18].value = 1;
    userfeatures[18].start = HB_FEATURE_GLOBAL_START;
    userfeatures[18].end = HB_FEATURE_GLOBAL_END;

    char *shaperprefs[3] = {"ot", "default", "aat"};

    // hb_shape(hb_font, hb_buffer, userfeatures, 15);
    hb_shape_full (hb_font, hb_buffer, nullptr, 0, shaperprefs);

    /* Get glyph information and positions out of the buffer. */
    unsigned int len = hb_buffer_get_length (hb_buffer);
    hb_glyph_info_t *info = hb_buffer_get_glyph_infos (hb_buffer, NULL);
    hb_glyph_position_t *pos = hb_buffer_get_glyph_positions (hb_buffer, NULL);

    float current_x = 0;
    float current_y = 0;
    printf("malloc here %ui\n", len);
    math_shape_params_t* params = (math_shape_params_t*)malloc(sizeof(math_shape_params_t) * len);
    printf("malloc==\n");
    
    float height = 0;
    float width = 0;
    float p0_x = FLT_MAX, p0_y = FLT_MAX, p1_x = FLT_MIN, p1_y = FLT_MIN;

    float advance_x;
    hb_face_t* harf_face = hb_ft_face_create(font->get_face(), nullptr);

    unsigned lookup_count = hb_ot_layout_table_get_lookup_count (harf_face, HB_OT_TAG_GSUB);
    unsigned int variants_count = 30;
    hb_codepoint_t variants[30];        

    for (unsigned int i = 0; i < len; i++){
        unsigned int cluster = info[i].cluster;
        // for (unsigned lookup = 0; lookup < lookup_count; ++lookup){
        //     printf("lookup: %u\n", lookup);
        
        //     hb_ot_layout_lookup_get_glyph_alternates (
        //         harf_face,
        //         lookup,
        //         info[i].codepoint,
        //         0,
        //         &variants_count,
        //         variants
        //     );
        //     printf("variants_count: %u\n", variants_count);

        //     for(int k=0; k<variants_count; k++) {
        //         printf("variant: %u\n", variants[k]);
        //     }
        // }
        Glyph* g = font->get_glyph(info[i].codepoint);

        current_x += pos[i].x_offset / 64.f;
        current_y += pos[i].y_offset / 64.f;

        params[i].codepoint = info[i].codepoint;
        params[i].x = current_x;
        params[i].y = current_y;
        params[i].p0_x = current_x + g->get_bounding_box().p0.x;
        params[i].p0_y = current_y + g->get_bounding_box().p0.y;
        params[i].p1_x = current_x + g->get_bounding_box().p1.x;
        params[i].p1_y = current_y + g->get_bounding_box().p1.y;
        params[i].n_custom_shapes = 0;
        params[i].custom_shapes = nullptr;
    
        if(g->get_bounding_box().p1.x == 0.f) {
            params[i].p1_x += pos[i].x_advance / 64.f;
        }
    
        params[i].stretch_x = 1.f;
        params[i].stretch_y = 1.f;

        params[i].advance_x = pos[i].x_advance / 64.f;
        params[i].advance_y = pos[i].y_advance / 64.f;

        // if(i == 0) {
        //     p0_x = params[i].p0_x;
        //     p0_y = params[i].p0_y;

        //     p1_x = params[i].p1_x;
        //     p1_y = params[i].p1_y;
        // }

        p0_x = std::min(p0_x, params[i].p0_x);
        p0_y = std::min(p0_y, params[i].p0_y);

        p1_x = std::max(p1_x, params[i].p1_x);
        p1_y = std::max(p1_y, params[i].p1_y);

        current_x += pos[i].x_advance / 64.f;
        current_y += pos[i].y_advance / 64.f;
        advance_x = pos[i].x_advance / 64.f;
        width = current_x;
        height = std::max(g->get_height(), height);

    }
    printf("malloc here\n");

    math_shape_desc_t* desc = (math_shape_desc_t*)malloc(sizeof(math_shape_desc_t));
    printf("malloc here\n");

    desc->params = params;
    desc->x = 0.f;
    desc->y = 0.f;
    desc->operations = 1;
    desc->p0_x = p0_x;
    desc->p0_y = p0_y;
    desc->p1_x = p1_x;
    desc->p1_y = p1_y;
    desc->width = desc->p1_x - desc->p0_x;
    desc->height = desc->p1_y - desc->p0_y;
    desc->n_params = len;

    desc->advance_x = 0.1f;
    desc->advance_y = 0.0f;

    printf("end parsing utf16\n");
    return desc;
}

math_shape_desc_t* parse_utf8_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr;

    std::string text = std::string((char*)node->value(), node->value_size());
    math_shape_desc_t* desc = parse_utf8(text, font);

    return desc;
}

math_shape_desc_t* parse_constant_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 
    std::string number(node->first_attribute("value")->value(), node->first_attribute("value")->value_size());
    return parse_utf8(number, font);
}

math_shape_desc_t* script_shape_desc(
    math_shape_desc_t* desc, math_shape_desc_t* superscript,
    math_shape_desc_t* subscript,
    Font* font,
    float scale = 0.5f,
    float delta_y_super_script = 0.0f,
    float delta_y_subs_script = 0.0f,
    float delta_x_super_script = 0.0f,
    float delta_x_subs_script = 0.0f
) {

    math_shape_desc_t* result = desc;
    math_shape_params_t param = desc->params[desc->n_params - 1];
    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);
    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);
    float italic_correction = hb_ot_math_get_glyph_italics_correction (harf_font, param.codepoint)/64.f;

    if(superscript) {
        stretch_math_shape_params(superscript, scale, scale);

        float base_line_y = param.p1_y + delta_y_super_script;
        float y = base_line_y - superscript->p1_y;
        float x = param.p1_x - superscript->p0_x  + delta_x_super_script;

        result = concat_math_shape_descs(result, superscript, x, y);
    }
    if(subscript) {
        stretch_math_shape_params(subscript, scale, scale);

        float base_line_y = param.p0_y + delta_y_subs_script;
        float y = base_line_y - subscript->p0_y;
        float x = param.p1_x - subscript->p0_x - italic_correction + delta_x_subs_script;
        result = concat_math_shape_descs(result, subscript, x, y);
    }


    return result;
}



math_shape_desc_t* parse_radical_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 
    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);
    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);

    math_shape_desc_t* radicand = parse_xml_node(node->first_node(), font);

    hb_codepoint_t gid; 

    std::string s("221a");

    int num = std::stoi(s, 0, 16);
    hb_font_get_nominal_glyph(harf_font, num, &gid);

    float extra_ascender =  hb_ot_math_get_constant(harf_font, HB_OT_MATH_CONSTANT_RADICAL_VERTICAL_GAP)/64.f; //* radical->params[0].stretch_y*0.068f;
    math_shape_desc_t* radical = get_math_shape_desc_stretchy(gid, HB_DIRECTION_TTB, radicand->p1_y - radicand->p0_y +  3*extra_ascender, font);
    // translate_math_shape_params(radical, 0.0f, 0.f);
    math_shape_params_t* bar = (math_shape_params_t*)malloc(sizeof(math_shape_params_t));

    float extra_width = 0.4f;
    float radicand_kerning = 0.0f;

    float bar_width = radicand->p1_x - radicand->p0_x - radicand_kerning + extra_width;
   
    float bar_height =  hb_ot_math_get_constant(harf_font, HB_OT_MATH_CONSTANT_OVERBAR_RULE_THICKNESS)/64.f; //* radical->params[0].stretch_y*0.068f;

    math_shape_desc_t* over_bar_desc = get_box_desc(bar_width, bar_height);

    // stretch_math_shape_params(over_bar_desc, 1.f, radical->params[0].stretch_y);

    float p1_y = radical->p1_y;
    float p1_x = radical->p1_x;

    unsigned int radicand_operations = radicand->operations;

    math_shape_desc_t* tmp = concat_math_shape_descs(radical, radicand, radical->p1_x - radicand->p0_x - radicand_kerning, radical->p0_y - radicand->p0_y);

    tmp = concat_math_shape_descs(tmp, over_bar_desc, p1_x - over_bar_desc->p0_x - 0.02f, p1_y - over_bar_desc->p1_y - over_bar_desc->p0_y);

    if(node->first_node()->next_sibling()) {
        math_shape_desc_t* indice = parse_xml_node(node->first_node()->next_sibling(), font);
        //radicalDegreeBottomRaisePercent
        font->get_face()->ascender/64.f;
    
        float v = hb_ot_math_get_constant(harf_font, HB_OT_MATH_CONSTANT_RADICAL_DEGREE_BOTTOM_RAISE_PERCENT)/100.f;
    
        stretch_math_shape_params(indice, 0.6f, 0.6f);
    
        tmp = concat_math_shape_descs(tmp, indice, tmp->x - 0.1f, tmp->p0_y + (v-0.1f)*(tmp->p1_y - tmp->p0_y));
    }

    hb_font_destroy(harf_font);

    return tmp;
}


//\u0031\u2044\u0038
math_shape_desc_t* parse_add_node(const rapidxml::xml_node<> *node, Font* font) {
    math_shape_desc_t* begining_shaped_desc = parse_xml_node(node->first_node(), font);
    math_shape_desc_t* midle_shaped_desc = parse_utf8(" + ", font);
    math_shape_desc_t* end_shaped_desc = parse_xml_node(node->first_node()->next_sibling(), font);

    math_shape_desc_t* tmp = concat_math_shape_descs(begining_shaped_desc, midle_shaped_desc, begining_shaped_desc->p1_x - midle_shaped_desc->p0_x, 0);
    tmp = concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x, 0);

    return tmp;
}

math_shape_desc_t* parse_subtract_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 

    math_shape_desc_t* begining_shaped_desc = parse_xml_node(node->first_node(), font);
    math_shape_desc_t* midle_shaped_desc = parse_utf8(" - ", font);
    math_shape_desc_t* end_shaped_desc = parse_xml_node(node->first_node()->next_sibling(), font);
    math_shape_desc_t* tmp = concat_math_shape_descs(begining_shaped_desc, midle_shaped_desc, begining_shaped_desc->p1_x - midle_shaped_desc->p0_x, 0);
    tmp = concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x, 0);
    return tmp;
}

math_shape_desc_t* parse_divide_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 

    math_shape_desc_t* begining_shaped_desc = parse_xml_node(node->first_node(), font);
    math_shape_desc_t* midle_shaped_desc = parse_utf8(" \u00F7 ", font);
    math_shape_desc_t* end_shaped_desc = parse_xml_node(node->first_node()->next_sibling(), font);
    math_shape_desc_t* tmp = concat_math_shape_descs(begining_shaped_desc, midle_shaped_desc, begining_shaped_desc->p1_x - midle_shaped_desc->p0_x, 0);
    tmp = concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x, 0);
    return tmp;
}

bool should_surround(const rapidxml::xml_node<> *node) {
    std::string node_type = std::string((char*)node->name(), node->name_size());

    if(node_type == "fraction") return false;
    if(node_type == "radical") return false;
    if(node_type == "text") return false;

    return true;
}

math_shape_desc_t* parse_multiply_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 
    const rapidxml::xml_attribute<char> * style = node->first_attribute("style");
    math_shape_desc_t* midle_shaped_desc = nullptr;
    if(style) {
        std::string value(style->value(), style->value_size());
        if(value == "dot") {
            midle_shaped_desc = parse_utf8("\u00A0\u22c5\u00A0", font);
        } else if(value == "cross") {
            midle_shaped_desc = parse_utf8(" \u00D7 ", font);
        } else if(value == "none"){
            // midle_shaped_desc = (math_shape_desc_t*)malloc(sizeof(math_shape_desc_t));
            // midle_shaped_desc->n_params = 0;
            // midle_shaped_desc->params = nullptr;
            // midle_shaped_desc->p0_x = 0.f;
            // midle_shaped_desc->p0_y = 0.f;
            // midle_shaped_desc->p1_x = 0.f;
            // midle_shaped_desc->p1_y = 0.f;
            // midle_shaped_desc->x = 0.f;
            // midle_shaped_desc->y = 0.f;
            // midle_shaped_desc->advance_x = 0.f;
            // midle_shaped_desc->advance_y = 0.f;
            // midle_shaped_desc->width = 0.f;
            // midle_shaped_desc->height = 0.f;
            // midle_shaped_desc->operations = 0;
            // midle_shaped_desc->operations = 0;
            midle_shaped_desc = nullptr;
            //nullptr;//parse_utf8("\u00A0", font);
        } else {
            midle_shaped_desc = parse_utf8("\u00A0\u22c5\u00A0", font);
        }
    } else {
        midle_shaped_desc = parse_utf8("\u00A0\u22c5\u00A0", font);
    }

    math_shape_desc_t* begining_shaped_desc = parse_xml_node(node->first_node(), font);
    if(should_surround(node->first_node()) && begining_shaped_desc->operations > 1) {
        hb_codepoint_t glyph_index_l;
        hb_codepoint_t glyph_index_r;
        hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);
        hb_font_get_glyph_from_name(harf_font, "parenleft", 9 , &glyph_index_l);
        hb_font_get_glyph_from_name(harf_font, "parenright", 10 , &glyph_index_r);
        begining_shaped_desc = surround_shape_desc_horizontal(glyph_index_l, glyph_index_r, begining_shaped_desc, font);
    }

    math_shape_desc_t* end_shaped_desc = parse_xml_node(node->first_node()->next_sibling(), font);
    if(should_surround(node->first_node()->next_sibling()) && end_shaped_desc->operations > 1) {
        hb_codepoint_t glyph_index_l;
        hb_codepoint_t glyph_index_r;
        hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);
        hb_font_get_glyph_from_name(harf_font, "parenleft", 9 , &glyph_index_l);
        hb_font_get_glyph_from_name(harf_font, "parenright", 10 , &glyph_index_r);
        end_shaped_desc = surround_shape_desc_horizontal(glyph_index_l, glyph_index_r, end_shaped_desc, font);
    }

    math_shape_desc_t* tmp = begining_shaped_desc;
    float advance = 0.0f;
    if(midle_shaped_desc) {
        tmp = concat_math_shape_descs(tmp, midle_shaped_desc, tmp->p1_x - midle_shaped_desc->p0_x, tmp->y - midle_shaped_desc->y);
    } else {
        advance = 0.1f;
    }
    tmp = concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x + advance, tmp->y - end_shaped_desc->y);
    return tmp;
}

math_shape_desc_t* parse_equal_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 


    math_shape_desc_t* begining_shaped_desc = parse_xml_node(node->first_node(), font);
    math_shape_desc_t* midle_shaped_desc = parse_utf8(" \u003D ", font);
    math_shape_desc_t* end_shaped_desc = parse_xml_node(node->first_node()->next_sibling(), font);
    math_shape_desc_t* tmp = concat_math_shape_descs(begining_shaped_desc, midle_shaped_desc, begining_shaped_desc->p1_x - midle_shaped_desc->p0_x, 0);
    tmp = concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x, 0);
    return tmp;
}

math_shape_desc_t* parse_different_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 

    math_shape_desc_t* begining_shaped_desc = parse_xml_node(node->first_node(), font);
    math_shape_desc_t* midle_shaped_desc = parse_utf8(" \u2260 ", font);
    math_shape_desc_t* end_shaped_desc = parse_xml_node(node->first_node()->next_sibling(), font);
    math_shape_desc_t* tmp = concat_math_shape_descs(begining_shaped_desc, midle_shaped_desc, begining_shaped_desc->p1_x - midle_shaped_desc->p0_x, 0);
    tmp = concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x, 0);
    return tmp;
}

math_shape_desc_t* parse_plus_minus_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 

    math_shape_desc_t* begining_shaped_desc = parse_xml_node(node->first_node(), font);
    math_shape_desc_t* midle_shaped_desc = parse_utf8(" \u00B1 ", font);
    math_shape_desc_t* end_shaped_desc = parse_xml_node(node->first_node()->next_sibling(), font);
    math_shape_desc_t* tmp = concat_math_shape_descs(begining_shaped_desc, midle_shaped_desc, begining_shaped_desc->p1_x - midle_shaped_desc->p0_x, 0);
    tmp = concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x, 0);
    return tmp;
}

math_shape_desc_t* parse_greater_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 

    math_shape_desc_t* begining_shaped_desc = parse_xml_node(node->first_node(), font);
    math_shape_desc_t* midle_shaped_desc = parse_utf8(" \u003E ", font);
    math_shape_desc_t* end_shaped_desc = parse_xml_node(node->first_node()->next_sibling(), font);
    math_shape_desc_t* tmp = concat_math_shape_descs(begining_shaped_desc, midle_shaped_desc, begining_shaped_desc->p1_x - midle_shaped_desc->p0_x, 0);
    tmp = concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x, 0);
    return tmp;
}

math_shape_desc_t* parse_greater_or_equal_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 

    math_shape_desc_t* begining_shaped_desc = parse_xml_node(node->first_node(), font);
    math_shape_desc_t* midle_shaped_desc = parse_utf8(" \u2265 ", font);
    math_shape_desc_t* end_shaped_desc = parse_xml_node(node->first_node()->next_sibling(), font);
    math_shape_desc_t* tmp = concat_math_shape_descs(begining_shaped_desc, midle_shaped_desc, begining_shaped_desc->p1_x - midle_shaped_desc->p0_x, 0);
    tmp = concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x, 0);
    return tmp;
}


math_shape_desc_t* parse_less_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 

    math_shape_desc_t* begining_shaped_desc = parse_xml_node(node->first_node(), font);
    math_shape_desc_t* midle_shaped_desc = parse_utf8(" \u003C ", font);
    math_shape_desc_t* end_shaped_desc = parse_xml_node(node->first_node()->next_sibling(), font);
    math_shape_desc_t* tmp = concat_math_shape_descs(begining_shaped_desc, midle_shaped_desc, begining_shaped_desc->p1_x - midle_shaped_desc->p0_x, 0);
    tmp = concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x, 0);
    return tmp;
}

math_shape_desc_t* parse_less_or_equal_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 

    math_shape_desc_t* begining_shaped_desc = parse_xml_node(node->first_node(), font);
    math_shape_desc_t* midle_shaped_desc = parse_utf8(" \u2264 ", font);
    math_shape_desc_t* end_shaped_desc = parse_xml_node(node->first_node()->next_sibling(), font);
    math_shape_desc_t* tmp = concat_math_shape_descs(begining_shaped_desc, midle_shaped_desc, begining_shaped_desc->p1_x - midle_shaped_desc->p0_x, 0);
    tmp = concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x, 0);
    return tmp;
}

math_shape_desc_t* parse_char_node(const rapidxml::xml_node<> *node, Font* font) {
    std::string s(node->first_attribute("code")->value(), node->first_attribute("code")->value_size());
    
    int num = std::stoi(s, 0, 16);
    
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::string u8str = converter.to_bytes(num);

    math_shape_desc_t* desc = parse_utf8(u8str, font);

    if(node->first_node("superscript") || node->first_node("subscript")) {
        math_shape_desc_t* superscript =  parse_xml_node(node->first_node("superscript")->first_node(), font);
        math_shape_desc_t* subscript =  parse_xml_node(node->first_node("subscript")->first_node(), font);
        float scale = std::max(superscript->p1_y - superscript->p0_y, subscript->p1_y - subscript->p0_y);
        desc = script_shape_desc(desc, superscript, subscript ,font, (desc->p1_y - desc->p0_y)/(2.3*scale), -0.3f, -0.3f); 
    }
    return desc;
}


math_shape_desc_t* parse_integral_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 
    const rapidxml::xml_attribute<char> * style = node->first_attribute("style");
    hb_codepoint_t integral_glyph_unicode;
    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);

    hb_font_get_nominal_glyph(harf_font, std::stoi("222b", 0, 16), &integral_glyph_unicode);

    math_shape_desc_t* midle_shaped_desc =  nullptr;

    float integral_height = 2.346000f;

    // if(style) {
    //     std::string value(style->value(), style->value_size());
    //     if(value == "english") {
    //         midle_shaped_desc = get_math_shape_desc_stretchy(integral_glyph_unicode, HB_DIRECTION_BTT, integral_height, font, 0.0f);
    //     } else if(value == "german") {
    //         midle_shaped_desc = get_math_shape_desc_stretchy(integral_glyph_unicode, HB_DIRECTION_BTT, integral_height, font, 0.0f);
    //     } else if(value == "russian"){
    //         midle_shaped_desc = get_math_shape_desc_stretchy(integral_glyph_unicode, HB_DIRECTION_BTT, integral_height, font, 0.0f);
    //     } else {
    //         midle_shaped_desc = get_math_shape_desc_stretchy(integral_glyph_unicode, HB_DIRECTION_BTT, integral_height, font, 0.0f);
    //     }
    // } else {
    //     midle_shaped_desc = get_math_shape_desc_stretchy(integral_glyph_unicode, HB_DIRECTION_BTT, integral_height, font, 0.0f);
    // }

    midle_shaped_desc = get_math_shape_desc_stretchy(integral_glyph_unicode, HB_DIRECTION_BTT, integral_height, font, 0.0f);


    math_shape_desc_t* equation =  parse_xml_node(node->first_node(), font);
    float advance_x = 0.0f;
    if(node->first_node()->next_sibling()) {
        math_shape_desc_t* from = nullptr;
        math_shape_desc_t* to = nullptr;

        if(node->first_node()->next_sibling())
        from =  parse_xml_node(node->first_node()->next_sibling(), font);

        if(node->first_node()->next_sibling() && node->first_node()->next_sibling()->next_sibling())
        to =  parse_xml_node(node->first_node()->next_sibling()->next_sibling(), font);

        float script_scale = 0.5f;

        if(from || to) {

            stretch_math_shape_params(from, script_scale, script_scale);
            stretch_math_shape_params(to, script_scale, script_scale);

            float height = std::max((from ? from->p1_y : 0) - (from ? from->p0_y : 0), (to ? to->p1_y : 0) - (to ? to->p0_y : 0));

        
            float y0 = 0.0f, x0 = 0.0f;
            float y1 = 0.0f, x1 = 0.0f;
    
            if(style) {
                std::string value(style->value(), style->value_size());
                if(value == "german" || value == "russian") {
                    // translate_math_shape_params(from, from->p1_x - from->p0_x/2.f, -0.05f);
                    // translate_math_shape_params(to, to->p1_x - to->p0_x/2.f, 0.05f);
        
                    float a = 1.f/((midle_shaped_desc->p1_y - midle_shaped_desc->p0_y)/(height));

                    y0 += to->p1_y - to->p0_y + 0.2f;
                    y1 -= from->p1_y - from->p0_y + 0.2f;

                    // x0 += 0.5f + (to->p1_x - to->p0_x)/2*(midle_shaped_desc->p1_x - midle_shaped_desc->p0_x);

                    x0 -= (to->p1_x - to->p0_x)*0.5f + 0.1f;
                    x1 -= (from->p1_x - from->p0_x)*0.5f + 0.2f;

                    // x1 += 0.5f;// + (((from->p1_x + from->p0_x)*0.5f) - ((midle_shaped_desc->p1_x + midle_shaped_desc->p0_x)*0.5f));

                    advance_x = midle_shaped_desc->p1_x; //std::max((to->p1_x - to->p0_x), (from->p1_x - from->p0_x))/2.f;
                    
                } else {
                    y0 += to->p1_y - to->p0_y - 0.2f;
                    x0 += 0.1f;
                    x1 += 0.1f;
                    // x0 += 0.1f; // small offset on subscript to feel more natural
                }
            }

            midle_shaped_desc = script_shape_desc(midle_shaped_desc, to, from, font, 1.0f, y0, y1, x0, x1); 

            //  if(style) {
            //     std::string value(style->value(), style->value_size());
            //     if(value == "german" || value == "russian") {
            //         advance_x = -1.f * (midle_shaped_desc->p1_x - advance_x);
            //     }
            //  }
        }
    }

    advance_x = 0.1f;
    float x =  midle_shaped_desc->p1_x - equation->p0_x + advance_x;

    math_shape_desc_t* tmp = concat_math_shape_descs(midle_shaped_desc, equation, x, midle_shaped_desc->y);
    
    float italic_correction = hb_ot_math_get_glyph_italics_correction (harf_font, integral_glyph_unicode)/64.f;
    translate_math_shape_params(tmp, -1*italic_correction, 0.0f);

    return tmp;
}


//1D4B6
//0061
void match_utf32_char_variants(uint32_t* t, std::string text) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32conv;
    std::u32string utf32 = utf32conv.from_bytes(text);
    for(int i=0; i<text.size(); i++) {
        printf("%c\n", text[i]);
        switch (text[i]) {
        case ' ':
            t[i] = 0x000000020;//text[i] /*- 0x00000041 */ + offset;
            break;
        case 'A':
            t[i] = 0x00001D434;//text[i] /*- 0x00000041 */ + offset;
            break;
        case 'B':
            t[i] = 0x00001D435;//text[i] /*- 0x00000042 */ + offset;
            break;

        case 'C':
            t[i] = 0x00001D436;//text[i] /*- 0x00000043 */ + offset;
            break;

        case 'D':
            t[i] = 0x00001D437;//text[i] /*- 0x00000044 */ + offset;
            break;
        
        case 'E':
            t[i] = 0x00001D438; //text[i] /*- 0x00000045 */ + offset;
            break;
        
        case 'F':
            t[i] = 0x00001D439;//text[i] /*- 0x00000046 */ + offset;
            break;

        case 'G':
            t[i] = 0x00001D43A;//text[i] /*- 0x00000047 */ + offset;
            break;

        case 'H':
            t[i] = 0x00001D43B;//text[i] /*- 0x00000048 */ + offset;
            break;
        
        case 'I':
            t[i] = 0x00001D43C;//text[i] /*- 0x00000049 */ + offset;
            break;
        
        case 'J':
            t[i] = 0x00001D43D;//text[i] /*- 0x0000004A */ + offset;
            break;
    
        case 'K':
            t[i] = 0x00001D43E;//text[i] /*- 0x0000004B */ + offset;
            break;

        case 'L':
            t[i] = 0x00001D43F;//text[i] /*- 0x0000004C */ + offset;
            break;

        case 'M':
            t[i] = 0x00001D440;//text[i] /*- 0x0000004D */ + offset;
            break;

        case 'N':
            t[i] = 0x00001D441;//text[i] /*- 0x0000004E */ + offset;
            break;

        case 'O':
            t[i] = 0x00001D442;//text[i] /*- 0x0000004F */ + offset;
            break;

        case 'P':
            t[i] = 0x00001D443;//text[i] /*- 0x00000050 */ + offset;
            break;
    
        case 'Q':
            t[i] = 0x00001D444;//text[i] /*- 0x00000051 */ + offset;
            break;

        case 'R':
            t[i] = 0x00001D445;//text[i] /*- 0x00000052 */ + offset;
            break;

        case 'S':
            t[i] = 0x00001D446;//text[i] /*- 0x00000053 */ + offset;
            break;

        case 'T':
            t[i] = 0x00001D447;//text[i] /*- 0x00000054 */ + offset;
            break;

        case 'U':
            t[i] = 0x00001D448;// text[i] /*- 0x00000055 */ + offset;
            break;

        case 'V':
            t[i] = 0x00001D449;//text[i] /*- 0x00000056 */ + offset;
            break;

        case 'W':
            t[i] = 0x00001D44A; //text[i] /*- 0x00000057 */ + offset;
            break;

        case 'X':
            t[i] = 0x00001D44B;//text[i] /*- 0x00000058 */ + offset;
            break;

        case 'Y':
            t[i] = 0x00001D44C;//text[i] /*- 0x00000059 */ + offset;
            break;
    
        case 'Z':
            t[i] = 0x00001D44D;//text[i] /*- 0x0000005A */ + offset;
            break;



        case 'a':
            t[i] = 0x00001D44E; //text[i] /*- 0x00000061 */ + offset;
            break;

        case 'b':
            t[i] = 0x00001D44F;//text[i] /*- 0x00000062 */ + offset;
            break;

        case 'c':
            t[i] = 0x00001D450; //text[i] /*- 0x00000063 */ + offset;
            break;

        case 'd':
            t[i] = 0x00001D451; //text[i] /*- 0x00000064 */ + offset;
            break;
        
        case 'e':
            t[i] = 0x00001D452; //text[i] /*- 0x00000065 */ + offset;
            break;
        
        case 'f':
            t[i] = 0x00001D453; //text[i] /*- 0x00000066 */ + offset;
            break;

        case 'g':
            t[i] = 0x00001D454; //text[i] /*- 0x00000067 */ + offset;
            break;

        case 'h':
            t[i] = 0x00001D455; //text[i] /*- 0x00000068 */ + offset;
            break;
        
        case 'i':
            t[i] = 0x00001D456; //text[i] /*- 0x00000069 */ + offset;
            break;
        
        case 'j':
            t[i] = 0x00001D457; //text[i] /*- 0x0000006A */ + offset;
            break;
    
        case 'k':
            t[i] = 0x00001D458; //text[i] /*- 0x0000006B */ + offset;
            break;

        case 'l':
            t[i] = 0x00001D459; //text[i] /*- 0x0000006C */ + offset;
            break;

        case 'm':
            t[i] = 0x00001D45A; //text[i] /*- 0x0000006D */ + offset;
            break;

        case 'n':
            t[i] = 0x00001D45B; //text[i] /*- 0x0000006E */ + offset;
            break;

        case 'o':
            t[i] = 0x00001D45C; //text[i] /*- 0x0000006F */ + offset;
            break;

        case 'p':
            t[i] = 0x00001D45D; //text[i] /*- 0x00000070 */ + offset;
            break;
    
        case 'q':
            t[i] = 0x00001D45E; //text[i] /*- 0x00000071 */ + offset;
            break;

        case 'r':
            t[i] = 0x00001D45F; //text[i] /*- 0x00000072 */ + offset;
            break;

        case 's':
            t[i] = 0x00001D460; //text[i] /*- 0x00000073 */ + offset;
            break;

        case 't':
            t[i] = 0x00001D461; //text[i] /*- 0x00000074 */ + offset;
            break;

        case 'u':
            t[i] = 0x00001D462; //text[i] /*- 0x00000075 */ + offset;
            break;

        case 'v':
            t[i] = 0x00001D463; //text[i] /*- 0x00000076 */ + offset;
            break;

        case 'w':
            t[i] = 0x00001D464; //text[i] /*- 0x00000077 */ + offset;
            break;

        case 'x':
            t[i] = 0x00001D465; //text[i] /*- 0x00000078 */ + offset;
            break;

        case 'y':
            t[i] = 0x00001D466; //text[i] /*- 0x00000079 */ + offset;
            break;
    
        case 'z':
            t[i] = 0x00001D467; //text[i] /*- 0x0000007A */ + offset;
            break;

        default:
            // t[i] = 0x00001D468; //text[i];
            t[i] = utf32[i];//std::uint32_t(reinterpret_cast<char32_t const *>(asInt.data()));
            break;
        }
    }
};

math_shape_desc_t* parse_mathtext_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr;

    std::string text = std::string((char*)node->value(), node->value_size());

    // std::string s0("01D44E");
    // int num0 = std::stoi(s0, 0, 16);
    // // std::string s1("0061");
    // hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);

    // hb_codepoint_t gid0;
    // // hb_codepoint_t gid1;
    // // int num1 = std::stoi(s1, 0, 16);

    // hb_font_get_nominal_glyph(harf_font, num0, &gid0);
    // hb_font_get_nominal_glyph(harf_font, num1, &gid1);


    // for(int i=0; i<desc->n_params; i++) {
    //     desc->params[i].codepoint -= gid1;
    //     desc->params[i].codepoint += gid0;
    
    //     // text[i] = text[i] + num1;
    // }
    uint32_t* t = (uint32_t*)malloc(sizeof(uint32_t)*text.length());
    match_utf32_char_variants(t, text);

    // for(int i=0; i<text.length(); i++) {
    //     // switch(text[i]) {
    //     //     case 'a':
    //     //         t[i] = 0x0001D44E;
    //     //     case 'b':
    //     //         t[i] = 0x0001D44E + 1;
    //     //     case 'c':
    //     //         t[i] = 0x0001D44E + 2;
    //     //     default:
    //     //         t[i] = text[i];
    //     // }
    //     // text[i] = 157;//'𝑎';

    //     // hb_font_get_glyph_from_name(harf_font, "parenleft", 9 , &glyph_index_l);
    //     printf("=============%i\n", text[i]);    
    //     // printf("=============%u\n", text[i]);    
    //     // printf("=============%c\n",  '𝑎');    
    //     // printf("=============%u\n",  '𝑎');    
    //     // printf("=============%lu\n", '𝑎');    
    //     // text[i] = text[i] + num1;
    // }

    
    math_shape_desc_t* desc = parse_utf32(t,text.length(), font);
    return desc;
}

math_shape_desc_t* parse_xml_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr;

    std::string node_type = std::string((char*)node->name(), node->name_size());
    std::cout << "parsing node_type: " << node_type << std::endl;

    if(node_type == "fraction") return parse_fraction_node(node, font);
    if(node_type == "constant") return parse_constant_node(node, font);
    if(node_type == "utf8") return parse_utf8_node(node, font);
    if(node_type == "add") return parse_add_node(node, font);
    if(node_type == "subtract") return parse_subtract_node(node, font);
    if(node_type == "divide") return parse_divide_node(node, font);
    if(node_type == "multiply") return parse_multiply_node(node, font);
    if(node_type == "plus_minus") return parse_plus_minus_node(node, font);
    if(node_type == "greater") return parse_greater_node(node, font);
    if(node_type == "greater_or_equal") return parse_greater_or_equal_node(node, font);
    if(node_type == "less") return parse_less_node(node, font);
    if(node_type == "less_or_equal") return parse_less_or_equal_node(node, font);
    if(node_type == "equal") return parse_equal_node(node, font);
    if(node_type == "different") return parse_different_node(node, font);
    if(node_type == "char") return parse_char_node(node, font);
    if(node_type == "radical") return parse_radical_node(node, font);
    if(node_type == "integral") return parse_integral_node(node, font);
    if(node_type == "mathtext") return parse_mathtext_node(node, font);

    return nullptr;
}

void visit_node(const rapidxml::xml_node<> *node, int indent = 0) {
    if(!node) return;

    printf("node: %.*s\n", node->name_size(), node->name());
    printf("value: %.*s\n", node->value_size(), node->value());

    // for(const rapidxml::xml_attribute<>* a = node->first_attribute(); a; a = a->next_attribute()) {
    //     printf(" %.*s", a->name_size(), a->name());
    //     printf("='%.*s'", a->value_size(), a->value());
    // }

    // printf("\n");

    for(const rapidxml::xml_node<>* n = node->first_node(); n; n = n->next_sibling()) {
        visit_node(n, indent+1);
    }

}

math_shape_desc_t* open_xml(Font* font) {
    rapidxml::xml_document<char> doc;
    std::ifstream theFile ("assets/xml/equation.xml");
    theFile.seekg(0, std::ios::end);
    size_t size = theFile.tellg();
    std::string buffer(size, ' ');
    theFile.seekg(0);
    theFile.read(&buffer[0], size); 
    printf("malloc open xml\n");

    char* buff = (char*)malloc(sizeof(char)*size);
    for(int i=0; i<size; i++) {
        buff[i] = buffer[i];
    }
	// std::cout << buffer << std::endl;
    doc.parse<0>(&buffer[0]);

    math_shape_desc_t* current = nullptr;
    // new math_shape_desc_t();
    // current->n_params = 0;
    // current->params = nullptr;
    // current->x = 0;
    // current->y = 0;
    // current->p0_x = FLT_MAX;
    // current->p0_y = FLT_MAX;
    // current->p1_x = FLT_MIN;
    // current->p1_y = FLT_MIN;

    for(const rapidxml::xml_node<>* n = doc.first_node("equation")->first_node(); n; n = n->next_sibling()) {
        printf("value: %.*s\n", n->value_size(), n->value());
        if(current) {
            math_shape_desc_t* tmp = parse_xml_node(n, font);
            current = concat_math_shape_descs(current, tmp, current->p1_x - tmp->p0_x + tmp->x, 0);
        } else {
            current = parse_xml_node(n, font);
        }
    }

    return current;
}
