#pragma once

#include <stdio.h>
#include "tree.h"

void zig(Node*);
void splay(Tree* tree, Node* elem);

int find_closest(Tree*);

int split(Tree*, Node*);
int merge(Tree*, Tree*, Node*);