#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "indexT.h"


//Definicion de tipos de datos.
typedef struct strings string;
typedef struct data_generic data_gen;
typedef struct data_stacks data_stack;
typedef struct nodes node;
typedef struct stacks stack;
typedef struct nodeParams nodeParam;
typedef struct actualParams paramList;
typedef struct Formalparams formalParam;

/* Tipo utilizado para representar los Strings.
 * nombre: nombre es el valor del string
 * linea: Numero de linea.
 */
typedef struct strings{
  char nombre[32];
  int linea;
}string;

/* Tipo utilizado para representar los posibles datos en el arbol y en el scope.
 * nombre: nombre de la variable o funcion.
 * valor: En caso de tenerlo.
 * tipo: Tipo de la variable (integer, bool) o tipo de retorno (VOID, integer, bool) en caso de ser una funcion
 * linea: Numero de linea.
 */
typedef struct data_generic{
  char nombre[32];
  int valor;
  int tipo;
  int const_var;
  int linea;
  int offset;
  bool global;
  bool param;
  bool inic;
  int nParam;
} data_gen;

/* Tipo utilizado para representar los posibles datos en el scope (cada nivel de la pila)
 * nombre: nombre de la variable o funcion.
 * valor: En caso de tenerlo.
 * tipo: Tipo de la variable (integer, bool) o tipo de retorno (VOID, integer, bool) en caso de ser una funcion
 * linea: Numero de linea.
 * es_funcion: Nos indica si el data_stack esta representando una funcion.
 * *params: Lista de parametros actuales de una funcion.
 * *formalParams: Lista de parametros formales de una funcion
 * *next: Puntero al proximo elemento del scope.
 */
typedef struct data_stacks{
  data_gen *data;
  bool es_funcion;
  int tipoOp;
  int nParams;
  int stack_size;
  node *block;
  paramList *params;
  formalParam *formalParams;
  struct data_stacks *next;
} data_stack;

/* Tipo utilizado para implementar el AST.
 * *info: Es un struct que representa la informacion del nodo.
 * *fst: Nodo que representa el primer hijo en caso de tenerlo, sino es NULL.
 * *snd: Nodo que representa el segundo hijo en caso de tenerlo, sino es NULL.
 * *trd: Nodo que representa el tercer hijo en caso de tenerlo, sino es NULL.
 */
typedef struct nodes{ 
  int linea;
  data_stack *info;
  struct nodes *fst;
  struct nodes *snd;
  struct nodes *trd;
}node;

/* Tipo utilizado para implementar la pila que representa los niveles de alcance (scope).
 * id: representa el ID del nivel.
 * parent: Hace referencia al ID del bloque en el que esta contenido (si es el principal, parent==NULL).
 * info: Puntero al primer elemento del scope.
 * *next: Puntero al proximo nivel del scope.
 */
typedef struct stacks{
  int id;
  int parent;
  data_stack *info;
  data_stack *last;
  struct stacks *next;
}stack;

/*
 * Tipo utilizado para representar los parametros de la funcion createNodeParam, con el fin de modularizar y simplificar los cambios.
 * c[32]: Identificador de variable o funcion.
 * val: Valor entero en caso de tenerlo.
 * tipoVar: Tipo de variable representado por un entero.
 * tipoRet: Tipo de valor de retorno en caso de ser una funcion.
 * oper: Tipo de operacion.
 * linea: Numero de linea.
 * *fst: Primer hijo.
 * *snd: Segundo hijo.
 * *trd: Tercer hijo.
 * es_funcion: Campo booleano que nos permite saber si estamos tratando una funcion
 * *params: Lista de parametros actuales de una funcion.
 */
typedef struct nodeParams{ 
  char nombre[32];
  int valor;
  int tipoVar;
  int tipoRet;
  int oper;
  int linea;
  node *fst;
  node *snd;
  node *trd;
  node *block;
  bool es_funcion;
  paramList *params;
}nodeParam;

/* Tipo utilizado para representar los parametros actuales de las funciones.
 * *parametro: Arbol que representa una expresion a evaluar, puede ser una invocacion a otro metodo, una expresion matematica, booleana, etc.
 * *next: Puntero al proximo parametro.
 */
typedef struct actualParams{
  int numero;
  node *parametro;
  struct actualParams *next;
} paramList;

/* Tipo utilizado para representar los parametros formales de las funciones.
 * *nombre: Nombre del parametro formal.
 * tipo: Tipo del parametro (integer,bool).
 * *next: Puntero al proximo parametro.
 */
typedef struct Formalparams{
  char nombre[32];
  int tipo;
  int numero;
  int offset;
  struct Formalparams *next;
} formalParam;

//VARIABLES GLOBALES:
node *root;
stack *current, *inicial;
formalParam *fstParam, *lastParam; //--Lista de parametros formales que se reinicia luego de insertada la funcion.
int niveles, nVars;


//DECLARACIONES DE METODOS:

//Crea un nodo del arbol.
node * createNode(nodeParam *param);

//Empaqueta toda la informacion necesaria para crear un nodo en un Struct nodeParam.
nodeParam * createNodeParam(string *s, int val, int tipoVar, int tipoRet, int oper, node *fst, node *snd, node *trd, bool es_funcion, paramList *params, int linea);

//Crea el data_stack para ser usado en otras funciones.
data_stack * crearDataStack(string *s, int tipo, int valor, int tipoOp, int linea, node *block, formalParam *params, bool es_func);

//Se utiliza para obtener el nombre de un data_gen.
string * getName(data_stack *d);

//Retorna el valor del campo value de un data_gen contenido en un data_stack.
int getValue(data_stack *d);

//Crea una nueva invocacion a una funcion.
void newCall(paramList *p, node *n);

//Esta funcion nos permite obbtener el primer hijo de un arbol.
node * getNodeFst(node *param);

//Esta funcion nos permite obbtener el segundo hijo de un arbol.
node * getNodeSnd(node *n);

//Esta funcion nos permite obbtener el tercer hijo de un arbol.
node * getNodeTrd(node *n);

//Esta funcion cuenta la cantidad de parametros formales de una funcion
int countParams(formalParam *pl);

//Esta funcion cuenta la cantidad de parametros actuales de una invocacion a funcion.
int counActualParams(paramList *pl);

//Esta funcion nos permite verificar que los parametros actuales coinciden con los formales, en cantidad y en tipos.
void checkParams(node *n);

//Esta funcion evalua un nodo.
int evalExpr(node *n, int tipoRet);

//Esta funcion nos retorna el numero de linea de un elemento del stack.
int getLinea(data_stack *d);

//Esta funcion nos permite obtener los parametros formales de una funcion.
formalParam * getParams(data_stack *d);

//Esta funcion libera la memoria utilizada por un arbol/sub-arbol arbol.
void eliminarArbol(node *n);

//Esta funcion elimina todos los arboles generados por las funciones.
void deleteFuncitonBlocks();

//Funcion que nos permite visualizar los parametros formales de una funcion.
void printFormalParams(formalParam *fp);

void printActualParams(paramList *pl);

//Funcion que comienza el chequeo semantico del programa.
void checkParams(node *n);

//Funcion que elimina los cuerpos de las funciones.
void deleteFuncitonBlocks();

//Funcoion que elimina los nodos generados por las invocaciones a funciones.
void deleteCalls(paramList *pl);

//Esta funcion elimina un arbol o sub-arbol.
void eliminarArbol(node *n);

void initVar(stack *s, char c[32]);

int buscar_var_id(stack *s, char c[32]);

//IMPLEMENTACION DE METODOS.

/*
 * Esta funcion inicializa el scope, creando el primer nivel que contendra a los demas.
 */
void init(){
  //printf("ENTRAMOS A INIT\n");
  nVars = 0;
  current = (stack *) malloc(sizeof(stack));
  inicial = (stack *) malloc(sizeof(stack));
  inicial->info = (data_stack *) malloc(sizeof(data_stack));
  inicial->last = inicial->info;
  fstParam =  (formalParam *) malloc(sizeof(formalParam));
  lastParam =  (formalParam *) malloc(sizeof(formalParam));
  current->next = NULL;
  current->parent = -1;
  current->info = NULL;
  current->id = 1;
  inicial = current;
  niveles = 1;
  tablaFst = (indexT *) malloc(sizeof(indexT));
  tablaLast = (indexT *) malloc(sizeof(indexT));
  tablaFst->id = 1;
  tablaFst->prev = NULL;
  tablaFst->next = NULL;
  tablaLast = tablaFst;
}

/*
 * Esta funcion devuelve el tope de la pila.
 */
stack * tope(){
  return current;
}

/*
 * Esta funcion nos permite obtener el campo tipo de un Struct data_stack.
 */
int getTipo(data_stack *d){
  if(d != NULL){
    data_gen *aux = d->data;
    return aux->tipo;
  }
  else{
    return -999;
  }
}

/*
 * Esta funcion nos permite obtener el ID del padre de un nivel.
 */
int getParent(){
  if(getIndexPrev(tablaLast) != NULL){
    return getIndexId(getIndexPrev(tablaLast));
  }
  else{
    return getIndexId(tablaLast);
  }
}

/*
 * Esta funcion crea un nuevo nivel.
 * n: ID del bloque que lo contiene
 */
void crear_nivel(){
  stack *newLevel = (stack *) malloc(sizeof(stack));
  newLevel->info = NULL;
  newLevel->last = newLevel->info;
  current->next = newLevel;
  current = newLevel;
  niveles = niveles + 1;
  insertar_index(niveles);
  newLevel->parent = getParent();
  newLevel->id = niveles;
}



/*
 * Esta funcion nos permite castear un nodeAux como un node.
 */
void printDataStack(data_stack *d, int id, int padre){
  printf("          |\n");
  printf("          |\n");
  printf("          |\n");
  printf("           ----------------------------- \n");

  printf("          | ID nivel:   | %d             |\n", id);


  if(padre <10 && padre > 0){
    printf("          | ID Padre:   | %d             |\n", padre);
  }
  else if((padre >9 && padre < 100) || (padre < 0)){
    printf("          | ID Padre:   | %d            |\n", padre);
  }
  else if((padre > 99 && padre < 1000)){
    printf("          | ID Padre:   | %d             |\n", padre);
  }

  printf("          | Es funcion: | %d             |\n", d->es_funcion);

  printf("          | Nombre:     | %s\n", d->data->nombre);

  if(d->data->valor <10 && d->data->valor > 0){
    printf("          | Valor:      | %d             |\n", d->data->valor);
  }
  else if((d->data->valor >9 && d->data->valor<100) || (d->data->valor < 0)){
    printf("          | Valor:      | %d            |\n", d->data->valor);
  }
  else if((d->data->valor > 99 && d->data->valor < 1000)){
    printf("          | Valor:      | %d           |\n", d->data->valor);
  }
  if(d->data->tipo <10){
    printf("          | Tipo:       | %d             |\n", d->data->tipo);
  }
  else{
    printf("          | Tipo:       | %d            |\n", d->data->tipo);
  }

  if(d->data->global){
    printf("          | Global: True     |           |\n");
  }
  else{
    printf("          | Global: False    |           |\n");
  }

  if(d->data->offset <10 && d->data->offset > 0){
    printf("          | Offset:      | %d             |\n", d->data->offset);
  }
  else if((d->data->offset >9 && d->data->offset<100) || (d->data->offset < 0)){
    printf("          | Offset:      | %d            |\n", d->data->offset);
  }
  else if((d->data->offset > 99 && d->data->offset < 1000)){
    printf("          | Offset:      | %d           |\n", d->data->offset);
  }

  if(d->data->inic){
    printf("          | Inic: True     |           |\n");
  }
  else{
    printf("          | Inic: False    |           |\n");
  }

  if(d->data->linea <10){
    printf("          | Linea:      | %d             |\n", d->data->linea);
  }
  else if(d->data->linea >9 && d->data->linea<100){
    printf("          | Linea:      | %d            |\n", d->data->linea);
  }
  else if((d->data->linea > 99 && d->data->linea < 1000)){
    printf("          | Linea:      | %d           |\n", d->data->linea);
  }
  printf("           ----------------------------- \n");
}

/*
 * Esta funcion imprime un nivel completo. Utiliza a la funcion printDataStack.
 * id: ID del bloque al que pertenece
 * padre: ID del bloque que lo contiene inmediatamente.
 * *d: Dato del nivel a imprimir.
 */
void printLevel(data_stack *d, int id, int padre){
  if(d != NULL){
    if(d->next == NULL){
      printDataStack(d, id, padre);
    }
    else{
      printDataStack(d, id, padre);
      while(d->next != NULL){
        d = d->next;
        printDataStack(d, id, padre);
      }
    }
  }
  else{
    printf("NIVEL ID: %d VACIO CON PADRE ID: %d\n", id, padre);
  }
}

/*
 * Esta funcion imprime el stack completo, utiliza a la funcion printLevel para imprimir cada nivel.
 */
void printStack(){
  printf("\n");
  printf("              STACK:\n");
  stack *s = (stack *) malloc(sizeof(stack));
  s = inicial;
  if(s == NULL){
    printf("STACK VACIO.\n");
  }
  else{
    printf(" ----------------------------- \n");
    printf("|           NIVEL: %d          |\n", s->id);
    printf("|                             | \n");
    printf("|                             | \n");
    printf(" ----------------------------- \n");
    printLevel(s->info, s->id, s->parent);
    s = s->next;
    while(s != NULL){
      printf(" ----------------------------- \n");
      printf("|           NIVEL: %d          |\n", s->id);
      printf("|                             | \n");
      printf("|                             | \n");
      printf(" ----------------------------- \n");
      printLevel(s->info, s->id, s->parent);
      s = s->next;
    }
  }
}

/*
 * Esta funcion busca un ID en un nivel determinado.
 * *s: Nivel en el cual buscar.
 * c[10]: ID a buscar.
 */
data_stack * buscar_id(stack *s, char c[32]){
  if(s->info != NULL){
    data_stack *aux = s->info;
    char name[32];
    strcpy(name, aux->data->nombre);
    while(((aux->next) !=  NULL)  && (strcmp(name,c)!= 0)){
      aux = (data_stack *) aux->next;
      strcpy(name, aux->data->nombre);
    }
    if(strcmp(name, c) == 0){return aux;}
    else{return NULL;}
  }
  else{ return NULL;}
}

/*
 * Esta funcion busca un nivel a partir de su ID, comenzando desde el tope de la "pila"
 * *s: Tope de la pila.
 * n: ID del nivel a buscar.
 */
stack * buscar_niv(stack *s, int n){
  if(s->id == n){
    return s;
  }else{
    while(((s->next) !=  NULL)  && (s->id != n)){
      s = (stack *) s->next;
    }
    if(s->id == n){return s;}
    else{return NULL;}
  }
}

/*
 * Buscamos las fnciones por su ID en el primer nivel, ya que es donde se declaran, no se admiten declaraciones de funciones anidadas.
 * c: ID de la funcion a buscar
 * return: data_Stack si encuentra el ID, NULL si no lo encuentra.
 */
data_stack * buscar_func(string *s){
  return buscar_id(inicial, s->nombre);
}

/*
 * Esta funcion busca un ID por niveles, le pasamos el nivel actual y si no encuentra el ID entonces busca en los niveles que lo contienen
 * *s: Nivel actual en el que iniciar la busqueda.
 * c[10]: ID a buscar.
*/
data_stack * buscar_por_niveles(stack *s, char c[32]){
  int id = s->parent;
  stack *auxS = s;
  data_stack *aux;

  aux = buscar_id(auxS,c);
  if(aux != NULL){
    return aux;
  }
  if(id != -1){
    auxS = buscar_niv(inicial, id);
    aux = buscar_id(auxS,c);
    if(aux != NULL){
      return aux;
    }
    id = auxS->parent;
    while(id != -1 && aux == NULL){
      auxS = buscar_niv(inicial, id);
      aux = buscar_id(auxS,c);
      id = auxS->parent;
    }
    return aux;
  }
  return NULL;
}

/*
 * Esta funcion busca un ID en un nivel determinado.
 * *s: Nivel en el cual buscar.
 * c[10]: ID a buscar.
 */
int buscar_var_id(stack *s, char c[32]){
  if(s->info != NULL){
    data_stack *aux = s->info;
    char name[32];
    strcpy(name, aux->data->nombre);
    while(((aux->next) !=  NULL)  && (strcmp(name,c)!= 0)){
      aux = (data_stack *) aux->next;
      strcpy(name, aux->data->nombre);
    }
    if(strcmp(name, c) == 0){aux->data->inic = true; return 1;}
    else{return -1;}
  }
  else{ return -1;}
}

void initVar(stack *s, char c[32]){
  int id = s->parent;
  int res;
  stack *auxS = s;

  res = buscar_var_id(auxS,c);
  if(res == -1){
    auxS = buscar_niv(inicial, id);
    res = buscar_var_id(auxS,c);
    if(res == -1){
      id = auxS->parent;
      while(id != -1 && res == -1){
        auxS = buscar_niv(inicial, id);
        res = buscar_var_id(auxS,c);
        id = auxS->parent;
      }
    }
  }
}

/*
 * Este metodo inserta una funcion en el primer nivel de la pila (ya que solo se pueden declarar al inicio del codigo).
 * *d: Informacion de la funcion representada en un data_stack.
 */
void insertar_funcion(data_stack *d){
  data_stack *newD = (data_stack *) malloc(sizeof(data_stack));
  newD = d;
  newD->block = d->block;
  newD->next = NULL;
  newD->nParams = countParams(d->formalParams);
  newD->formalParams = d->formalParams;
  newD->stack_size = nVars;
  stack *aux = inicial;

  data_stack *res = buscar_id(inicial, d->data->nombre);

  if(res != NULL){
    createError(res->data->linea, FUNCEXIST);
    printErrors();
  }
  else{
    nVars = 0;
    res = (data_stack *) aux->info;
    if(res != NULL){
      while((res->next) != NULL){
        res = (data_stack *) res->next;
      }
      res->next = (data_stack *)newD;
      res = newD;
    }
    else{
      res = newD;
      aux->info = newD;
    }
  }
}

/*
 * Esta funcion nos permite contar los parametros actuales de una invocacion.
 * *pl: paramList: lista nodos que representan expresiones.
 */
int counActualParams(paramList *pl){
  int params = 0;
  if(pl != NULL){
    paramList *aux = pl;
    node *n = aux->parametro;
    if(aux != NULL){
      if(n!= NULL){
        params = params + 1;
        pl->numero = params;
      }
      while(aux->next != NULL){
      aux = aux->next;
      n = aux->parametro;
      if(n!= NULL){
        pl->numero = params;
        params = params + 1;
      }
     }
    }
  }
  return params;  
}

/*
 * Esta funcion nos permite contar los parametros formales.
 * *pl: formalParam: lista de parametros.
 */
int countParams(formalParam *pl){
  int params = 0;
  formalParam *aux = pl;
  if(aux != NULL){
   params = params + 1;
   while(aux->next != NULL){
     params = params + 1;
     aux = aux->next;
   }
  }
  return params;
}

/*
 * Esta funcion nos permite obtener la lista de parametros formales.
 * *d: data_stack que contiene todos los datos necesarios.
 */
formalParam * getParams(data_stack *d){
  return d->formalParams;
}

/*
 * Esta funcion nos permite insertar un simbolo en la tabla de simbolos
 * la cual esta representada como una lista de listas. La lista principal representa una "pila".
 */
void insertar(data_stack *d){
  data_stack *newD = (data_stack *) malloc(sizeof(data_stack));
  newD = (data_stack *)d;
  newD->next = NULL;

  stack *aux = tope();
  data_stack *res = buscar_id(current, d->data->nombre);
  if(res != NULL){
    if(d->es_funcion){
      printNodeError(createError(res->data->linea, FUNCEXIST));
    }
    else{
      printNodeError(createError(res->data->linea, VAREXIST));
    }
  }
  else{
    res = (data_stack *) aux->info;
    if(res != NULL){ //Nivel corriente no vacio.
      if(res->tipoOp == PARAMETRO){
        nVars = nVars + 1;
        formalParam *auxP = lastParam;
        formalParam *fp = (formalParam *) malloc(sizeof(formalParam));
        strcpy(fp->nombre, d->data->nombre);
        fp->tipo = d->data->tipo;

        if(auxP == NULL){
          fp->numero = 1;
          fp->offset = fp->numero;
          newD->data->offset = fp->offset;
          newD->data->inic = true;
          lastParam = fp;
          lastParam->next = NULL;
          fstParam->next = lastParam;
        }
        else{
          fp->numero = (lastParam->numero) + 1;
          fp->offset = fp->numero;
          newD->data->offset = fp->offset;
          newD->data->inic = true;
          lastParam->next = fp;
          lastParam = fp;
        }
      }
      if(d->tipoOp == VARR){
        nVars = nVars + 1;
        if((tope()->id) == (1)){
          newD->data->global = true;
        }
        newD->data->offset = nVars;
        newD->data->inic = false;
      }
      aux->last->next = (data_stack *)newD;
      aux->last = aux->last->next;
    }
    else{ //Nivel corriente vacio
      if(d->tipoOp == PARAMETRO){
        nVars = nVars + 1;
        formalParam *auxP = lastParam;
        formalParam *fp = (formalParam *) malloc(sizeof(formalParam));
        strcpy(fp->nombre, d->data->nombre);
        fp->tipo = d->data->tipo;
        fp->numero = 1;
        fp->offset = fp->numero;
        newD->data->offset = fp->offset;
        newD->data->inic = true;
        fstParam = fp;
        fstParam->next = NULL;
        lastParam = fstParam;
      }
      if(d->tipoOp == VARR){
        nVars = nVars + 1;
        if((tope()->id) == (1)){
          newD->data->global = true;
        }
        newD->data->offset = nVars;
        newD->data->inic = false;
      }
      res = (data_stack *)newD;
      aux->info = res;
      aux->last = aux->info;
    }
  }
}

/*
 * Esta funcion nos permite crear un data_stack para insertar en un arbol o en el stack.
 * *s: Es un Struct string que representa el nombre de la funcion o variable a insertar.
 * tipo: El tipo de la variable o el tipo de retorno de la funcion.
 * valor: valor de la variable si es que lo tiene.
 * tipoOp: Representa el tipo de operacion a realizar con la informacion cargada.
 * linea: Numero de linea donde se leyo la informacion.
 * *block: Representa el cuerpo de una funcion (en caso de serlo, sino es NULL).
 * *params: Lista de parametros formales de una funcion (si no es funcion, es NULL).
 * es_func: Este campo nos permite indicar e identificar a las funciones.
 */
data_stack * crearDataStack(string *s, int tipo, int valor, int tipoOp, int linea, node *block, formalParam *params, bool es_func){
  data_gen *auxGen = (data_gen *) malloc(sizeof(data_gen));
  strcpy(auxGen->nombre, s->nombre);
  auxGen->tipo = tipo;
  auxGen->valor = valor;
  auxGen->linea = linea;
  if(PARAMETRO == PARAMETRO){
    auxGen->param = true;
  }
  else{
    auxGen->param = false;
  }
  data_stack *aux = (data_stack *) malloc(sizeof(data_stack));
  aux->data = auxGen;
  aux->tipoOp = tipoOp;

  aux->block = block;
  aux->formalParams = params;
  aux->nParams = countParams(params);
  aux->es_funcion = es_func;
  return aux;
}

/*
 * Esta funcion realmente no sirve para nada, es totalmente inutil, retorna lo mismo que se le pasa como parametro
 * Seguramente se creo a altas horas de la madrugada cuando la razon y la logica se encuentran totalmente opacadas por el sueño.
 * *d: Ni siquiera importa...de hecho, pensandolo bien, en lo que escribi esta descripcion, podria haber eliminado la funcion...
 */
string * getNombre(string *d){
  return d;
}

/*
 * Esta funcion nos permite convertir un char [] en un struct string.
 * c[32]: palabra a convertir a string.
 */
string * toString(char c[32]){
  string *s = (string *) malloc(sizeof(string));
  strcpy(s->nombre, c);
  return s;
}

/*
 * Esta funcion nos permite obtener el campo nombre de un data_stack
 * *d: data_stack.
 */
string * getName(data_stack *d){
  string *s;
  if(d != NULL){
    char res[32];
    strcpy(res, d->data->nombre);
    s = toString(res);
    return s;
  }
  s = (string *) malloc(sizeof(string));
  strcpy(s->nombre, "NOMBRE NO ENCONTRADO - DATANULL");
  return s;

}

/*
 * Esta funcion nos permite obtener campo valor de un data_stack
 * *d: data_stack que contiene a value.
 */
int getValue(data_stack *d){
  data_gen *aux = d->data;
  return aux->valor;
}

/*
 * Esta funcion nos permite obtener el primer hijo de un nodo
 * *n: Nodo padre.
 */
node * getNodeFst(node *n){
  if(n->fst != NULL){
    return(n->fst);
  }
  else{
    return NULL;
  }
}

/*
 * Esta funcion nos permite obtener el segundo hijo de un nodo
 * *n: Nodo padre.
 */
node * getNodeSnd(node *n){
  if(n->snd != NULL){
    return(n->snd);
  }
  else{
    return NULL;
  }
}

/*
 * Esta funcion nos permite obtener el tercer hijo de un nodo
 * *n: Nodo padre.
 */
node * getNodeTrd(node *n){
  if(n->trd != NULL){
    return(n->trd);
  }
  else{
    return NULL;
  }
}

/*
 * Luego de que se genera la lista de parametros de una funcion, al ser esta global debe ser reiniciada.
 * para que la proxima definicion de funcion no tenga parametros quen no le corresponden.
 */
void resetParams(){
  fstParam = (formalParam *)malloc(sizeof(formalParam));
  fstParam->next = NULL;
  lastParam = fstParam;
}

/*
 * Esta fue utilizada para visualizar los parametros formales de una funcion
 * *fp: Lista de parametros formales.
 */
void printFormalParams(formalParam *fp){
  if(fp==NULL){
    printf("Parametros vacios\n");
  }
  else{
    while (fp!=NULL){
      printf("Nombre: %s - Tipo: %d\n", fp->nombre, fp->tipo);
      fp = fp->next;
    }
  }
}

/*
 * Esta fue utilizada para visualizar los parametros actuales de una invocacion.
 * *pl: Lista de parametros actuales.
 */
void printActualParams(paramList *pl){
  paramList *aux = pl;
  node *n;
  if(aux==NULL){
    printf("Parametros vacios\n");
  }
  else{
    n = aux->parametro;
    if(n!=NULL){
      printf("Nombre: %s - Tipo: %d\n", n->info->data->nombre, n->info->data->tipo);
    }
    aux = aux->next;
    while(aux!=NULL){
      n = aux->parametro;
      if(n!=NULL){
        printf("Nombre: %s - Tipo: %d  -Numero: %d\n", n->info->data->nombre, n->info->data->tipo, aux->numero);
      }
      aux = aux->next;

    }
  }
}

/*
 * Esta funcion nos permite recuperar el primer nodo de la lista de parametros formales que se esta generando
 * Luego de que se genera la lista de parametros de una funcion, al ser esta global debe ser reiniciada.
 * *pl: Es la lista de parametros actuales.
 */
formalParam * getFormalParams(){
  return fstParam;
}

/*
 * Esta funcion nos permite recuperar la informacion de un nodo.
 * *n: Nodo que contiene la informacion.
 */
data_stack * getNodeData(node *n){
  if(n != NULL){return n->info;}
  else{return NULL;}
}  

/*
 * Esta funcion se utiliza para obtener el numero de linea de algun dato en la pila o de un nodo.
 * *d: No hay mucho que decir, es un data_Stack
 */
int getLinea(data_stack *d){
  return d->data->linea;
}

/*
 * Esta funcion se utiliza para obtener el tipo de la ultima variable declarada, se utiliza en la declaracion de multiples variables
 * del mismo tipo
 */
int lastType(){
  stack *aux = current;
  data_stack *aux2 = (data_stack *)aux->info;
  while(aux2->next!= NULL){
    aux2 = (data_stack *) aux2->next;
  }
  return aux2->data->tipo;
}


/*
 * Esta funcion nos permite crear un nodeParam que luego se utiliza para generar un nuevo nodo del arbol.
 * *s: Es un Struct string que representa el nombre del nodo.
 * val: valor del nodo en caso de tenerlo (por ejemplo en las constantes).
 * tipoVar: Se suele utilizar para repsentar el tipo de una variable.
 * tipoRet: Se utiliza para indicar el tipo de retorno de una funcion.
 * oper: Representa el tipo de operacion a realizar.
 * *fst: Representa el primer hijo en caso de tenerlo, si no tiene, es NULL.
 * *snd: Representa el segundo hijo..idem al primero
 * *trd: idem a los anteriores.
 * *block: Representa el cuerpo de una funcion (en caso de serlo, sino es NULL).
 * es_func: Este campo nos permite indicar e identificar a las funciones.
 * *params: Lista de parametros actuales de una funcion (si no es funcion, es NULL).
 * linea: Numero de linea donde se leyo la informacion.
 */
nodeParam * createNodeParam(string *s, int val, int tipoVar, int tipoRet, int oper, node *fst, node *snd, node *trd, bool es_funcion, paramList *params, int linea){
  nodeParam *nodeAux = (nodeParam *) malloc(sizeof(nodeParam));
  strcpy(nodeAux->nombre,s->nombre);
  nodeAux->valor = val;
  nodeAux->tipoVar = tipoVar;
  nodeAux->tipoRet = tipoRet;
  nodeAux->oper = oper;
  nodeAux->linea = linea;
  nodeAux->fst = fst;
  nodeAux->snd = snd;
  nodeAux->trd = trd;
  nodeAux->es_funcion = es_funcion;
  nodeAux->params = params;
  return nodeAux;
}

/*
 * Esta funcion nos permite crear un nodo con la informacion obtenida en createNodeParam().
 * *param: Es un struct que contiene toda la informacion necesaria para representar un nodo.
 */
node * createNode(nodeParam *param){

  data_gen *data = (data_gen *) malloc(sizeof(data_gen));
  data_stack *dataS = (data_stack *) malloc(sizeof(data_stack));
  node *n = (node *) malloc(sizeof(node));

  if(param != NULL){
    if((param->oper) == ASIGNACIONN){
      dataS = buscar_por_niveles(tope(), param->fst->info->data->nombre);
      if(dataS == NULL){
        createError(param->linea, UNDECLAREDVAR);
      }
      else{
        initVar(tope(), param->fst->info->data->nombre);
        dataS = crearDataStack(toString(param->nombre), param->tipoVar, param->valor, param->oper, param->linea, NULL, NULL, false);
      }
    }
    else if(param->oper == VARR || param->oper == PARAMETRO){
      dataS = buscar_por_niveles(current, param->nombre);
      if(dataS == NULL){
        char c[256];
        strcpy(c, " variable no declarada: ");
        strcat(c, param->nombre);
        createNewError(param->linea, c, UNDECLAREDVAR);
      }
    }
    else if(param->oper == INVOCC){
      dataS = crearDataStack(toString(param->nombre), param->tipoVar, param->valor, param->oper,  param->linea, NULL, NULL, true);
      dataS->params = param->params;
    }
    else{
      dataS = crearDataStack(toString(param->nombre), param->tipoVar, param->valor, param->oper, param->linea, NULL, NULL, false);
    }
    treeSize = treeSize + 1;
    n->info = dataS;
    n->linea = param->linea;
    n->fst = param->fst; n->snd = param->snd; n->trd = param->trd;
  }
  return n;
}

/*
 * Esta funcion nos permite crear una nueva invocacion a una funcion.
 * Se va creando una lista de parametros actuales representados por nodos, ya que los parametros actuales son expresiones.
 * *p: Lista de parametros actuales a donde vamos a cargar el nuevo parametro leido.
 * *n: Es el parametro leido representado como un nodo.
 */
void newCall(paramList *p, node *n){
  paramList *newParam = (paramList *) malloc(sizeof(paramList));
  paramList *aux = p;


  if(aux == NULL){
    //n->info->data->nParam = 1;
    newParam->parametro = n;
    newParam->numero = 1;
    aux = newParam;
  }
  else{
    int i = 0;
    while(aux->next != NULL){
      aux = aux->next;
      i = i+1;
    }
    //n->info->data->nParam = i + 1;
    newParam->parametro = n;
    newParam->numero = i +1;
    aux->next = newParam;
  }
}

/*
 * Esta funcion inicializa todo el chequeo semantico del programa, ya que el mismo esta cargado en el stack
 * La funcion main() que contiene el cuerpo principal del programa es la ultima funcion cargada en el primer nivel del stack.
 * *s: Este parametro deberia ser el nivel inicial del stack, que es donde estan todas las funciones incluyendo a la main().
 */
void checkFunctions(stack *s){
  data_stack *origin = s->info;
  data_stack *aux = origin;

  if(aux != NULL){
    if(aux->es_funcion){
      evalExpr(aux->block, getTipo(aux));
    }
    while(aux->next != NULL){
      aux = aux->next;
      if(aux->es_funcion){
        evalExpr(aux->block, getTipo(aux));
      }
    }
  }
}

/*
 * Esta funcion evalua una expresion y retorna su tipo, si encuentra algun conflicto genera un error y lo carga en la lista.
 * *n: Este parametro representa la expresion;
 * tipoRet: Es el tipo que esperamos deberia retornar la expresion. Si son distintos, se genera un error.
 */
int evalExpr(node *n, int tipoRet){
  if(n!=NULL){
    data_stack *data = n->info;
    if(data != NULL){
      int op = data->tipoOp;
      string *s = getName(data);
      char cAux[32];
      strcpy(cAux, s->nombre);
      if(op == VARR || op == CONSTANTEE || op == PARAMETRO){
        if(op == VARR){
          if(!(data->data->inic)){
            char c[256];
            strcpy(c, " variable no inicializada: ");
            strcat(c, cAux);
            createNewError(data->data->linea, c, UNINITIALIZENVAR);
          }
        }
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
        evalExpr(getNodeFst(n), tipoRet);
        evalExpr(getNodeSnd(n), tipoRet);
        
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
  }
  return VOIDD;
}

/*
 * Esta funcion controla que la invocacion a una funcion sea correcta.
 * Primero verifica si la cantidad de parametros ingresadas es la correta.
 * En caso de que el chequeo anterior sea correcto, se procede a verificar el orden y tipo de los parametros
 * *n: Es el nodo que representa la invocacion de la funcion.
 */
void checkParams(node *n){
  data_stack *data = buscar_func(toString(n->info->data->nombre));
  paramList *paramInvoc = n->info->params;
  formalParam *formal = data->formalParams;
  bool control = true;
  int nn = counActualParams(paramInvoc);
  if(data->nParams != nn){
    createError(getLinea(getNodeData(n)), INVOCPARAMS);
  }
  else{
    while((paramInvoc != NULL) && control){
      if(paramInvoc->parametro== NULL){
        paramInvoc = paramInvoc->next;
      }
      int res = evalExpr(paramInvoc->parametro, IGNORE);
      if((res != formal->tipo) && (res != UNKNOW)) {
        createNewError(getLinea(data), "Error de tipos en el la invocacion ", WRONGTYPEPARAM);
        control =false;
      }
      if(paramInvoc->parametro!= NULL){
        formal = formal->next;
      }
      paramInvoc = paramInvoc->next;
    }
  }
}

/*
 * Esta funcion se utiliza para liberar la memoria utilizada por las llamadas a funciones ya que los parametros actuales son nodos
 * *pl: Es la lista de parametros actuales.
 */
void deleteCalls(paramList *pl){
  if(pl!=NULL){
    eliminarArbol(pl->parametro);
    while(pl->next!=NULL){
      pl = pl->next;
      eliminarArbol(pl->parametro);
    }
  }
}

/*
 * Esta funcion se utiliza para liberar la memoria utilizada por los cuerpos de las funciones.
 * Es la funcion principal encargada de liberar la memoria.
 */
void deleteFuncitonBlocks(){
  data_stack *res = inicial->info;
  data_stack *aux = res;
  if(aux->es_funcion){
    eliminarArbol(aux->block);
  }
  while(aux->next != NULL){
    aux = aux->next;
    if(aux->es_funcion){
      eliminarArbol(aux->block);
    } 
  }

}

/*
 * Esta funcion se utiliza para liberar la memoria utilizada por un arbol o subarbol.
 * *n: Raiz del arbol o subarbol a eliminar.
 */
void eliminarArbol(node *n){
  if (n != NULL) {
    data_stack *data = n->info;
    eliminarArbol(getNodeFst(n));
    eliminarArbol(getNodeSnd(n));
    eliminarArbol(getNodeTrd(n));
    deleteCalls(data->params);
    treeSize = treeSize - 1;
    free(n);
  }
}