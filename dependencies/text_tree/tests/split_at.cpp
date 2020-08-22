#include <iostream> 
#include <stdio.h>
#include <stdlib.h>

#include "string.h"
#include "assert.h"
#include "text_tree.h"

using namespace text_tree;

int main() {
    node_t* root = nullptr;

    root = insert_character_at(root, 'a', 0);
    root = insert_character_at(root, 'b', 1);
    root = insert_character_at(root, 'c', 2);
    root = insert_character_at(root, 'd', 3);

    node_t* root0 = nullptr;

    root0 = insert_character_at(root0, 'a', 0);
    root0 = insert_character_at(root0, 'b', 1);
    root0 = insert_character_at(root0, 'c', 2);
    root0 = insert_character_at(root0, 'd', 3);

    node_t* beg = split_at(root, 2);
    node_t* beg0 = split_at(root0, 4);

    assert(strcmp(to_string(beg, 0, lenght(beg) - 1).c_str(), "ab") == 0);
    assert(strcmp(to_string(root, 0, lenght(root) - 1).c_str(), "cd") == 0);
    assert(strcmp(to_string(beg0, 0, lenght(beg0) - 1).c_str(), "abcd") == 0);
    assert(strcmp(to_string(root0, 0, lenght(root0) - 1).c_str(), "") == 0);


    return 0;
}