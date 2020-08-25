#ifndef NODES_MULTIPLY_H
#define NODES_MULTIPLY_H

#include "core/desc.h"
#include "core/utf8.h"

extern math_shape_desc_t* parse_xml_equations_node(const rapidxml::xml_node<> *node, Font* font);

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

    const rapidxml::xml_node<>* first_part = node->first_node();

    math_shape_desc_t* tmp = parse_xml_equations_node(first_part, font);

    if(should_surround(first_part) && tmp->operations > 1) {
        hb_codepoint_t glyph_index_l;
        hb_codepoint_t glyph_index_r;
        hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);
        hb_font_get_glyph_from_name(harf_font, "parenleft", 9 , &glyph_index_l);
        hb_font_get_glyph_from_name(harf_font, "parenright", 10 , &glyph_index_r);
        surround_shape_desc_horizontal(glyph_index_l, glyph_index_r, tmp, font);
    }

    for(const rapidxml::xml_node<>* n = first_part->next_sibling(); n; n = n->next_sibling()) {
    
        math_shape_desc_t* midle_shaped_desc = nullptr;

        if(style) {
            std::string value(style->value(), style->value_size());
            if(value == "dot") {
                midle_shaped_desc = parse_utf8("\u00A0\u22c5\u00A0", font);
            } else if(value == "cross") {
                midle_shaped_desc = parse_utf8(" \u00D7 ", font);
            } else if(value == "none"){
                midle_shaped_desc = nullptr;
            } else {
                midle_shaped_desc = parse_utf8("\u00A0\u22c5\u00A0", font);
            }
        } else {
            midle_shaped_desc = parse_utf8("\u00A0\u22c5\u00A0", font);
        }
    

        math_shape_desc_t* end_shaped_desc = parse_xml_equations_node(n, font);
        
        if(should_surround(n) && end_shaped_desc->operations > 1) {
            hb_codepoint_t glyph_index_l;
            hb_codepoint_t glyph_index_r;
        
            hb_font_t* harf_font = hb_ft_font_create (font->get_face(), NULL);
            hb_font_get_glyph_from_name(harf_font, "parenleft", 9 , &glyph_index_l);
            hb_font_get_glyph_from_name(harf_font, "parenright", 10 , &glyph_index_r);
        
            surround_shape_desc_horizontal(glyph_index_l, glyph_index_r, end_shaped_desc, font);
        }

        float advance = 0.0f;
    
        if(midle_shaped_desc) {
            concat_math_shape_descs(tmp, midle_shaped_desc, tmp->p1_x - midle_shaped_desc->p0_x, tmp->y - midle_shaped_desc->y);
        } else {
            advance = 0.1f;
        }
    
        concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x + advance, tmp->y - end_shaped_desc->y);
    }

    return tmp;
}

#endif