#pragma once

#include "tree.h"

void zig(Node*);
void splay(Tree* tree, Node* elem);
void set_parent(Node* elem, Node* parent);

int find_closest(Tree*);

Node** split(Tree*, char*);
Node* merge(Node*, Node*, Node*);