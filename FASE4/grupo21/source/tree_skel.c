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
#include <netdb.h>
#include <pthread.h>
#include <stdbool.h>
#include <zookeeper/zookeeper.h>

#define ZDATALEN 1024 * 1024
typedef struct String_vector zoo_string; 

struct rtree_t* next_server;
static char *root_path = "/chain";
static char *watcher_ctx = "ZooKeeper Data Watcher";

char hbuffer[256];
struct hostent *hostent_s;
char *ipbuffer;
zhandle_t *zh;
int next_node_len = 1024;

struct tree_t *tree_s;
zoo_string* children_list;
struct op_proc *operation;
int last_assigned;
struct request_t *queue_head;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t tree_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_not_empty = PTHREAD_COND_INITIALIZER;
pthread_t *thread;
int *thread_param;
int thread_number;
int *r;
int verify(int);
void connection_watcher_server(zhandle_t*, int, int, const char*, void*);


/* Inicia o skeleton da árvore.
* O main() do servidor deve chamar esta função antes de poder usar a
* função invoke().
* A função deve lançar N threads secundárias responsáveis por atender
* pedidos de escrita na árvore.
* Retorna 0 (OK) ou -1 (erro, por exemplo OUT OF MEMORY)
*/
int tree_skel_init(int port) {   //PODE-SE MUDAR O PARÂMETRO AQUI?
    operation = malloc(sizeof(struct op_proc));
    operation->in_progress = malloc(sizeof(int) * 1);
    thread_number = 1;
    if (operation == NULL) {
        free(operation->in_progress);
        free(operation);
    }
    for (int i = 0; i < 1; i++) {
        operation->in_progress[i] = 0;
    } 
    operation->max_proc = 0;
    last_assigned = 1;
    queue_head = NULL;
    tree_s = tree_create();
    int n_threads = 1;
    thread = (pthread_t*) malloc(sizeof(pthread_t) * n_threads); //NAO LIBERTADO FALTA JOIN
    thread_param = malloc(sizeof(int) * n_threads); //NAO LIBERTADO FALTA JOIN
    zookeeper_connect_server(port);

    printf("main() a iniciar\n");
    for (int i=0; i < n_threads; i++){
        thread_param[i] = i+1;
        if (pthread_create(&thread[i], NULL, &thread_impressao, (void *) &thread_param[i]) != 0){
            printf("\nThread %d não criada.\n", i);
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
    free(thread_param);
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

    switch(opCode) {

        case MESSAGE_T__OPCODE__OP_SIZE:
            msg->opcode = MESSAGE_T__OPCODE__OP_SIZE + 1;
            msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
            msg->size = treeSize;
            return 0;
            break;

        

        case MESSAGE_T__OPCODE__OP_PUT:

            struct request_t *request1 = (struct request_t *) malloc(sizeof(struct request_t));
            if(request1 == NULL) {
                msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return -1;
                break;
            } else {
                msg->opcode = MESSAGE_T__OPCODE__OP_PUT + 1;
                msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
                msg->size = last_assigned;

                request1->op_n = last_assigned;
                last_assigned++;
                request1->op = 1;
                char *key_r = malloc(strlen(msg->entry->key) + 1);
                strcpy(key_r, msg->entry->key);
                request1->key = key_r;
                char *data_r = malloc(strlen(msg->entry->data->data) + 1);
                strcpy(data_r, msg->entry->data->data);
                request1->data = data_r;
                request1->datasize = msg->entry->data->datasize;

                pthread_mutex_lock(&queue_lock);

                if(queue_head == NULL){
                    queue_head = request1;
                    request1->next_request = NULL;
                } else{
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
            }

        case MESSAGE_T__OPCODE__OP_DEL:

            struct request_t *request2 = (struct request_t *) malloc(sizeof(struct request_t));
            if(request2 == NULL) {
                msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
                msg->c_type = MESSAGE_T__C_TYPE__CT_NONE;
                return -1;
                break;
            } else {
                msg->opcode = MESSAGE_T__OPCODE__OP_DEL + 1;
                msg->c_type = MESSAGE_T__C_TYPE__CT_RESULT;
                msg->size = last_assigned;

                request2->op_n = last_assigned;
                last_assigned++;
                request2->op = 0;
                char *key_r = malloc(strlen(msg->entry->key) + 1);
                strcpy(key_r, msg->entry->key);
                request2->key = key_r;
                request2->data = NULL;
                request2->datasize = 0;

                pthread_mutex_lock(&queue_lock);

                if(queue_head == NULL){
                    queue_head = request2;
                    request2->next_request = NULL;
                } else{
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
            if(verify(msg->size) == 0) {
                msg->opcode = MESSAGE_T__OPCODE__OP_ERROR;
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
    if (op_n <= operation->max_proc) { 
        return 1;
    } 
    else if (op_n > operation->max_proc) {
        return 0;
    }
    else {
        for(int k = 0; k < thread_number; k++) {
            if(operation->in_progress[k] == op_n) {
                return 1;
            }
        }
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
                    printf("Ocorreu um erro a apagar o elemento %s da árvore", request->key);
                    if((request->op_n > operation->max_proc))
                        operation->max_proc = request->op_n;
                } else {
                    if((request->op_n > operation->max_proc))
                        operation->max_proc = request->op_n;
                }
            pthread_mutex_unlock(&tree_lock);
        } else { //PUT
            pthread_mutex_lock(&tree_lock); 
            struct data_t *data;
            data = data_create2(request->datasize, request->data);
            if(tree_put(tree_s, request->key, data) == -1) {
                printf("Ocorreu um erro a colocar o elemento %s na árvore", request->key);
                if((request->op_n > operation->max_proc))
                    operation->max_proc = request->op_n;
            } else {
                if((request->op_n > operation->max_proc))
                    operation->max_proc = request->op_n;
            }
            free(request->data);
            pthread_mutex_unlock(&tree_lock);
        }
        queue_head = request->next_request;
        free(request->key);
        free(request);
        pthread_mutex_unlock(&queue_lock);
    }
    pthread_exit(NULL);
    return NULL;
}

void *thread_impressao(void *params){
	int *thread_number = (int *) params;

	printf("Thread %d a iniciar\n", *thread_number);

		process_request(params);

	printf("Thread %d a terminar\n", *thread_number);

	return 0;
}

/* Função que faz watch à mudança do estado da ligação.
*/
void connection_watcher_server(zhandle_t *zzh, int type, int state, const char *path, void* context) {
	if (type == ZOO_SESSION_EVENT) {
		if (state == ZOO_CONNECTED_STATE) {
			next_server->is_connected = 1; 
		} else {
			next_server->is_connected = 0; 
		}
	} 
}

void create_zookeeper_child_ephemeral_sequence() {
    char node_path[120] = "";
    strcat(node_path, root_path);
    strcat(node_path, "/node");
    int newpath_length = 1024;
    char* newpath = malloc(newpath_length);

    if(ZOK != zoo_create(next_server->zh, node_path, NULL, -1, & ZOO_OPEN_ACL_UNSAFE, ZOO_EPHEMERAL | ZOO_SEQUENCE, newpath, newpath_length)) {
        printf("Erro creating znode from path %s!\n", node_path);
        exit(EXIT_FAILURE);
    }

    printf("Ephemeral sequencial ZNode created! ZNode path: %s\n", newpath);
}

/* Função que faz watch aos filhos.
*/
static void child_watcher_server(zhandle_t *wzh, int type, int state, const char *zpath, void *watcher_ctx) {
	children_list =	(zoo_string *) malloc(sizeof(zoo_string));
	if (state == ZOO_CONNECTED_STATE)	 {
		if (type == ZOO_CHILD_EVENT) {
 			if (ZOK != zoo_wget_children(next_server->zh, root_path, child_watcher_server, watcher_ctx, children_list)) {
 				fprintf(stderr, "Error setting watch at %s!\n", root_path);
 			}
			fprintf(stderr, "\n=== znode listing === [ %s ]", root_path); 
            char* current_node = malloc(next_node_len);
            char* lastdigit = current_node[strlen(current_node) - 1];
            int current_node_num = atoi(lastdigit);
            int* lastd = malloc(children_list->count);
            char* next_node = malloc(next_node_len);
            char hnextbuffer[256];
            struct hostent *hostent_next;
            char *nextipbuffer;
            int next_port;
			for (int i = 0; i < children_list->count; i++)  {
                lastd[i] = atoi(children_list->data[i][strlen(children_list->data) - 1]);
                if (current_node_num == lastd[i]) {
                    for (int i = 0; i < sizeof(lastd); i++) {
                        int next_node_num = -1;
                        for (int j = i + 1; j < sizeof(lastd); j++) {
                            if (lastd[i] < lastd[j]) {
                                next_node_num = lastd[j];
                                break;
                            }
                        }
                        for (int i = 0; i < children_list->count; i++)  {
                            if (next_node_num == atoi(children_list->data[i][strlen(children_list->data) - 1])) {
                                next_node = children_list->data[i];
                            }
                        }
                    }
                } else {
                    printf("O nosso node não se encontra na lista");
                }
				fprintf(stderr, "\n(%d): %s", i+1, children_list->data[i]);
			}
            int next_name = gethostname(hnextbuffer, sizeof(hnextbuffer));
            hostent_next = gethostbyname(hnextbuffer);
            nextipbuffer = inet_ntoa(*((struct in_addr *) hostent_next->h_addr_list[0])); 
            strcat(nextipbuffer,":");
            strcat(nextipbuffer, next_port);
			fprintf(stderr, "\n=== done ===\n");
		 } 
	 }
	 free(children_list);
}

/* Função que liga o ZooKeeper.
*/
int zookeeper_connect_server(int host_port) {
    next_server->zh = zookeeper_init(host_port, connection_watcher_server,	2000, 0, NULL, 0); 
	if (next_server->zh == NULL)	{
		fprintf(stderr, "Error connecting to ZooKeeper server!\n");
	    exit(EXIT_FAILURE);
	}

    int h_name = gethostname(hbuffer, sizeof(hbuffer));
    hostent_s = gethostbyname(hbuffer);
    ipbuffer = inet_ntoa(*((struct in_addr *) hostent_s->h_addr_list[0])); 
    strcat(ipbuffer,":");
    strcat(ipbuffer, host_port);
    return 0;
}

int connect_zookeeper(char *IP, char * port) {
    int retval;
    zookeeper_connect_server(port);
    if(next_server->is_connected) {
        if(ZNONODE == zoo_exists(next_server->zh, root_path, 0, NULL)) {
            printf("Ocorrue um erro, o node ainda não existe");

            if(ZOK == zoo_create(next_server->zh, root_path, NULL, -1, &ZOO_OPEN_ACL_UNSAFE, 0, NULL, 0) ){
                printf("O node foi criado");
                create_zookeeper_child_ephemeral_sequence();
            } else {
                printf("Erro ao criar o node");
                free(next_server);
                return -1;
            }
        }
        if (ZOK != zoo_wget_children(zh, root_path, &child_watcher_server, watcher_ctx, children_list)) {
				printf("Error setting watch at %s!\n", root_path);
		}
        return 0;        
    }
    return -1;
}