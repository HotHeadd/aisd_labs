#pragma once

#include "tree.h"
#include <stdio.h>

void print_tree(const Node* root, const int);
void traversal(const Node*, FILE* stream);

void print_found(const Node* found);

int tree_to_txt(const Node* root, const char* filename);
int tree_from_txt(Node** root, const char* filename);