#include "param.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef DBG_ALL
#define DBG_READ
#define DBG_STRCT
#define DBG_DRV
#define DBG_FREE
#define DBG_WRITE
#endif

#ifdef DBG_STRCT
void debugCncl(Cncl *, int);
#endif

void error(char *);
Cncl *readCncl(char *);
void derivation(Cncl *, int);
int cmpVal(Val *, Val *);
Val *copyVal(Val *);
void freeCncl(Cncl *);
void writeCncl(Cncl *, int);
void texCncl(Cncl *);

int main(int argc, char *argv[])
{
    if (argc > 2)
        error("arg is not correct.\n");

    char *str = (char *)malloc(sizeof(char) * 501);

    if (argc == 1)
    {
        char ch;
        int cnt = 0;
        printf("input expression within 500 characters (end with ;)\n> ");
        while ((ch = fgetc(stdin)) != EOF)
        {
            if (ch == '\n')
            {
                printf("> ");
                continue;
            }
            if (ch == ';')
            {
                str[cnt] = '\0';
                break;
            }
            str[cnt] = ch;
            cnt++;
            if (cnt > 500)
            {
                printf("too long.");
                exit(EXIT_FAILURE);
            }
        }
        printf("\n");
    }
    else
    {
        char *filename = argv[1];
        FILE *fp;
        if ((fp = fopen(filename, "r")) == NULL)
        {
            printf("fopen error.");
            exit(EXIT_FAILURE);
        }
        fgets(str, 500, fp);
        int l = strlen(str);
        if (str[l - 1] == '\n')
            str[l - 1] = '\0';
    }

#ifdef DBG_READ
    printf("read start.\n");
#endif
    Cncl *cncl_ob = readCncl(str);
#ifdef DBG_READ
    printf("read complete.\n\n");
#endif

#ifdef DBG_STRCT
    printf("debug start.\n");
    debugCncl(cncl_ob, 0);
    printf("debug complete.\n\n");
#endif

#ifdef DBG_DRV
    printf("derivation start.\n");
#endif
    derivation(cncl_ob, 0);
#ifdef DBG_DRV
    printf("derivation complete.\n\n");
#endif

#ifdef DBG_WRITE
    printf("write start.\n");
#endif
#ifndef TEX
    writeCncl(cncl_ob, 0);
    printf("\n");
#else
    texCncl(cncl_ob);
#endif
#ifdef DBG_WRITE
    printf("write complete.\n\n");
#endif

#ifdef DBG_FREE
    printf("free start.\n");
#endif
    freeCncl(cncl_ob);
#ifdef DBG_FREE
    printf("free complete.\n\n");
#endif

    return 0;
}
