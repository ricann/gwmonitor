#ifndef MATRIX_H
#define MATRIX_H

#include "commoninc_std.h"

//ricann 20150823
typedef	unsigned char uint8;
typedef unsigned short uint16;
typedef	unsigned int uint32;

typedef struct MyMatrix{
    uint32 row;
    uint32 colum;
    //uint32 rowlen;
    //uint8 * data;
    uint8 ** rowpoint;
}*mymatrix;

int matrix_init(uint32 rownum, uint32 columnum, mymatrix mat);
int matrix_inverse(mymatrix A,mymatrix A_1);
int matrix_equations(mymatrix A,uint8* D, uint32 size);

#endif // MATRIX_H
