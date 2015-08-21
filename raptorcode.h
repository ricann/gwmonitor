#ifndef RAPTORCODE_H
#define RAPTORCODE_H

#include "def.h"
#include "matrix.h"

typedef struct RaptorParam{
    uint32 K;
    uint32 S;
    uint32 L;
    uint32 H;
    mymatrix Amat;
    mymatrix A_1mat;
}*RParam;

typedef struct Triple{
    uint32 a;
    uint32 b;
    uint8 d;
}*triple;

typedef struct RaptorParam_dec{
    uint32 K;
    uint32 S;
    uint32 L;
    uint32 H;
//	uint32 M;
    uint32 N;
    char timestamp[20];/*********addition : 时间戳***********/
    mymatrix Amat_dec;
    uint16* list;
}*RParam_dec;

void raptor_init(uint32 k,uint32 n, RParam_dec parameter);

void raptor_parameterfree(RParam_dec parameter);

uint32 raptor_decode(RParam_dec parameter, uint8* input_src, uint8* output_return, uint32 T);
void raptor_free(uint8* pointer);

#endif // RAPTORCODE_H
