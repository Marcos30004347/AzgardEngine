#ifndef NODES_POWER_H
#define NODES_POWER_H

#include "core/desc.h"
#include "core/utf8.h"

extern math_shape_desc_t* parse_xml_equations_node(const rapidxml::xml_node<> *node, Font* font);

math_shape_desc_t* parse_power_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 

    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);

    hb_codepoint_t integral_glyph_id;
    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);
    float script_scale = 0.5f;


    math_shape_desc_t* expoent =  parse_xml_equations_node(node->first_node("expoent")->first_node(), font);

    math_shape_desc_t* base =  parse_xml_equations_node(node->first_node("base")->first_node(), font);

    stretch_math_shape_params(expoent, 0.6f, 0.6f);

    script_shape_desc(base, expoent, nullptr, font, 1.0f, (expoent->p1_y - expoent->p0_y) - 0.2f, 0.0f, 0.1f);

    return base;
}


#endif