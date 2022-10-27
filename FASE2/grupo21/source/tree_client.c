/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "inet.h"
#include "client_stub-private.h"
#include "client_stub.h"

struct rtree_t *tree;

int main(int argc, char *argv[]) {

	printf("Bem-vindo cliente");
	printf("\n");
	tree = rtree_connect((char *)argv[1]);
	if(tree == NULL) {
		printf("Ocorreu um erro na inicialização do programa. Certifique-se de que está a chamar o programa com 'ficheiro.c' 'hostname:port");
	}

	int quit = 0;
	while(quit == 0) {
		char* command = malloc(100);
		printf("Introduza um comamdo para ser executado sobre a árvore");
		printf("\n");
		char input [100];
		fgets(input, 100, stdin);
		command = strtok(input, " \n");
		printf("test2");
		if(strcmp(command, "size") == 0) {
			printf("test");
			if(rtree_size(tree) == -1) {
				printf("Ocorreu um erro na busca de size");
			}
			printf("\n");
		} else if(strcmp(command, "quit") == 0) {
			rtree_disconnect(tree);
			quit = 1;
			printf("\n");
		} else {
			printf("ola");
		}
 	}
	return 0;
}