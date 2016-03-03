// filename: lexer.c
// Batch 47
// 2013A7PS126P Gyanendra Mishra
// 2013A7PS151P Prabhjyot Singh Sodhi

// lexerDef.h     : Contains all data definitions used in lexer.c
#include<stdlib.h>

#ifndef LEXERDEF_H_INCLUDED
#define LEXERDEF_H_INCLUDED
typedef struct
{
    int id;
    char * name;
    int lineNo;
}tokenInfo;

int lineNo;
int state;
int offset;

typedef int buffersize;
typedef char* buffer;

buffer 	b = (buffer) malloc(100*sizeof(buffer));


#endif