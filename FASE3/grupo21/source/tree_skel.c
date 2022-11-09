/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "inet.h"
#include "tree_skel-private.h"
#include "sdmessage.pb-c.h"
#include "tree.h"

struct tree_t *tree_s;
struct op_proc *operation;

/* Inicia o skeleton da árvore.
* O main() do servidor deve chamar esta função antes de poder usar a
* função invoke().
* A função deve lançar N threads secundárias responsáveis por atender
* pedidos de escrita na árvore.
* Retorna 0 (OK) ou -1 (erro, por exemplo OUT OF MEMORY)
*/
int tree_skel_init(int N) {  
    operation->max_proc = 0;
    operation->in_progress = NULL;
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
    int op_n;

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
                msg->data_s = (ProtobufCBinaryData*) valuesR;
                msg->size = treeSize;
                return 0;
                break;
            }

        case MESSAGE_T__OPCODE__OP_VERIFY:
            if(verify(op_n) == 0) {
                msg->opcode = MESSAGE_T__OPCODE__OP_ERROR; //não é verify + 1?
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return -1;
                break;
            } else {
                msg->opcode = MESSAGE_T__OPCODE__OP_VERIFY + 1;
                msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
                return 0;
                break;
            }


        default:
            return -1;
            break;
    }
    return -1;
}

/* Verifica se a operação identificada por op_n foi executada.
*/
int verify(int op_n) {
    if (op_n < operation->max_proc) {
        return 1;
    } else {
        return 0;
    }
}

/* Função da thread secundária que vai processar pedidos de escrita.
*/
void * process_request (void *params) {
    return NULL;
}