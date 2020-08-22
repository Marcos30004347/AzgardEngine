#ifndef NODES_radical_H
#define NODES_radical_H

#include "core/desc.h"
#include "core/square.h"

extern math_shape_desc_t* parse_xml_equations_node(const rapidxml::xml_node<> *node, Font* font);

math_shape_desc_t* parse_root_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 
    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);
    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);

    math_shape_desc_t* radicand = parse_xml_equations_node(node->first_node("radicand")->first_node(), font);
    hb_codepoint_t gid; 

    std::string s("221a");
    int num = std::stoi(s, 0, 16);
    hb_font_get_nominal_glyph(harf_font, num, &gid);

    float extra_ascender =  hb_ot_math_get_constant(harf_font, HB_OT_MATH_CONSTANT_RADICAL_VERTICAL_GAP)/64.f; //* radical->params[0].stretch_y*0.068f;
    math_shape_desc_t* radical = get_math_shape_desc_stretchy(gid, HB_DIRECTION_TTB, radicand->p1_y - radicand->p0_y +  3*extra_ascender, font);
    // translate_math_shape_params(radical, 0.0f, 0.f);
    math_shape_params_t* bar = init_shape_param();

    float extra_width = 0.4f;
    float radicand_kerning = 0.0f;

    float bar_width = radicand->p1_x - radicand->p0_x - radicand_kerning + extra_width;
   
    float bar_height =  hb_ot_math_get_constant(harf_font, HB_OT_MATH_CONSTANT_OVERBAR_RULE_THICKNESS)/64.f; //* radical->params[0].stretch_y*0.068f;

    math_shape_desc_t* over_bar_desc = get_box_desc(bar_width, bar_height);

    // stretch_math_shape_params(over_bar_desc, 1.f, radical->params[0].stretch_y);


    unsigned int radicand_operations = radicand->operations;
    translate_math_shape_params(radical, 0.0f, radicand->p0_y - radical->p0_y);

    float radp1x = radical->p1_x;
    float radp1y = radical->p1_y;

    concat_math_shape_descs(radical, radicand, radical->p1_x - radicand->p0_x - radicand_kerning, radical->p0_y - radicand->p0_y);
    concat_math_shape_descs(radical, over_bar_desc, radp1x - over_bar_desc->p0_x - 0.02f, radp1y - over_bar_desc->p1_y - over_bar_desc->p0_y);

    if(node->first_node("degree")) {
        math_shape_desc_t* degree = parse_xml_equations_node(node->first_node("degree")->first_node(), font);
        //radicalDegreeBottomRaisePercent
        font->get_face()->ascender/64.f;
    
        float v = hb_ot_math_get_constant(harf_font, HB_OT_MATH_CONSTANT_RADICAL_DEGREE_BOTTOM_RAISE_PERCENT)/100.f;
    
        stretch_math_shape_params(degree, 0.6f, 0.6f);
        concat_math_shape_descs(radical, degree, radical->x - 0.1f, radical->p0_y + (v)*(radical->p1_y - radical->p0_y));
    }

    hb_font_destroy(harf_font);

    return radical;
}


#endif