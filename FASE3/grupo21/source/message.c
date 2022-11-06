/*
Grupo 21:
	Francisco Teixeira | FC56305
	Alexandre Rodrigues | FC54472
	Afonso Soares | FC56314
*/
#include "inet.h"
#include "sdmessage.pb-c.h"
#include "message-private.h"
#include <errno.h>

int write_all(int sock, uint8_t *buf, int len) {
    int bufsize = len;
    while(len > 0) {
        int res = write(sock, buf, len);
        if(res < 0) {
            if(errno == EINTR) continue;
            perror("write failed:");
            return res;
        }
        buf += res;
        len -= res;
    }
    return bufsize;
}

int read_all(int sock, uint8_t *buf, int len) {
    int res;
    int readlen = 0;
    while (readlen < len) {
        res = read(sock, buf + readlen, len - readlen);
        if (res < 1) {
            return res;
        }
        readlen = readlen + res;
    }
    return readlen;
}