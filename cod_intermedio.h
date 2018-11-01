#include "lib.h"

//DEFINICION DE TIPOS:
typedef struct codTresDirs tresDir;
typedef struct tresDirList tresDirL;

typedef struct codTresDirs {
  int op;
  data_gen op1;
  data_gen op2;
  data_gen res;
  struct codTresDirs *next;
}tresDir;

typedef struct tresDirList{
  char nombre[32];
  tresDir *fst;
  struct tresDirList *next;
} tresDirL;


//VARIABLES GLOBALES:

int temp,labels;
tresDirL *head_td, *last_td;

//DECLARACION DE METODOS:
void initTresDirList();

void generate_temp(char c[32]);

void generate_label(char c[32]);

void agregar_instruccion(tresDirL *pos, tresDir *param);

void crear_instrucciones(tresDirL *t, node *n);

void agregar_funcion(data_stack *d);

void generar_codigo();

data_gen * recuperar_var(node *n);

//IMPLEMENTACION DE METODOS:

void initTresDirList(){
  temp = 0;
  labels = 0;
  head_td = (tresDirL *) malloc(sizeof(tresDirL));
  head_td->next = NULL;
  last_td = head_td;
}

void generate_temp(char c[32]){
  temp = temp + 1;
  strcpy(c, "Temp");
  char aux[32];
  sprintf(aux,"%d",temp);
  strcat(c, aux);
}

void generate_label(char c[32]){
  labels = labels + 1;
  strcpy(c, "Label");
  char aux[32];
  sprintf(aux,"%d",labels);
  strcat(c, aux);
}
/*
 * Esta esta la funcion principal que se encarga de generar todo el codigo de tres direcciones
 * Recorre en nivel inicial del stack en busca de las funciones e inserta cada una en la lista principal de tipo tresDirL.
 * Luego de insertar una funcion, genera todo el codigo de su cuerpo, el cual inserta en el nodo corriente de la lista general
 * cada nodo de la lista general tiene a su vez una lista que representa su cuerpo de instrucciones
 */
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

/*
 * Esta funcion se encarga de generar un nuevo nodo en la lista general para insertar una nueva funcion.
 * *d: Datos de la funcion
 */
void agregar_funcion(data_stack *d){
  tresDirL *param = (tresDirL *) malloc(sizeof(tresDirL));
  strcpy(param->nombre, d->data->nombre);
  param->fst = NULL;
  if(head_td == NULL){
    head_td = param;
    last_td = head_td;
  }
  else{
    last_td->next = param;
    last_td = param;
  }
}

/*
 * Esta funcion se encarga de agregar una instruccion, es utilizada en la funcion crear_instrucciones().
 * *pos: Posicion en la lista general donde se va a insertar la instruccion.
 * *param: Instruccion que se va a insertar.
 */
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

data_gen * recuperar_var(node *n){
  return (n->info->data);
}

void crear_instrucciones(tresDirL *t, node *n){
  if(n!=NULL){
    data_stack *data = n->info;
    if(data != NULL){
      int op = data->tipoOp;
      tresDir *instruccion = (tresDir *) malloc(sizeof(tresDir));
      instruccion->op = op
      string *s = getName(data);
      char cAux[32];
      strcpy(cAux, s->nombre);

      if(op == CONSTANTEE){
        data_gen *res = (data_gen *) malloc(sizeof(data_gen));

        instruccion->op1 = data->data;
        generate_temp(res->nombre);

        res->offset = data->data->offset;
        res->valor = tree->content->value;
        res->tipo = CONSTANT;
        res->ret = tree->content->ret;

        instruccion->res = res;
        agregar_instruccion(instruccion);
      }
      else if(op == ASIGNACIONN){
        instruccion->op1 = recuperar_var(getNodeFst(n));
        instruccion->res = recuperar_var(getNodeSnd(n));
        agregar_instruccion(instruccion);
      }
      /*
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
      }*/
    }
  }
  return NULL;
}