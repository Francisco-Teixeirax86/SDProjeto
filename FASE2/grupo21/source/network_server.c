/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "tree_skel.h"
#include "message-private.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

struct sockaddr_in server;
int sockfd;

/* Função para preparar uma socket de receção de pedidos de ligação
 * num determinado porto.
 * Retornar descritor do socket (OK) ou -1 (erro).
 */
int network_server_init(short port) {
	// Cria socket TCP
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		perror("Erro ao criar socket");
		return -1;
	}
	// Preenche estrutura server para bind
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	// Faz bind
	if (bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0){
		perror("Erro ao fazer bind");
		close(sockfd);
		return -1;
	};
	// Faz listen
	if (listen(sockfd, 0) < 0){
		perror("Erro ao executar listen");
		close(sockfd);
		return -1;
	};
	return sockfd;
}

/* Esta função deve:
 * - Aceitar uma conexão de um cliente;
 * - Receber uma mensagem usando a função network_receive;
 * - Entregar a mensagem de-serializada ao skeleton para ser processada;
 * - Esperar a resposta do skeleton;
 * - Enviar a resposta ao cliente usando a função network_send.
 */
int network_main_loop(int listening_socket) {
	int newsocketfd;
	struct sockaddr_in client;
	socklen_t size_client;
	while ((newsocketfd = accept(listening_socket,(struct sockaddr *) &client, &size_client)) != -1) {
		
		int receiving = 0;
		while(receiving == 0) {
			MessageT *msg = network_receive(newsocketfd);

			if(msg == NULL ) {
				receiving = 1;
				close(newsocketfd)
				continue;
			}

			invoke(msg);

			if((network_send(newsocketfd, msg) == -1)) {
				close(newsocketfd);
				return -1;
			};
		}
		return 0;
    }
	return 0;
}

/* Esta função deve:
 * - Ler os bytes da rede, a partir do client_socket indicado;
 * - De-serializar estes bytes e construir a mensagem com o pedido,
 *   reservando a memória necessária para a estrutura message_t.
 */
MessageT *network_receive(int client_socket) {
	int nbytes = 0;
	int msg_size = 0;
	if (nbytes = read_all(client_socket, &msg_size, sizeof(int)) == -1) {
		close(client_socket);
		return NULL;
	}
	int host_size;
	host_size = ntohl(msg_size);
	char *buf = malloc(host_size);
	if (nbytes = read_all(client_socket, buf, host_size) == -1) {
		close(client_socket);
		return NULL;
	}

	MessageT *msg = (MessageT * ) malloc(sizeof(MessageT));
	if(msg == NULL) {
		return NULL;
	}

	*msg = message_t__unpack(NULL, host_size, buf);
	
	return msg;

}

/* Esta função deve:
 * - Serializar a mensagem de resposta contida em msg;
 * - Libertar a memória ocupada por esta mensagem;
 * - Enviar a mensagem serializada, através do client_socket.
 */
int network_send(int client_socket, MessageT *msg) {
	int msg_psize = message_t__get_packed_size(msg);
	int net_size = htonl(msg_psize);
	char *buf = malloc(msg_psize);
	message_t__pack(msg, buf);
	if (nbytes = write_all(client_socket, &msg_size, sizeof(int)) == -1) {
		close(client_socket);
		return -1;
	}
	if (nbytes = write_all(client_socket, buf, net_size) == -1) {
		close(client_socket);
		return -1;
	}
	message_t__free_unpacked(msg, NULL);
	free(buf);
    return 0;
}

/* A função network_server_close() liberta os recursos alocados por
 * network_server_init().
 */
int network_server_close() {
    return close(sockfd);
}
