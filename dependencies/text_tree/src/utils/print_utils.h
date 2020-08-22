#ifndef NODE_T_PRINT_UTILS_H
#define NODE_T_PRINT_UTILS_H

#include<iostream>
#include<stdio.h>

#include "tree.h"

using namespace std;

#define COUNT 9 

void print_2d_util_char(node_t *root, int space)  
{  
    if (root == NULL)  
        return;  
  
    space += COUNT;  
  
    print_2d_util_char(root->right, space);  
  
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
    cout<<root->character<<"\n";  
  
    print_2d_util_char(root->left, space);  
}  


void print_2d_characters(node_t *root)  
{  
    print_2d_util_char(root, 0);  
} 

void print_indices(node_t* root) {
    if(!root) return;
    print_indices(root->left);
    printf("%i ", root->weight);
    print_indices(root->right);
}

void print_characters(node_t* root) {
    if(!root) return;
    print_characters(root->left);
    printf("%c", root->character);
    print_characters(root->right);
}

#endif