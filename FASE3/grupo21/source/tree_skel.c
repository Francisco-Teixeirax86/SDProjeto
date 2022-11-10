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
#include <pthread.h>

struct tree_t *tree_s;
struct op_proc *operation;
int last_assigned;
struct request_t *queue_head;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t tree_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_not_empty = PTHREAD_COND_INITIALIZER;


/* Inicia o skeleton da árvore.
* O main() do servidor deve chamar esta função antes de poder usar a
* função invoke().
* A função deve lançar N threads secundárias responsáveis por atender
* pedidos de escrita na árvore.
* Retorna 0 (OK) ou -1 (erro, por exemplo OUT OF MEMORY)
*/
int tree_skel_init(int N) {  
    operation->max_proc = 0;
    operation->in_progress = 0;
    last_assigned = 1;
    queue_head = NULL;
    tree_s = tree_create();
    int n_threads = atoi(N);
    pthread_t thread[n_threads];
    int thread_param[n_threads];
    int r;

    printf("main() a iniciar\n");

/*
    // Cria N threads
    for (int i=0; i < n_threads; i++){
        thread_param[i] = i+1;
        if (pthread_create(&thread[i], NULL, &thread_impressao, (void) &thread_param[i]) != 0){
            printf("\nThread %d não criada.\n", i);
            exit(EXIT_FAILURE);
        }
    }
*/
    /* Join para N threads. */
    for (int i=0; i < n_threads; i++){
        if (pthread_join(thread[i], (void **) &r) != 0){
            perror("\nErro no join.\n");
            exit(EXIT_FAILURE);
        }
    }

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

            printf("Nova operação de del com o seguinte ID: %d", last_assigned);
            struct request_t *request= (struct request_t *) malloc(sizeof(struct request_t));
            request->op_n = last_assigned;
            last_assigned++;
            request->op = 1;
            request->key = msg->entry->key;
            request->data = msg->entry->data->data;
            request->msg = msg;

            pthread_mutex_lock(&queue_lock);

            if(queue_head == NULL){
                queue_head = request;
                request->next_request = NULL;
            }
            else{
                struct request_t *tptr = queue_head;
                while (tptr->next_request != NULL)
                    tptr=tptr->next_request;
                tptr->next_request=request; 
                request->next_request=NULL;
            } 
            pthread_cond_signal(&queue_not_empty);
            pthread_mutex_unlock(&queue_lock);
            free(request);

           return 0;
           break;
        case MESSAGE_T__OPCODE__OP_DEL:

            printf("Nova operação de put com o seguinte ID: %d", last_assigned);
            struct request_t *request= (struct request_t *) malloc(sizeof(struct request_t));
            request->op_n = last_assigned;
            last_assigned++;
            request->op = 0;
            request->key = msg->entry->key;
            request->data = NULL;
            request->msg = msg;

            pthread_mutex_lock(&queue_lock);

            if(queue_head == NULL){
                queue_head = request;
                request->next_request = NULL;
            }
            else{
                struct request_t *tptr = queue_head;
                while (tptr->next_request != NULL)
                    tptr=tptr->next_request;
                tptr->next_request=request; 
                request->next_request=NULL;
            } 
            pthread_cond_signal(&queue_not_empty);
            pthread_mutex_unlock(&queue_lock);
            free(request);

           return 0;
           break;
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

    while(1){

        pthread_mutex_lock(&queue_lock);

        while(queue_head==NULL)
            pthread_cond_wait(&queue_not_empty, &queue_lock);

        struct request_t *request = queue_head;

    if(request->op == 0){ //DELETE
        pthread_mutex_lock(&tree_lock);  
        if(tree_del(tree_s, request->key) == -1) {
                request->msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
                request->msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return -1;
                break;
            } else {
                request->msg->opcode = MESSAGE_T__OPCODE__OP_DEL + 1;
                request->msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
                if((request->op_n > operation->max_proc))
                    operation->max_proc = request->op_n;

                return 0;
                break;
            }
        pthread_mutex_unlock(&tree_lock);
    } else { //PUT
        pthread_mutex_lock(&tree_lock); 
        struct data_t *data;
        data = data_create2(strlen(request->data), request->data);
        if(tree_put(tree_s, request->key, data) == -1) {
            request->msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
            request->msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
            return -1;
            break;
        } else {
            request->msg->opcode = MESSAGE_T__OPCODE__OP_PUT + 1;
            request->msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
            if((request->op_n > operation->max_proc))
                operation->max_proc = request->op_n;
            return 0;
            break;
        }
        pthread_mutex_unlock(&tree_lock);
    }

        pthread_mutex_unlock(&queue_head);
    }

}