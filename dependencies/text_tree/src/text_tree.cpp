#include<string.h>
#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>


#include"text_tree.h"

using namespace text_tree;

void update_weight(node_t* node) {
    if(!node) return;

    if(node->left) {
        node->weight = node->left->weight + 1;

        if(node->left->right) {
            node_t* tmp =  node->left->right;
            while(tmp) {
                node->weight += tmp->weight + 1;
                tmp = tmp->right;
            }
        }
    }
    else {
        node->weight = 0;
    }
}


void update_heights(node_t* node) {
    if(!node) return;

    int lh = node->left ? node->left->height : -1;
    int rh = node->right ? node->right->height : -1;

    node->height = 1 + std::max(lh, rh);
}



node_t* left_rotate(node_t* A) {
    node_t* P = A->parent;
    node_t* B = A->right;

    A->right = B->left;

    if(B->left) B->left->parent = A;

    B->left = A;
    A->parent = B;
    B->parent = P;

    if(P) {
        if(P->left == A) P->left = B;
        else P->right = B;
    }


    update_weight(A);
    update_heights(A);

    update_weight(B);
    update_heights(B);

    return B;
}


node_t* right_rotate(node_t* A) {
    node_t* P = A->parent;
    node_t* B = A->left;

    A->left = B->right;
    if(B->right) B->right->parent = A;

    B->right = A;
    A->parent = B;
    B->parent = P;

    if(P) {
        if(P->left == A) P->left = B;
        else P->right = B;
    }

    update_weight(A);
    update_heights(A);

    update_weight(B);
    update_heights(B);

    return B;
}


int get_height(node_t* node) {
    return (node ? node->height + 1: 0);
}

node_t* balance(node_t* node) {
    if(!node) return node;

    int balance = get_height(node->left) - get_height(node->right);

    if(balance > 1) {
        if(get_height(node->left->left) >= get_height(node->left->right)) {
            return right_rotate(node);
        } else {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
    }

    if(balance < -1) {
        if(get_height(node->right->right) >= get_height(node->right->left)) {
           return left_rotate(node);
        } else {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }
    }

    return node;
}


node_t* balance_tree(node_t* node) {
    if(!node) return nullptr;
    balance_tree(node->left);
    balance_tree(node->right);
    return balance(node);
}

node_t* update(node_t* node) {
    update_heights(node);
    node = balance(node);
    update_weight(node);
    return node;
}

node_t* text_tree::append_tree_left(node_t* node0, node_t* node1) {
    if(!node0) return node1;

    if(node0->left) {
        text_tree::append_tree_left(node0->left, node1);
    } else {
        node0->left = node1;
        if(node1) node1->parent = node0;
    }

    return update(node0);
}

node_t* text_tree::append_tree_right(node_t* node0, node_t* node1) {
    if(!node0) return node1;

    if(node0->right) {
        text_tree::append_tree_right(node0->right, node1);
    } else {
        node0->right = node1;
        if(node1) node1->parent = node0;
    }

    return update(node0);
}

node_t* _insert_tree_at(node_t* node, node_t* to_insert, unsigned int weight, node_t* parent) {
    if(!node) {
        // insert new leaf
        to_insert->parent = parent;
        return update(to_insert);

    } else if(node->weight + 1 == weight) {
        node_t* tmp = node->left;
        node->left = to_insert;
        to_insert->parent = node;

        if(tmp) {
            // MAYBE THERE IS A BETTER WAY TO APPEND_tree_left
            append_tree_left(to_insert, tmp);
        }
    
    } else if(node->weight + 1 < weight) {
        node->right = _insert_tree_at(node->right, to_insert, weight - node->weight - 1, node);
    } else {
        node->left = _insert_tree_at(node->left, to_insert, weight, node);
    }

    return update(node);
}

node_t* text_tree::insert_tree_at(node_t* node, node_t* to_insert, unsigned int weight,  node_t* parent) {
    return _insert_tree_at(node, to_insert, weight + 1, parent);
}


node_t* _insert_character_at(node_t* node, char c, unsigned int weight, node_t* parent) {
    if(!node) {
        // insert new leaf
        node_t* t = new node_t(c);
        t->parent = parent;
        return t;
    } else if(node->weight + 1 == weight) {
        // implace insert
        node_t* tmp = new node_t(c);
        tmp->parent = node;

        if(node->left) {
            tmp->left = node->left;
            node->left->parent = tmp;
        }

        node->left = tmp;
    
        tmp = update(tmp);
    } else if(node->weight + 1 < weight) {
        node->right = _insert_character_at(node->right, c, weight - node->weight - 1, node);
    } else {
        node->left = _insert_character_at(node->left, c, weight, node);
    }

    node = update(node);
    return node;
}

node_t* text_tree::insert_character_at(node_t* node, char c, unsigned int weight, node_t* parent) {
    return _insert_character_at(node, c, weight + 1, parent);
}

node_t* text_tree::insert_characters_at(node_t* node, const char* to_insert, unsigned int weight) {
    node_t* node_to_insert = nullptr;
    for(int i=0; i<strlen(to_insert); i++) {
        node_to_insert = text_tree::insert_character_at(node_to_insert, to_insert[i], i);
    }

    return text_tree::insert_tree_at(node, node_to_insert, weight);
}


node_t* _remove_character_at(node_t* & node, unsigned int weight) {
    if(!node) {
       return nullptr;
    } else if(node->weight + 1 == weight) {
        // implace insert
        node_t* root = nullptr;

        if(node->right) {
            root = node->right;
            root = text_tree::append_tree_left(root, node->left);
            root->parent = node->parent;
        } else if(node->left) {
            root = node->left;
            root->parent = node->parent;
        }

        if(node->parent) {
            if(node->parent->left == node) {
                node->parent->left = root;
            }
            else {
                node->parent->right = root;
            }
        } 

        return root;
    } else if(node->weight + 1 < weight) {
        _remove_character_at(node->right, weight - node->weight - 1);
    } else {
        _remove_character_at(node->left, weight);
    }

    return update(node);
}



node_t* text_tree::remove_character_at(node_t* node, unsigned int weight) {
    return _remove_character_at(node, weight + 1);
}

node_t* text_tree::split_at(node_t* &node, unsigned int weight) {
    if(!node) {
       return nullptr;
    } else if(node->weight + 1 <= weight) {
        int _w = node->weight;

        node_t* deleted_node = node;
        node_t* node_right = node->right;

        if(node->right) {
            node->right->parent = node->parent;
        }
    
        if(node->parent) {
            if(node->parent->left == node) {
                node->parent->left = node->right;
            } else {
                node->parent->right = node->right;
            }
        }

        deleted_node->right = nullptr;
        deleted_node->parent = nullptr;
    
        if(node_right) {
            node = node_right;
        }

        if(!node || !node->right) {
            node = nullptr;
        }
    
        node_t* tmp = text_tree::append_tree_right(deleted_node, text_tree::split_at(node_right, weight - _w - 1));;
        
        node = node_right;

        return tmp;
    }

    node_t* tmp = text_tree::split_at(node->left, weight);
    node = update(node);

    return tmp;
}

char _index(node_t* node, unsigned int i) {
    if(node->weight + 1 == i) return node->character;
    else if(node->weight + 1 < i) return _index(node->right, i - node->weight - 1);
    else return _index(node->left, i);
}

char text_tree::index(node_t* node, unsigned int i) {
    return _index(node, i + 1);
}


node_t* text_tree::remove_characters_between(node_t* &node, unsigned int i, unsigned int j) {
    node_t* first_part = split_at(node, i);
    text_tree::split_at(node, j - i + 1);
    return text_tree::append_tree_left(node, first_part);
}

node_t* text_tree::subtree(node_t* node, unsigned int i, unsigned int j) {
    text_tree::split_at(node, i);
    return text_tree::split_at(node, j - i + 1);
}

void _stream_section(node_t* node, std::stringstream& stream, int start, int end) {
    if(!node) {
        return;
    }
    if( node->weight+1 >= start) {
        _stream_section(node->left, stream,  start, end);
    }
    if(node->weight+1 >= start &&  end - node->weight - 1 >= 0) {
        stream << node->character;
    }

    if( end - node->weight - 1 >= 0) {
        _stream_section(node->right, stream,  start - node->weight - 1, end - node->weight - 1);
    }

}

void text_tree::stream_section(node_t* node, std::stringstream& stream, int start, int end) {
    _stream_section(node, stream, start+1, end+1);
}

size_t text_tree::lenght(node_t* node) {
    if(!node) return 0;
    
    return node->weight + 1 + text_tree::lenght(node->right);
}


std::string text_tree::to_string(node_t* node, int start, int end) {
    std::stringstream stream;

    text_tree::stream_section(node, stream, start, end);

    return stream.str();
}
