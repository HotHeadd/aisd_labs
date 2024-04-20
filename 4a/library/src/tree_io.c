#include <stdio.h>
#include <stdlib.h>
#include <graphviz/gvc.h>
#include "tree.h"
#include "tree_io.h"
#include "basic.h"

void put_data(const Node* root, FILE* stream){
    fprintf(stream, "{%s}: [", root->key);
    info_t* elem = root->info;
    int start = 1;
    while (elem != NULL){
        if (start) start -= 1;
        else fprintf(stream, ", ");
        fprintf(stream, "%u", elem->value);
        elem = elem->next;
    }
    fprintf(stream, "]\n");
    return;
}

void print_tree(const Node* root, const int level){
    if (level == 0) printf("Здравствуйте, ваше дерево:\n");
    if (root == NULL){
        if (level != 0){
            for (int i = 0; i < level; i++)
                printf(i == level - 1 ? "|->\n" : "    ");
        }
        return;
    }
    for (int i = 0; i < level; i++)
        printf(i == level - 1 ? "|-> " : "    ");
    put_data(root, stdout);
    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);
}

void traversal(const Node* root, FILE* stream){
    if (root->right != NULL)
        traversal(root->right, stream);
    put_data(root, stream);
    if (root->left != NULL)
        traversal(root->left, stream);
}

void print_found(const Node* found){
    printf("Найденный элемент: ");
    put_data(found, stdout);
    return;
}

int txt_out_rec(const Node* root, const char* filename){
    if (root == NULL) return NO_TREE;
    FILE* output = fopen(filename, "a");
    info_t* elem = root->info;
    elem = root->info;
    while (elem != NULL){
        fprintf(output, "%s\n", root->key);
        fprintf(output, "%d\n", elem->value);
        elem = elem->next;
    }
    fclose(output);
    txt_out_rec(root->left, filename);
    txt_out_rec(root->right, filename);
    return GOOD;
}

int tree_to_txt(const Node* root, const char* filename){
    FILE* output = fopen(filename, "w");
    if (output == NULL) return FILE_ERROR;
    fclose(output);
    return txt_out_rec(root, filename);
}

int tree_from_txt(Node** root, const char* filename){
    free_tree(*root);
    *root = NULL;
    FILE* input = fopen(filename, "r");
    if (input == NULL) return FILE_ERROR;
    char* key;
    unsigned info;
    int count = 0;
    int res = 0;
    while ((key = file_readline(input)) != NULL){
        res = fscanf(input, "%u", &info);
        if (res == 0){
            free_tree(*root);
            return FILE_ERROR;
        }
        if (insert(root, key, info) == KEY_EXIST) free(key);
        fscanf(input, "%*c");
    }
    fclose(input);
    return GOOD;
}

void print_gv(Node* root){
    // %20 space
    // %7B {
    // %7D }
    // -%3E ->
    // %22 "
    char* link = "https://dotrend.dozen.mephi.ru/?dot=digraph%20G%20%7B";
    char* example = "https://dotrend.dozen.mephi.ru/?dot=digraph%20G%20%7B%22A%20asd%22-%3EB%7D";
    char* end = "%7D";
    printf("%s\n", example);

    // #define NO_LAYOUT_OR_RENDERING
    
    // int main(void) {
    // #ifndef NO_LAYOUT_OR_RENDERING
    // // set up a graphviz context - but only once even for multiple graphs
    // GVC_t *gvc = gvContext();
    // #endif

    // // Create a simple digraph
    // Agraph_t *g = agopen("g", Agdirected, 0);
    // Agnode_t *n = agnode(g, "n", 1);
    // Agnode_t *m = agnode(g, "m", 1);
    // Agedge_t *e = agedge(g, n, m, 0, 1);

    // // Set an attribute - in this case one that affects the visible rendering
    // agsafeset(n, "color", "red", "");

    // #ifdef NO_LAYOUT_OR_RENDERING
    // // Just write the graph without layout
    // agwrite(g, stdout);
    // #else
    // // Use the directed graph layout engine
    // gvLayout(gvc, g, "dot");

    // // Output in .dot format
    // gvRender(gvc, g, "dot", stdout);

    // gvFreeLayout(gvc, g);
    // #endif

    // agclose(g);

    // return EXIT_SUCCESS;
    // }
    return;
}