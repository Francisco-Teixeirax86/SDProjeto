/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "data.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data_t *data_create(int size){
    
    struct data_t *newData = malloc(sizeof(struct data_t));
    if(newData == NULL){
        free(newData);
        return NULL;
    }
    if(size>0){
        newData -> datasize = size;
    } else {
        free(newData);
        return NULL;
    }
    newData -> data = malloc(size);
    if (newData->data == NULL) {
        free(newData);
        return NULL;
    }
    return newData;
}

struct data_t *data_create2(int size, void *data){

    struct data_t *newData = malloc(sizeof(struct data_t));
    if(newData == NULL){
        free(newData);
        return NULL;
    }
    if(size>0){
        newData -> datasize = size;
    } else {
        free(newData);
        return NULL;
    }
    if(data == NULL){
        free(newData);
        return NULL;
    }
    newData -> data = data;
    return newData;
}

void data_destroy(struct data_t *data){
    if(data != NULL){
        if (data->data != NULL) {
            free(data->data);
        }
        free(data);
    }
}

struct data_t *data_dup(struct data_t *data){
    if(data != NULL && data -> datasize > 0 && data -> data != NULL){
       void *copyData = malloc (data->datasize);
       memcpy(copyData, data->data, data->datasize);
       return data_create2(data->datasize, copyData);
    } else {
        return NULL;
    }
}



void data_replace(struct data_t *data, int new_size, void *new_data){
        free(data->data);
        data->datasize = new_size;
        data->data = new_data;
}