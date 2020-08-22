#ifndef UTILS_H
#define UTILS_H

void pack2shorts(unsigned short i, unsigned short j, unsigned int* k) {
    *k = ((i<<16) | ((j) & 0xffff));
}

void unpack2shorts (unsigned int i, unsigned short *j, unsigned short *k) {
    *j = (unsigned short) i;
    *k = (unsigned short) (i >> 16);
}

#endif