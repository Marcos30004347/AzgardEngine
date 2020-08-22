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

    root = insert_character_at(root, 'a', 0);
    root = insert_character_at(root, 'b', 1);
    root = insert_character_at(root, 'c', 2);
    root = insert_character_at(root, 'd', 3);

    root0 = insert_character_at(root0, 'A', 0);
    root0 = insert_character_at(root0, 'B', 1);
    root0 = insert_character_at(root0, 'C', 2);
    root0 = insert_character_at(root0, 'D', 3);

    root = append_tree_right(root, root0);

    assert(strcmp(to_string(root, 0, lenght(root) - 1).c_str(), "abcdABCD") == 0);

    return 0;
}