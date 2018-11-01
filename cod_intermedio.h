#include "lib.h"

//DEFINICION DE TIPOS:
typedef struct codTresDirs tresDir;
typedef struct tresDirList tresDirL;


typedef struct tresDirList{
  char nombre[32];
  tresDir *fst;
  struct tresDirList *next;
} tresDirL;

typedef struct codTresDirs {
	int op;
	data_gen op1;
	data_gen op2;
	data_gen res;
	struct codTresDirs *next;
}tresDir;


//VARIABLES GLOBALES:

int temp,labels;
tresDirL *head_td, *last_td;

//DECLARACION DE METODOS:
void initTresDirList();

void generate_temp(char c[32]);

void generate_label(char c[32]);

void agregar_instruccion(tresDirL *pos, tresDir *param);

tresDir * crear_instrucciones(tresDirL *t, node *n);

void agregar_funcion(data_stack *d);

void generar_codigo();

//IMPLEMENTACION DE METODOS:

void initTresDirList(){
  temp = 0;
  labels = 0;
  head_td = NULL;
  last_td = head_td;
}

void generate_temp(char c[32]){
  temp = temp + 1;
  strcpy(c, "Temp");
  strcat(c, temp);
}

void generate_label(char c[32]){
  labels = labels + 1;
  strcpy(c, "Label");
  strcat(c, labels);
}

void agregar_funcion(data_stack *d){
  tresDirL *param = (tresDirL *) malloc(sizeof(tresDirL));
  strcpy(param->nombre, d->data->nombre);
  param->fst = NULL;

  if (head_td == NULL){
    head_td = param;
    last_td = head_td;
  }
  else {
    last_td->next = param;
    last_td = param;
  }
}

void agregar_instruccion(tresDirL *pos, tresDir *param){
  if(pos->fst == NULL){
    pos->fst = param;
  }
  else{
    tresDir *aux = pos->fst;
    while(aux->next != NULL){
      aux = aux->next;
    }
    aux->next = param;
  }

}

void generar_codigo(){
  if(inicial!=NULL){
    stack *aux = inicial;
    data_stack *d = aux->info;
    while(d!=NULL){
      if(d->es_funcion){
        agregar_funcion(d);
        crear_instrucciones(last_td, d->block);
      }
      d = d->next;
    }
  }
}

tresDir * crear_instrucciones(tresDirL *t, node *n){
 /* if(n!=NULL){
    data_stack *data = n->info;
    if(data != NULL){
      int op = data->tipoOp;
      string *s = getName(data);
      char cAux[32];
      strcpy(cAux, s->nombre);
      if(op == VARR || op == CONSTANTEE || op == PARAMETRO){
        return (getTipo(data));
      }
      if(op == INVOCC){
        checkParams(n);
        return (getTipo(data));
      }
      else if (op == ASIGNACIONN){
        int res1 = evalExpr(getNodeFst(n), tipoRet);
        int res2 = evalExpr(getNodeSnd(n), tipoRet);
        if(res1 == res2){
        }
        else if(res1 == VOIDD){
          createNewError(getLinea(data), "Error de tipos en la expresion, la funcion invocada debe retornar un resultado ", WRONGTYPE);return WRONGTYPE;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en la asignacion: La expresion debe ser del mismo tipo que la variable ", WRONGTYPE);return WRONGTYPE;
        }
      }
      else if (op == RESTAA && (getNodeSnd(n) != NULL)){
        if((evalExpr(getNodeFst(n), tipoRet) == INTEGERR) && (evalExpr(getNodeSnd(n), tipoRet) == INTEGERR)){
          return INTEGERR;
        }
        else{
          createNewError(getLinea(data), "Los operandos de una resta deben ser de tipo integer", WRONGTYPE);return WRONGTYPE;
        }
      }
      else if (op == RESTAA && (getNodeSnd(n) == NULL)){
        if(evalExpr(getNodeFst(n), tipoRet) == INTEGERR){
          return INTEGERR;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en el opuesto: Se esperaba una expresion de tipo entero ", WRONGTYPE);return WRONGTYPE;
        }
      }
      else if ((op == DIVV) ||(op == PRODD) || (op == MODD) || (op == SUMAA)){
        if((evalExpr(getNodeFst(n), tipoRet) == INTEGERR) && (evalExpr(getNodeSnd(n), tipoRet) == INTEGERR)){
          return INTEGERR;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en una operacion aritmetica binaria: Se espera que los operandos sean de tipo integer ", WRONGTYPE);return WRONGTYPE;
        }
      }
      else if ((op == ANDD) || (op == ORR)){
        if((evalExpr(getNodeFst(n), tipoRet) == BOOLEAN) && (evalExpr(getNodeSnd(n), tipoRet) == BOOLEAN)){
          return BOOLEAN;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en una operacion logica binaria: Ambas expresiones deben ser de tipo bool ", WRONGTYPE);return WRONGTYPE;
        }
      }
      else if ((op == MAYORR) ||(op == MENORR) || (op == MENIGUALL) || (op == MAYIGUALL) || (op == IGUALDADD)){
        if((evalExpr(getNodeFst(n), tipoRet) == INTEGERR) && (evalExpr(getNodeSnd(n), tipoRet) == INTEGERR)){
          return BOOLEAN;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en una operacion aritmetica-logica binaria: Ambas expresiones deben ser de tipo integer ", WRONGTYPE);return WRONGTYPE;
        }
      }
      else if (op == NOTT){
        if(evalExpr(getNodeFst(n), tipoRet) == BOOLEAN){
          return BOOLEAN;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en la negacion: La expresion debe ser de tipo bool ", WRONGTYPE);return WRONGTYPE;
        }
      }
      else if (op == IFTHENN || op == WHILEE){
        if(evalExpr(getNodeFst(n), tipoRet) == BOOLEAN){
          evalExpr(getNodeSnd(n), tipoRet);
          return BOOLEAN;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en la condicion ", WRONGTYPE);return WRONGTYPE;
        }
      }
      else if (op == IFTHENELSEE){
        if(evalExpr(getNodeFst(n), tipoRet) == BOOLEAN){
          evalExpr(getNodeSnd(n), tipoRet);
          evalExpr(getNodeTrd(n), tipoRet);
          return BOOLEAN;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en la condicion ", WRONGTYPE);return WRONGTYPE;
        }
      }
      else if (op == BLOCK){
        evalExpr(getNodeFst(n), tipoRet);
      }
      else if (op == BLOCKNULL){
        return tipoRet;
      }
      else if (op == STATEMENTS){
        evalExpr(getNodeSnd(n), tipoRet);
        evalExpr(getNodeFst(n), tipoRet);
      }
      else if (op == RETURNN){
        int res = evalExpr(getNodeFst(n), tipoRet);
        if(res == tipoRet){
          return tipoRet;
        }
        else if(res != WRONGTYPE){
          createNewError(getLinea(data), "Error de tipos en el return: El tipo de la expresion del return debe ser igual al tipo de retorno de la funcion ", WRONGTYPE);return WRONGTYPE;}
      }
    }
  }*/
  return NULL;
}