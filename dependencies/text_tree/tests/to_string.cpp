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

    assert(strcmp(to_string(root, 0, 1).c_str(), "ab") == 0);
    assert(strcmp(to_string(root, 0, 3).c_str(), "abcd") == 0);

    return 0;
}