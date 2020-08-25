//std
#include <sstream>
#include <fstream>

//core
#include "core/desc.h"

//nodes
#include "add.h"
#include "subtract.h"
#include "multiply.h"
#include "mathtext.h"
#include "constant.h"
#include "fraction.h"
#include "greater.h"
#include "greater-or-equal.h"
#include "less.h"
#include "less-or-equal.h"
#include "pluss-minus.h"
#include "utf8.h"
#include "utf16.h"
#include "utf32.h"
#include "divide.h"
#include "equal.h"
#include "different.h"
#include "divide.h"
#include "char.h"
#include "root.h"
#include "subtract.h"
#include "integral.h"
#include "power.h"


math_shape_desc_t* parse_xml_equations_node(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr;

    std::string node_type = std::string((char*)node->name(), node->name_size());
    std::cout << "parsing node_type: " << node_type << std::endl;

    if(node_type == "fraction") return parse_fraction_node(node, font);
    if(node_type == "constant") return parse_constant_node(node, font);
    if(node_type == "utf8") return parse_utf8_node(node, font);
    if(node_type == "add") return parse_add_node(node, font);
    if(node_type == "subtract") return parse_subtract_node(node, font);
    if(node_type == "divide") return parse_divide_node(node, font);
    if(node_type == "multiply") return parse_multiply_node(node, font);
    if(node_type == "plus_minus") return parse_plus_minus_node(node, font);
    if(node_type == "greater") return parse_greater_node(node, font);
    if(node_type == "greater_or_equal") return parse_greater_or_equal_node(node, font);
    if(node_type == "less") return parse_less_node(node, font);
    if(node_type == "less_or_equal") return parse_less_or_equal_node(node, font);
    if(node_type == "equal") return parse_equal_node(node, font);
    if(node_type == "different") return parse_different_node(node, font);
    if(node_type == "char") return parse_char_node(node, font);
    if(node_type == "root") return parse_root_node(node, font);
    if(node_type == "integral") return parse_integral_node(node, font);
    if(node_type == "mathtext") return parse_mathtext_node(node, font);
    if(node_type == "power") return parse_power_node(node, font);

    return nullptr;
}

math_shape_desc_t* parse_xml_text_nodes(const rapidxml::xml_node<> *node, Font* font) {
    if(!node) return nullptr;

    std::string node_type = std::string((char*)node->name(), node->name_size());
    std::cout << "parsing node_type: " << node_type << std::endl;

    if(node_type == "utf8") return parse_utf8_node(node, font);
    if(node_type == "utf16") return parse_utf16_node(node, font);
    if(node_type == "utf32") return parse_utf32_node(node, font);
    if(node_type == "mathtext") return parse_mathtext_node(node, font);

    return nullptr;
}

math_shape_desc_t* parse_equation(const rapidxml::xml_node<> *node, Font* font) {

    math_shape_desc_t* current = nullptr;
    
    for(const rapidxml::xml_node<>* n = node->first_node(); n; n = n->next_sibling()) {
        if(current) {
            printf("ala\n");
            
            math_shape_desc_t* tmp = parse_xml_equations_node(n, font);
            current = concat_math_shape_descs(current, tmp, current->p1_x - tmp->p0_x + tmp->x, 0);
        } else {
            current = parse_xml_equations_node(n, font);
        }
    }
    return current;
}

math_shape_desc_t* parse_text(const rapidxml::xml_node<> *node, Font* font) {

    math_shape_desc_t* current = nullptr;
    
    for(const rapidxml::xml_node<>* n = node->first_node(); n; n = n->next_sibling()) {
        if(current) {
            printf("ala\n");
            math_shape_desc_t* tmp = parse_xml_text_nodes(n, font);
            current = concat_math_shape_descs(current, tmp, current->p1_x - tmp->p0_x + tmp->x, 0);
        } else {
            
            current = parse_xml_text_nodes(n, font);
        }
    }
    return current;
}


math_shape_desc_t* open_xml(Font* font) {
    rapidxml::xml_document<char> doc;
    std::ifstream theFile ("assets/xml/equation.xml");
    theFile.seekg(0, std::ios::end);
    size_t size = theFile.tellg();
    std::string buffer(size, ' ');
    theFile.seekg(0);
    theFile.read(&buffer[0], size); 

    char* buff = (char*)malloc(sizeof(char)*size);
    for(int i=0; i<size; i++) {
        buff[i] = buffer[i];
    }

    doc.parse<0>(&buffer[0]);


    math_shape_desc_t* current = nullptr;

    for(const rapidxml::xml_node<>* n = doc.first_node(); n; n = n->next_sibling()) {
        std::string node_type = std::string((char*)n->name(), n->name_size());

        if(node_type == "Equation") {
            if(current) {
                math_shape_desc_t* tmp = parse_equation(n, font);
                concat_math_shape_descs(current, tmp, current->p1_x - tmp->p0_x + tmp->x, 0);
            } else {

                current = parse_equation(n, font);
            }
        } else if(node_type == "Text") {
            if(current) {
                math_shape_desc_t* tmp = parse_text(n, font);
                concat_math_shape_descs(current, tmp, current->p1_x - tmp->p0_x + tmp->x, 0);
            } else {

                current = parse_text(n, font);
            }
        }
        
        // if(current) {
        //     math_shape_desc_t* tmp = parse_xml_node(n, font);
        //     current = concat_math_shape_descs(current, tmp, current->p1_x - tmp->p0_x + tmp->x, 0);
        // } else {
        //     current = parse_xml_node(n, font);
        // }
    }
    printf("end parsing\n");
    return current;
}
