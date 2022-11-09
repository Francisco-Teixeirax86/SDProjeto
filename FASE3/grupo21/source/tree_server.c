/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "inet.h"
#include "network_server.h"
#include "tree_skel.h"


struct rtree_t *tree;

int main(int argc, char *argv[]) {

	if(argc != 2) {
		printf("Certifique-se que executou o programa corretamente, ./serve <port>");
		printf("\n");
		return -1;
	}

	int socket = network_server_init(atoi(argv[1]));
	if(socket == -1) {
		printf("Ocorreu um erro ao criar o server");
	}
	network_main_loop(socket);
	network_server_close();
	tree_skel_destroy();


}