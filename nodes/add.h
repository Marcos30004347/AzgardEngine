#ifndef NODES_ADD_H
#define NODES_ADD_H

#include "core/desc.h"
#include "core/utf8.h"

extern math_shape_desc_t* parse_xml_equations_node(const rapidxml::xml_node<> *node, Font* font);



math_shape_desc_t* parse_add_node(const rapidxml::xml_node<> *node, Font* font) {
    const rapidxml::xml_node<> *first_node = node->first_node();

    math_shape_desc_t* tmp = parse_xml_equations_node(first_node, font);


    for(const rapidxml::xml_node<>* n = first_node->next_sibling(); n; n = n->next_sibling()) {
    
        math_shape_desc_t* add_shape_desc = parse_utf8(" + ", font);
        math_shape_desc_t* end_shaped_desc = parse_xml_equations_node(n, font);

        concat_math_shape_descs(tmp, add_shape_desc, tmp->p1_x - add_shape_desc->p0_x, tmp->y);
        concat_math_shape_descs(tmp, end_shaped_desc, tmp->p1_x - end_shaped_desc->p0_x, tmp->y);
    }

    return tmp;
}

#endif