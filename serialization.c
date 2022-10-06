#include "data.h"
#include "entry.h"
#include "serialization.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/* Serializa todas as keys presentes no array de strings keys
 * para o buffer keys_buf que será alocado dentro da função.
 * O array de keys a passar em argumento pode ser obtido através 
 * da função tree_get_keys. Para além disso, retorna o tamanho do
 * buffer alocado ou -1 em caso de erro.
 */
int keyArray_to_buffer(char **keys, char **keys_buf) {

    if(keys == NULL || keys_buf == NULL) {
        return -1;
    }

    int i = 0;
    int keysSize = 0;
    while(keys[i] != NULL){
        keysSize += strlen(keys[i]);
        i++;
    }
    int bufferSize = sizeof(char)*keysSize;
    *keys_buf = malloc(bufferSize+sizeof(int));
    if(*keys_buf == NULL) {
        return -1;
    }
    sprintf(keys_buf[0], "%d", bufferSize);
    i = 1;
    while(keys[i] != NULL){
        char *tempChar = malloc(strlen(keys[i]));
        memcpy(tempChar, keys[i], sizeof(int));
        keys_buf[i] = tempChar;
        free(tempChar);
        i++;
    }

    return bufferSize;
}

/* De-serializa a mensagem contida em keys_buf, com tamanho
 * keys_buf_size, colocando-a e retornando-a num array char**,
 * cujo espaco em memória deve ser reservado. Devolve NULL
 * em caso de erro.
 */
char** buffer_to_keyArray(char *keys_buf, int keys_buf_size){

    if(keys_buf == NULL || keys_buf_size<0){
        return NULL;
    }

    char **returnArray = malloc(keys_buf_size-sizeof(int));

    if(returnArray == NULL){
        return NULL;
    }
    
    int i = 0;

    while(keys_buf[i] != '\0'){
        char *tempChar = malloc(strlen(keys_buf[i+1]));
        memcpy(tempChar, keys_buf[i+1], sizeof(int));
        returnArray[i] = tempChar;
        free(tempChar);
        i++;
    }

    return returnArray;
}
