#include "param.h"
#include <stdlib.h>
#include <string.h>

#ifdef DBG_ALL
#define DBG_CP
#endif

#ifdef DBG_CP
#include <stdio.h>
#endif

Int *copyInt(Int *);
Bool *copyBool(Bool *);
Clsr *copyClsr(Clsr *);
ClsrRec *copyClsrRec(ClsrRec *);
Consv *copyConsv(Consv *);
Env *copyEnv(Env *);
Val *copyVal(Val *);
Var *copyVar(Var *);
Op *copyOp(Op *);
If *copyIf(If *);
Let *copyLet(Let *);
Fun *copyFun(Fun *);
App *copyApp(App *);
LetRec *copyLetRec(LetRec *);
Conse *copyConse(Conse *);
Match *copyMatch(Match *);
Consp *copyConsp(Consp *);
Pat *copyPat(Pat *);
Clauses *copyClauses(Clauses *);
Exp *copyExp(Exp *);

Int *copyInt(Int *sample)
{
#ifdef DBG_CP
    printf("copyInt start\n");
#endif
    Int *ob = (Int *)malloc(sizeof(Int));
    ob->i = sample->i;
    return ob;
}

Bool *copyBool(Bool *sample)
{
#ifdef DBG_CP
    printf("copyBool start\n");
#endif
    Bool *ob = (Bool *)malloc(sizeof(Bool));
    ob->b = sample->b;
    return ob;
}

Clsr *copyClsr(Clsr *sample)
{
#ifdef DBG_CP
    printf("copyClsr start\n");
#endif
    Clsr *ob = (Clsr *)malloc(sizeof(Clsr));
    ob->env_ = copyEnv(sample->env_);
    ob->arg = copyVar(sample->arg);
    ob->exp_ = copyExp(sample->exp_);
    return ob;
}

ClsrRec *copyClsrRec(ClsrRec *sample)
{
#ifdef DBG_CP
    printf("copyClsrRec start\n");
#endif
    ClsrRec *ob = (ClsrRec *)malloc(sizeof(ClsrRec));
    ob->env_ = copyEnv(sample->env_);
    ob->fun = copyVar(sample->fun);
    ob->arg = copyVar(sample->arg);
    ob->exp_ = copyExp(sample->exp_);
    return ob;
}

Consv *copyConsv(Consv *sample)
{
#ifdef DBG_CP
    printf("copyConsv start\n");
#endif
    Consv *ob = (Consv *)malloc(sizeof(Consv));
    ob->val1_ = copyVal(sample->val1_);
    ob->val2_ = copyVal(sample->val2_);
    return ob;
}

Env *copyEnv(Env *sample)
{
    if (sample == NULL)
        return NULL;
#ifdef DBG_CP
    printf("copyEnv start\n");
#endif
    Env *ob = (Env *)malloc(sizeof(Env));
    ob->var_ = copyVar(sample->var_);
    ob->val_ = copyVal(sample->val_);
    ob->prev = copyEnv(sample->prev);
    return ob;
}

Val *copyVal(Val *sample)
{
#ifdef DBG_CP
    printf("copyVal start\n");
#endif
    Val *ob = (Val *)malloc(sizeof(Val));
    ob->val_type = sample->val_type;
    if (ob->val_type == INT_)
    {
        ob->u.int_ = copyInt(sample->u.int_);
    }
    else if (ob->val_type == BOOL_)
    {
        ob->u.bool_ = copyBool(sample->u.bool_);
    }
    else if (ob->val_type == CLSR)
    {
        ob->u.clsr_ = copyClsr(sample->u.clsr_);
    }
    else if (ob->val_type == CLSRREC)
    {
        ob->u.clsrrec_ = copyClsrRec(sample->u.clsrrec_);
    }
    else if (ob->val_type == CONS_)
    {
        ob->u.consv_ = copyConsv(sample->u.consv_);
    }
    return ob;
}

Var *copyVar(Var *sample)
{
#ifdef DBG_CP
    printf("copyVar start\n");
#endif
    Var *ob = (Var *)malloc(sizeof(Var));
    ob->var_name = (char *)malloc(sizeof(char) * (strlen(sample->var_name) + 1));
    strcpy(ob->var_name, sample->var_name);
    return ob;
};

Op *copyOp(Op *sample)
{
#ifdef DBG_CP
    printf("copyOp start\n");
#endif
    Op *ob = (Op *)malloc(sizeof(Op));
    ob->op_type = sample->op_type;
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
    return ob;
}

If *copyIf(If *sample)
{
#ifdef DBG_CP
    printf("copyIf start\n");
#endif
    If *ob = (If *)malloc(sizeof(If));
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
    ob->exp3_ = copyExp(sample->exp3_);
    return ob;
}

Let *copyLet(Let *sample)
{
#ifdef DBG_CP
    printf("copyLet start\n");
#endif
    Let *ob = (Let *)malloc(sizeof(Let));
    ob->var_ = copyVar(sample->var_);
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
    return ob;
}

Fun *copyFun(Fun *sample)
{
#ifdef DBG_CP
    printf("copyFun start\n");
#endif
    Fun *ob = (Fun *)malloc(sizeof(Fun));
    ob->arg = copyVar(sample->arg);
    ob->exp_ = copyExp(sample->exp_);
    return ob;
}

App *copyApp(App *sample)
{
#ifdef DBG_CP
    printf("copyApp start\n");
#endif
    App *ob = (App *)malloc(sizeof(App));
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
    return ob;
}

LetRec *copyLetRec(LetRec *sample)
{
#ifdef DBG_CP
    printf("copyLetRec start\n");
#endif
    LetRec *ob = (LetRec *)malloc(sizeof(LetRec));
    ob->fun = copyVar(sample->fun);
    ob->arg = copyVar(sample->arg);
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
    return ob;
}

Conse *copyConse(Conse *sample)
{
#ifdef DBG_CP
    printf("copyConse start\n");
#endif
    Conse *ob = (Conse *)malloc(sizeof(Conse));
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
    return ob;
}

Match *copyMatch(Match *sample)
{
#ifdef DBG_CP
    printf("copyMatch start\n");
#endif
    Match *ob = (Match *)malloc(sizeof(Match));
    ob->exp_ = copyExp(sample->exp_);
    ob->clauses_ = copyClauses(sample->clauses_);
    return ob;
}

Consp *copyConsp(Consp *sample)
{
#ifdef DBG_CP
    printf("copyConsp start\n");
#endif
    Consp *ob = (Consp *)malloc(sizeof(Consp));
    ob->pat1_ = copyPat(sample->pat1_);
    ob->pat2_ = copyPat(sample->pat2_);
    return ob;
}

Pat *copyPat(Pat *sample)
{
#ifdef DBG_CP
    printf("copyPat start\n");
#endif
    Pat *ob = (Pat *)malloc(sizeof(Pat));
    ob->pat_type = sample->pat_type;
    if (ob->pat_type == VARP)
    {
        ob->u.var_ = copyVar(sample->u.var_);
    }
    else if (ob->pat_type == CONSP)
    {
        ob->u.consp_ = sample->u.consp_;
    }
}

Clauses *copyClauses(Clauses *sample)
{
    if (sample == NULL)
        return NULL;
#ifdef DBG_CP
    printf("copyClauses start\n");
#endif
    Clauses *ob = (Clauses *)malloc(sizeof(Clauses));
    ob->pat_ = copyPat(sample->pat_);
    ob->exp_ = copyExp(sample->exp_);
    ob->next = copyClauses(sample->next);
    return ob;
}

Exp *copyExp(Exp *sample)
{
#ifdef DBG_CP
    printf("copyExp start\n");
#endif
    Exp *ob = (Exp *)malloc(sizeof(Exp));
    ob->exp_type = sample->exp_type;
    if (ob->exp_type == INT)
        ob->u.int_ = copyInt(sample->u.int_);
    else if (ob->exp_type == BOOL)
        ob->u.bool_ = copyBool(sample->u.bool_);
    else if (ob->exp_type == VAR)
        ob->u.var_ = copyVar(sample->u.var_);
    else if (ob->exp_type == OP)
        ob->u.op_ = copyOp(sample->u.op_);
    else if (ob->exp_type == IF)
        ob->u.if_ = copyIf(sample->u.if_);
    else if (ob->exp_type == LET)
        ob->u.let_ = copyLet(sample->u.let_);
    else if (ob->exp_type == FUN)
        ob->u.fun_ = copyFun(sample->u.fun_);
    else if (ob->exp_type == APP)
        ob->u.app_ = copyApp(sample->u.app_);
    else if (ob->exp_type == LETREC)
        ob->u.letrec_ = copyLetRec(sample->u.letrec_);
    else if (ob->exp_type == CONS)
        ob->u.conse_ = copyConse(sample->u.conse_);
    else if (ob->exp_type == MATCH)
        ob->u.match_ = copyMatch(sample->u.match_);
    return ob;
}
