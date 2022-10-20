/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/

#include "sdmessage.pb-c.h"
#include "inet.h"
#include "message-private.h"

int write_all(int sock, char *buf, int len) {
    int bufsize = len;
    while(len > 0) {
        int res = write(sock, buf, len);
        if(res < 0) {
            if(errno == EINTR) continue;
            perror(“write failed:”);
            return res;
        }
        buf += res;
        len -= res;
    }
    return bufsize;
}

int read_all(int sock, char *buf, int len) {
    int res;
    int read = 0;
    while (read < len) {
        res = read(sock, buf + read, len - read);
        if (res < 1) { //error
            return res;
        }
        read = read + res;
    }
    return read;
}