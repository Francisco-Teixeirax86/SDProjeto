/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "inet.h"
#include "sdmessage.pb-c.h"
#include "tree.h"

struct tree_t *tree_s;

/* Inicia o skeleton da árvore.
 * O main() do servidor deve chamar esta função antes de poder usar a
 * função invoke(). 
 * Retorna 0 (OK) ou -1 (erro, por exemplo OUT OF MEMORY)
 */
int tree_skel_init() {   
    tree_s = tree_create();
    if (tree_s == NULL) {
        return -1;
    }
    return 0;
}

/* Liberta toda a memória e recursos alocados pela função tree_skel_init.
 */
void tree_skel_destroy() {
    tree_destroy(tree_s);
}

/* Executa uma operação na árvore (indicada pelo opcode contido em msg)
 * e utiliza a mesma estrutura message_t para devolver o resultado.
 * Retorna 0 (OK) ou -1 (erro, por exemplo, árvore nao incializada)
*/
int invoke(MessageT *msg) {
    
    struct data_t *data;
    MessageT__Opcode opCode = msg->opcode;
    char **keysR;
    void **valuesR;
    int treeSize = tree_size(tree_s);

    switch(opCode) {

        case MESSAGE_T__OPCODE__OP_SIZE:
            msg->opcode = MESSAGE_T__OPCODE__OP_SIZE + 1;
            msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
            msg->size = treeSize;
            return 0;
            break;

        

        case MESSAGE_T__OPCODE__OP_PUT:
            data = data_create2(msg->entry->data->datasize, msg->entry->data->data);
            if(tree_put(tree_s, msg->entry->key, data) == -1) {
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
            if(tree_del(tree_s, msg->entry->key) == -1) {
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
            data = tree_get(tree_s, msg->entry->key);
            if(data == NULL) {
                msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return -1;
                break;
            } else {
                msg->opcode = MESSAGE_T__OPCODE__OP_GET + 1;
                msg->c_type = MESSAGE_T__C_TYPE__CT_VALUE;
                msg->entry->data->datasize = data->datasize;
                msg->entry->data->data = data->data;
                return 0;
                break;
            }

        case MESSAGE_T__OPCODE__OP_HEIGHT:
            msg->opcode = MESSAGE_T__OPCODE__OP_HEIGHT + 1;
            msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
            msg->height = tree_height(tree_s);
            return 0;
            break;

        case MESSAGE_T__OPCODE__OP_GETKEYS:
            keysR = tree_get_keys(tree_s);
            if(keysR == NULL) {
                msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return -1;
                break;
            } else {
                msg->opcode = MESSAGE_T__OPCODE__OP_GETKEYS + 1;
                msg->c_type = MESSAGE_T__C_TYPE__CT_KEYS;
                msg->n_keys = treeSize;
                msg->keys = keysR;
                msg->size = sizeof(keysR);
                return 0;
                break;
            }

        case MESSAGE_T__OPCODE__OP_GETVALUES:
            valuesR = tree_get_values(tree_s);
            if(valuesR == NULL) {
                msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return -1;
                break;
            } else {
                msg->opcode = MESSAGE_T__OPCODE__OP_GETVALUES + 1;
                msg->c_type = MESSAGE_T__C_TYPE__CT_VALUES;
                msg->n_data_s = treeSize;
                msg->data_s = (char**) valuesR;
                msg->size = treeSize;
                return 0;
                break;
            }

        default:
            return -1;
            break;
    }
    return -1;
}