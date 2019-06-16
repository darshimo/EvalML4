#include "param.h"
#include <stdio.h>

void texInt(Int *);
void texBool(Bool *);
void texClsr(Clsr *);
void texClsrRec(ClsrRec *);
void texConsv(Consv *);
void texEnv(Env *);
void texVal(Val *);
void texVar(Var *);
void texOp(Op *);
void texIf(If *);
void texLet(Let *);
void texFun(Fun *);
void texApp(App *);
void texLetRec(LetRec *);
void texConse(Conse *);
void texMatch(Match *);
void texExp(Exp *);
int texAsmp(Asmp *);
void texInfr(Infr *);
void texEval(Eval *);
void texCncl(Cncl *);

void ind(int);
void writeRuleName(Cncl *);


void texInt(Int *ob){
    printf("%d",ob->i);
    return;
}

void texBool(Bool *ob){
    if(ob->b)printf("{\\rm true}");
    else printf("{\\rm false}");
    return;
}

void texClsr(Clsr *ob){
    printf("(");
    texEnv(ob->env_);
    printf(")[{\\rm fun}~");
    texVar(ob->arg);
    printf("\\to ");
    texExp(ob->exp_);
    printf("]");
    return;
}

void texClsrRec(ClsrRec *ob){
    printf("(");
    texEnv(ob->env_);
    printf(")[{\\rm rec}~");
    texVar(ob->fun);
    printf("={\\rm fun}~");
    texVar(ob->arg);
    printf("\\to ");
    texExp(ob->exp_);
    printf("]");
    return;
}

void texConsv(Consv *ob){
    char paren = 0;
    if(ob->val1_->val_type==CONS_)paren=1;

    if(paren)printf("(");
    texVal(ob->val1_);
    if(paren)printf(")");
    printf(" :: ");
    texVal(ob->val2_);
    return;
}

void texEnv(Env *ob){
    if(ob==NULL)return;
    if(ob->prev!=NULL){
        texEnv(ob->prev);
        printf(",");
    }
    texVar(ob->var_);
    printf("=");
    texVal(ob->val_);
    return;
}

void texVal(Val *ob){
    if(ob->val_type==INT_){
        texInt(ob->u.int_);
    }else if(ob->val_type==BOOL_){
        texBool(ob->u.bool_);
    }else if(ob->val_type==CLSR){
        texClsr(ob->u.clsr_);
    }else if(ob->val_type==CLSRREC){
        texClsrRec(ob->u.clsrrec_);
    }else if(ob->val_type==CONS_){
        texConsv(ob->u.consv_);
    }else{
        printf("[]");
    }
    return;
}

void texVar(Var *ob){
    printf("{\\rm %s}",ob->var_name);
    return;
}

void texOp(Op *ob){
    char paren1 = 0;
    char paren2 = 0;

    if(ob->exp1_->exp_type==IF || ob->exp1_->exp_type==LET || ob->exp1_->exp_type==LETREC || ob->exp1_->exp_type==MATCH){
        paren1 = 1;
    }
    if(ob->exp2_->exp_type==IF || ob->exp2_->exp_type==LET || ob->exp2_->exp_type==LETREC || ob->exp2_->exp_type==MATCH){
        paren2 = 1;
    }
    if(ob->op_type==TIMES && ob->exp1_->exp_type==OP){
        if(ob->exp1_->u.op_->op_type==PLUS || ob->exp1_->u.op_->op_type==MINUS){
            paren1 = 1;
        }
    }
    if(ob->op_type==TIMES && ob->exp2_->exp_type==OP){
        if(ob->exp2_->u.op_->op_type==PLUS || ob->exp2_->u.op_->op_type==MINUS){
            paren2 = 1;
        }
    }

    if(paren1)printf("(");
    texExp(ob->exp1_);
    if(paren1)printf(")");
    if(ob->op_type==PLUS){
        printf(" + ");
    }else if(ob->op_type==TIMES){
        printf(" * ");
    }else if(ob->op_type==MINUS){
        printf(" - ");
    }else{
        printf(" < ");
    }
    if(paren2)printf("(");
    texExp(ob->exp2_);
    if(paren2)printf(")");
    return;
}

void texIf(If *ob){
    printf("{\\rm if}~");
    texExp(ob->exp1_);
    printf("~{\\rm then}~");
    texExp(ob->exp2_);
    printf("~{\\rm else}~");
    texExp(ob->exp3_);
    return;
}

void texLet(Let *ob){
    printf("{\\rm let}~");
    texVar(ob->var_);
    printf ("=");
    texExp(ob->exp1_);
    printf ("~{\\rm in}~");
    texExp(ob->exp2_);
    return;
}

void texFun(Fun *ob){
    printf("{\\rm fun}~");
    texVar(ob->arg);
    printf("\\to ");
    texExp(ob->exp_);
    return;
}

void texApp(App *ob){
    char paren1 = 0;
    char paren2 = 0;

    if(ob->exp1_->exp_type == IF || ob->exp1_->exp_type == LET || ob->exp1_->exp_type == FUN || ob->exp1_->exp_type == LETREC || ob->exp1_->exp_type == MATCH)paren1 = 1;
    if(ob->exp2_->exp_type == OP || ob->exp2_->exp_type == IF || ob->exp2_->exp_type == LET || ob->exp2_->exp_type == FUN || ob->exp2_->exp_type == LETREC || ob->exp2_->exp_type == APP || ob->exp2_->exp_type == CONS || ob->exp2_->exp_type == MATCH)paren2 = 1;

    if(paren1)printf("(");
    texExp(ob->exp1_);
    if(paren1)printf(")");
    printf("~");
    if(paren2)printf("(");
    texExp(ob->exp2_);
    if(paren2)printf(")");
    return;
}

void texLetRec(LetRec *ob){
    printf("{\\rm let~rec}~");
    texVar(ob->fun);
    printf("={\\rm fun}~");
    texVar(ob->arg);
    printf("\\to ");
    texExp(ob->exp1_);
    printf("~{\\rm in}~");
    texExp(ob->exp2_);
    return;
}

void texConse(Conse *ob){
    char paren1 = 0;
    char paren2 = 0;
    if(ob->exp1_->exp_type==OP || ob->exp1_->exp_type==IF || ob->exp1_->exp_type==LET || ob->exp1_->exp_type==FUN || ob->exp1_->exp_type==APP || ob->exp1_->exp_type==LETREC || ob->exp1_->exp_type==CONS)paren1 = 1;
    if(ob->exp2_->exp_type==OP || ob->exp2_->exp_type==IF || ob->exp2_->exp_type==LET || ob->exp2_->exp_type==FUN || ob->exp2_->exp_type==APP || ob->exp2_->exp_type==LETREC)paren2 = 1;

    if(paren1)printf("(");
    texExp(ob->exp1_);
    if(paren1)printf(")");
    printf(" :: ");
    if(paren2)printf("(");
    texExp(ob->exp2_);
    if(paren2)printf(")");
    return;
}

void texMatch(Match *ob){
    printf("{\\rm match}~");
    texExp(ob->exp1_);
    printf("~{\\rm with} [] \\to ");
    texExp(ob->exp2_);
    printf(" | ");
    texVar(ob->x);
    printf(" :: ");
    texVar(ob->y);
    printf("\\to ");
    texExp(ob->exp3_);
    return;
}

void texExp(Exp *ob){
    if(ob->exp_type==INT){
        texInt(ob->u.int_);
    }else if(ob->exp_type==BOOL){
        texBool(ob->u.bool_);
    }else if(ob->exp_type==VAR){
        texVar(ob->u.var_);
    }else if(ob->exp_type==OP){
        texOp(ob->u.op_);
    }else if(ob->exp_type==IF){
        texIf(ob->u.if_);
    }else if(ob->exp_type==LET){
        texLet(ob->u.let_);
    }else if(ob->exp_type==FUN){
        texFun(ob->u.fun_);
    }else if(ob->exp_type==APP){
        texApp(ob->u.app_);
    }else if(ob->exp_type==LETREC){
        texLetRec(ob->u.letrec_);
    }else if(ob->exp_type==CONS){
        texConse(ob->u.conse_);
    }else if(ob->exp_type==MATCH){
        texMatch(ob->u.match_);
    }else{
        printf("[]");
    }
    return;
}

int texAsmp(Asmp *ob){
    if(ob==NULL)return 0;
    texCncl(ob->cncl_);
    return 1 + texAsmp(ob->next);
}

void texInfr(Infr *ob){
    printf("%d",ob->int1);
    InfrOpType tmp = ob->infr_type;
    if(tmp == PLUS)printf("~{\\rm plus}~");
    else if(tmp == MINUS)printf("~{\\rm minus}~");
    else if(tmp == TIMES)printf("~{\\rm times}~");
    else printf("~{\\rm less~than}~");
    printf("%d",ob->int2);
    printf("~{\\rm is}~");
    texVal(ob->val_);
    return;
}

void texEval(Eval *ob){
    texEnv(ob->env_);
    if(ob->env_!=NULL)printf(" ");
    printf("\\vdash ");
    texExp(ob->exp_);
    printf("\\Downarrow ");
    texVal(ob->val_);
    return;
}

void texCncl(Cncl *ob){
    int n = texAsmp(ob->asmp_);

    if(n==0)printf("\\AxiomC{}\n");

    printf("\\RightLabel{(");
    writeRuleName(ob);
    printf(")}\n");

    if(n==0||n==1)printf("\\UnaryInfC{$");
    else if(n==2)printf("\\BinaryInfC{$");
    else if(n==3)printf("\\TrinaryInfC{$");
    if(ob->cncl_type==INFR)texInfr(ob->u.infr_);
    else texEval(ob->u.eval_);
    printf("$}\n");

    return;
}
