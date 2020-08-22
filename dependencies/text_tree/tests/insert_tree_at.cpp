#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "text_tree.h"
#include"assert.h"
#include "string.h"

using namespace text_tree;

int main() {
    node_t* root = nullptr;
    node_t* node_to_insert = nullptr;
    node_t* node_to_insert1 = nullptr;
    node_t* node_to_insert2 = nullptr;

    root = insert_character_at(root, 'a' , 0);
    root = insert_character_at(root, 'b' , 1);
    root = insert_character_at(root, 'c' , 2);
    root = insert_character_at(root, 'd' , 3);

    node_to_insert = insert_character_at(node_to_insert, 'A' , 0);
    node_to_insert = insert_character_at(node_to_insert, 'B' , 1);
    node_to_insert = insert_character_at(node_to_insert, 'C' , 2);

    root = insert_tree_at(root, node_to_insert, 3);

    assert(strcmp(to_string(root, 0, lenght(root) - 1).c_str(), "abcABCd") == 0);

    node_to_insert1 = insert_character_at(node_to_insert1, 'A' , 0);
    node_to_insert1 = insert_character_at(node_to_insert1, 'B' , 1);
    node_to_insert1 = insert_character_at(node_to_insert1, 'C' , 2);
    root = insert_tree_at(root, node_to_insert1, 0);

    assert(strcmp(to_string(root, 0, lenght(root) - 1).c_str(), "ABCabcABCd") == 0);

    node_to_insert2 = insert_character_at(node_to_insert2, 'A' , 0);
    node_to_insert2 = insert_character_at(node_to_insert2, 'B' , 1);
    node_to_insert2 = insert_character_at(node_to_insert2, 'C' , 2);

    root = insert_tree_at(root, node_to_insert2, lenght(root));

    assert(strcmp(to_string(root, 0, lenght(root) - 1).c_str(), "ABCabcABCdABC") == 0);
    
    exit(0);   
}