#include "lib.h"

//DEFINICION DE TIPOS:
typedef struct codTresDirs tresDir;
typedef struct tresDirList tresDirL;
typedef struct globalVarsList globalVars;

/* Tipo utilizado para representar un codigo de tres direcciones.
 * op: Representa la operacion a realizar mediante su codigo (los codigos se encuentran en constantes.h).
 * *op1: El primero operando.
 * *op2: El segundo operando.
 * *res: El resultado de la operacion.
 * *next: Puntero al proximo codigo de tres direcciones.
 */
typedef struct codTresDirs {
  int op;
  data_gen *op1;
  data_gen *op2;
  data_gen *res;
  struct codTresDirs *next;
}tresDir;

/* Tipo utilizado para representar la lista de codigos de tres direcciones de cada funcion.
 * La lista principal de tipo tresDirL contiene todas las funciones del programa
 * luego cada funcion contiene una lista de codigo de tres direcciones que representa el cuerpo de la misma.
 * stackSize: representa el tamaño del stack utilizado por esa funcion, contemplando parametros, variables locale y el uso de temporales.
 * nombre[32]: Es el nombre de la funcion.
 * *fst: Puntero al primer codigo de tres direcciones de la funcion, cada funcion tiene su lista de codigos de tres direcciones.
 * *last: Puntero al ultimo codigo de tres direcciones de la funcion.
 * *next: Puntero al proximo elemento de la lista de codigo de tres direcciones, es decir a la proxima funcion..
 */
typedef struct tresDirList{
  int stackSize;
  char nombre[32];
  bool is_gv;
  int tipo;
  tresDir *fst;
  tresDir *last;
  struct tresDirList *next;
} tresDirL;

typedef struct globalVarsList{
  data_gen *var;
  struct globalVarsList *next;
}globalVars;

//VARIABLES GLOBALES:

int temp,labels, instrucciones, stackPos, stackParams;
tresDirL *head_td, *last_td;
globalVars *fst_var, *last_var; //Lista de variables globales.

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

void cargar_parametros_actuales(tresDirL *pos, paramList *pl);

data_gen * getLastResult();

char * opToString(int op);

void createJmp(int p, data_gen *res);

void agregar_variable_global(data_gen *res);

void cargar_variables_globales(globalVars *head);

int getJump(tresDir *instruccion);

//IMPLEMENTACION DE METODOS:

/*
 * Esta funcion inicializa la lista de codigos de tres direcciones.
 */
void initTresDirList(){
  temp = 0;
  labels = 0;
  instrucciones = 0;
  stackPos = 0;
  stackParams = 0;
  head_td = (tresDirL *) malloc(sizeof(tresDirL));
  head_td->fst = NULL;
  head_td->next = NULL;
  last_td = head_td;
  fst_var = NULL;
  last_var = fst_var;
}

/*
 * Esta funcion se encarga de generar los nombres y la posicion en el stack de los temporales.
 */
void generate_temp(char c[32]){
  temp = temp + 1;
  strcpy(c, "TMP");
  char aux[32];
  sprintf(aux,"%d",temp);
  strcat(c, aux);
  stackPos = stackPos + 1;
}

/*
 * Esta funcion se encarga de generar los nombres de los labels (no utilizan lugar en el scope, se utilizan para ahcer los jump).
 */
void generate_label(char c[32]){
  labels = labels + 1;
  strcpy(c, "LBB_");
  char aux[32];
  sprintf(aux,"%d",labels);
  strcat(c, aux);
}

/*
 * Esta funcion se encarga de generar los Jumps.
 */
void createJmp(int p, data_gen *res){
  tresDir *jmp = (tresDir *) malloc(sizeof(tresDir));
  jmp->op = p;
  jmp->res = res;
  agregar_instruccion(last_td, jmp);
}

/*
 * Esta funcion obtiene el ultimo elemento de la lista de codigo de tres direcciones de una funcion 
 * (utilizada para obtener el resultado de una evaluacion recursiva de una expresion).
 */
data_gen * getLastResult(){
  if(last_td->fst != NULL){
    return last_td->last->res;
  }
  else{
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
      if((d->es_funcion) && !(d->es_extern)){
        agregar_funcion(d);
        cargar_parametros_formales(d->formalParams);
        stackPos = d->stack_size;
        crear_instrucciones(last_td, d->block);
        last_td->stackSize = stackPos;
        temp = 0;
      }
      else if(d->data->global){
        //Las variables globales se insertan al final del archivo, pero estan al principio del primer nivel
        //Motivo por el cual las pasamos a una lista de variables globales y las cargamos al final.
        agregar_variable_global(d->data);
      }
      d = d->next;
    }
    cargar_variables_globales(fst_var);
  }
}

/*
 * Esta funcion inseta una variable global en la lista de variables globales
 * *res: Variable global.
 */
void agregar_variable_global(data_gen *res){
  globalVars *var = (globalVars *) malloc(sizeof(globalVars));
  var->var = res;
  var->next = NULL;
  if(fst_var == NULL){
    fst_var = var;
    last_var = fst_var;
  }
  else{
    last_var->next = var;
    last_var = var;
  }
}

/*
 * Esta funcion se encarga de genrar el codigo de tres direcciones una vez cargadas todas las variables y funciones del nivel.
 * *head: Puntero al inicio de la lista.
 */
void cargar_variables_globales(globalVars *head){
  globalVars *aux = head;
  while(aux != NULL){
    tresDirL *variable = (tresDirL *) malloc(sizeof(tresDirL));
    data_gen *res = aux->var;
    strcpy(variable->nombre, res->nombre);
    variable->is_gv = true;
    variable->tipo = res->tipo;
    if(head_td == NULL){
      head_td = variable;
      last_td = head_td;
    }
    else{
      last_td->next = variable;
      last_td = variable;
    }
    aux = aux->next;
  }

}

/*
 * Esta funcion se encarga de generar un nuevo nodo en la lista general para insertar una nueva funcion.
 * *d: Datos de la funcion.
 */
void agregar_funcion(data_stack *d){
  tresDirL *param = (tresDirL *) malloc(sizeof(tresDirL));
  strcpy(param->nombre, d->data->nombre);
  param->fst = NULL;
  param->last = param->fst;
  param->is_gv = false;
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
  tresDir *aux = pos->fst;
  if(aux == NULL){
    pos->fst = param;
    pos->fst->next = NULL;
    pos->last = pos->fst;
  }
  else{
    pos->last->next = (tresDir *) malloc(sizeof(tresDir));
    pos->last->next = param;
    pos->last = pos->last->next;
  }

}

/*
 * Esta funcion se encarga de generar el codigo de tres direcciones correspondientes a los parametros actuales
 * en una invocacion a una funcion.
 * *pos: Posicion en la lista general donde se va a insertar la instruccion.
 * *pl: Lista de parametros actuales que hay que resolver ya que pueden ser expresiones complejas.
 */
void cargar_parametros_actuales(tresDirL *pos, paramList *pl){
  paramList *aux = pl;
  node *n;
  if(aux != NULL){
    int i = 0;
    n = aux->parametro;
    if(n!=NULL){
      tresDir *instruccion = (tresDir *) malloc(sizeof(tresDir));
      data_gen *res = (data_gen *) malloc(sizeof(data_gen));
      instruccion->next = NULL;
      i = i + 1;
      data_gen *param = eval_expr(n);
      param->nParam = i;
      instruccion->op = CARGAR_ACTUAL_PARAMS;
      instruccion->op1 = param;
      generate_temp(res->nombre);
      res->offset = stackPos;
      instruccion->res = res;
      agregar_instruccion(last_td, instruccion);
      
    }
    aux = aux->next;
    while(aux!=NULL){
      n = aux->parametro;
      if(n!=NULL){
        tresDir *instruccion = (tresDir *) malloc(sizeof(tresDir));
        data_gen *res = (data_gen *) malloc(sizeof(data_gen));
        instruccion->next = NULL;
        i = i + 1;
        data_gen *param = eval_expr(n);
        param->nParam = i;
        instruccion->op = CARGAR_ACTUAL_PARAMS;
        instruccion->op1 = param;
        generate_temp(res->nombre);
        res->offset = stackPos;
        instruccion->res = res;
        agregar_instruccion(last_td, instruccion);
      }
      aux = aux->next;
    }
  }
}

/*
 * Esta funcion se encarga de generar el codigo de tres direcciones correspondientes a los parametros formales
 * de una funcion, es decir recupera los parametros actuales pasados en la invocacion y los asigna en los registros correspondientes.
 * *Lista de parametros formales de la funcion.
 */
void cargar_parametros_formales(formalParam *params){
  if(params != NULL){
    formalParam *auxParam = params;
    while(auxParam != NULL){
      tresDir *instruccion = (tresDir *) malloc(sizeof(tresDir));
      data_gen *dataAux = (data_gen *) malloc(sizeof(data_gen));
      dataAux->tipo = auxParam->tipo;
      dataAux->nParam = auxParam->numero;
      stackPos = auxParam->numero;
      dataAux->offset = auxParam->numero;
      strcpy(dataAux->nombre, auxParam->nombre);
      instruccion->op = CARGAR_PARAMS;
      instruccion->res = dataAux;
      agregar_instruccion(last_td, instruccion);
      auxParam = auxParam->next;
    }
  }
}

/*
 * Esta funcion se encarga de evaluar las expresiones que pueden ser siples (variables o parametros) o expresiones complejas
 * las cuales resuelve de forma recursiva, generando todas las instrucciones intermedias.
 * *n: Nodo que representa la instruccion.
 */
data_gen * eval_expr(node *n){
  data_gen *aux = n->info->data;
  if(aux != NULL){
    if((n->info->tipoOp == VARR) || (n->info->tipoOp == PARAMETRO) || (n->info->tipoOp == CONSTANTEE)){
      if(n->info->tipoOp == VARR){
        aux->offset = aux->offset;
      }
      return aux;
    }
    else{ //Resolvemos la expresion de forma recursiva.
      crear_instrucciones(last_td, n);
      return getLastResult();
    }
  }
  return NULL;
}

/*
 * Esta funcion es una de las principales, se encarga de generar el codigo de tres direcciones de una funcion.
 * Utiliza a la funcion agregar_instruccion().
 * *t: Posicion en la lista general donde se van a insertar las instrucciones.
 * *n: Cuerpo de la funcion.
 */
void crear_instrucciones(tresDirL *t, node *n){
  if(n!=NULL){
    data_stack *data = n->info;
    if(data != NULL){
      int op = data->tipoOp;
      tresDir *instruccion = (tresDir *) malloc(sizeof(tresDir));
      data_gen *res = (data_gen *) malloc(sizeof(data_gen));

      if(op == CONSTANTEE){
        instruccion->op = CTE_INSTRUCCION;
        instruccion->op1 = data->data;
        generate_temp(res->nombre);
        res->offset = stackPos;
        res->valor = data->data->valor;
        res->tipo = CONSTANTEE;
        res->const_var = data->data->tipo;

        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if(op == ASIGNACIONN){
        instruccion->op = ASIGN_INSTRUCCION;
        
        node *oper = getNodeSnd(n);
        if((oper->info->tipoOp == VARR) || (oper->info->tipoOp == PARAMETRO)){
          tresDir *movRax = (tresDir *) malloc(sizeof(tresDir));
          movRax->op = MOV;
          movRax->res = eval_expr(oper);
          agregar_instruccion(t, movRax);
        }

        instruccion->op1 = eval_expr(getNodeSnd(n));
        instruccion->res = eval_expr(getNodeFst(n));
        agregar_instruccion(t, instruccion);
      }
      else if(op == IGUALDADD){
        instruccion->op = EQ_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        res->offset = stackPos;
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if(op == NOTT){
        instruccion->op = NOT_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        res->valor = 0;
        generate_temp(res->nombre);
        res->offset = stackPos;
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == RESTAA && (getNodeSnd(n) != NULL)){
        instruccion->op = SUB_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        res->offset = stackPos;
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == RESTAA && (getNodeSnd(n) == NULL)){
        instruccion->op = OPUESTO_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        res->valor = 0;
        res->tipo = INTEGERR;
        generate_temp(res->nombre);
        res->offset = stackPos;
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == SUMAA){
        instruccion->op = ADD_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));

        res->valor = 0;
        generate_temp(res->nombre);

        res->offset = stackPos;
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == PRODD){
        instruccion->op = PROD_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        res->offset = stackPos;
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == DIVV){
        instruccion->op = DIV_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        res->offset = stackPos;
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == MODD){
        instruccion->op = MOD_INSTRUCCION;
        instruccion->op1 = eval_expr(getNodeFst(n));
        instruccion->op2 = eval_expr(getNodeSnd(n));
        res->valor = 0;
        generate_temp(res->nombre);
        res->offset = stackPos;
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if ((op == ANDD) || (op == ORR)){
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
        res->offset = stackPos;
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if ((op == MAYORR) ||(op == MENORR)){
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
        res->offset = stackPos;
        instruccion->res = res;
        agregar_instruccion(t, instruccion);
      }
      else if (op == IFTHENN){
        data_gen *endLabel = (data_gen *) malloc(sizeof(data_gen));
        data_gen *JmpType = (data_gen *) malloc(sizeof(data_gen));
        generate_label(endLabel->nombre);
        instruccion->op = IF_INSTRUCCION;
        instruccion->op2 = endLabel;
        instruccion->res = eval_expr(getNodeFst(n));

        agregar_instruccion(t, instruccion); //Condicion.

        crear_instrucciones(t, getNodeSnd(n)); //Cuerpo del then.

        tresDir *endIf = (tresDir *) malloc(sizeof(tresDir)); //End del if
        endIf->op = END_IF;
        endIf->res = endLabel;
        agregar_instruccion(t, endIf);
      }
      else if (op == IFTHENELSEE){
        data_gen *elseJmp = (data_gen *) malloc(sizeof(data_gen));
        generate_label(elseJmp->nombre);

        data_gen *endLabel = (data_gen *) malloc(sizeof(data_gen));
        generate_label(endLabel->nombre);

        data_gen *JmpType = (data_gen *) malloc(sizeof(data_gen));

        instruccion->op = IF_ELSE_INSTRUCCION;
        instruccion->res = eval_expr(getNodeFst(n));

        instruccion->op2 = elseJmp;
        agregar_instruccion(t, instruccion); //Condicion.

        crear_instrucciones(t, getNodeSnd(n));

        createJmp(JMP,endLabel);

        tresDir *elseInstr = (tresDir *) malloc(sizeof(tresDir));
        elseInstr->op = ELSE_INSTRUCCION;
        elseInstr->res = elseJmp;
        agregar_instruccion(t, elseInstr);

        crear_instrucciones(t, getNodeTrd(n));

        tresDir *elseEnd = (tresDir *) malloc(sizeof(tresDir));
        elseEnd->op = END_ELSE;
        elseEnd->res = endLabel;
        agregar_instruccion(t, elseEnd);
      }
      else if (op == WHILEE){
        data_gen *endLabel = (data_gen *) malloc(sizeof(data_gen));
        data_gen *labelWhile = (data_gen *) malloc(sizeof(data_gen));

        instruccion->op = LABEL_WHILE_INSTRUCCION;
        generate_label(labelWhile->nombre);
        instruccion->res = labelWhile;
        agregar_instruccion(t, instruccion);
        
        tresDir *whileInstruccion = (tresDir *) malloc(sizeof(tresDir));
        whileInstruccion->op = WHILE_INSTRUCCION;
        generate_label(endLabel->nombre);

        //Seteamos el tipo de Jump a realizar segun el tipo de la condicion (<,>,&&,||,!,==...).
        //int jmp = getJump(last_td->last);
        //whileInstruccion->op1->valor = jmp; 

        whileInstruccion->res = eval_expr(getNodeFst(n));
        whileInstruccion->op2 = endLabel;
        agregar_instruccion(t, whileInstruccion); //Condicion.

        crear_instrucciones(t, getNodeSnd(n));

        createJmp(JMP,labelWhile);

        tresDir *endWhile = (tresDir *) malloc(sizeof(tresDir));
        endWhile->op = LABEL_END_WHILE_INSTRUCCION;
        endWhile->res = endLabel;
        agregar_instruccion(t, endWhile);
      }

      else if (op == BLOCK){
        crear_instrucciones(t, getNodeFst(n));
      }
      else if (op == STATEMENTS){
        crear_instrucciones(t, getNodeFst(n));
        crear_instrucciones(t, getNodeSnd(n));
      }
      else if (op == RETURNN){
        if(n->tipoRet != VOIDD){
          instruccion->res = eval_expr(getNodeFst(n));
          instruccion->op = RETURN_INSTRUCCION;
          agregar_instruccion(t, instruccion);
        }
      }
      else if (op == INVOCC){
        tresDir *invocFunc = (tresDir *) malloc(sizeof(tresDir));
        if(data->params != NULL){
          invocFunc->op = CALL_WITH_PARAMS;
          cargar_parametros_actuales(t, data->params);
        }
        else{
          invocFunc->op = CALL;
        }
        data_gen *function = (data_gen *) malloc(sizeof(data_gen));
        strcpy(function->nombre, data->data->nombre);
        function->tipo = data->data->tipo;
        function->nParam = data->data->nParam;
        invocFunc->op1 = function;
        generate_temp(res->nombre);
        res->offset = stackPos;
        invocFunc->res = res;
        agregar_instruccion(t, invocFunc);
      }
    }
  }
}

int getJump(tresDir *instruccion){
  int op = instruccion->op;
  switch(op) {
     case MEN_INSTRUCCION   :
        return JGE;
        break;

     case MAY_INSTRUCCION   :
        return JLE;
        break;

     case EQ_INSTRUCCION  :
        return JNE;
        break;

     case JGE  :
        return JGE;
        break;

     case JE  :
        return JE;
        break;
     default :
     return -1;
  }
}

/*
 * Esta funcion nos permite traducir los codigos de las operacioens a Strings mas representativos para luego imprimir la lista.
 * *op: Codigo numerico de la operacion a traducir.
 */
char * opToString(int op){
  switch(op) {

     case JMP  :
        return "JMP";
        break;

     case JNE  :
        return "JNE";
        break;

     case JLE  :
        return "JLE";
        break;

     case JGE  :
        return "JGE";
        break;

     case JE  :
        return "JE";
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
     case CALL_WITH_PARAMS  :
        return "CALL_WITH_PARAMS";
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
     case ELSE_INSTRUCCION  :
        return "ELSE_INSTRUCCION";
        break;
     case END_IF  :
        return "END_IF";
        break;
     case END_ELSE  :
        return "END_ELSE";
        break;
    case LABEL_WHILE_INSTRUCCION  :
        return "LABEL_WHILE_INSTRUCCION";
        break;
    case LABEL_END_WHILE_INSTRUCCION  :
        return "LABEL_END_WHILE_INSTRUCCION";
        break;
    case CARGAR_ACTUAL_PARAMS  :
        return "CARGAR_ACTUAL_PARAMS";
        break;
     default :
     return "NULL";
  }
}

/*
 * Esta funcion se encarga de imprimir una istruccion.
 * *p: Instruccion a imprimir.
 */
void printInstruccion(tresDir *p){
  tresDir *aux = p;
  if(aux!= NULL){
    data_gen *aux1 = aux->op1;
    data_gen *aux2 = aux->op2;
    data_gen *aux3 = aux->res;
    if (aux1 == NULL){
      aux1 = (data_gen *) malloc(sizeof(data_gen));
      strcpy(aux1->nombre, "_" );
    }
    if (aux2 == NULL){
      aux2 = (data_gen *) malloc(sizeof(data_gen));
      strcpy(aux2->nombre, "_" );
    }
      printf("          |\n");
      if((strcmp(aux1->nombre, "int_cte") == 0) || (strcmp(aux1->nombre, "bool_cte") == 0)){
        printf("          |%s  %d  %s %s \n", opToString(aux->op), aux1->valor, aux2->nombre, aux3->nombre);
      }
      else{
        printf("          |%s  %s  %s %s \n", opToString(aux->op), aux1->nombre, aux2->nombre, aux3->nombre);
      }
  }
}

/*
 * Esta funcion imprime la lista de instrucciones de una funcion.
 * *d: Puntero al primer elemento de la lista de instrucciones de una funcion.
 */
void printFc(tresDir *d){
  tresDir *aux = d;
  if(aux != NULL){
    if(aux->next == NULL){
      printInstruccion(aux);
    }
    else{
      printInstruccion(aux);
      while(aux->next != NULL){
        aux = aux->next;
        printInstruccion(aux);
      }
    }
  }
}

/*
 * Esta funcion imprime todo el codigo de tres direcciones generado.
 */
void printLista(){
  printf("\n");
  printf("              Lista:\n");
  tresDirL *t = head_td;
  if(t == NULL){
    printf("Lista Vacia.\n");
  }
  else{
    printf(" ----------------------------- \n");
    printf("    inicio_%s           \n", t->nombre);
    printf(" ----------------------------- \n");
    printFc(t->fst);
    printf(" ----------------------------- \n");
    printf("    fin_%s           \n", t->nombre);
    printf(" ----------------------------- \n");
    t = t->next;
    while(t != NULL){
      printf(" ----------------------------- \n");
      printf("    inicio_%s           \n", t->nombre);
      printf(" ----------------------------- \n");
      printFc(t->fst);
      printf(" ----------------------------- \n");
      printf("    fin_%s           \n", t->nombre);
      printf(" ----------------------------- \n");
      t = t->next;
    }
  }
}