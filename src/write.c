#include "param.h"
#include <stdio.h>

void writeInt(Int *);
void writeBool(Bool *);
void writeClsr(Clsr *);
void writeClsrRec(ClsrRec *);
void writeEnv(Env *);
void writeVal(Val *);
void writeVar(Var *);
void writeOp(Op *);
void writeIf(If *);
void writeLet(Let *);
void writeFun(Fun *);
void writeApp(App *);
void writeLetRec(LetRec *);
void writeExp(Exp *);
void writeAsmp(Asmp *, int);
void writeInfr(Infr *);
void writeEval(Eval *);
void writeCncl(Cncl *, int);

void ind(int);
void writeRuleName(Cncl *);


void writeInt(Int *int_ob){
    printf("%d",int_ob->i);
    return;
}

void writeBool(Bool *bool_ob){
    if(bool_ob->b)printf("true");
    else printf("false");
    return;
}

void writeClsr(Clsr *clsr_ob){
    printf("(");
    writeEnv(clsr_ob->env_);
    printf(")[fun ");
    writeVar(clsr_ob->arg);
    printf(" -> ");
    writeExp(clsr_ob->exp_);
    printf("]");
    return;
}

void writeClsrRec(ClsrRec *clsrrec_ob){
    printf("(");
    writeEnv(clsrrec_ob->env_);
    printf(")[rec ");
    writeVar(clsrrec_ob->fun);
    printf(" = fun ");
    writeVar(clsrrec_ob->arg);
    printf(" -> ");
    writeExp(clsrrec_ob->exp_);
    printf("]");
    return;
}

void writeEnv(Env *env_ob){
    if(env_ob==NULL)return;
    if(env_ob->prev!=NULL){
        writeEnv(env_ob->prev);
        printf(", ");
    }
    writeVar(env_ob->var_);
    printf(" = ");
    writeVal(env_ob->val_);
    return;
}

void writeVal(Val *val_ob){
    if(val_ob->val_type==INT_){
        writeInt(val_ob->u.int_);
    }else if(val_ob->val_type==BOOL_){
        writeBool(val_ob->u.bool_);
    }else if(val_ob->val_type==CLSR){
        writeClsr(val_ob->u.clsr_);
    }else{
        writeClsrRec(val_ob->u.clsrrec_);
    }
    return;
}

void writeVar(Var *var_ob){
    printf("%s",var_ob->var_name);
    return;
}

void writeOp(Op *op_ob){
    char paren1 = 0;
    char paren2 = 0;

    if(op_ob->exp1_->exp_type==IF || op_ob->exp1_->exp_type==LET || op_ob->exp1_->exp_type==LETREC){
        paren1 = 1;
    }
    if(op_ob->exp2_->exp_type==IF || op_ob->exp2_->exp_type==LET || op_ob->exp2_->exp_type==LETREC){
        paren2 = 1;
    }
    if(op_ob->op_type==TIMES && op_ob->exp1_->exp_type==OP){
        if(op_ob->exp1_->u.op_->op_type==PLUS || op_ob->exp1_->u.op_->op_type==MINUS){
            paren1 = 1;
        }
    }
    if(op_ob->op_type==TIMES && op_ob->exp2_->exp_type==OP){
        if(op_ob->exp2_->u.op_->op_type==PLUS || op_ob->exp2_->u.op_->op_type==MINUS){
            paren2 = 1;
        }
    }

    if(paren1)printf("(");
    writeExp(op_ob->exp1_);
    if(paren1)printf(")");
    if(op_ob->op_type==PLUS){
        printf(" + ");
    }else if(op_ob->op_type==TIMES){
        printf(" * ");
    }else if(op_ob->op_type==MINUS){
        printf(" - ");
    }else{
        printf(" < ");
    }
    if(paren2)printf("(");
    writeExp(op_ob->exp2_);
    if(paren2)printf(")");
    return;
}

void writeIf(If *if_ob){
    printf("if ");
    writeExp(if_ob->exp1_);
    printf(" then ");
    writeExp(if_ob->exp2_);
    printf(" else ");
    writeExp(if_ob->exp3_);
    return;
}

void writeLet(Let *let_ob){
    printf("let ");
    writeVar(let_ob->var_);
    printf (" = ");
    writeExp(let_ob->exp1_);
    printf (" in ");
    writeExp(let_ob->exp2_);
    return;
}

void writeFun(Fun *fun_ob){
    printf("fun ");
    writeVar(fun_ob->arg);
    printf(" -> ");
    writeExp(fun_ob->exp_);
    return;
}

void writeApp(App *app_ob){
    char paren1 = 0;
    char paren2 = 0;

    if(app_ob->exp1_->exp_type == IF || app_ob->exp1_->exp_type == LET || app_ob->exp1_->exp_type == FUN || app_ob->exp1_->exp_type == LETREC)paren1 = 1;
    if(app_ob->exp2_->exp_type == OP || app_ob->exp2_->exp_type == IF || app_ob->exp2_->exp_type == LET || app_ob->exp2_->exp_type == FUN || app_ob->exp2_->exp_type == LETREC || app_ob->exp2_->exp_type == APP)paren2 = 1;

    if(paren1)printf("(");
    writeExp(app_ob->exp1_);
    if(paren1)printf(")");
    printf(" ");
    if(paren2)printf("(");
    writeExp(app_ob->exp2_);
    if(paren2)printf(")");
    return;
}

void writeLetRec(LetRec *letrec_ob){
    printf("let rec ");
    writeVar(letrec_ob->fun);
    printf(" = fun ");
    writeVar(letrec_ob->arg);
    printf(" -> ");
    writeExp(letrec_ob->exp1_);
    printf(" in ");
    writeExp(letrec_ob->exp2_);
    return;
}

void writeExp(Exp *exp_ob){
    if(exp_ob->exp_type==INT){
        writeInt(exp_ob->u.int_);
    }else if(exp_ob->exp_type==BOOL){
        writeBool(exp_ob->u.bool_);
    }else if(exp_ob->exp_type==VAR){
        writeVar(exp_ob->u.var_);
    }else if(exp_ob->exp_type==OP){
        writeOp(exp_ob->u.op_);
    }else if(exp_ob->exp_type==IF){
        writeIf(exp_ob->u.if_);
    }else if(exp_ob->exp_type==LET){
        writeLet(exp_ob->u.let_);
    }else if(exp_ob->exp_type==FUN){
        writeFun(exp_ob->u.fun_);
    }else if(exp_ob->exp_type==APP){
        writeApp(exp_ob->u.app_);
    }else{
        writeLetRec(exp_ob->u.letrec_);
    }
    return;
}

void writeAsmp(Asmp *asmp_ob, int d){
    if(asmp_ob==NULL)return;
    printf("\n");
    writeCncl(asmp_ob->cncl_, d);
    if(asmp_ob->next!=NULL)printf(";");
    else printf("\n");
    writeAsmp(asmp_ob->next, d);
    return;
}

void writeInfr(Infr *infr_ob){
    printf("%d",infr_ob->int1);
    InfrOpType tmp = infr_ob->infr_type;
    if(tmp == PLUS)printf(" plus ");
    else if(tmp == MINUS)printf(" minus ");
    else if(tmp == TIMES)printf(" times ");
    else printf(" less than ");
    printf("%d",infr_ob->int2);
    printf(" is ");
    writeVal(infr_ob->val_);
    return;
}

void writeEval(Eval *eval_ob){
    writeEnv(eval_ob->env_);
    if(eval_ob->env_!=NULL)printf(" ");
    printf("|- ");
    writeExp(eval_ob->exp_);
    printf(" evalto ");
    writeVal(eval_ob->val_);
    return;
}

void writeCncl(Cncl *cncl_ob, int d){
    ind(d);
    if(cncl_ob->cncl_type==INFR)writeInfr(cncl_ob->u.infr_);
    else writeEval(cncl_ob->u.eval_);
    printf(" by ");
    writeRuleName(cncl_ob);
    printf(" {");
    writeAsmp(cncl_ob->asmp_, d+1);
    if(cncl_ob->asmp_!=NULL)ind(d);
    printf("}");
    return;
}
