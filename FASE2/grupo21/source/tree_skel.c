/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "sdmessage.pb-c.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    
}