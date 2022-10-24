/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "inet.h"
#include "client_stub-private.h"
#include "client_stub.h"
#include "data.h"
#include "entry.h"
#include "network_client.h"
#include "sdmessage.pb-c.h"

/* Remote tree. A definir pelo grupo em client_stub-private.h
 */
struct rtree_t *tree;

/* Função para estabelecer uma associação entre o cliente e o servidor, 
 * em que address_port é uma string no formato <hostname>:<port>.
 * Retorna NULL em caso de erro.
 */
struct rtree_t *rtree_connect(const char *address_port) {
    
    //Dados
    tree = (struct rtree_t *) malloc (sizeof(struct rtree_t));
    char *host = strtok((char *)address_port, ":");
    int port = atoi(strtok(NULL,":"));

    tree->socket.sin_family = AF_INET;
    tree->socket.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &tree->socket.sin_addr) < 1) {
        printf("Erro ao converter IP\n");
        close(tree->sockfd);
        return NULL;
    }

    // Estabelece conexão com o servidor definido em server (a socket é criada em network_client)
    int connect = network_connect(tree);
    if(connect == -1){ //Verificar se a conexão foi bem sucedida em network_connect
        free(tree);
        return NULL;
    }

    return tree;

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
    if (rtree == NULL) {
        return -1;
    }
    //malloc necessário?
    MessageT *msg = (MessageT * ) malloc(sizeof(MessageT)); //VAI SER PRECISO TROCAR message_t PARA MessageT OU _MessageT
    message_t__init(msg);
    entry_t__init(msg->entry); //PARÃMETRO ENTRY NÃO EXISTE NO PROTO (TEM DE SER CRIADO?)
    msg->entry->key = entry->key; //PARÃMETRO KEY NÃO EXISTE NO PROTO (TEM DE SER CRIADO?)
    msg->entry->data->datasize = entry->value->datasize; //PARÃMETRO DATASIZE NÃO EXISTE NO PROTO (TEM DE SER CRIADO?)
    msg->entry->data->data = entry->value->data;
    msg->opcode = MESSAGE_T__OPCODE__OP_PUT;
    msg->c_type = MESSAGE_T__C_TYPE__CT_ENTRY;
    msg->key = key; //PARÃMETRO KEY NÃO EXISTE NO PROTO (TEM DE SER CRIADO?)

    MessageT *responseMsg = network_send_receive(rtree, msg); //&msg?
    if(responseMsg == NULL){
        return -1;
    }
    if(responseMsg->opcode == MESSAGE_T__OPCODE__OP_PUT) {
        message_t__free_unpacked(responseMsg, NULL);
        return 0;
    }  
    else{ //EM CASO DE ERRO
        message_t__free_unpacked(responseMsg, NULL);
        return -1;
    }
}

/* Função para obter um elemento da árvore.
 * Em caso de erro, devolve NULL.
 */
struct data_t *rtree_get(struct rtree_t *rtree, char *key) {
    if (rtree == NULL) {
        return -1;
    }
    //malloc necessário?
    MessageT *msg = (MessageT * ) malloc(sizeof(MessageT)); //VAI SER PRECISO TROCAR message_t PARA MessageT OU _MessageT
    message_t__init(msg);
    msg->opcode = MESSAGE_T__OPCODE__OP_GET;
    msg->c_type = MESSAGE_T__C_TYPE__CT_KEY;
    msg->key = key; //PARÃMETRO KEY NÃO EXISTE NO PROTO (TEM DE SER CRIADO?)

    MessageT *responseMsg = network_send_receive(rtree, msg); //&msg?
    if(responseMsg == NULL){
        return -1;
    }
    if(responseMsg->opcode == MESSAGE_T__OPCODE__OP_GET + 1 && responseMsg->c_type == MESSAGE_T__C_TYPE__CT_VALUE) {
        //FALTA CRIAR DATA
    }  
    else{ //EM CASO DE ERRO
        message_t__free_unpacked(responseMsg, NULL);
        //FALTA CRIAR DATA
    }
    //FALTA CRIAR DATA
}

/* Função para remover um elemento da árvore. Vai libertar 
 * toda a memoria alocada na respetiva operação rtree_put().
 * Devolve: 0 (ok), -1 (key not found ou problemas).
 */
int rtree_del(struct rtree_t *rtree, char *key) {
    if (rtree == NULL) {
        return -1;
    }
    //malloc necessário?
    MessageT *msg = (MessageT * ) malloc(sizeof(MessageT)); //VAI SER PRECISO TROCAR message_t PARA MessageT OU _MessageT
    message_t__init(msg);
    msg->opcode = MESSAGE_T__OPCODE__OP_DEL;
    msg->c_type = MESSAGE_T__C_TYPE__CT_KEY;
    msg->key = key; //PARÃMETRO KEY NÃO EXISTE NO PROTO (TEM DE SER CRIADO?)

    MessageT *responseMsg = network_send_receive(rtree, msg); //&msg?
    if(responseMsg == NULL){
        return -1;
    }
    if(responseMsg->opcode == MESSAGE_T__OPCODE__OP_DEL + 1 && responseMsg->c_type == MESSAGE_T__C_TYPE__CT_NONE) {
        message_t__free_unpacked(responseMsg, NULL);
        return 0;
    }  
    else{ //EM CASO DE ERRO
        message_t__free_unpacked(responseMsg, NULL);
        return -1;
    }
}

/* Devolve o número de elementos contidos na árvore.
 */
int rtree_size(struct rtree_t *rtree) {
    if (rtree == NULL) {
        return -1;
    }
    //malloc necessário?
    MessageT *msg = (MessageT * ) malloc(sizeof(MessageT)); //VAI SER PRECISO TROCAR message_t PARA MessageT OU _MessageT
    message_t__init(msg);
    msg->opcode = MESSAGE_T__OPCODE__OP_SIZE;
    msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;

    MessageT *responseMsg = network_send_receive(rtree, msg); //&msg?
    if(responseMsg == NULL){
        return -1;
    }
    int nelem = 0;
    if(responseMsg->opcode == MESSAGE_T__OPCODE__OP_SIZE + 1 && responseMsg->c_type == MESSAGE_T__C_TYPE__CT_RESULT) {
        nelem = responseMsg->size; //PARÃMETRO SIZE NÃO EXISTE NO PROTO (TEM DE SER CRIADO?)
        message_t__free_unpacked(responseMsg, NULL);
    }  
    else{ //EM CASO DE ERRO
        message_t__free_unpacked(responseMsg, NULL);
        return -1;
    }
    printf("O nº de elementos da árvore é: %d\n", nelem);
    return nelem;
}

/* Função que devolve a altura da árvore.
 */
int rtree_height(struct rtree_t *rtree) {
    if (rtree == NULL) {
        return -1;
    }
    //malloc necessário?
    MessageT *msg = (MessageT * ) malloc(sizeof(MessageT)); //VAI SER PRECISO TROCAR message_t PARA MessageT OU _MessageT
    message_t__init(msg);
    msg->opcode = MESSAGE_T__OPCODE__OP_HEIGHT;
    msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;

    MessageT *responseMsg = network_send_receive(rtree, msg); //&msg?
    if(responseMsg == NULL){
        return -1;
    }
    int height = 0;
    if(responseMsg->opcode == MESSAGE_T__OPCODE__OP_HEIGHT + 1 && responseMsg->c_type == MESSAGE_T__C_TYPE__CT_RESULT) {
        height = responseMsg->height; //PARÃMETRO HEIGHT NÃO EXISTE NO PROTO (TEM DE SER CRIADO?)
        message_t__free_unpacked(responseMsg, NULL);
    }  
    else{ //EM CASO DE ERRO
        message_t__free_unpacked(responseMsg, NULL);
        return -1;
    }
    printf("A altura da árvore é: %d\n", height);
    return height;
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