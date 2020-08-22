#ifndef NODES_FRACTION_H
#define NODES_FRACTION_H

#include "core/desc.h"
#include "core/utf8.h"
#include "core/square.h"

extern math_shape_desc_t* parse_xml_equations_node(const rapidxml::xml_node<> *node, Font* font);


math_shape_desc_t* parse_fraction_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr;

    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);

    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), nullptr);

    const rapidxml::xml_node<>* numerator_node = node->first_node("numerator")->first_node();
    const rapidxml::xml_node<>* denominator_node = node->first_node("denominator")->first_node();

    math_shape_desc_t* numerator_shaped_desc = parse_xml_equations_node(numerator_node, font);
    math_shape_desc_t* denominator_shaped_desc = parse_xml_equations_node(denominator_node, font);

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


    float fraction_bar_extra_width = 1.f;


    float bar_tickness = hb_ot_math_get_constant(harf_font, HB_OT_MATH_CONSTANT_FRACTION_RULE_THICKNESS)/64.f;

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


    concat_math_shape_descs(
        fraction_bar,
        numerator_shaped_desc,
        (frac_b_p1_x + frac_b_p0_x)/2.f - (numerator_shaped_desc->p0_x + numerator_shaped_desc->p1_x)/2.f,
        frac_b_p1_y - numerator_shaped_desc->p0_y + numerator_margin
    );

    concat_math_shape_descs(
        fraction_bar,
        denominator_shaped_desc,
        (frac_b_p1_x + frac_b_p0_x)/2.f - (denominator_shaped_desc->p0_x + denominator_shaped_desc->p1_x)/2.f,
        -1.f*(denominator_shaped_desc->p1_y - frac_b_p0_y + denominator_margin)
    );

    fraction_bar->operations = 1 + numerator_operations + denominator_operationss;

    hb_font_destroy(harf_font);

    return fraction_bar;

}


#endif