/*
    Batch No: 47
    Gyanendra Mishra 2013A7PS126P
    Prabhjyot Singh Sodhi 2013A7PS151P
    Filename:driver.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "semantic.h"
#include "codegen.h"

void printSize(int pt_size, int ast_size){
	printf("\n");
    printf(" %15s %25s %25s\n", "Tree Type", "Number of Nodes", "Memory Allocated" );
    printf(" %15s %25d %25d\n", "Parse Tree", pt_size, sizeof(parseTree)* pt_size);
    printf(" %15s %25d %25d\n", "AST", ast_size, sizeof(parseTree)* ast_size);
    printf("Compression: %.2f\n", ((pt_size-ast_size)/(float)pt_size)*100);
};

void commentFreeCode(char const* Filename){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(Filename, "r");
    if(fp == NULL){
        printf("Invalid source file\n");
        exit(-1);
    }
    while((read = getline(&line, &len, fp)) != -1){
        if(line[0] == '\n'){
            continue;
        }
        int position_of_comment = -1;
        int i = 0;
        while(i!=read){
            if(line[i] == '%'){
                position_of_comment = i;
                break;
            }
            i++;
        }

        if(position_of_comment == -1){
            printf("%s\n", line);
        }
        else if (position_of_comment != 0){
            line[position_of_comment] = '\0';
            printf("%s\n", line);
        }
    }
}

void printAllTokens(char const* Filename){
    FILE * fp;
    fp = fopen(Filename, "r");
    buffersize k = 25;
    lineNo=1;
    state = 1;

    buffer b;
    buffersize bufsize = 25;

    b = (buffer) malloc(sizeof(char)*bufsize);

    tokenInfo token = getNextToken(fp, b, k);
    printf("%25s%25s%25s\n", "Token Name", "Lexeme", "Line Number");

    while(strcmp(token.name, "$")!=0){
        printf("%25s%25s%25d\n",getCorrespondingToken(token.id),token.name,token.lineNo);
        state = 1;
        token = getNextToken(fp, b, k);
    }
    fclose(fp);
}

int main(int argc, char const *argv[])
{
    if (argc < 2){
        printf("Insufficient arguments provided, run as follows ./compiler testcase1.txt");
        return 0;
    }

    printf("---------------------------------------------------\n");
    printf("Level 4: Symbol Table/Type Checking/ Semantic Analysis works/ AST -- ALL WORK.\n");
    printf("---------------------------------------------------\n");

    while(1){
        printf("\n---------------------------------------------------\n");
        printf("Press a number to choose the corresponding option\n");
        // printf("Press 1 to see comment free code\n");
        printf("Press 1 to see a list of tokens generated by the lexer\n");
        printf("Press 2 for parsing and verifying syntactic correctness of code\n");
        printf("Press 3 for printing the abstract syntax tree\n");
        printf("Press 4 for printing the memory allocation of ast and parse tree\n");
        printf("Press 5 for printing the symbol table\n");
        printf("Press 6 for printing front end compilation, type checking and semantic correctness\n");
        printf("Press 7 for producing assembly code to code.asm\n");
        printf("Press 8 to exit!\n");
        printf("---------------------------------------------------\n");

        char c;
        int choice;
        scanf(" %c",&c);
        choice = c - '0';
        if(choice == 1)
            printAllTokens(argv[1]);
        else if(choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7)
        {
            table t = (int **) malloc(table_row * sizeof(int *));
            int i = 0;
            error_count = 0;

            for (i=0; i<table_row; i++)
                 t[i] = (int *) malloc(table_row * sizeof(int));


            FILE * fp;
            fp = fopen("grammar.txt", "r");

            createParseTable(fp, t);

            fclose(fp);

            error_in_lexer = 0;
            error_in_parsing = 0;
            symbolerror = 0;

            parseTree answer = parseInputSourceCode(argv[1], t);

            int ast_size  = 0;
            int pt_size = 0;

            if (choice == 2 && error_in_lexer == 0 && error_in_parsing == 0){
                fprintf(stdout, "\n %20s %15s %15s %15s %20s %15s %15s\n", "lexemeCurrentNode", "lineNo", "token", "valueIFNumber", "parentNodeSymbol", "ifLeafNode(Yes/No)", "NodeSymbol");
                printParseTree_r(answer, stdout, &pt_size, 1);
                printf("%s\n", "\nNo syntactic errors");
            }
            else if(choice == 2){
                printf("%s\n", "\nSyntactic errors exist, cant print");
            }
            else{
                pt_size = 0;
            	printParseTree_r(answer, stdout, &pt_size, -1);
            }

            if (choice  == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7){
                if(error_in_lexer == 0 && error_in_parsing == 0)
                    answer = ast(answer);

                if (choice == 3 && error_in_lexer == 0 && error_in_parsing == 0){
                    fprintf(stdout, "\n %20s %15s %15s %15s %20s %15s %15s\n", "lexemeCurrentNode", "lineNo", "token", "valueIFNumber", "parentNodeSymbol", "ifLeafNode(Yes/No)", "NodeSymbol");
                    printParseTree_r(answer, stdout, &ast_size, 1);
                }
                else if(choice == 3){
                    printf("%s\n", "Syntactic errors exist, ast not built");
                }

                if (choice == 4 && error_in_lexer == 0 && error_in_parsing == 0){
                	printParseTree_r(answer, stdout, &ast_size, -1);
                    printSize(pt_size, ast_size);
                }
                else if(choice == 4){
                    printf("%s\n", "Syntactic errors exist, ast not built");
                }

                if ((choice == 5 || choice == 6 || choice == 7) && error_in_parsing == 0 && error_in_lexer == 0){
                    hashtable *st = createSymbolTable(answer, 100);

                    if (choice == 5){
                        printSymbolTable(st, 100);
                    }

                    if(choice == 6 || choice == 7){
                        if(choice == 6 || choice == 7){
                            i = 0;
                            for(i=0 ;i< error_count; i++){
                                printf("%s", symboltable_errors[i]);
                            }
                            semanticAnalyzer(answer, st);
                        }
                        if(symbolerror == 0 && choice == 6){
                            printf("No Semantic or Syntactic Errors\n");
                        }
                        if (choice == 7 && symbolerror == 0){
                            codegen(answer, st);
                            printf("%s\n", "Find your file at code.asm");
                        }
                        else if(choice == 7){
                            printf("Cant compile as semantic errors exist");
                        }
                    }
                }
                else if (choice == 5 || choice == 6 || choice == 7){
                    printf("Can't proceed with symbol table creation, semantic analysis or asm creation as  syntactic errors exist\n");
                }

            }


        }
        else if(choice == 8 )
        {
            printf("\n\nThank You!\n");
                exit(0);
        }
        else {
            printf("Please enter valid input\n");
        }
    }


    return 0;
}
