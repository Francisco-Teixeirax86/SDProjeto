/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#ifndef _TREE_SKEL_H
#define _TREE_SKEL_H

#include "sdmessage.pb-c.h"
#include "tree.h"

struct op_proc {
	int max_proc; //regista o maior identificador das operações de escrita já concluídas
	int* in_progress; //regista o identificador das operações de escrita que estão a ser atendidas por um conjunto de threads dedicadas às escritas
};

#endif