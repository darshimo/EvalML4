#include "param.h"
#include <stdlib.h>
#include <string.h>

//#define DEBUG
#ifdef DEBUG
#include <stdio.h>
#endif

Int *copyInt(Int *);
Bool *copyBool(Bool *);
Clsr *copyClsr(Clsr *);
ClsrRec *copyClsrRec(ClsrRec *);
Env *copyEnv(Env *);
Val *copyVal(Val *);
Var *copyVar(Var *);
Op *copyOp(Op *);
If *copyIf(If *);
Let *copyLet(Let *);
Fun *copyFun(Fun *);
App *copyApp(App *);
LetRec *copyLetRec(LetRec *);
Exp *copyExp(Exp *);


Int *copyInt(Int *sample){
#ifdef DEBUG
    printf("copyInt start\n");
#endif
    Int *ob = (Int *)malloc(sizeof(Int));
    ob->i = sample->i;
#ifdef DEBUG
    printf("copyInt end\n");
#endif
    return ob;
}

Bool *copyBool(Bool *sample){
#ifdef DEBUG
    printf("copyBool start\n");
#endif
    Bool *ob = (Bool *)malloc(sizeof(Bool));
    ob->b = sample->b;
#ifdef DEBUG
    printf("copyBool end\n");
#endif
    return ob;
}

Clsr *copyClsr(Clsr *sample){
#ifdef DEBUG
    printf("copyClsr start\n");
#endif
    Clsr *ob = (Clsr *)malloc(sizeof(Clsr));
    ob->env_ = copyEnv(sample->env_);
    ob->arg = copyVar(sample->arg);
    ob->exp_ = copyExp(sample->exp_);
#ifdef DEBUG
    printf("copyClsr end\n");
#endif
    return ob;
}

ClsrRec *copyClsrRec(ClsrRec *sample){
#ifdef DEBUG
    printf("copyClsrRec start\n");
#endif
    ClsrRec *ob = (ClsrRec *)malloc(sizeof(ClsrRec));
    ob->env_ = copyEnv(sample->env_);
    ob->fun = copyVar(sample->fun);
    ob->arg = copyVar(sample->arg);
    ob->exp_ = copyExp(sample->exp_);
#ifdef DEBUG
    printf("copyClsrRec end\n");
#endif
    return ob;
}

Env *copyEnv(Env *sample){
    if(sample==NULL)return NULL;
#ifdef DEBUG
    printf("copyEnv start\n");
#endif
    Env *ob = (Env *)malloc(sizeof(Env));
    ob->var_ = copyVar(sample->var_);
    ob->val_ = copyVal(sample->val_);
    ob->prev = copyEnv(sample->prev);
#ifdef DEBUG
    printf("copyEnv end\n");
#endif
    return ob;
}

Val *copyVal(Val *sample){
#ifdef DEBUG
    printf("copyVal start\n");
#endif
    Val *ob = (Val *)malloc(sizeof(Val));
    ob->val_type = sample->val_type;
    if(ob->val_type==INT_){
        ob->u.int_ = copyInt(sample->u.int_);
    }else if(ob->val_type==BOOL_){
        ob->u.bool_ = copyBool(sample->u.bool_);
    }else if(ob->val_type==CLSR){
        ob->u.clsr_ = copyClsr(sample->u.clsr_);
    }else{
        ob->u.clsrrec_ = copyClsrRec(sample->u.clsrrec_);
    }
#ifdef DEBUG
    printf("copyVal end\n");
#endif
    return ob;
}

Var *copyVar(Var *sample){
#ifdef DEBUG
    printf("copyVar start\n");
#endif
    Var *ob = (Var *)malloc(sizeof(Var));
    ob->var_name = (char *)malloc(sizeof(char)*(strlen(sample->var_name)+1));
    strcpy(ob->var_name, sample->var_name);
#ifdef DEBUG
    printf("copyVar end\n");
#endif
    return ob;
};

Op *copyOp(Op *sample){
#ifdef DEBUG
    printf("copyOp start\n");
#endif
    Op *ob = (Op *)malloc(sizeof(Op));
    ob->op_type = sample->op_type;
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
#ifdef DEBUG
    printf("copyOp end\n");
#endif
    return ob;
}

If *copyIf(If *sample){
#ifdef DEBUG
    printf("copyIf start\n");
#endif
    If *ob = (If *)malloc(sizeof(If));
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
    ob->exp3_ = copyExp(sample->exp3_);
#ifdef DEBUG
    printf("copyIf end\n");
#endif
    return ob;
}

Let *copyLet(Let *sample){
#ifdef DEBUG
    printf("copyLet start\n");
#endif
    Let *ob = (Let *)malloc(sizeof(Let));
    ob->var_ = copyVar(sample->var_);
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
#ifdef DEBUG
    printf("copyLet end\n");
#endif
    return ob;
}

Fun *copyFun(Fun *sample){
#ifdef DEBUG
    printf("copyFun start\n");
#endif
    Fun *ob = (Fun *)malloc(sizeof(Fun));
    ob->arg = copyVar(sample->arg);
    ob->exp_ = copyExp(sample->exp_);
#ifdef DEBUG
    printf("copyFun end\n");
#endif
    return ob;
}

App *copyApp(App *sample){
#ifdef DEBUG
    printf("copyApp start\n");
#endif
    App *ob = (App *)malloc(sizeof(App));
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
#ifdef DEBUG
    printf("copyApp end\n");
#endif
    return ob;
}

LetRec *copyLetRec(LetRec *sample){
#ifdef DEBUG
    printf("copyLetRec start\n");
#endif
    LetRec *ob = (LetRec *)malloc(sizeof(LetRec));
    ob->fun = copyVar(sample->fun);
    ob->arg = copyVar(sample->arg);
    ob->exp1_ = copyExp(sample->exp1_);
    ob->exp2_ = copyExp(sample->exp2_);
#ifdef DEBUG
    printf("copyLetRec end\n");
#endif
    return ob;
}

Exp *copyExp(Exp *sample){
#ifdef DEBUG
    printf("copyExp start\n");
#endif
    Exp *ob = (Exp *)malloc(sizeof(Exp));
    ob->exp_type = sample->exp_type;
    if(ob->exp_type==INT)ob->u.int_ = copyInt(sample->u.int_);
    else if(ob->exp_type==BOOL)ob->u.bool_ = copyBool(sample->u.bool_);
    else if(ob->exp_type==VAR)ob->u.var_ = copyVar(sample->u.var_);
    else if(ob->exp_type==OP)ob->u.op_ = copyOp(sample->u.op_);
    else if(ob->exp_type==IF)ob->u.if_ = copyIf(sample->u.if_);
    else if(ob->exp_type==LET)ob->u.let_ = copyLet(sample->u.let_);
    else if(ob->exp_type==FUN)ob->u.fun_ = copyFun(sample->u.fun_);
    else if(ob->exp_type==APP)ob->u.app_ = copyApp(sample->u.app_);
    else ob->u.letrec_ = copyLetRec(sample->u.letrec_);
#ifdef DEBUG
    printf("copyExp end\n");
#endif
    return ob;
}
