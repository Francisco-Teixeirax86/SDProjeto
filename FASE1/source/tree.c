#include "tree.h"
#include "entry.h"
#include "data.h"
#include "tree-private.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


struct tree_t *tree_create(){
    
    struct tree_t *newTree = malloc(sizeof(struct tree_t));
    if(newTree == NULL){
       // free(newTree);
        return NULL;
    }
    newTree -> root = node_create();
    newTree -> size = 0;

    return newTree;
}   

void tree_destroy(struct tree_t *tree){
    if(tree != NULL){
        node_destroy(tree->root);
        free(tree);
    }
}

int tree_put(struct tree_t *tree, char *key, struct data_t *value){
    if(key != NULL && tree != NULL && value != NULL){
        char *createdKey = malloc(strlen(key)+1);
        strcpy(createdKey,key);
        struct data_t *createdData = data_dup(value);
        struct entry_t *createdEntry = entry_create(createdKey,createdData);

        if(tree->root->value == NULL){
            tree->root->value = createdEntry;
            tree->size = (tree->size)+1;
        } else {
            struct node_t *correctNode = getNode(key, tree->root);
            if(correctNode != NULL){
                int res = strcmp(key, correctNode->value->key);
                if(res == 0){
                    entry_destroy(correctNode->value);
                    correctNode->value = createdEntry;
                } else if(res < 0) {
                    correctNode->leftChild = node_create();
                    correctNode->leftChild->value = createdEntry;
                    tree->size = (tree->size)+1;
                } else {
                    correctNode->rightChild = node_create();
                    correctNode->rightChild->value = createdEntry;
                    tree->size = (tree->size)+1;
                }
            } 
        } 
        return 0;
    } else {
        return -1;
    }
}


struct data_t *tree_get(struct tree_t *tree, char *key){
    
    struct node_t *correctNode = getNode(key, tree->root);
    int res = strcmp(key, correctNode->value->key);
    if(correctNode!=NULL){
        if(res == 0){
            return data_dup(correctNode->value->value);
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }

}

/* Função para remover um elemento da árvore, indicado pela chave key,
 * libertando toda a memória alocada na respetiva operação tree_put.
 * Retorna 0 (ok) ou -1 (key not found).
 */
int tree_del(struct tree_t *tree, char *key) {
    if(key != NULL && tree != NULL){
        if(search_tree(key, tree->root) == true){
            node_del(tree->root, key);
            tree->size = (tree->size) - 1;
            return 0;
        } else {
            return -1;
        }
    } else return -1;
}

int tree_size(struct tree_t *tree){
    return tree->size;
}

int tree_height(struct tree_t *tree){
    return searchTreeDepth(tree->root);
}

char **tree_get_keys(struct tree_t *tree){

    if(tree == NULL){
        return NULL;
    }

    char **keys = (char **) malloc(sizeof(char)*(sizeOfKeys(tree->root, 0)));

    if(keys == NULL) {
        return NULL;
    }

    getKeysInorder(tree->root, keys, 0);

    return keys;
}


void **tree_get_values(struct tree_t *tree){

    void **values = malloc(sizeof(tree->size)+1);
    values[(tree->size)] = NULL;
    return (void **) getValues(tree->root, values, 0);
}

void tree_free_keys(char **keys){
    for(int i = 0; i < sizeof(keys); i++){
        free(keys[i]);
    }
    free(keys);
}

void tree_free_values(void **values){
    for(int i = 0; i < sizeof(values); i++){
        free(values[i]);
    }
    free(values);
}


//---------------------///-----------------------//

//Retorna o tamanho de todas as strings somado, se temos "abc", "bcd", "cde", "def" então a função retorna
//12. Usada na tree get keys para saber o tamanho a reservar na memoria
int sizeOfKeys(struct node_t *node, int currentSize){

    if(node->leftChild != NULL) {
        currentSize = currentSize + strlen(node->value->key);
        currentSize = sizeOfKeys(node->leftChild, currentSize);
    }

    if(node->rightChild != NULL) {
        currentSize = currentSize + strlen(node->value->key);
        currentSize = sizeOfKeys(node->rightChild, currentSize);
    }
    if(node->leftChild == NULL && node->rightChild == NULL) {
        currentSize = currentSize + strlen(node->value->key);
    }
    return currentSize;

}

struct node_t *node_del(struct node_t *node,char *key) {
    int cmp = strcmp(key, node->value->key);

    if(cmp < 0) {
        node->leftChild = node_del(node->leftChild, key);
    } else if (cmp > 0) {
        node->rightChild = node_del(node->rightChild, key);
    } else {

        if(node -> leftChild == NULL && node ->rightChild == NULL) {
            node_destroy(node);
            return NULL;
            
        } else if(node -> leftChild != NULL && node ->rightChild == NULL) {
            struct node_t *newNode = node->leftChild;
            node_destroy(node);
            return newNode;

        } else if(node -> leftChild == NULL && node ->rightChild != NULL) {
            struct node_t *newNode = node->rightChild;
            node_destroy(node);
            return newNode;

        } else {
            struct node_t *InorderSuccesor = findInorderSucessor(node->leftChild);
            node->value = entry_dup(InorderSuccesor->value);
            node->leftChild = node_del(node->leftChild, InorderSuccesor->value->key);
        }

    }

    return node;
    
}

struct node_t *findInorderSucessor(struct node_t *node) {
    if(node != NULL) {
        struct node_t *currentNode = node;

        while(currentNode->rightChild != NULL) {
            currentNode = currentNode->rightChild;
        }

        return currentNode;
    }

    return NULL;
    
}

void *getValues(struct node_t *node, void **values, int i){
    values[i] = node->value;
    if((node->leftChild) != NULL && (node->rightChild) != NULL){
        values[i+1] = getValues(node->leftChild, values, i+1);
        values[i+2] = getValues(node->rightChild, values, i+2);
    } else if ((node->leftChild) != NULL && (node->rightChild) == NULL){
        values[i+1] = getValues(node->leftChild, values, i+1);
    } else if ((node->leftChild) == NULL && (node->rightChild) != NULL){
        values[i+1] = getValues(node->rightChild, values, i+1);
    }
    return values;
}


void getKeys(struct node_t *node, char **keys, int i){
    int currentPos = i;
    if((node->leftChild) == NULL && (node->rightChild) == NULL){
        keys[currentPos] = node->value->key;
        return;
    }
    if((node->leftChild) != NULL && (node->rightChild) == NULL){
        getKeys(node->leftChild, keys, currentPos+1);
    }
    if((node->leftChild) == NULL && (node->rightChild) != NULL){
        getKeys(node->rightChild, keys, currentPos+1);
    } 
}

void getKeysInorder(struct node_t *node, char **keys, int pos) {

    int posInternal = pos;
    if(node != NULL) {
        getKeysInorder(node->leftChild, keys, posInternal);
        char *temp_key = malloc(sizeof(char)*strlen(node->value->key));
        strcpy(temp_key, node->value->key);
        keys[posInternal] = temp_key;
        posInternal++;
        getKeysInorder(node->rightChild, keys, posInternal);
    }
}

int searchTreeDepth(struct node_t *node){
    if (node != NULL){
        int leftDepth = searchTreeDepth(node->leftChild);
        int rightDepth = searchTreeDepth(node->rightChild);
        
        if(node->leftChild != NULL) leftDepth++;
        if(node->rightChild != NULL) rightDepth++;
        
        if(leftDepth>rightDepth) return leftDepth;
        else return rightDepth;
    } else {
        return 0;
    }
}



bool search_tree(char *key, struct node_t *node){
   
    if(key != NULL && (node->value) != NULL){
        int res = strcmp(key,node->value->key);
        if(res == 0){
            return true;
        } else if (res < 0){           
            if((node->leftChild) == NULL){
                return false;
            } else {
                return search_tree(key, node->leftChild);
            }
        } else {
            if((node->rightChild) == NULL){
                return false;
            } else {
                return search_tree(key, node->rightChild);
            }
        }
    } else {
        return false;
    }
}

struct node_t *getNode(char *key, struct node_t * node){
        int res = strcmp(key,node->value->key);
        if(res == 0){
            return node;
        } else if (res < 0){           
            if((node->leftChild) == NULL){
                return node;
            } else {
                return getNode(key, node->leftChild);
            }
        } else {
            if((node->rightChild) == NULL){
                return node;
            } else {
                return getNode(key, node->rightChild);
            }
        }
}


struct node_t *node_create(){
    
    struct node_t *newNode = malloc(sizeof(struct node_t));
    if(newNode == NULL){
        free(newNode);
        return NULL;
    }
    newNode -> value = NULL;
    newNode -> leftChild = NULL;
    newNode -> rightChild = NULL;

    return newNode;
}

void node_destroy(struct node_t *node){
    entry_destroy(node->value);
    free(node);
}