#include "param.h"
#include <stdlib.h>

//#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#endif

void freeInt(Int *);
void freeBool(Bool *);
void freeClsr(Clsr *);
void freeClsrRec(ClsrRec *);
void freeEnv(Env *);
void freeVal(Val *);
void freeVar(Var *);
void freeOp(Op *);
void freeIf(If *);
void freeLet(Let *);
void freeFun(Fun *);
void freeApp(App *);
void freeLetRec(LetRec *);
void freeExp(Exp *);
void freeAsmp(Asmp *);
void freeInfr(Infr *);
void freeEval(Eval *);
void freeCncl(Cncl *);


void freeInt(Int *int_ob){
#ifdef DEBUG
    printf("free int\n");
#endif
    free(int_ob);
    return;
}

void freeBool(Bool *bool_ob){
#ifdef DEBUG
    printf("free bool\n");
#endif
    free(bool_ob);
    return;
}

void freeClsr(Clsr *clsr_ob){
#ifdef DEBUG
    printf("free clsr\n");
#endif
    freeEnv(clsr_ob->env_);
    freeVar(clsr_ob->arg);
    freeExp(clsr_ob->exp_);
    free(clsr_ob);
    return;
}

void freeClsrRec(ClsrRec *clsrrec_ob){
#ifdef DEBUG
    printf("free clsrrec\n");
#endif
    freeEnv(clsrrec_ob->env_);
    freeVar(clsrrec_ob->fun);
    freeVar(clsrrec_ob->arg);
    freeExp(clsrrec_ob->exp_);
    free(clsrrec_ob);
    return;
}

void freeEnv(Env *env_ob){
    if(env_ob==NULL)return;
#ifdef DEBUG
    printf("free env\n");
#endif
    freeVar(env_ob->var_);
    freeVal(env_ob->val_);
    freeEnv(env_ob->prev);
    free(env_ob);
    return;
}

void freeVal(Val *val_ob){
#ifdef DEBUG
    printf("free val\n");
#endif
    if(val_ob->val_type==INT_)freeInt(val_ob->u.int_);
    else if(val_ob->val_type==BOOL_)freeBool(val_ob->u.bool_);
    else if(val_ob->val_type==CLSR)freeClsr(val_ob->u.clsr_);
    else freeClsrRec(val_ob->u.clsrrec_);
    free(val_ob);
    return;
}

void freeVar(Var *var_ob){
#ifdef DEBUG
    printf("free var\n");
#endif
    free(var_ob->var_name);
    free(var_ob);
    return;
}

void freeOp(Op *op_ob){
#ifdef DEBUG
    printf("free op\n");
#endif
    freeExp(op_ob->exp1_);
    freeExp(op_ob->exp2_);
    free(op_ob);
    return;
}

void freeIf(If *if_ob){
#ifdef DEBUG
    printf("free if\n");
#endif
    freeExp(if_ob->exp1_);
    freeExp(if_ob->exp2_);
    freeExp(if_ob->exp3_);
    free(if_ob);
    return;
}

void freeLet(Let *let_ob){
#ifdef DEBUG
    printf("free let\n");
#endif
    freeVar(let_ob->var_);
    freeExp(let_ob->exp1_);
    freeExp(let_ob->exp2_);
    free(let_ob);
    return;
}

void freeFun(Fun *fun_ob){
#ifdef DEBUG
    printf("free fun\n");
#endif
    freeVar(fun_ob->arg);
    freeExp(fun_ob->exp_);
    free(fun_ob);
    return;
}

void freeApp(App *app_ob){
#ifdef DEBUG
    printf("free app\n");
#endif
    freeExp(app_ob->exp1_);
    freeExp(app_ob->exp2_);
    free(app_ob);
    return;
}

void freeLetRec(LetRec *letrec_ob){
#ifdef DEBUG
    printf("free letrec\n");
#endif
    freeVar(letrec_ob->fun);
    freeVar(letrec_ob->arg);
    freeExp(letrec_ob->exp1_);
    freeExp(letrec_ob->exp2_);
    return;
}

void freeExp(Exp *exp_ob){
#ifdef DEBUG
    printf("free exp\n");
#endif
    if(exp_ob->exp_type==INT)freeInt(exp_ob->u.int_);
    else if(exp_ob->exp_type==BOOL)freeBool(exp_ob->u.bool_);
    else if(exp_ob->exp_type==VAR)freeVar(exp_ob->u.var_);
    else if(exp_ob->exp_type==OP)freeOp(exp_ob->u.op_);
    else if(exp_ob->exp_type==IF)freeIf(exp_ob->u.if_);
    else if(exp_ob->exp_type==LET)freeLet(exp_ob->u.let_);
    else if(exp_ob->exp_type==FUN)freeFun(exp_ob->u.fun_);
    else if(exp_ob->exp_type==APP)freeApp(exp_ob->u.app_);
    else freeLetRec(exp_ob->u.letrec_);
    free(exp_ob);
    return;
}

void freeAsmp(Asmp *asmp_ob){
    if(asmp_ob==NULL)return;
#ifdef DEBUG
    printf("free asmp\n");
#endif
    freeCncl(asmp_ob->cncl_);
    freeAsmp(asmp_ob->next);
    free(asmp_ob);
    return;
}

void freeInfr(Infr *infr_ob){
#ifdef DEBUG
    printf("free infr\n");
#endif
    freeVal(infr_ob->val_);
    free(infr_ob);
    return;
}

void freeEval(Eval *eval_ob){
#ifdef DEBUG
    printf("free eval\n");
#endif
    freeEnv(eval_ob->env_);
    freeExp(eval_ob->exp_);
    freeVal(eval_ob->val_);
    free(eval_ob);
    return;
}

void freeCncl(Cncl *cncl_ob){
#ifdef DEBUG
    printf("free cncl\n");
#endif
    freeAsmp(cncl_ob->asmp_);
    if(cncl_ob->cncl_type==INFR)freeInfr(cncl_ob->u.infr_);
    else freeEval(cncl_ob->u.eval_);
    free(cncl_ob);
    return;
}
