/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#ifndef _MESSAGE_PRIVATE_H
#define _MESSAGE_PRIVATE_H

#include "sdmessage.pb-c.h"
#include "inet.h"

struct request_t {
	int op_n; //o número da operação
	int op; //a operação a executar. op=0 se for um delete, op=1 se for um put
	char* key; //a chave a remover ou adicionar
	char* data; // os dados a adicionar em caso de put, ou NULL em caso de delete
//adicionar campo(s) necessário(s) para implementar fila do tipo produtor/consumidor
};

/*
 * Função que envia uma string inteira pela rede
*/
int write_all(int sock, uint8_t *buf, int len);

/*
 * Função que recebe uma string inteira pela rede
*/
int read_all(int sock, uint8_t *buf, int len);

#endif