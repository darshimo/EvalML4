#include "param.h"
#include <stdio.h>

void debugInt(Int *, int);
void debugBool(Bool *, int);
void debugClsr(Clsr *, int);
void debugClsrRec(ClsrRec *, int);
void debugEnv(Env *, int);
void debugVal(Val *, int);
void debugVar(Var *, int);
void debugOp(Op *, int);
void debugIf(If *, int);
void debugLet(Let *, int);
void debugFun(Fun *, int);
void debugApp(App *, int);
void debugLetRec(LetRec *, int);
void debugExp(Exp *, int);
void debugInfr(Infr *, int);
void debugEval(Eval *, int);
void debugCncl(Cncl *, int);
void tree(int);


void debugInt(Int *int_ob, int d){
    tree(d);
    printf("int\n");
    tree(d+1);
    printf("%d\n",int_ob->i);
    return;
}

void debugBool(Bool *bool_ob, int d){
    tree(d);
    printf("bool\n");
    tree(d+1);
    if(bool_ob->b)printf("true\n");
    else printf("false\n");
    return;
}

void debugClsr(Clsr *clsr_ob, int d){
    tree(d);
    printf("clsr\n");
    debugEnv(clsr_ob->env_,d+1);
    debugVar(clsr_ob->arg,d+1);
    debugExp(clsr_ob->exp_,d+1);
    return;
}

void debugClsrRec(ClsrRec *clsrrec_ob, int d){
    tree(d);
    printf("clsrrec\n");
    debugEnv(clsrrec_ob->env_,d+1);
    debugVar(clsrrec_ob->fun,d+1);
    debugVar(clsrrec_ob->arg,d+1);
    debugExp(clsrrec_ob->exp_,d+1);
    return;
}

void debugEnv(Env *env_ob, int d){
    if(env_ob==NULL){
        tree(d);
        printf("env\n");
        return;
    }
    debugEnv(env_ob->prev,d);
    debugVar(env_ob->var_,d+1);
    debugVal(env_ob->val_,d+1);
    return;
};

void debugVal(Val *val_ob, int d){
    tree(d);
    printf("val\n");
    if(val_ob->val_type==INT_){
        debugInt(val_ob->u.int_,d+1);
    }else if(val_ob->val_type==BOOL_){
        debugBool(val_ob->u.bool_,d+1);
    }else if(val_ob->val_type==CLSR){
        debugClsr(val_ob->u.clsr_,d+1);
    }else{
        debugClsrRec(val_ob->u.clsrrec_,d+1);
    }
    return;
};

void debugVar(Var *var_ob, int d){
    tree(d);
    printf("var\n");
    tree(d+1);
    printf("%s\n",var_ob->var_name);
    return;
}

void debugOp(Op *op_ob, int d){
    tree(d);
    if(op_ob->op_type==PLUS)printf("op(+)\n");
    else if(op_ob->op_type==TIMES)printf("op(*)\n");
    else if(op_ob->op_type==MINUS)printf("op(-)\n");
    else printf("op(<)\n");
    debugExp(op_ob->exp1_,d+1);
    debugExp(op_ob->exp2_,d+1);
    return;
};

void debugIf(If *if_ob, int d){
    tree(d);
    printf("if\n");
    debugExp(if_ob->exp1_,d+1);
    debugExp(if_ob->exp2_,d+1);
    debugExp(if_ob->exp3_,d+1);
    return;
};

void debugLet(Let *let_ob, int d){
    tree(d);
    printf("let\n");
    debugVar(let_ob->var_,d+1);
    debugExp(let_ob->exp1_,d+1);
    debugExp(let_ob->exp2_,d+1);
    return;
}

void debugFun(Fun *fun_ob, int d){
    tree(d);
    printf("fun\n");
    debugVar(fun_ob->arg,d+1);
    debugExp(fun_ob->exp_,d+1);
    return;
}

void debugApp(App *app_ob, int d){
    tree(d);
    printf("app\n");
    debugExp(app_ob->exp1_,d+1);
    debugExp(app_ob->exp2_,d+1);
    return;
}

void debugLetRec(LetRec *letrec_ob, int d){
    tree(d);
    printf("letrec\n");
    debugVar(letrec_ob->fun,d+1);
    debugVar(letrec_ob->arg,d+1);
    debugExp(letrec_ob->exp1_,d+1);
    debugExp(letrec_ob->exp2_,d+1);
    return;
}

void debugExp(Exp *exp_ob, int d){
    tree(d);
    printf("exp\n");
    if(exp_ob->exp_type==INT){
        debugInt(exp_ob->u.int_,d+1);
    }else if(exp_ob->exp_type==BOOL){
        debugBool(exp_ob->u.bool_,d+1);
    }else if(exp_ob->exp_type==VAR){
        debugVar(exp_ob->u.var_,d+1);
    }else if(exp_ob->exp_type==OP){
        debugOp(exp_ob->u.op_,d+1);
    }else if(exp_ob->exp_type==IF){
        debugIf(exp_ob->u.if_,d+1);
    }else if(exp_ob->exp_type==LET){
        debugLet(exp_ob->u.let_,d+1);
    }else if(exp_ob->exp_type==FUN){
        debugFun(exp_ob->u.fun_,d+1);
    }else if(exp_ob->exp_type==APP){
        debugApp(exp_ob->u.app_,d+1);
    }else{
        debugLetRec(exp_ob->u.letrec_,d+1);
    }
    return;
};

void debugInfr(Infr *infr_ob, int d){
    tree(d);
    printf("infr\n");
    return;
};

void debugEval(Eval *eval_ob, int d){
    tree(d);
    printf("eval\n");

    debugEnv(eval_ob->env_,d+1);
    debugExp(eval_ob->exp_,d+1);
    debugVal(eval_ob->val_,d+1);
    return;
};

void debugCncl(Cncl *cncl_ob,int d){
    tree(d);
    printf("cncl\n");
    if(cncl_ob->cncl_type==INFR){
        debugInfr(cncl_ob->u.infr_,d+1);
    }else{
        debugEval(cncl_ob->u.eval_,d+1);
    }
    return;
}
