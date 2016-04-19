/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename: typechecker.h
*/

#ifndef SEMANTIC_H_INCLUDED
#define SEMANTIC_H_INCLUDED

#include "symboltable.h"
#include "parser.h"
#include "typechecker.h"

void handle_oth_stmts(parseTree stmt_it, hashtable *ht, char* scope);
void handle_stmts(parseTree stmts, hashtable *ht, char* scope);

#endif