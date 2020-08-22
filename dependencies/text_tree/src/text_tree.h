#ifndef NODE_T_H
#define NODE_T_H

#include<sstream>

namespace text_tree {
/**
 * Main structure of the tree.
**/
struct node_t {
    node_t *left, *right, *parent;
    
    int weight;
    int height;

    char character;

    node_t() {
        left = right = parent = nullptr;
        weight = 0;
        height = 0;
        character = '\0';
    }

    node_t(char c) {
        left = right = parent = nullptr;
        height = 0; 
        weight = 0;

        character = c;
    }
};

/**
 * Return character at index.
**/
char index(node_t* node, unsigned int i);

/**
 * Append tree to the left of another tree.
**/
node_t* append_tree_left(node_t* node0, node_t* node1);

/**
 * Append tree to the right of another tree.
**/
node_t* append_tree_right(node_t* node0, node_t* node1);

/**
 * Insert tree inside another tree at index.
**/
node_t* insert_tree_at(node_t* node, node_t* to_insert, unsigned int index,  node_t* parent = nullptr);

/**
 * Insert character at index.
**/
node_t* insert_character_at(node_t* node, char c, unsigned int index, node_t* parent = nullptr);

/**
 * Insert string at index.
**/
node_t* insert_characters_at(node_t* node, const char* to_insert, unsigned int index);

/**
 * Remove character at index.
**/
node_t* remove_character_at(node_t* node, unsigned int index);

/**
 * Remove character between two indices.
**/
node_t* remove_characters_between(node_t* &node, unsigned int i, unsigned int j);

/**
 * Return a subtree that is contained between two indices.
**/
node_t* subtree(node_t* node, unsigned int i, unsigned int j);

/**
 * Split the current tree in to two,
 * return the first half and set the node to be the second half.
**/
node_t* split_at(node_t* &node, unsigned int index);

/**
* Insert in the stream the string delimited by start and end.
**/
void stream_section(node_t* node, std::stringstream& stream, int start, int end);

/**
* Return the string string delimited by start and end.
**/
std::string to_string(node_t* node, int start, int end);

/**
 * Return the number of characters inside the tree
 **/
size_t lenght(node_t* node);

};


#endif