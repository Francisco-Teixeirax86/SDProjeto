#ifndef _TREE_PRIVATE_H
#define _TREE_PRIVATE_H

#include "tree.h"
#include "entry.h"
#include "data.h"

struct tree_t {
	struct node *root; //Valor da raiz da arvore
	int size; //tamanho da arvore	
};

struct node_t {
	struct entry_t *value; //valor do node atual
	struct node_t *leftChild; //pointer para o node filho esquerdo;
	struct node_t *rightChild; //pointer para o node filho direito;
};

/*
	Funcão que cria um node vazio
*/
struct node_t *node_create();

/*
	Função que destroi um node e os seus filhos, libertanto a memória por ela ocupada
*/
void  *node_destroy(struct node_t *node);

/*
	Função que persquisa uma key especifica numa tree 
*/
char *search_tree(char *key, struct tree_t *tree);



#endif
