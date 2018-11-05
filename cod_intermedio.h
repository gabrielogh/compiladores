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

void printFc(tresDir *d);

void printLista();

data_gen * eval_expr(node *n);

void cargar_parametros_formales(formalParam *params);

data_gen * getLastResult();

char * opToString(int op);

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

data_gen * getLastResult(){
  //printf("ENTRAMOS A GET LASR RESULT\n");
  if(last_td->fst != NULL){
    tresDir *aux = last_td->fst;
    while(aux->next != NULL){
      aux = aux->next;
    }    
    //printf("SALIMOS DE GET LAST RESULT CON AUX\n");
    return aux->res;
  }
  else{
    //printf("SALIMOS DE GET LAST RESULT CON NULL\n");
    return NULL;
  }
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
        printf("TEMPORALES INICIA CON: %d\n", temp);
        agregar_funcion(d);
        cargar_parametros_formales(d->formalParams);
        crear_instrucciones(last_td, d->block);
      }
      d = d->next;
    }
  }
}

void cargar_parametros_formales(formalParam *params){
  if(params != NULL){
    formalParam *auxParam = params;
    while(auxParam != NULL){
      tresDir *instruccion = (tresDir *) malloc(sizeof(tresDir));
      data_gen *dataAux = (data_gen *) malloc(sizeof(data_gen));
      dataAux->tipo = auxParam->tipo;
      strcpy(dataAux->nombre, auxParam->nombre);
      
      instruccion->op = CARGAR_PARAMS;
      instruccion->op1 = dataAux;
      instruccion->res = dataAux;
      agregar_instruccion(last_td, instruccion);
      auxParam = auxParam->next;
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

data_gen * eval_expr(node *n){
  //printf("ENTRAMOS A EVAL EXPR\n");
  data_gen *aux = n->info->data;
  if(aux != NULL){
    if((n->info->tipoOp == VARR) || (n->info->tipoOp == PARAMETRO)){
      return aux;
    }
    else{
      crear_instrucciones(last_td, n);
      return getLastResult();
    }
  }
  //printf("SALIMOS DE EVAL EXPR CON NULL\n");
  return NULL;
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
        printf("ENTRAMOS A CONSTANTE\n");
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
        printf("ENTRAMOS A ASIGNACION A: %s\n", getName(getNodeFst(n)->info)->nombre);
        instruccion->op = ASIGN_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->res = eval_expr(getNodeSnd(n));
        agregar_instruccion(t, instruccion);
      }
      else if(op == IGUALDADD){
        printf("ENTRAMOS A IGUALDAD\n");
        instruccion->op = EQ_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }

      else if (op == RESTAA && (getNodeSnd(n) != NULL)){
        printf("ENTRAMOS A RESTA\n");
        instruccion->op = SUB_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == RESTAA && (getNodeSnd(n) == NULL)){
        printf("ENTRAMOS A OPEUSTO\n");
        instruccion->op = OPUESTO_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        res->valor = 0;
        res->tipo = INTEGERR;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == SUMAA){
        printf("ENTRAMOS A SUMA\n");
        instruccion->op = ADD_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == PRODD){
        printf("ENTRAMOS A PROD\n");
        instruccion->op = PROD_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == DIVV){
        printf("ENTRAMOS A DIV\n");
        instruccion->op = DIV_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == MODD){
        printf("ENTRAMOS A MOD\n");
        instruccion->op = MOD_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if ((op == ANDD) || (op == ORR)){
        printf("ENTRAMOS A OR U AND\n");
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
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
        printf("ENTRAMOS A MAYOR O MENOR\n");
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
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
        printf("ENTRAMOS A IF THEN\n");
        data_gen *endLabel = (data_gen *) malloc(sizeof(data_gen));
        instruccion->op = IF_INSTRUCCION;
        generate_label(endLabel->nombre);
        instruccion->op1 = endLabel;

        instruccion->res = eval_expr(getNodeFst(n));

        agregar_instruccion(t, instruccion);

        crear_instrucciones(t, getNodeSnd(n));
      }

      else if (op == BLOCK){
        node *auxNode = getNodeFst(n);
        printf("ENTRAMOS A BOCK CON HIJO: %s DE TIPO: %d\n", auxNode->info->data->nombre, auxNode->info->data->tipo);
        crear_instrucciones(t, auxNode);
      }
      else if (op == STATEMENTS){
        printf("ENTRAMOS A STATEMENTS\n");
        crear_instrucciones(t, getNodeSnd(n));
        crear_instrucciones(t, getNodeFst(n));
      }
      else if (op == RETURNN){
        node *auxNode = getNodeFst(n);
        printf("ENTRAMOS A RETURN CON HIJO: %s DE TIPO: %d\n", auxNode->info->data->nombre, auxNode->info->data->tipo);
        instruccion->op = RETURN_INSTRUCCION;
        instruccion->res = eval_expr(getNodeFst(n));
        agregar_instruccion(t, instruccion);
      }
    }
  }
}

char * opToString(int op){
  switch(op) {

     case JMP  :
        return "JMP";
        break;
    
     case MOV  :
        return "MOV";
        break;

     case CMP  :
        return "CMP";
        break;

     case CARGAR_PARAMS  :
        return "CARGAR_PARAMS";
        break;

     case IF_INSTRUCCION  :
        return "IF_INSTRUCCION";
        break;

     case IF_ELSE_INSTRUCCION  :
        return "IF_ELSE_INSTRUCCION";
        break;
     case WHILE_INSTRUCCION  :
        return "WHILE_INSTRUCCION";
        break;
     case CALL  :
        return "CALL";
        break;
     case CALL_PARAMS  :
        return "CALL_PARAMS";
        break;
     case ASIGN_INSTRUCCION  :
        return "ASIGN_INSTRUCCION";
        break;
     case CTE_INSTRUCCION  :
        return "CTE_INSTRUCCION";
        break;
     case EQ_INSTRUCCION  :
        return "EQ_INSTRUCCION";
        break;
     case ADD_INSTRUCCION  :
        return "ADD_INSTRUCCION";
        break;
     case SUB_INSTRUCCION  :
        return "SUB_INSTRUCCION";
        break;
     case MAY_INSTRUCCION  :
        return "MAY_INSTRUCCION";
        break;
     case MEN_INSTRUCCION  :
        return "MEN_INSTRUCCION";
        break;
     case NEG_INSTRUCCION  :
        return "NEG_INSTRUCCION";
        break;
     case NOT_INSTRUCCION  :
        return "NOT_INSTRUCCION";
        break;
     case OPUESTO_INSTRUCCION  :
        return "OPUESTO_INSTRUCCION";
        break;
     case PROD_INSTRUCCION  :
        return "PROD_INSTRUCCION";
        break;
     case DIV_INSTRUCCION  :
        return "DIV_INSTRUCCION";
        break;
     case MOD_INSTRUCCION  :
        return "MOD_INSTRUCCION";
        break;
     case AND_INSTRUCCION  :
        return "AND_INSTRUCCION";
        break;
     case OR_INSTRUCCION  :
        return "OR_INSTRUCCION";
        break;
     case RETURN_INSTRUCCION  :
        return "RETURN_INSTRUCCION";
        break;
     default :
     return "NULL";
  }
}

/*
 * Esta funcion nos permite castear un nodeAux como un node.
 */
void printInstruccion(tresDir *p){
  if(p!= NULL){
    data_gen *aux1 = p->op1;
    data_gen *aux2 = p->op2;
    data_gen *aux3 = p->res;

    printf("          |\n");
    printf("          |\n");
    printf("          |\n");
    printf("           ----------------------------- \n");
    printf("          | Operacion:   | %s \n", opToString(p->op));
    printf("          | Operador1:   | %s                 \n", aux1->nombre);
    printf("          | Operador2:   | %s                 \n", aux2->nombre);
    printf("          | Resultado:   | %s                 \n", aux3->nombre);
    printf("           ----------------------------- \n");
  }
}

/*
 * Esta funcion imprime un nivel completo. Utiliza a la funcion printDataStack.
 * id: ID del bloque al que pertenece
 * padre: ID del bloque que lo contiene inmediatamente.
 * *d: Dato del nivel a imprimir.
 */
void printFc(tresDir *d){
  if(d != NULL){
    if(d->next == NULL){
      printInstruccion(d);
    }
    else{
      printInstruccion(d);
      while(d->next != NULL){
        d = d->next;
        printInstruccion(d);
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
    printf("|           inicio_%s           |\n", t->nombre);
    printf("|                             | \n");
    printf(" ----------------------------- \n");
    printFc(t->fst);
    printf(" ----------------------------- \n");
    printf("|           fin_%s           |\n",t->nombre);
    printf("|                             | \n");
    printf(" ----------------------------- \n");
    t = t->next;
    while(t != NULL){
      printf(" ----------------------------- \n");
      printf("|           inicio_%s           |\n", t->nombre);
      printf("|                             | \n");
      printf(" ----------------------------- \n");
      printFc(t->fst);
      printf(" ----------------------------- \n");
      printf("|           fin_%s           |\n",t->nombre);
      printf("|                             | \n");
      printf(" ----------------------------- \n");
      t = t->next;
    }
  }
}