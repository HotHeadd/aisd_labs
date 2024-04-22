#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void put_data_simple(const Node* root, FILE* stream){
    fprintf(stream, "%s -- ", root->key);
    info_t* elem = root->info;
    int start = 1;
    while (elem != NULL){
        if (start) start -= 1;
        else fprintf(stream, " ");
        fprintf(stream, "%u", elem->value);
        elem = elem->next;
    }
    fprintf(stream, "\n");
    return;
}

void print_root(const Node* root, const int level){
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
    print_root(root->left, level + 1);
    print_root(root->right, level + 1);
}

void print_tree(const Tree* tree){
    Node* root = tree->root;
    print_root(root, 0);
}

void travel_rec(const Node* root, FILE* stream, int mode){
    if (root == NULL) return;
    if (root->right != NULL)
        travel_rec(root->right, stream, mode);
    if (mode == 1) 
        put_data(root, stream);
    if (mode == 0) 
        put_data_simple(root, stream);
    if (root->left != NULL)
        travel_rec(root->left, stream, mode);
}

void traversal(const Tree* tree, FILE* stream, int mode){
    Node* root = tree->root;
    travel_rec(root, stream, mode);
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

int tree_to_txt(const Tree* tree, const char* filename){
    FILE* output = fopen(filename, "w");
    if (output == NULL) return FILE_ERROR;
    fclose(output);
    Node* root = tree->root;
    return txt_out_rec(root, filename);
}

int tree_from_txt(Tree* tree, const char* filename){
    free_tree(tree, 0);
    tree->root = NULL;
    FILE* input = fopen(filename, "r");
    if (input == NULL) return FILE_ERROR;
    char* key;
    unsigned info;
    int count = 0;
    int res = 0;
    while ((key = file_readline(input)) != NULL){
        res = fscanf(input, "%u", &info);
        if (res == 0){
            free_tree(tree, 0);
            return FILE_ERROR;
        }
        if (insert(tree, key, info) == KEY_EXIST) free(key);
        fscanf(input, "%*c");
    }
    fclose(input);
    return GOOD;
}

char* transform(Node* root){
    char* key = root->key;
    char* infostr = calloc(1, sizeof(char));
    info_t* info = root->info;
    while (info != NULL){
        if (info != root->info){
            infostr = realloc(infostr, (strlen(infostr) + 3)*sizeof(char));
            strcat(infostr, ", ");
        }
        int length = snprintf(NULL, 0, "%u", info->value);
        char* buffer = calloc(length+1, sizeof(char));
        snprintf(buffer, length + 1, "%u", info->value);
        infostr = realloc(infostr, (strlen(infostr) + strlen(buffer) + 1)*sizeof(char));
        strcat(infostr, buffer);
        free(buffer);
        info = info->next;
    }
    char* result = calloc(strlen(key)+strlen(infostr)+6, sizeof(char));
    strcat(result, "\"");
    strcat(result, key);
    strcat(result, "\"\n[");
    strcat(result, infostr);
    strcat(result, "]");
    free(infostr);
    return result;
}

void fill_agraph(Agraph_t* tree, Node* root){
    Agnode_t *first, *second;
    Agedge_t *edge;
    char* keyandinfo = transform(root);
    first = agnode(tree, keyandinfo, 1);
    free(keyandinfo);
    if (root->left != NULL){
        keyandinfo = transform(root->left);
        second = agnode(tree, keyandinfo, 1);
        free(keyandinfo);
        edge = agedge(tree, first, second, 0, 1);
        fill_agraph(tree, root->left);
    }
    if (root->right != NULL){
        keyandinfo = transform(root->right);
        second = agnode(tree, keyandinfo, 1);
        free(keyandinfo);
        edge = agedge(tree, first, second, 0, 1);
        fill_agraph(tree, root->right);
    }
}

void print_gv(Tree* tree){
    if (tree->root == NULL) return;
    GVC_t *gvc = gvContext();
    Agraph_t *tree_gr = agopen("tree", Agdirected, 0);
    fill_agraph(tree_gr, tree->root);
    gvLayout(gvc, tree_gr, "dot");
    FILE* out = fopen("image.svg", "w");
    gvRender(gvc, tree_gr, "svg", out); 
    // это даёт какую-то тонну утечек памяти всех сортов, и я не знаю как это исправить.
    // Тестовые примеры с официального сайта дают такие же утечки памяти
    fclose(out);
    system("nomacs image.svg -m frameless"); // просмотр изображения
    remove("image.svg");
    gvFreeLayout(gvc, tree_gr);
    agclose(tree_gr);
    gvFreeContext(gvc);
    return;
}