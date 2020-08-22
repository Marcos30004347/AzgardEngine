#ifndef NODES_UTF8_H
#define NODES_UTF8_H

#include<string>

#include "core/desc.h"
#include "core/utf8.h"


math_shape_desc_t* parse_utf8_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr;

    const rapidxml::xml_attribute<char> * features = node->first_attribute("features");
    
    const char* feats = "kern 1 0 -1 liga 1 0 -1";

    if(features) {
        feats = std::string(features->value(), features->value_size()).c_str();

    }

    std::string text = std::string((char*)node->value(), node->value_size());
    math_shape_desc_t* desc = parse_utf8(text, font, feats);

    return desc;
}


#endif