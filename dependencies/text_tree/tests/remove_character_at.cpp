#include <iostream> 
#include <stdio.h>
#include <stdlib.h>

#include "string.h"
#include "assert.h"
#include "text_tree.h"

using namespace text_tree;

int main() {
    node_t* root = nullptr;
    node_t* root0 = nullptr;
    node_t* root1 = nullptr;

    root = insert_character_at(root, 'a', 0);
    root = insert_character_at(root, 'b', 1);
    root = insert_character_at(root, 'c', 2);
    root = insert_character_at(root, 'd', 3);

    root0 = insert_character_at(root0, 'a', 0);
    root0 = insert_character_at(root0, 'b', 1);
    root0 = insert_character_at(root0, 'c', 2);
    root0 = insert_character_at(root0, 'd', 3);

    root1 = insert_character_at(root1, 'a', 0);
    root1 = insert_character_at(root1, 'b', 1);
    root1 = insert_character_at(root1, 'c', 2);
    root1 = insert_character_at(root1, 'd', 3);

    root = remove_character_at(root, 1);
    root0 = remove_character_at(root0, 0);
    root1 = remove_character_at(root1, 3);

    assert(strcmp(to_string(root, 0, lenght(root) - 1).c_str(), "acd") == 0);
    assert(strcmp(to_string(root0, 0, lenght(root0) - 1).c_str(), "bcd") == 0);
    assert(strcmp(to_string(root1, 0, lenght(root1) - 1).c_str(), "abc") == 0);

    return 0;
}