#include "data.h"
#include "entry.h"
#include "serialization.h"
#include <stdio.h>

/* Serializa todas as keys presentes no array de strings keys
 * para o buffer keys_buf que será alocado dentro da função.
 * O array de keys a passar em argumento pode ser obtido através 
 * da função tree_get_keys. Para além disso, retorna o tamanho do
 * buffer alocado ou -1 em caso de erro.
 */
int keyArray_to_buffer(char **keys, char **keys_buf) {

    if(**keys == NULL) {
        return -1;
    }

    int size = htonl(sizeof(keys));
    int bufferSize = sizeof(int) + sizeof(keys);
    *keys_buf = malloc(bufferSize);

    if(*keys_buf == NULL) {
        return -1;
    }
    
    memcpy(*keys_buf, &size, sizeof(int));
    int i = 0;
    while(*keys + i == NULL) {
        memcpy(*keys_buf + sizeof(int) + sizeof(*keys + i), *keys + i, sizeof(keys));
    }
    return bufferSize;
}

/* De-serializa a mensagem contida em keys_buf, com tamanho
 * keys_buf_size, colocando-a e retornando-a num array char**,
 * cujo espaco em memória deve ser reservado. Devolve NULL
 * em caso de erro.
 */
char** buffer_to_keyArray(char *keys_buf, int keys_buf_size);
