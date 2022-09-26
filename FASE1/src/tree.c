#include "tree.h"
#include "entry.h"
#include "data.h"
#include "tree-private.h"
#include <stdio.h>

struct tree_t *tree_create(){
    
    struct tree_t *newTree = malloc(sizeof(struct tree_t));
    if(newTree == NULL){
        free(newTree);
        return NULL;
    }
    newTree -> root = node_create();
    newTree -> size = 0;
}

void tree_destroy(struct tree_t *tree){
    if(tree != NULL){
        node_destroy(tree->root);
        free(tree);
    }
}

int tree_put(struct tree_t *tree, char *key, struct data_t *value){

}






//---------------------///-----------------------//

bool *search_tree(char *key, struct tree_t *tree){
    if(strcmp((((tree->root)->value)->key), key) == 0){
        return true;
    }
}




struct node_t *node_create(){
    
    struct node_t *newNode = malloc(sizeof(struct node_t));
    if(newNode == NULL){
        free(newNode);
        return NULL
    }
    newNode -> value = NULL;
    newNode -> leftChild = NULL;
    newNode -> rightChild = NULL;
}

void  *node_destroy(struct node_t *node){
    if(node != NULL){
        if((node->leftChild != NULL)){
            node_destroy(node->leftChild);
        }
        if((node->rightChild != NULL)) {
            node_destroy(node->rightChild);
        }
        entry_destroy(node->value);
        free(node);
    }
}