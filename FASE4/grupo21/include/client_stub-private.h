/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#ifndef _CLIENT_STUB_PRIVATE_H
#define _CLIENT_STUB_PRIVATE_H

#include "client_stub.h"
#include "inet.h"

struct rtree_t {
    struct sockaddr_in socket; //Informação pertinente ao server
    int sockfd; //Socket a usar pelo cliente
	struct rtree_t head;
	struct rtree_t tail;
};

#endif