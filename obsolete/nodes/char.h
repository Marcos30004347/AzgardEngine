#ifndef NODES_CHAR_H
#define NODES_CHAR_H

#include "core/desc.h"
#include "core/utf8.h"

extern math_shape_desc_t* parse_xml_equations_node(const rapidxml::xml_node<> *node, Font* font);

math_shape_desc_t* parse_char_node(const rapidxml::xml_node<> *node, Font* font) {
    std::string s(node->first_attribute("code")->value(), node->first_attribute("code")->value_size());
    
    int num = std::stoi(s, 0, 16);
    
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
    std::string u8str = converter.to_bytes(num);

    math_shape_desc_t* desc = parse_utf8(u8str, font);

    if(node->first_node("superscript") || node->first_node("subscript")) {
        math_shape_desc_t* superscript =  parse_xml_equations_node(node->first_node("superscript")->first_node(), font);
    
        math_shape_desc_t* subscript =  parse_xml_equations_node(node->first_node("subscript")->first_node(), font);
    
        float scale = std::max(superscript->p1_y - superscript->p0_y, subscript->p1_y - subscript->p0_y);
    
        script_shape_desc(desc, superscript, subscript ,font, (desc->p1_y - desc->p0_y)/(2.3*scale), -0.3f, -0.3f); 
    
    }
    return desc;
}


#endif