/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "inet.h"
#include "client_stub.h"
#include "client_stub-private.h"
#include "message-private.h"
#include "sdmessage.pb-c.h"

/* Esta função deve:
 * - Obter o endereço do servidor (struct sockaddr_in) a base da
 *   informação guardada na estrutura rtree;
 * - Estabelecer a ligação com o servidor;
 * - Guardar toda a informação necessária (e.g., descritor do socket)
 *   na estrutura rtree;
 * - Retornar 0 (OK) ou -1 (erro).
 */
int network_connect(struct rtree_t *rtree) {

	// Cria socket TCP
	if ((rtree->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Erro ao criar socket TCP");
		return -1;
	}

	// Estabelece conexão com o servidor definido em server
	if (connect(rtree->sockfd, (struct sockaddr *) &rtree->socket, sizeof(rtree->socket)) < 0) {
		perror("Erro ao conectar-se ao servidor");
		close(rtree->sockfd);
		return -1;
	}

	return 0;
}

/* Esta função deve:
 * - Obter o descritor da ligação (socket) da estrutura rtree_t;
 * - Serializar a mensagem contida em msg;
 * - Enviar a mensagem serializada para o servidor;
 * - Esperar a resposta do servidor;
 * - De-serializar a mensagem de resposta;
 * - Retornar a mensagem de-serializada ou NULL em caso de erro.
 */
MessageT *network_send_receive(struct rtree_t * rtree, MessageT *msg) {

	int msgLen = message_t__get_packed_size(msg);
	int len = htonl(msgLen);
	uint8_t *buf = malloc(len);

	message_t__pack(msg, buf);

	write(rtree->sockfd, &len, sizeof(int));
	write_all(rtree->sockfd, buf, len);
	free(buf);

	int len_received;
	read(rtree->sockfd, &len_received,sizeof(int));
	msgLen = ntohl(len_received);

	uint8_t str[msgLen];
  	read_all(rtree->sockfd,str, msgLen);

	str[msgLen] = '\0';

	msg = message_t__unpack(NULL, msgLen, str);

	if(msg->opcode != MESSAGE_T__OPCODE__OP_ERROR) {
		return msg;
	}

	return NULL;
 
}

/* A função network_close() fecha a ligação estabelecida por
 * network_connect().
 */
int network_close(struct rtree_t * rtree) {
    return close(rtree->sockfd);
}