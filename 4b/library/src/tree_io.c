#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphviz/gvc.h>
#include "tree.h"
#include "tree_io.h"
#include "basic.h"
#include "stack.h"

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

void print_found(const Node* found){
    printf("Найденный элемент: ");
    put_data(found, stdout);
    return;
}

void swap(char** bottom, char** top){
    char* buff = *bottom;
    *bottom = *top;
    *top = buff;
}

int check(char* elem, char* bottom, char* top){
    return ((strcmp(elem, bottom) < 0) || (strcmp(elem, top) > 0));
}

void traversal(const Tree* tree, FILE* stream, char* bottom, char* top){
    Node* root = tree->root;
    if (strcmp(bottom, top) > 0) {
        swap(&bottom, &top);
    }
    stack_tm* stack = get_stack(SIZE);
    while ((peek(stack) != NULL) || (root != NULL)){
        if (root != NULL){
            push(stack, root);
            root = root->left;
        }
        else{
            pop(stack, &root);
            if (check(root->key, bottom, top)) {
                put_data(root, stream);
            }
            root = root->right;
        }
    }
    free_stack(stack);
}

int tree_to_txt(const Tree* tree, const char* filename){
    FILE* output = fopen(filename, "w");
    if (output == NULL) return FILE_ERROR;
    Node* root = tree->root;
    if (root == NULL) return NO_TREE;
    stack_tm* stack = get_stack(SIZE);
    Node* last = NULL;
    while ((peek(stack) != NULL) || (root != NULL)){
        if (root != NULL){
            push(stack, root);
            root = root->left;
        }
        else{
            Node* pn = peek(stack);
            if (pn->right != NULL && last != pn->right){
                root = pn->right;
            }
            else{
                info_t* elem = pn->info;
                while (elem != NULL){
                    fprintf(output, "%s\n", pn->key);
                    fprintf(output, "%d\n", elem->value);
                    elem = elem->next;
                }
                pop(stack, &last);
            }
        }
    }
    fclose(output);
    free_stack(stack);
    return GOOD;
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
            free(key);
            fclose(input);
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
    static int nils = 0;
    if (root == NULL){
        char* ret = calloc(6+(nils/26), sizeof(char));
        for (int i=0; i<3;i++){
            ret[i] = nils%26 +'a';
        }
        ret[3] = '\n';
        for (int i=4; i<4+(nils/26)+1;i++){
            ret[i] = nils%26 +'a';
            if ((i%5 == 0) && (i != 5))
                ret[i] = '\n';
        }
        nils++;
        return ret;
    }
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

Agnode_t* draw(Agraph_t* tree, Node* elem){
    char* keyandinfo = transform(elem);
    Agnode_t* second = agnode(tree, keyandinfo, 1);
    free(keyandinfo);
    return second;
}

void fill_agraph(Agraph_t* tree, Node* root){
    if (root == NULL) return;
    stack_tm* stack = get_stack(SIZE);
    Agnode_t *first, *second;
    Agedge_t *edge;
    char* keyandinfo;
    push(stack, root);
    while (peek(stack) != NULL){
        pop(stack, &root);
        first = draw(tree, root);
        if (root->parent != NULL){
            second = draw(tree, root->parent);
            edge = agedge(tree, second, first, 0, 1);
        }
        if (root->right != NULL){
            if (root->left == NULL){
                second = draw(tree, NULL);
                edge = agedge(tree, first, second, 0, 1);
                agsafeset(second, "style", "invis", "");
                agsafeset(edge, "style", "invis", "");
            }
            push(stack, root->right);
        }
        if (root->left != NULL){
            if (root->right == NULL){
                second = draw(tree, root->left);
                second = draw(tree, NULL);
                edge = agedge(tree, first, second, 0, 1);
                agsafeset(second, "style", "invis", "");
                agsafeset(edge, "style", "invis", "");
            }
            push(stack, root->left);
        }
    }
    free_stack(stack);
}

void print_gv(Tree* tree){
    if (tree->root == NULL) return;
    GVC_t *gvc = gvContext();
    Agraph_t *tree_gr = agopen("tree", Agdirected, 0);
    fill_agraph(tree_gr, tree->root);
    gvLayout(gvc, tree_gr, "dot");
    FILE* out = fopen("image.svg", "w");
    gvRender(gvc, tree_gr, "svg", out); 
    fclose(out);
    system("nomacs image.svg -m frameless"); // просмотр изображения
    remove("image.svg");
    gvFreeLayout(gvc, tree_gr);
    agclose(tree_gr);
    gvFreeContext(gvc);
    return;
}