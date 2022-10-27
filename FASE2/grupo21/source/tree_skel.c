/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "inet.h"
#include "sdmessage.pb-c.h"
#include "tree.h"

struct tree_t *tree;

/* Inicia o skeleton da árvore.
 * O main() do servidor deve chamar esta função antes de poder usar a
 * função invoke(). 
 * Retorna 0 (OK) ou -1 (erro, por exemplo OUT OF MEMORY)
 */
int tree_skel_init() {
    tree = tree_create();
    if (tree == NULL) {
        return -1;
    }
    return 0;
}

/* Liberta toda a memória e recursos alocados pela função tree_skel_init.
 */
void tree_skel_destroy() {
    tree_destroy(tree);
}

/* Executa uma operação na árvore (indicada pelo opcode contido em msg)
 * e utiliza a mesma estrutura message_t para devolver o resultado.
 * Retorna 0 (OK) ou -1 (erro, por exemplo, árvore nao incializada)
*/
int invoke(MessageT *msg) {
    
    struct data_t *data;
    MessageT__Opcode opCode = msg->opcode;

    switch(opCode) {

        case MESSAGE_T__OPCODE__OP_SIZE:

            msg->opcode = MESSAGE_T__OPCODE__OP_SIZE + 1;
            msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
            msg->size = tree_size(tree);
            return 0;
            break;

        

        case MESSAGE_T__OPCODE__OP_PUT:
            if(tree_put(tree, msg->entry->key, msg->entry->data) == -1) {
                printf("Ocorreu um erro ao colocar a chave na árvore");
                msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return -1;
                break;
            } else {
                msg->opcode = MESSAGE_T__OPCODE__OP_PUT + 1;
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return 0;
                break;
            }

        case MESSAGE_T__OPCODE__OP_DEL:
            if(tree_del(tree, msg->entry->key) == -1) {
                printf("Ocorreu um erro a apagar a chave, certifique-se de que a chave fornecidade existe na tree");
                msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return -1;
                break;
            } else {
                msg->opcode = MESSAGE_T__OPCODE__OP_DEL + 1;
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return 0;
                break;
            }

        case MESSAGE_T__OPCODE__OP_GET:
            data = tree_get(tree, msg->keys);
            if(data == NULL) {
                printf("Ocorreu um erro na procura da chave, certifique-se de que a chave fornecidade existe na tree");
                msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return -1;
                break;
            } else {
                msg->opcode = MESSAGE_T__OPCODE__OP_GET + 1;
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return 0;
                break;
            }

        case MESSAGE_T__OPCODE__OP_HEIGHT:

            msg->opcode = MESSAGE_T__OPCODE__OP_HEIGHT + 1;
            msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
            msg->size = tree_height(tree);
            return 0;
            break;

        default:
            return -1;
            break;
    }
    return -1;
}