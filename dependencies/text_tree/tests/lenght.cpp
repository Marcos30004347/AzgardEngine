#include <iostream> 
#include <stdio.h>
#include <stdlib.h>

#include"assert.h"
#include "text_tree.h"

using namespace text_tree;

int main() {
    node_t* root = nullptr;

    assert(lenght(root) == 0);

    root = insert_character_at(root, 'a', 0);
    root = insert_character_at(root, 'b', 1);
    root = insert_character_at(root, 'c', 2);
    root = insert_character_at(root, 'd', 3);

    assert(lenght(root) == 4);

    return 0;
}