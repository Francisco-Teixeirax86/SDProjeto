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
#include "entry.h"
#include <pthread.h>
#include <stdbool.h>

struct tree_t *tree_s;
struct op_proc *operation;
int last_assigned;
struct request_t *queue_head;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t tree_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_not_empty = PTHREAD_COND_INITIALIZER;
pthread_t thread;
int *thread_param;
int thread_number;
int verify(int);


/* Inicia o skeleton da árvore.
* O main() do servidor deve chamar esta função antes de poder usar a
* função invoke().
* A função deve lançar N threads secundárias responsáveis por atender
* pedidos de escrita na árvore.
* Retorna 0 (OK) ou -1 (erro, por exemplo OUT OF MEMORY)
*/
int tree_skel_init(int N) {  
    operation = malloc(sizeof(struct op_proc));
    operation->in_progress = malloc(sizeof(int) * N);
    thread_number = N;
    if (operation == NULL) {
        free(operation->in_progress);
        free(operation);
    }
    for (int i = 0; i < N; i++) {
        operation->in_progress[i] = 0;
    } 
    operation->max_proc = 0;
    last_assigned = 1;
    queue_head = NULL;
    tree_s = tree_create();
    int n_threads = N;
    thread = (pthread_t) malloc(sizeof(pthread_t) * n_threads);
    thread_param = malloc(sizeof(int) * n_threads);

    printf("main() a iniciar\n");
    for (int i=0; i < n_threads; i++){
        thread_param[i] = i+1;
        if (pthread_create(&thread+i, NULL, &thread_impressao, (void *) &thread_param[i]) != 0){
            printf("\nThread %d não criada.\n", i);
            exit(EXIT_FAILURE);
        }
    }
   
    struct data_t *datateste = data_create2(sizeof("adeus"), "adeus");
    tree_put(tree_s, "ola", datateste);

    if (tree_s == NULL) {
        return -1;
    }

    return 0;
}

/* Liberta toda a memória e recursos alocados pela função tree_skel_init.
 */
void tree_skel_destroy() {
    free(operation->in_progress);
    free(operation);
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
    int op_n = -1;

    switch(opCode) {

        case MESSAGE_T__OPCODE__OP_SIZE:
            msg->opcode = MESSAGE_T__OPCODE__OP_SIZE + 1;
            msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
            msg->size = treeSize;
            return 0;
            break;

        

        case MESSAGE_T__OPCODE__OP_PUT:

            printf("Nova operação de put com o seguinte ID: %d", last_assigned);
            struct request_t *request1= (struct request_t *) malloc(sizeof(struct request_t));
            request1->op_n = last_assigned;
            last_assigned++;
            request1->op = 1;
            request1->key = msg->entry->key;
            request1->data = msg->entry->data->data;
            request1->msg = msg;

            pthread_mutex_lock(&queue_lock);

            if(queue_head == NULL){
                queue_head = request1;
                request1->next_request = NULL;
            }
            else{
                struct request_t *tptr = queue_head;
                while (tptr->next_request != NULL)
                    tptr=tptr->next_request;
                tptr->next_request=request1; 
                request1->next_request=NULL;
            }
            pthread_cond_signal(&queue_not_empty);
            pthread_mutex_unlock(&queue_lock);

           return 0;
           break;
        case MESSAGE_T__OPCODE__OP_DEL:

            printf("Nova operação de put com o seguinte ID: %d", last_assigned);
            struct request_t *request2= (struct request_t *) malloc(sizeof(struct request_t));
            request2->op_n = last_assigned;
            last_assigned++;
            request2->op = 0;
            request2->key = msg->entry->key;
            request2->data = NULL;
            request2->msg = msg;

            pthread_mutex_lock(&queue_lock);

            if(queue_head == NULL){
                queue_head = request2;
                request2->next_request = NULL;
            }
            else{
                struct request_t *tptr = queue_head;
                while (tptr->next_request != NULL)
                    tptr=tptr->next_request;
                tptr->next_request=request2; 
                request2->next_request=NULL;
            }
            pthread_cond_signal(&queue_not_empty);
            pthread_mutex_unlock(&queue_lock);

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
void *process_request(void *params) {

    int *thread_number = (int *) params;
    while(1){

        pthread_mutex_lock(&queue_lock);

        while(queue_head==NULL)
            pthread_cond_wait(&queue_not_empty, &queue_lock);

        struct request_t *request = queue_head;
        operation->in_progress[*thread_number-1] = request->op_n;
        

        if(request->op == 0){ //DELETE
            pthread_mutex_lock(&tree_lock);  
            if(tree_del(tree_s, request->key) == -1) {
                    request->msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
                    request->msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                    if((request->op_n > operation->max_proc))
                        operation->max_proc = request->op_n;
                } else {
                    request->msg->opcode = MESSAGE_T__OPCODE__OP_DEL + 1;
                    request->msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
                    if((request->op_n > operation->max_proc))
                        operation->max_proc = request->op_n;
                }
            pthread_mutex_unlock(&tree_lock);
        } else { //PUT
            pthread_mutex_lock(&tree_lock); 
            struct data_t *data;
            data = data_create2(strlen(request->data), request->data);
            if(tree_put(tree_s, request->key, data) == -1) {
                request->msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
                request->msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                if((request->op_n > operation->max_proc))
                    operation->max_proc = request->op_n;
                free(data);
            } else {
                request->msg->opcode = MESSAGE_T__OPCODE__OP_PUT + 1;
                request->msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
                if((request->op_n > operation->max_proc))
                    operation->max_proc = request->op_n;
                free(data);
            }
            pthread_mutex_unlock(&tree_lock);
        }
        pthread_mutex_unlock(&queue_lock);
    }
    pthread_exit("Exit");
    return NULL;
}


void *thread_impressao(void *params){
	int *thread_number = (int *) params;

	printf("Thread %d a iniciar\n", *thread_number);

		process_request(params);
		
		printf("Thread %d diz: %s \n", *thread_number, "Imprimi!");

	printf("Thread %d a terminar\n", *thread_number);

	return 0;
}