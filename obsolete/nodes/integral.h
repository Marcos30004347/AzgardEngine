#ifndef NODES_INTEGRAL_H
#define NODES_INTEGRAL_H

#include "core/desc.h"
#include "core/utf8.h"

extern math_shape_desc_t* parse_xml_equations_node(const rapidxml::xml_node<> *node, Font* font);


math_shape_desc_t* parse_integral_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 
    printf("kkkkk\n");

    FT_Set_Char_Size(font->get_face(), 64, 64, 0, 0);
    const rapidxml::xml_attribute<char> * style = node->first_attribute("style");

    hb_codepoint_t integral_glyph_id;
    hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);
    hb_font_get_nominal_glyph(harf_font, std::stoi("222b", 0, 16), &integral_glyph_id);


    float integral_height = 2.346000f;

    math_shape_desc_t* int_shape_desc = get_math_shape_desc_stretchy(integral_glyph_id, HB_DIRECTION_BTT, integral_height, font, 0.0f);

    float advance_x = 0.0f;
    math_shape_desc_t* from = nullptr;
    math_shape_desc_t* to = nullptr;

    if(node->first_node("from"))
        from = parse_xml_equations_node(node->first_node("from")->first_node(), font);

    if(node->first_node("to"))
        to = parse_xml_equations_node(node->first_node("to")->first_node(), font);

    float script_scale = 0.5f;

    if(from || to) {

        stretch_math_shape_params(from, script_scale, script_scale);
        stretch_math_shape_params(to, script_scale, script_scale);

        float y0 = 0.0f, x0 = 0.0f;
        float y1 = 0.0f, x1 = 0.0f;

        if(style) {
            std::string value(style->value(), style->value_size());
            if(value == "german" || value == "russian") {

                y0 += to->p1_y - to->p0_y + 0.2f;
                y1 -= from->p1_y - from->p0_y + 0.2f;


                x0 -= (to->p1_x - to->p0_x)*0.5f + 0.1f;
                x1 -= (from->p1_x - from->p0_x)*0.5f + 0.2f;


                advance_x = int_shape_desc->p1_x;
                
            } else {
                y0 += to->p1_y - to->p0_y - 0.2f;
                x0 += 0.1f;
                x1 += 0.1f;
            }
        }
    printf("kkkkk\n");

        script_shape_desc(int_shape_desc, to, from, font, 1.0f, y0, y1, x0, x1); 
    }

    printf("kkkkk\n");

    math_shape_desc_t* equation =  parse_xml_equations_node(node->first_node("function")->first_node(), font);
    advance_x = 0.1f;

    float x =  int_shape_desc->p1_x - equation->p0_x + advance_x;

    concat_math_shape_descs(int_shape_desc, equation, x, int_shape_desc->y);
    
    float italic_correction = hb_ot_math_get_glyph_italics_correction (harf_font, integral_glyph_id)/64.f;
    
    translate_math_shape_params(int_shape_desc, -1*italic_correction, 0.0f);

    return int_shape_desc;
}


#endif