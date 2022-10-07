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

    int keysCounter = 0;
    int keySize = 0;
    int bufferCounter = 0;
    while(keys[keysCounter] != NULL){
        keySize += strlen(keys[keysCounter]);
        keysCounter++;
    }
    keys_buf = malloc(sizeof(int)*keysCounter+keySize);

    if(keys_buf == NULL) {
        return -1;
    }

    keysCounter = 0;
    while(keys[keysCounter] != NULL){
        memcpy(keys_buf[bufferCounter], (int*) strlen(keys[keysCounter]), sizeof(int));
        memcpy(keys_buf[bufferCounter+1], keys[keysCounter], strlen(keys[keysCounter]));
        keysCounter++;
        bufferCounter += 2;
    }
    

    return sizeof(int)*keysCounter+keySize;
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