#ifndef NODES_MATHTEXT_H
#define NODES_MATHTEXT_H

#include "core/desc.h"
#include "core/utf32.h"
#include "maps/math-alphabet.h"



math_shape_desc_t* parse_mathtext_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr;

    std::string text = std::string((char*)node->value(), node->value_size());

    const rapidxml::xml_attribute<char> * features = node->first_attribute("features");
    
    const char* feats = "kern 1 0 -1 liga 1 0 -1";

    if(features) {
        feats = std::string(features->value(), features->value_size()).c_str();

    }

    uint32_t* t = (uint32_t*)malloc(sizeof(uint32_t)*text.length());

    match_utf32_char_variants(t, text);

    math_shape_desc_t* desc = parse_utf32(t,text.length(), font, feats);
    return desc;
}


#endif