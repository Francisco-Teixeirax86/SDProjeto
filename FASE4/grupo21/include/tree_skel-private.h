/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#ifndef _TREE_SKEL_H
#define _TREE_SKEL_H

#include "sdmessage.pb-c.h"
#include "tree.h"
#include "sdmessage.pb-c.h"
#include <zookeeper/zookeeper.h>


struct op_proc {
	int max_proc; //regista o maior identificador das operações de escrita já concluídas
	int* in_progress; //regista o identificador das operações de escrita que estão a ser atendidas por um conjunto de threads dedicadas às escritas
};

struct request_t {
	int op_n; //o número da operação
	int op; //a operação a executar. op=0 se for um delete, op=1 se for um put
	char* key; //a chave a remover ou adicionar
	char* data; // os dados a adicionar em caso de put, ou NULL em caso de delete
	int datasize;
	struct request_t *next_request;
//adicionar campo(s) necessário(s) para implementar fila do tipo produtor/consumidor
};

struct rtree_t {
	zhandle_t *zh;
	int is_connected;

	struct sockaddr_in socket; //Informação pertinente ao server
    int sockfd; //Socket a usar pelo cliente
};


/*
* Função que imprime e corre o processo das threads.
*/
void *thread_impressao(void *params);

#endif