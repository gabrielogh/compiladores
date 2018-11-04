#include "lib.h"

//DEFINICION DE TIPOS:
typedef struct codTresDirs tresDir;
typedef struct tresDirList tresDirL;

typedef struct codTresDirs {
  int op;
  data_gen *op1;
  data_gen *op2;
  data_gen *res;
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

void printInstruccion(tresDir *d);

void printFc(tresDirL *d);

void printLista();

data_gen * recuperar_var(node *n);

void cargar_parametros_formales(formalParam *params);

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
        cargar_parametros_formales(d->formalParams);
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

void cargar_parametros_formales(formalParam *params){
  if(params != NULL){
    
  }
}

void crear_instrucciones(tresDirL *t, node *n){
  if(n!=NULL){
    data_stack *data = n->info;
    if(data != NULL){
      int op = data->tipoOp;
      tresDir *instruccion = (tresDir *) malloc(sizeof(tresDir));
      data_gen *res = (data_gen *) malloc(sizeof(data_gen));
      string *s = getName(data);
      char cAux[32];
      strcpy(cAux, s->nombre);

      if(op == CONSTANTEE){
        instruccion->op = CTE_INSTRUCCION;
        instruccion->op1 = data->data;
        generate_temp(res->nombre);

        res->offset = data->data->offset;
        res->valor = data->data->valor;
        res->tipo = CONSTANTEE;
        res->const_var = data->data->tipo;

        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if(op == ASIGNACIONN){
        instruccion->op = ASIGN_INSTRUCCION;
        instruccion->op1 = recuperar_var(getNodeFst(n));
        instruccion->res = recuperar_var(getNodeSnd(n));
        agregar_instruccion(t, instruccion);
      }
      else if(op == IGUALDADD){
        instruccion->op = EQ_INSTRUCCION;
        instruccion->op1 = recuperar_var(getNodeFst(n));
        instruccion->op2 = recuperar_var(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }

      else if (op == RESTAA && (getNodeSnd(n) != NULL)){
        instruccion->op = SUB_INSTRUCCION;
        instruccion->op1 = recuperar_var(getNodeFst(n));
        instruccion->op2 = recuperar_var(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == RESTAA && (getNodeSnd(n) == NULL)){
        instruccion->op = OPUESTO_INSTRUCCION;
        instruccion->op1 = recuperar_var(getNodeFst(n));
        res->valor = 0;
        res->tipo = INTEGERR;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == SUMAA){
        instruccion->op = ADD_INSTRUCCION;
        instruccion->op1 = recuperar_var(getNodeFst(n));
        instruccion->op2 = recuperar_var(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == PRODD){
        instruccion->op = PROD_INSTRUCCION;
        instruccion->op1 = recuperar_var(getNodeFst(n));
        instruccion->op2 = recuperar_var(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == DIVV){
        instruccion->op = DIV_INSTRUCCION;
        instruccion->op1 = recuperar_var(getNodeFst(n));
        instruccion->op2 = recuperar_var(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == MODD){
        instruccion->op = MOD_INSTRUCCION;
        instruccion->op1 = recuperar_var(getNodeFst(n));
        instruccion->op2 = recuperar_var(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if ((op == ANDD) || (op == ORR)){
        instruccion->op1 = recuperar_var(getNodeFst(n));
        instruccion->op2 = recuperar_var(getNodeSnd(n));
        if(op == ANDD){
          instruccion->op = AND_INSTRUCCION;
        }
        else{
          instruccion->op = OR_INSTRUCCION;
        }
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if ((op == MAYORR) ||(op == MENORR)){
        instruccion->op1 = recuperar_var(getNodeFst(n));
        instruccion->op2 = recuperar_var(getNodeSnd(n));
        if(op == MAYORR){
          instruccion->op = MAY_INSTRUCCION;
        }
        else{
          instruccion->op = MEN_INSTRUCCION;
        }
        res->tipo = BOOLEAN;
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == IFTHENN){


      }
      /*
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
}

/*
 * Esta funcion nos permite castear un nodeAux como un node.
 */
void printInstruccion(tresDir *p){
  data_gen *aux1 = p->op1;
  data_gen *aux2 = p->op2;
  data_gen *aux3 = p->res;

  printf("          |\n");
  printf("          |\n");
  printf("          |\n");
  printf("           ----------------------------- \n");

  printf("          | Operacion:   | %d             |\n", p->op);
  printf("          | Op1:   | %s             |\n", aux1->nombre);
  printf("          | Op2:   | %s             |\n", aux2->nombre);
  printf("          | Res:   | %s             |\n", aux3->nombre);
  printf("           ----------------------------- \n");
}

/*
 * Esta funcion imprime un nivel completo. Utiliza a la funcion printDataStack.
 * id: ID del bloque al que pertenece
 * padre: ID del bloque que lo contiene inmediatamente.
 * *d: Dato del nivel a imprimir.
 */
void printFc(tresDirL *d){
  if(d != NULL){
    if(d->next == NULL){
      printInstruccion(d->fst);
    }
    else{
      printInstruccion(d->fst);
      while(d->next != NULL){
        d = d->next;
        printInstruccion(d->fst);
      }
    }
  }
  else{
    printf("FC vacio");
  }
}

/*
 * Esta funcion imprime el stack completo, utiliza a la funcion printLevel para imprimir cada nivel.
 */
void printLista(){
  printf("\n");
  printf("              Lista:\n");
  tresDirL *t = (tresDirL *) malloc(sizeof(tresDirL));
  t = head_td;
  if(t == NULL){
    printf("Lista Vacia.\n");
  }
  else{
    printf(" ----------------------------- \n");
    printf("|           Inicio:           |\n");
    printf("|                             | \n");
    printf(" ----------------------------- \n");
    printFc(t);
    printf(" ----------------------------- \n");
    printf("|           Fin:           |\n");
    printf("|                             | \n");
    printf(" ----------------------------- \n");
    t = t->next;
    while(t != NULL){
      printf(" ----------------------------- \n");
      printf("|           Inicio:           |\n");
      printf("|                             | \n");
      printf(" ----------------------------- \n");
      printFc(t);
      printf(" ----------------------------- \n");
      printf("|           Fin:           |\n");
      printf("|                             | \n");
      printf(" ----------------------------- \n");
      t = t->next;
    }
  }
}