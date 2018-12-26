#include "param.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#define DEBUG

#ifdef DEBUG
#include <stdio.h>
void ind(int d);
#endif


void error(char *);
Val *copyVal(Val *);
Var *copyVar(Var *);

Int *readInt(char *);
Bool *readBool(char *);
Clsr *readClsr(char *, char *);
ClsrRec *readClsrRec(char *, char *);
Env *readEnv(char *);
Val *readVal(char *);
Var *readVar(char *);
If *readIf(char *);
Op *readOp(char *);
Let *readLet(char *);
Fun *readFun(char *);
App *readApp(char *);
LetRec *readLetRec(char *);
Exp *readExp(char *);
Infr *readInfr(char *);
Eval *readEval(char *);
Cncl *readCncl(char *);


Int *readInt(char *str){
#ifdef DEBUG
    printf("int : %s\n",str);
#endif
    Int *int_ob = (Int *)malloc(sizeof(Int));
    int_ob->i = atoi(str);
    return int_ob;
}


Bool *readBool(char *str){
#ifdef DEBUG
    printf("bool : %s\n",str);
#endif
    Bool *bool_ob = (Bool *)malloc(sizeof(Bool));
    if(str[0]=='t')bool_ob->b = 1;
    else bool_ob->b = 0;
    return bool_ob;
}


Clsr *readClsr(char *str1, char *str2){
#ifdef DEBUG
    printf("clsr : (%s)[%s]\n",str1,str2);
#endif
    Clsr *clsr_ob = (Clsr *)malloc(sizeof(Clsr));
    clsr_ob->env_ = readEnv(str1);
    char *tmp;
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");
    tmp = str2;
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");
    *(tmp+strcspn(tmp," "))='\0';

    clsr_ob->arg = (Var *)malloc(sizeof(Var));
    clsr_ob->arg->var_name = (char *)malloc(sizeof(char)*(strlen(tmp)+1));
    strcpy(clsr_ob->arg->var_name,tmp);
    clsr_ob->exp_ = readExp(str2);
    return clsr_ob;
}


ClsrRec *readClsrRec(char *str1, char *str2){
#ifdef DEBUG
    printf("clserec : (%s)[%s]\n",str1,str2);
#endif
    ClsrRec *clsrrec_ob = (ClsrRec *)malloc(sizeof(ClsrRec));
    clsrrec_ob->env_ = readEnv(str1);

    char *tmp1, *tmp2;
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");
    tmp1 = str2;
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");
    tmp2 = str2;
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");
    *(tmp1+strcspn(tmp1," "))='\0';
    *(tmp2+strcspn(tmp2," "))='\0';

    clsrrec_ob->fun = (Var *)malloc(sizeof(Var));
    clsrrec_ob->fun->var_name = (char *)malloc(sizeof(char)*(strlen(tmp1)+1));
    strcpy(clsrrec_ob->fun->var_name,tmp1);
    clsrrec_ob->arg = (Var *)malloc(sizeof(Var));
    clsrrec_ob->arg->var_name = (char *)malloc(sizeof(char)*(strlen(tmp2)+1));
    strcpy(clsrrec_ob->arg->var_name,tmp2);
    clsrrec_ob->exp_ = readExp(str2);

    return clsrrec_ob;
}


Env *readEnv(char *str){
    if(*str=='\0')return NULL;

    Env *env_ob = (Env *)malloc(sizeof(Env));

    Env *env_tmp = NULL;

    char *tmp1 = str;
    str = NULL;
    char *tmp2 = tmp1;

    int count = 0;
    while(1){
        tmp2 += strcspn(tmp2,"(),");
        if(*tmp2=='('){
            count++;
        }else if(*tmp2==')'){
            count--;
        }else if(*tmp2==','){
            if(count==0){
                str = tmp2;
            }
        }else{
            break;
        }
        tmp2++;
    }

    if(str==NULL){
        str = tmp1;
    }else{
        *str = '\0';
        str++;
        str+=strspn(str," ");
        env_tmp = readEnv(tmp1);
    }
    //char *str1 = strtok(str,"=");
    //char *str2 = strtok(NULL,"=");
    char *str1 = str;
    char *str2 = strchr(str1,'=');
    *str2 = '\0';
    str2++;
    str2+=strspn(str2," ");

#ifdef DEBUG
    printf("env : %s,%s\n",str1,str2);
#endif

    env_ob->var_ = readVar(str1);
    env_ob->val_ = readVal(str2);
    env_ob->prev = env_tmp;

    return env_ob;
}


Val *readVal(char* str){
#ifdef DEBUG
    printf("val : %s\n",str);
#endif
    Val *val_ob = (Val *)malloc(sizeof(Val));

    if(str[0]=='t'||str[0]=='f'){
        val_ob->val_type = BOOL_;
        val_ob->u.bool_ = readBool(str);
    }else if(47<str[0]&&str[0]<58){
        val_ob->val_type = INT_;
        val_ob->u.int_ = readInt(str);
    }else if(str[0]=='('){
        char *str1, *str2;
        str++;
        str1 = str;
        int count = 0;
        while(1){
            str+=strcspn(str,"()");
            if(*str=='('){
                count++;
            }else if(*str==')'){
                if(count==0){
                    break;
                }
                count--;
            }else{
                error("1mismatch parentheses.");
            }
            str++;
        }
        *str = '\0';
        str+=2;
        str+=strspn(str," ");
        str2 = str;
        *strrchr(str2,']') = '\0';
        if(str2[0]=='f'){
            val_ob->val_type = CLSR;
            val_ob->u.clsr_ = readClsr(str1,str2);
        }else if(str2[0]=='r'){
            val_ob->val_type = CLSRREC;
            val_ob->u.clsrrec_ = readClsrRec(str1,str2);
        }else{
            error("val is not correct\n");
        }
    }else{
        error("val is not correct\n");
    }

    return val_ob;
}


Var *readVar(char *str){
#ifdef DEBUG
    printf("var : %s\n",str);
#endif
    Var *var_ob = (Var *)malloc(sizeof(Var));
    *(str+strcspn(str," "))='\0';
    var_ob->var_name = (char *)malloc(sizeof(char)*(strlen(str)+1));
    strcpy(var_ob->var_name,str);
    return var_ob;
}


If *readIf(char *str){
#ifdef DEBUG
    printf("if  : %s\n",str);
#endif
    If *if_ob = (If *)malloc(sizeof(If));

    int count = 0;
    char *str1,*str2,*str3;
    str+=strcspn(str," ");
    str+=strspn(str," ");
    str1 = str;
    while(*str!='\0'){
        if(strncmp(str-1," if ", 4)==0){
            count++;
        }else if(strncmp(str-1," then ",6)==0){
            if(count){
                count--;
            }else{
                *str = '\0';
                str++;
                break;
            }
        }
        str+=strcspn(str," ");
        str+=strspn(str," ");
    }
    str+=strcspn(str," ");
    str+=strspn(str," ");
    str2 = str;
    while(*str!='\0'){
        if(strncmp(str-1," if ",4)==0){
            count++;
        }else if(strncmp(str-1," else ",6)==0){
            if(count){
                count--;
            }else{
                *str = '\0';
                str++;
                break;
            }
        }
        str+=strcspn(str," ");
        str+=strspn(str," ");
    }
    str+=strcspn(str," ");
    str+=strspn(str," ");
    str3 = str;

    if_ob->exp1_ = readExp(str1);
    if_ob->exp2_ = readExp(str2);
    if_ob->exp3_ = readExp(str3);

    return if_ob;
}


Op *readOp(char* str){
#ifdef DEBUG
    printf("op  : %s\n",str);
#endif
    Op *op_ob = (Op *)malloc(sizeof(Op));

    int count = 0;
    op_ob->op_type = TIMES;
    char *str1, *str2;
    str1 = str;
    str2 = NULL;
    while(1){
        str += strcspn(str,"(+-*<)il");
        if(str[0]=='('){
            count++;
        }else if(str[0]==')'){
            count--;
        }else if(count==0){
            if(strncmp(str-1," if ",4)*strncmp(str-1," let ",5)==0){
                break;
            }else if(strncmp(str-1," + ",3)==0){
                op_ob->op_type=PLUS;
                str2 = str;
            }else if(strncmp(str-1," - ",3)==0){
                if(str==str1){
                    str++;
                    continue;
                }
                op_ob->op_type=MINUS;
                str2 = str;
            }else if(strncmp(str-1," < ",3)==0){
                op_ob->op_type=LT;
                str2 = str;
                break;
            }else if(strncmp(str-1," * ",3)==0){
                if(op_ob->op_type==TIMES){
                    str2 = str;
                }
            }else if(*str=='\0'){
                break;
            }
        }
        str++;
    }

    if(str2==NULL)error("invalid.");

    *str2 = '\0';
    str2++;
    str2 += strspn(str2," ");
    op_ob->exp1_ = readExp(str1);
    op_ob->exp2_ = readExp(str2);

    return op_ob;
}


Let *readLet(char *str){
#ifdef DEBUG
    printf("let : %s\n",str);
#endif
    Let *let_ob = (Let *)malloc(sizeof(Let));

    char *str1, *str2;

    str += strcspn(str," ");
    str += strspn(str," ");
    str1 = str;
    str1 += strcspn(str1," ");
    str1 += strspn(str1," ");
    str1 += strcspn(str1," ");
    str1 += strspn(str1," ");
    str2 = str1;

    int count = 0;
    while(1){
        str2+=strcspn(str2,"li");
        if(strncmp(str2-1," let ",5)==0){
            count++;
        }else if(strncmp(str2-1," in ",4)==0){
            if(count==0){
                break;
            }
            count--;
        }else if(*str2=='\0'){
            error("2mismatch let and in.");
        }
        str2++;
    }

    *str2 = '\0';
    str2++;
    str2 += strcspn(str2," ");
    str2 += strspn(str2," ");

    let_ob->var_ = readVar(str);
    let_ob->exp1_ = readExp(str1);
    let_ob->exp2_ = readExp(str2);

    return let_ob;
}


Fun *readFun(char *str){
#ifdef DEBUG
    printf("fun : %s\n",str);
#endif
    Fun *fun_ob = (Fun *)malloc(sizeof(Fun));
    char *tmp;
    str += strcspn(str," ");
    str += strspn(str," ");
    tmp = str;
    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");
    *(tmp+strcspn(tmp," "))='\0';

    fun_ob->arg = (Var *)malloc(sizeof(Var));
    fun_ob->arg->var_name = (char *)malloc(sizeof(char)*(strlen(tmp)+1));
    strcpy(fun_ob->arg->var_name,tmp);
    fun_ob->exp_ = readExp(str);

    return fun_ob;
}


App *readApp(char *str){
#ifdef DEBUG
    printf("app : %s\n",str);
#endif
    App *app_ob = (App *)malloc(sizeof(App));
    char *str1 = str;
    char *str2 = NULL;
    int count;

    while(1){
        if(*str=='('){
            count = 0;
            str++;
            while(1){
                str+=strcspn(str,"()");
                if(*str=='('){
                    count++;
                }else if(*str==')'){
                    if(count==0){
                        break;
                    }
                    count--;
                }else{
                    error("3mismatch parentheses.");
                }
                str++;
            }
            str++;
        }else{
            str+=strcspn(str," ");
        }
        str+=strspn(str," ");
        if(*str=='\0'){
            break;
        }else{
            str2 = str;
        }
    }

    if(str2==NULL)error("sole app.");

    *(str2-1)='\0';

    app_ob->exp1_ = readExp(str1);
    app_ob->exp2_ = readExp(str2);
    return app_ob;
}


LetRec *readLetRec(char *str){
#ifdef DEBUG
    printf("letrec : %s\n",str);
#endif
    LetRec *letrec_ob = (LetRec *)malloc(sizeof(LetRec));
    char *tmp1, *tmp2, *tmp3;
    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");
    tmp1 = str;
    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");
    tmp2 = str;
    str += strcspn(str," ");
    str += strspn(str," ");
    str += strcspn(str," ");
    str += strspn(str," ");
    tmp3 = str;
    *(tmp1+strcspn(tmp1," "))='\0';
    *(tmp2+strcspn(tmp2," "))='\0';

    letrec_ob->fun = (Var *)malloc(sizeof(Var));
    letrec_ob->fun->var_name = (char *)malloc(sizeof(char)*(strlen(tmp1)+1));
    strcpy(letrec_ob->fun->var_name,tmp1);
    letrec_ob->arg = (Var *)malloc(sizeof(Var));
    letrec_ob->arg->var_name = (char *)malloc(sizeof(char)*(strlen(tmp2)+1));
    strcpy(letrec_ob->arg->var_name,tmp2);

    int count = 0;
    while(1){
        str+=strcspn(str,"li");
        if(strncmp(str-1," let ",5)==0){
            count++;
        }else if(strncmp(str-1," in ",4)==0){
            if(count==0){
                break;
            }
            count--;
        }else if(*str=='\0'){
            error("4mismatch let and in.");
        }
        str++;
    }
    *str = '\0';
    str+=2;
    str += strspn(str," ");

    letrec_ob->exp1_ = readExp(tmp3);
    letrec_ob->exp2_ = readExp(str);

    return letrec_ob;
}


Exp *readExp(char* str){

    if(str[0]=='('){
        int count = 0;
        char *tmp1, *tmp2;
        tmp1 = str+1;
        while(1){
            tmp1+=strcspn(tmp1,"()");
            if(*tmp1=='('){
                count++;
            }else if(*tmp1==')'){
                if(count==0){
                    break;
                }
                count--;
            }else{
                error("5mismatch parentheses.");
            }
            tmp1++;
        }
        if(*tmp1=='\0')error("6mismatch parentheses.");
        tmp2=tmp1 + 1;
        if(*(tmp2+strspn(tmp2," "))=='\0'){
            str++;
            *tmp1 = '\0';
            return readExp(str);
        }
    }

#ifdef DEBUG
    //printf("exp : %s\n",str);
#endif

    Exp *exp_ob = (Exp *)malloc(sizeof(Exp));

    if(strncmp(str,"let rec ",8)==0){//when exp is letrec
        exp_ob->exp_type = LETREC;
        exp_ob->u.letrec_ = readLetRec(str);
    }else if(strncmp(str,"let ",4)==0){//when exp is let
        exp_ob->exp_type = LET;
        exp_ob->u.let_ = readLet(str);
    }else if(strncmp(str,"fun ",4)==0){//when exp is fun
        exp_ob->exp_type = FUN;
        exp_ob->u.fun_ = readFun(str);
    }else if(strncmp(str,"if ",3)==0){//when exp is if
        exp_ob->exp_type = IF;
        exp_ob->u.if_ = readIf(str);
    }else if(strncmp(str,"true",4)*strncmp(str,"false",5)==0){//when exp is bool
        exp_ob->exp_type = BOOL;
        exp_ob->u.bool_ = readBool(str);
    }else{

        char *tmp;
        tmp = str;
        tmp += strspn(tmp,"0123456789");
        tmp += strspn(tmp," ");
        if(*tmp=='\0'){//when exp is int
            exp_ob->exp_type = INT;
            exp_ob->u.int_ = readInt(str);
        }else{

            tmp = str;
            tmp += strcspn(tmp," ()+-*<");
            tmp += strspn(tmp," ");
            if(*tmp=='\0'){//when exp is var
                exp_ob->exp_type = VAR;
                exp_ob->u.var_ = readVar(str);
            }else{

                tmp = str;
                int count = 0;
                while(1){
                    tmp+=strcspn(tmp,"()+-*<");
                    if(*tmp=='('){
                        count++;
                    }else if(*tmp==')'){
                        count--;
                    }else if(*tmp!='\0'){
                        if(count==0)break;
                    }else{
                        break;
                    }
                    tmp++;
                }
                if(*tmp=='\0'){//when exp is app
                    exp_ob->exp_type = APP;
                    exp_ob->u.app_ = readApp(str);
                }else{//when exp is op
                    exp_ob->exp_type = OP;
                    exp_ob->u.op_ = readOp(str);
                }
            }
        }
    }

    return exp_ob;
}


Eval *readEval(char* str){
#ifdef DEBUG
    printf("eval: %s\n",str);
#endif
    Eval *eval_ob = (Eval *)malloc(sizeof(Eval));

    char *str1, *str2, *str3;
    str1 = str;
    str2 = strstr(str1,"|-");
    *str2 = '\0';
    str2+=2;
    str2+=strspn(str2," ");
    str3 = strstr(str2," evalto ");
    *str3 = '\0';
    str3+=8;
    str3+=strspn(str3," ");

    eval_ob->env_ = readEnv(str1);
    eval_ob->exp_ = readExp(str2);
    eval_ob->val_ = readVal(str3);

    return eval_ob;
}


Infr *readInfr(char* str){
#ifdef DEBUG
    printf("infr: %s\n",str);
#endif
    Infr *infr_ob = (Infr *)malloc(sizeof(Infr));

    char *tp;

    tp = strtok(str," ");
    infr_ob->int1 = atoi(tp);

    tp = strtok(NULL," ");
    if(strcmp(tp,"plus")==0){
        infr_ob->infr_type = PLUS;
    }else if(strcmp(tp,"minus")==0){
        infr_ob->infr_type = MINUS;
    }else if(strcmp(tp,"times")==0){
        infr_ob->infr_type = TIMES;
    }else{
        infr_ob->infr_type = LT;
        tp = strtok(NULL," ");
    }

    tp = strtok(NULL," ");
    infr_ob->int2 = atoi(tp);

    tp = strtok(NULL," ");

    tp = strtok(NULL," ");
    infr_ob->val_ = readVal(tp);

    return infr_ob;
}


Cncl *readCncl(char* str){
#ifdef DEBUG
    printf("cncl: %s\n",str);
#endif
    Cncl* cncl_ob = (Cncl *)malloc(sizeof(Cncl));

    str += strspn(str," ");
    if(strstr(str," is ")==NULL){
        cncl_ob->cncl_type = EVAL;
        cncl_ob->u.eval_ = readEval(str);
    }else{
        cncl_ob->cncl_type = INFR;
        cncl_ob->u.infr_ = readInfr(str);
    }

    return cncl_ob;
}
