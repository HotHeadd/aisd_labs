#pragma once

#include "tree.h"

void print_tree(const Node* root, const int);
void print_found(Node* found);
int tree_to_txt(const Node* root, const char* filename);
int tree_from_txt(Node** root, const char* filename);