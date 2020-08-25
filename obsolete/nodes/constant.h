#ifndef NODES_constant_H
#define NODES_constant_H

#include "core/desc.h"
#include "core/utf8.h"


math_shape_desc_t* parse_constant_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr; 
    std::string number(node->first_attribute("value")->value(), node->first_attribute("value")->value_size());
    return parse_utf8(number, font);
}



#endif