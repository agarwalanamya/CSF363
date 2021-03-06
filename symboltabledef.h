/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:symboltableDef.h
*/

/* Used to define data structure used by symbol table
*/

#ifndef SYMBOLTABLEDEF_H_INCLUDED
#define SYMBOLTABLEDEF_H_INCLUDED

#include <stdio.h>

#define table_row 60

struct entry;
struct record_dec;

// a linkedlist that stores information of record types
struct record_dec {
    char *type;
    char *name;
    struct record_dec *next;
};

typedef struct record_dec record_dec;

typedef struct {
	// d2b
    char *key;
    //int
    char *type;
    //_main
    char *scope;
    // 2
    int width;
    int offset;
    // lineNo
    int lineNo;
    // pointer
    struct entry *next;
    int isInputParameter;
    int isOutputParameter;
    int assigned;
    int ParameterNumber;
    int isRecordDeclaration;
    int isRecordInstance;
    record_dec *record;
}entry;


typedef struct {
    int size;
    entry **table;
}hashtable;

hashtable *create( int size );
int hash(char *key, hashtable *ht);
entry *newentry(hashtable *ht, char *key, char *type, char * scope, int lineNo, int isInputParameter, int isOutputParameter, int ParameterNumber);
void upsert(hashtable *ht, char *key, char *type, char * scope, int lineNo, int isInputParameter, int isOutputParameter, int ParameterNumber);
entry *get(hashtable *ht, char *key, char * scope);

#endif
