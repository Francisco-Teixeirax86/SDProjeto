/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "data.h"
#include "entry.h"
#include "network_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Remote tree. A definir pelo grupo em client_stub-private.h
 */
//struct rtree_t;

/* Função para estabelecer uma associação entre o cliente e o servidor, 
 * em que address_port é uma string no formato <hostname>:<port>.
 * Retorna NULL em caso de erro.
 */
struct rtree_t *rtree_connect(const char *address_port) {
    
    //Dados
    client_tree = (struct rtree_t *) malloc (sizeof(struct rtree_t));
    char *hostname = strtok((char *)address_port, ":");
    int port = atoi(strtok(NULL,":"));

    // Preenche estrutura server para estabelecer conexão
    client_tree->socket.sin_family = AF_INET;
    client_tree->socket.sin_port = htons(port);
    if (inet_pton(AF_INET, argv[1], &server.sin_addr) < 1) {
        printf("Erro ao converter IP\n");
        close(client_tree->socket);
        free(client_tree);
    return -1;
    }

    // Estabelece conexão com o servidor definido em server (a socket é criada em network_client)
    int value = network_connect(tree_global);
    if(value == -1){ //Verificar se a conexão foi bem sucedida em network_connect
        free(tree_global);
        return NULL;
    }

    return(tree_global);

}

/* Termina a associação entre o cliente e o servidor, fechando a 
 * ligação com o servidor e libertando toda a memória local.
 * Retorna 0 se tudo correr bem e -1 em caso de erro.
 */
int rtree_disconnect(struct rtree_t *rtree) {
    if (rtree == NULL) {
        return -1;
    }
    if (network_close(rtree) != 0) {
        return -1;
    }
    free(rtree);
    return 0;

}

/* Função para adicionar um elemento na árvore.
 * Se a key já existe, vai substituir essa entrada pelos novos dados.
 * Devolve 0 (ok, em adição/substituição) ou -1 (problemas).
 */
int rtree_put(struct rtree_t *rtree, struct entry_t *entry) {

}

/* Função para obter um elemento da árvore.
 * Em caso de erro, devolve NULL.
 */
struct data_t *rtree_get(struct rtree_t *rtree, char *key) {

}

/* Função para remover um elemento da árvore. Vai libertar 
 * toda a memoria alocada na respetiva operação rtree_put().
 * Devolve: 0 (ok), -1 (key not found ou problemas).
 */
int rtree_del(struct rtree_t *rtree, char *key) {

}

/* Devolve o número de elementos contidos na árvore.
 */
int rtree_size(struct rtree_t *rtree) {

    struct message_t *msg = (struct message_t * ) malloc(sizeof(struct message_t));
    message_t__init(msg);
    if(msg == NULL){
        return -1;
    }
    msg.opcode = MESSAGE_T__OPCODE__OP_SIZE;
    msg.c_type = MESSAGE_T__C_TYPE__CT_NONE;
    msg = network_send_receive(rtree,msg);

    printf("The size of the tree is: %d\n", msg->message.size);
}

/* Função que devolve a altura da árvore.
 */
int rtree_height(struct rtree_t *rtree) {

}

/* Devolve um array de char* com a cópia de todas as keys da árvore,
 * colocando um último elemento a NULL.
 */
char **rtree_get_keys(struct rtree_t *rtree) {

}

/* Devolve um array de void* com a cópia de todas os values da árvore,
 * colocando um último elemento a NULL.
 */
void **rtree_get_values(struct rtree_t *rtree) {
    
}