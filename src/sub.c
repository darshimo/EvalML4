#include <stdio.h>
#include "param.h"

int cmpVar(Var *, Var *);
void error(char *);

void ind(int d)
{
    int i;
    for (i = 0; i < d; i++)
    {
        printf("  ");
    }
    return;
}

void tree(int d)
{
    int i;
    for (i = 0; i < d; i++)
    {
        printf("\x1b[%dm", (i % 6) + 31);
        if (i < d - 1)
            printf("│ ");
        else
            printf("├─");
    }
    printf("\x1b[39m");
    return;
}

void writeRuleName(Cncl *cncl_ob)
{
    RuleType tmp = cncl_ob->rule_type;
    if (tmp == M_VAR)
        printf("M-Var");
    else if (tmp == M_NIL)
        printf("M-Nil");
    else if (tmp == M_CONS)
        printf("M-Cons");
    else if (tmp == M_WILD)
        printf("M-Wild");
    else if (tmp == NM_CONSNIL)
        printf("NM-ConsNil");
    else if (tmp == NM_NILCONS)
        printf("NM-NilCons");
    else if (tmp == NM_CONSCONSL)
        printf("NM-ConsConsL");
    else if (tmp == NM_CONSCONSR)
        printf("NM-ConsConsR");
    else if (tmp == E_INT)
        printf("E-Int");
    else if (tmp == E_BOOL)
        printf("E-Bool");
    else if (tmp == E_IFT)
        printf("E-IfT");
    else if (tmp == E_IFF)
        printf("E-IfF");
    else if (tmp == E_PLUS)
        printf("E-Plus");
    else if (tmp == E_MINUS)
        printf("E-Minus");
    else if (tmp == E_TIMES)
        printf("E-Times");
    else if (tmp == E_LT)
        printf("E-Lt");
    else if (tmp == E_VAR)
        printf("E-Var");
    else if (tmp == E_LET)
        printf("E-Let");
    else if (tmp == E_FUN)
        printf("E-Fun");
    else if (tmp == E_APP)
        printf("E-App");
    else if (tmp == E_LETREC)
        printf("E-LetRec");
    else if (tmp == E_APPREC)
        printf("E-AppRec");
    else if (tmp == E_NIL)
        printf("E-Nil");
    else if (tmp == E_CONS)
        printf("E-Cons");
    else if (tmp == E_MATCHM1)
        printf("E-MatchM1");
    else if (tmp == E_MATCHM2)
        printf("E-MatchM2");
    else if (tmp == E_MATCHN)
        printf("E-MatchN");
    else if (tmp == B_PLUS)
        printf("B-Plus");
    else if (tmp == B_MINUS)
        printf("B-Minus");
    else if (tmp == B_TIMES)
        printf("B-Times");
    else
        printf("B-Lt");
    return;
}

Val *getVal(Env *eps, Var *x)
{
    if (eps == NULL)
        error("var is not found.");
    if (cmpVar(eps->var_, x) == 0)
        return eps->val_;
    return getVal(eps->prev, x);
}

Env *linkEnv(Env *ob1, Env *ob2)
{
    Env *tmp1 = copyEnv(ob1);
    Env *tmp2 = copyEnv(ob2);

    if (tmp2 == NULL)
    {
        return tmp1;
    }
    if (tmp1 == NULL)
    {
        return tmp2;
    }

    Env *ob = tmp2;

    while (tmp2->prev != NULL)
    {
        tmp2 = tmp2->prev;
    }
    tmp2->prev = tmp1;

    return ob;
}

int interCheckEnv(Env *ob1, Env *ob2)
{ // having common variables, return 1
    while (ob1 != NULL)
    {
        Var *var1 = ob1->var_;
        while (ob2 != NULL)
        {
            Var *var2 = ob2->var_;

            if (cmpVar(var1, var2) == 0)
                return 1;

            ob2 = ob2->prev;
        }
        ob1 = ob1->prev;
    }

    return 0;
}

Env *unionEnv(Env *ob1, Env *ob2)
{
    if (interCheckEnv(ob1, ob2))
    {
        error("envs have common variables.");
    }

    return linkEnv(ob1, ob2);
}