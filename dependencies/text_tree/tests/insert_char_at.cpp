#include <iostream> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "text_tree.h"
#include"assert.h"

using namespace text_tree;

int main() {
    node_t* root = nullptr;

    root = insert_character_at(root, 'a' , 0);
    root = insert_character_at(root, 'b' , 1);
    root = insert_character_at(root, 'c' , 2);
    root = insert_character_at(root, 'd' , 3);

    assert(strcmp(to_string(root, 0, lenght(root) - 1).c_str(), "abcd") == 0);

    root = insert_character_at(root, 'A' , 0);
    root = insert_character_at(root, 'A' , 3);
    assert(strcmp(to_string(root, 0, lenght(root) - 1).c_str(), "AabAcd") == 0);
    
    return 0;   
}