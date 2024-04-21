#pragma once

#include "tree.h"
#include <stdio.h>

void print_tree(const Node* root, const int);
void traversal(const Node*, FILE* stream, int);

void print_found(const Node* found);

void print_gv(Node* root);

int tree_to_txt(const Node* root, const char* filename);
int tree_from_txt(Node** root, const char* filename);