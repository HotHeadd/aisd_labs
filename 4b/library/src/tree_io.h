#pragma once

#include "tree.h"
#include <stdio.h>

void print_tree(const Tree* tree);
void traversal(const Tree*, FILE* stream, char*, char*);

void print_found(const Node* found);

void print_gv(Tree*);

int tree_to_txt(const Tree*, const char* filename);
int tree_from_txt(Tree*, const char* filename);