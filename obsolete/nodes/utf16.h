#ifndef NODES_UTF16_H
#define NODES_UTF16_H

#include<string>

#include "core/desc.h"
#include "core/utf16.h"


math_shape_desc_t* parse_utf16_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr;

    const rapidxml::xml_attribute<char> * features = node->first_attribute("features");
    
    const char* feats = "kern 1 0 -1 liga 1 0 -1";

    if(features) {
        feats = std::string(features->value(), features->value_size()).c_str();

    }
    std::u16string text = std::u16string((char16_t*)node->value(), node->value_size());

    math_shape_desc_t* desc = parse_utf16((uint16_t*)&text[0], text.length() , font, feats);

    return desc;
}


#endif