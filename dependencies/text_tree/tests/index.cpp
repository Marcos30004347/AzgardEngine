#include <iostream> 
#include <stdio.h>
#include <stdlib.h>

#include "text_tree.h"

using namespace text_tree;

int main() {
    node_t* root = nullptr;

    root = insert_character_at(root, 'a', 0);
    root = insert_character_at(root, 'b', 1);
    root = insert_character_at(root, 'c', 2);
    root = insert_character_at(root, 'd', 3);

    if(
        index(root, 0) == 'a'
    &&  index(root, 1) == 'b'
    &&  index(root, 2) == 'c'
    &&  index(root, 3) == 'd'
    ) {
        exit(0);
    }

    exit(1);
}