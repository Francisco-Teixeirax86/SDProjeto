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
    *keys_buf = malloc(bufferSize);

    if(*keys_buf == NULL) {
        return -1;
    }

    i = 0;
    while(keys[i] != NULL){
        char *tempKey = malloc(sizeof(char)*strlen(keys[i]));
        memcpy(tempKey, keys[i], sizeof(int));
        keys_buf[i] = tempKey;
        free(tempKey);
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

    char **returnArray = malloc(keys_buf_size*sizeof(char));

    if(returnArray == NULL){
        return NULL;
    }
    
    char *token = strtok(keys_buf, "\0");
    int i = 0;

    while(token != NULL){
        char *tempToken = malloc(sizeof(char)*strlen(token));
        memcpy(tempToken, token, sizeof(char)*strlen(token));
        returnArray[i] = tempToken;
        token = strtok(keys_buf, "\0");
        free(tempToken);
        i++;
    }

    return returnArray;
}