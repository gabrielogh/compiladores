#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "indexT.h"


//Definicion de tipos de datos.
typedef struct strings string;
typedef struct nodes node;
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
  int linea;
} data_gen;

/* Tipo utilizado para representar los posibles datos en el scope (cada nivel de la pila)
 * nombre: nombre de la variable o funcion.
 * valor: En caso de tenerlo.
 * tipo: Tipo de la variable (integer, bool) o tipo de retorno (VOID, integer, bool) en caso de ser una funcion
 * linea: Numero de linea.
 * es_funcion: Nos indica si el data_stack esta representando una funcion.
 * params: Puntero al primer parametro de la lista.
 * *next: Puntero al proximo elemento del scope.
 */
typedef struct data_stacks{
  data_gen *data;
  bool es_funcion;
  int tipoOp;
  int nParams;
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
    struct stacks *next;
}stack;

/*
 * Tipo utilizado para representar los parametros de la funcion insertar, con el fin de modularizar y simplificar los cambios.
 * c[32]: Identificador de variable o funcion.
 * val: Valor entero en caso de tenerlo.
 * tipoVar: Tipo de variable representado por un entero.
 * tipoRet: Tipo de valor de retorno en caso de ser una funcion.
 * *fst: Primer hijo.
 * *snd: Segundo hijo.
 * *trd: Tercer hijo.
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
  struct Formalparams *next;
} formalParam;

//VARIABLES GLOBALES:
node *root;
stack *current, *inicial;
formalParam *fstParam, *lastParam;
int niveles;


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

void eliminarArbol(node *n);

//Esta funcion nos permite obbtener el primer hijo de un arbol.
node * getNodeFst(node *param);

//Esta funcion nos permite obbtener el segundo hijo de un arbol.
node * getNodeSnd(node *n);

//Esta funcion nos permite obbtener el tercer hijo de un arbol.
node * getNodeTrd(node *n);

//Se utiliza para obtener los parametros de una funcion.
paramList * getStackInfo(stack *s);

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

void checkParams(node *n);

void deleteFuncitonBlocks();

void deleteCalls(paramList *pl);

//IMPLEMENTACION DE METODOS.

/*
 * Esta funcion inicializa el scope, creando el primer nivel que contendra a los demas.
 */
void init(){
  //printf("ENTRAMOS A INIT\n");
  current = (stack *) malloc(sizeof(stack));
  inicial = (stack *) malloc(sizeof(stack));
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
  if(debug){
    printf("ENTRAMOS A GETTIPO\n");
  }
  if(d != NULL){
    data_gen *aux = d->data;
    if(debug){
      printf("VAMOS A SALIR DE GETTIPO\n");
    }
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
  if(debug){
    printf("ENTRAMOS A GET PARENT\n");
  }
  if(getIndexPrev(tablaLast) != NULL){
    if(debug){
      printf("PADRE PREVIO OBTENIDO: ID: %d\n", getIndexId(tablaLast));
    }
    return getIndexId(getIndexPrev(tablaLast));
  }
  else{
    if(debug){
      printf("PADRE ACTUAL OBTENIDO: ID: %d\n", getIndexId(tablaLast));
    }
    return getIndexId(tablaLast);
  }
}

/*
 * Esta funcion crea un nuevo nivel.
 * n: ID del bloque que lo contiene
 */
void crear_nivel(){
  if(debug){
    printf("ENTRAMOS A CREAR NIVEL\n");
  }
  stack *newLevel = (stack *) malloc(sizeof(stack));
  current->next = newLevel;
  current = newLevel;
  niveles = niveles + 1;
  insertar_index(niveles);
  newLevel->parent = getParent();
  newLevel->id = niveles;
  if(debug){
    printf("SE CREO EL NIVEL %d CON PADRE: %d\n",niveles, newLevel->parent);
  }
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
  if(debug){
    printf("ENTRMAOS AL PRINTLEVEL\n");
  }
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
  if(debug){
    printf("ENTRAMOS A BUSCAR ID: %s\n", c);
  }
  if(s->info != NULL){
    data_stack *aux = s->info;
    if(debug){
      printf("PASA EL DATA STACK\n");
    }
    char name[32];
    strcpy(name, aux->data->nombre);
    if(debug){
      printf(" ID: %s\n", name);
    }
    while(((aux->next) !=  NULL)  && (strcmp(name,c)!= 0)){
      aux = (data_stack *) aux->next;
      strcpy(name, aux->data->nombre);
    }
    if(strcmp(name, c) == 0){
      if(debug){
        printf("Nivel no vacio y VARIABLE EXISTE: %s y %s resultado de comparar: %d\n", c, name,strcmp(name, c));
        printf("VOLVEMOS A BUSCAR X NIVELES CON AUX\n");
      }
      return aux;
    }
    else{
      if(debug){
        printf("Nivel no vacio pero ID no encontrado comparando: %s y %s\n", c, name);
        printf("VOLVEMOS A BUSCAR X NIVELES CON NULL\n");
      }
      return NULL;
    }
  }
  else{
    if(debug){
      printf("NIVEL VACIO BUSCANDO ID\n");
    }
    return NULL;
  }
}

/*
 * Esta funcion busca un nivel a partir de su ID, comenzando desde el tope de la "pila"
 * *s: Tope de la pila.
 * n: ID del nivel a buscar.
 */
stack * buscar_niv(stack *s, int n){
  if(debug){
    printf("ENTRAMOS A BUSCAR NIVEL con ID: %d\n", n);
  }
  if(s->id == n){
    return s;
  }else{
    while(((s->next) !=  NULL)  && (s->id != n)){
      s = (stack *) s->next;
    }
    if(s->id == n){
      return s;
    }
    else{
      return NULL;
    }
  }
}

/*
 * Buscamos las fnciones por su ID en el primer nivel, ya que es donde se declaran, no se admiten declaraciones de funciones anidadas.
 * c: ID de la funcion a buscar
 * return: data_Stack si encuentra el ID, NULL si no lo encuentra.
 */
data_stack * buscar_func(string *s){
  //printf("ENTRAMOS A BUSCAR FUNCION: %s\n", s->nombre);
  //printStack();
  return buscar_id(inicial, s->nombre);
}

/*
 * Esta funcion busca un ID por niveles, le pasamos el nivel actual y si no encuentra el ID entonces busca en los niveles que lo contienen
 * *s: Nivel actual en el que iniciar la busqueda.
 * c[10]: ID a buscar.
*/
data_stack * buscar_por_niveles(stack *s, char c[32]){
  if(debug){
    printf("ENTRAMOS A BUSCAR POR NIVELES EN EL NIVEL: ID: %d y el padre: ID: %d\n", s->id, s->parent);
  }
  int id = s->parent;
  stack *auxS = s;
  data_stack *aux;

  aux = buscar_id(auxS,c);
  if(aux != NULL){
    return aux;
  }
  if(id != -1){
    if(debug){
      printf("VAMOS A BUSCAR AL PADRE\n");
    }
    auxS = buscar_niv(inicial, id);
    if(debug){
      printf("ENCONTRAMOS AL PADRE");
    }
    aux = buscar_id(auxS,c);
    if(aux != NULL){
      if(debug){
        printf("VAMOS A SALIR DE BUSCAR POR NIVELES CON AUX\n");
      }
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
 * Este metodo inserta una funcion en el primer nivel de la pila (ya que solo se pueden declarar al inicio del codigo).
 * *d: Informacion de la funcion representada en un data_stack.
 */
void insertar_funcion(data_stack *d){
  if(debug){
    char s[32];
    strcpy(s, (d->data->nombre));
    printf("ENTRAMOS A INSERTAR FUNCION: %s\n", s);
    printf("EL CUERPO ES NULL?? %d\n", d->block == NULL);
  }

  data_stack *newD = (data_stack *) malloc(sizeof(data_stack));
  newD = d;
  newD->block = d->block;
  newD->next = NULL;
  newD->nParams = countParams(d->formalParams);
  newD->formalParams = d->formalParams;
  stack *aux = inicial;

  data_stack *res = buscar_id(inicial, d->data->nombre);

  if(res != NULL){
    createError(res->data->linea, FUNCEXIST);
    printErrors();
  }
  else{
    if(debug){
      printf("RES==NULL EN INSERTAR\n");
    }
    res = (data_stack *) aux->info;
    if(debug){
      printf("VAMOS A ENTRAR AL WHILE EN INSERTAR\n");
    }
    if(res != NULL){
      while((res->next) != NULL){
        if(debug){
          printf("ENTRAMOS AL WHILE EN INSERTAR: ID %s\n", res->data->nombre);
        }
        res = (data_stack *) res->next;
      }
      if(debug){
        printf("SALIO DEL WHILE EN INSERTAR\n");
      }
      res->next = (data_stack *)newD;
      res = newD;
    }
    else{
      res = newD;
      aux->info = newD;
    }
    if(debug){
      printf("Funcion '%s' insertada con exito\n", d->data->nombre);
    }

  }
}

/*
 * Esta funcion nos permite contar los parametros actuales de una invocacion.
 * *pl: paramList: lista nodos que representan expresiones.
 */
int counActualParams(paramList *pl){
  int params = 0;
  paramList *aux = pl;
  node *n = aux->parametro;
  if(aux != NULL){
   if(n!= NULL){
      params = params + 1;
   }
   while(aux->next != NULL){
    aux = aux->next;
    n = aux->parametro;
    if(n!= NULL){
      params = params + 1;
    }
   }
  }
  else{
    if(debug){printf("LA LISTA DE PARAMETROS ES NULA\n");}
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
  else{
    if(debug){printf("LA LISTA DE PARAMETROS ES NULA\n");}
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
 * Esta funcion nos permite obtener la informacion de un node.
 */
void insertar(data_stack *d){
  if(debug){
    printf("ENTRAMOS A INSERTAR EN LA TABLA EL ID: %s EN EL NIVEL: %d Y YIPO DE OP: %d\n", d->data->nombre, current->id, d->tipoOp);
  }
  data_stack *newD = (data_stack *) malloc(sizeof(data_stack));
  newD = (data_stack *)d;
  newD->next = NULL;

  stack *aux = tope();
  data_stack *res = buscar_id(current, d->data->nombre);
  if(res != NULL){
    if(debug){
      printf("RES != NULL EN INSERTAR.\n");
    }
    if(d->es_funcion){
      printNodeError(createError(res->data->linea, FUNCEXIST));
    }
    else{
      printNodeError(createError(res->data->linea, VAREXIST));
    }
  }
  else{
    if(debug){
      printf("RES==NULL EN INSERTAR\n");
    }
    res = (data_stack *) aux->info;
    if(res != NULL){
      if(res->tipoOp == PARAMETRO){
        formalParam *auxP = lastParam;
        formalParam *fp = (formalParam *) malloc(sizeof(formalParam));

        strcpy(fp->nombre, d->data->nombre);
        fp->tipo = d->data->tipo;

        if(auxP == NULL){
          lastParam = fp;
          lastParam->next = NULL;
          fstParam->next = lastParam;
        }
        else{
          lastParam->next = fp;
          lastParam = fp;
        }
      }
    }
    else{
      if(d->tipoOp == PARAMETRO){
        formalParam *auxP = lastParam;
        formalParam *fp = (formalParam *) malloc(sizeof(formalParam));
        strcpy(fp->nombre, d->data->nombre);
        fp->tipo = d->data->tipo;

        fstParam = fp;
        fstParam->next = NULL;
        lastParam = fstParam;
      }
    }
    if(debug){
      printf("VAMOS A ENTRAR AL WHILE EN INSERTAR\n");
    }
    if(res != NULL){
      while((res->next) != NULL){
        if(debug){
          printf("ENTRAMOS AL WHILE EN INSERTAR\n");
        }
        res = (data_stack *) res->next;
      }
      if(debug){
        printf("SALIO DEL WHILE EN INSERTAR\n");
      }
      res->next = (data_stack *)newD;
    }
    else{
      res = (data_stack *)newD;
      aux->info = res;
    }
    if(debug){
      printf("variable '%s' insertada con exito\n", d->data->nombre);
      printf("MOSTRANDO NIVEL: \n");
      printLevel(aux->info, aux->id, aux->parent);
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
  data_stack *aux = (data_stack *) malloc(sizeof(data_stack));
  aux->data = auxGen;
  aux->tipoOp = tipoOp;
  aux->block = block;
  aux->formalParams = params;
  aux->nParams = countParams(params);
  aux->es_funcion = es_func;
  if(tipoOp == INSERTFUNC && debug){
    printf("Cantidad de parametros en createDataStack?: %d\n", aux->nParams);
  }
  return aux;
}

string * getNombre(string *d){
  return d;
}

string * toString(char c[32]){
  string *s = (string *) malloc(sizeof(string));
  strcpy(s->nombre, c);
  return s;
}

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

int getValue(data_stack *d){
  data_gen *aux = d->data;
  return aux->valor;
}

node * getNodeFst(node *param){
  if(param->fst != NULL){
    return(param->fst);
  }
  else{
    return NULL;
  }
}

node * getNodeSnd(node *n){
  if(n->snd != NULL){
    return(n->snd);
  }
  else{
    return NULL;
  }
}

node * getNodeTrd(node *n){
  if(n->trd != NULL){
    return(n->trd);
  }
  else{
    return NULL;
  }
}

paramList * getStackInfo(stack *s){
  return s->info->params;
}

void resetParams(){
  fstParam = (formalParam *)malloc(sizeof(formalParam));
  fstParam->next = NULL;
  lastParam = fstParam;
}

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
        printf("Nombre: %s - Tipo: %d\n", n->info->data->nombre, n->info->data->tipo);
      }
      aux = aux->next;

    }
  }
}

formalParam * getFormalParams(){
  return fstParam;
}

data_stack * getNodeData(node *n){
  if(debug){
    printf("ENTRAMOS A GETNODEDATA\n");
  }
  if(n != NULL){
    if(debug){
      printf("VAMOS A SALIR DE GETNODEDATA\n");
    }
    return n->info;
  }
  else{
    if(debug){
      printf("VAMOS A SALIR DE GETNODEDATA CON NULL\n");
    }
    return NULL;
  }
}  

int getLinea(data_stack *d){
  return d->data->linea;
}

int lastType(){
  if(debug){
    printf("ENTRAMOS A LAST TYPE\n");
    printf("MOSTRANDO NIVEL EN EL QUE VAMOS A BUSCAR EL TIPO DE LA ULTIMA VARIABLE: \n");
    printLevel(inicial->info, inicial->id, inicial->parent);
  }
  stack *aux = current;
  data_stack *aux2 = (data_stack *)aux->info;
  if(debug){
    printf("VAMOS A ENTRAR AL WHILE EN LAST TYPE\n");
  }
  while(aux2->next!= NULL){
    aux2 = (data_stack *) aux2->next;
  }
  if(debug){
    printf("SALIMOS DEL WHILE EN LAST TYPE con: %d\n", aux2->data->tipo);
  }
  return aux2->data->tipo;
}


/*
 * Esta funcion nos permite crear la informarcion necesaria para un nodo.
 */
nodeParam * createNodeParam(string *s, int val, int tipoVar, int tipoRet, int oper, node *fst, node *snd, node *trd, bool es_funcion, paramList *params, int linea){
  if(debug){
    printf("ENTRAMOS A CREATE NODE PARAM\n");
  }
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
  if(es_funcion && debug){
    printf("SALIMOS DE CREATE NODE PARAM con OPER = %d Y NOMBRE: %s\n", nodeAux->oper, nodeAux->nombre);
  }
  return nodeAux;
}

/*
 * Esta funcion nos permite crear un nodo.
 */
node * createNode(nodeParam *param){
  if(debug){
    printf("ENTRAMOS A CREATE NODE\n");
  }

  data_gen *data = (data_gen *) malloc(sizeof(data_gen));
  data_stack *dataS = (data_stack *) malloc(sizeof(data_stack));
  node *n = (node *) malloc(sizeof(node));

  if(param != NULL){
    if(debug){
      printf("NO ES NULL\n");
    }
    if((param->oper) == ASIGNACIONN){
      if(debug){
        printf("PASO LA ASIGNACION\n");
        printf("VAMOS A BUSCAR POR NIVELES DESDE CREATE NODE ASIGNACION\n");
      }
      dataS = buscar_por_niveles(tope(), param->snd->info->data->nombre);
      if(dataS == NULL){
        if(debug){
          printf(KRED "ERROR DESDE CREATE NODE CON ASIGNACION VARIABLE: %s\n", param->snd->info->data->nombre);printf(KNRM);
        }
        createError(param->linea, UNDECLAREDVAR);
      }
      else{
        dataS = crearDataStack(toString(param->nombre), param->tipoVar, param->valor, param->oper, param->linea, NULL, NULL, false);
      }
    }
    else if(param->oper == VARR || param->oper == PARAMETRO){
      if(debug){
        printf("VAMOS A BUSCAR POR NIVELES DESDE CREATE NODE VARR: ID: %s\n", param->nombre);
      }
      dataS = buscar_por_niveles(current, param->nombre);
      if(dataS == NULL){
        if(debug){
          printf(KRED "ERROR DESDE CREATE NODE CON VARR\n");printf(KNRM);
        }
        char c[256];
        strcpy(c, " variable no declarada: ");
        strcat(c, param->nombre);
        createNewError(param->linea, c, UNDECLAREDVAR);
      }
    }
    else if(param->oper == INVOCC){
      if(debug){
        printf("CREATE NODE: INVOC\n");
      }
      dataS = crearDataStack(toString(param->nombre), param->tipoVar, param->valor, param->oper,  param->linea, NULL, NULL, true);
      dataS->params = param->params;
      
    }
    else{
      if(debug){
        printf("ENTRAMOS A CREATE NODE CON %s \n", param->nombre);
      }
      dataS = crearDataStack(toString(param->nombre), param->tipoVar, param->valor, param->oper, param->linea, NULL, NULL, false);
    }
    treeSize = treeSize + 1;
    n->info = dataS;
    n->fst = param->fst; n->snd = param->snd; n->trd = param->trd;
    if(debug){
      printf("VAMOS A MOSTRAR NODO:\n");
      string *s = getName(dataS);
      printf("%s %s,%d\n","---MOSTRANDO NODO: ", param->nombre, param->valor);
    }
  }
  else{
    printf("PARAMETRO NULO EN CREATE NODE\n");
  }
  return n;
}

/*
 * Esta funcion nos permite crear una nueva invocacion a una funcion.
 */
void newCall(paramList *p, node *n){
  if(true){
    printf("ENTRAMOS A NEW CALL\n");
  }
  paramList *newParam = (paramList *) malloc(sizeof(paramList));
  paramList *aux = p;
  newParam->parametro = n;

  if(aux == NULL){
    aux = newParam;
  }
  else{
    while(aux->next != NULL){
      aux = aux->next;
    }
    aux->next = newParam;
  }
}

void checkFunctions(stack *s){
  data_stack *origin = s->info;
  data_stack *aux = origin;

  if(aux != NULL){
    if(aux->es_funcion){
      printFormalParams(aux->formalParams);
      evalExpr(aux->block, getTipo(aux));
    }
    while(aux->next != NULL){
      aux = aux->next;
      if(aux->es_funcion){
        if(debug){
          printf("ES FUNCION EN EL WHILE . ES NULL? %d\n", aux->block==NULL);
          printf(KRED "EL NOMBRE DE LA FUNCION ES: %s Y SU TIPO DE RETORNO ES: %d  Y TIENE %d PARAMETROS\n", aux->data->nombre, getTipo(aux), aux->nParams); printf(KNRM);
          printFormalParams(aux->formalParams);
          printf("EL NOMBRE DEL NODO ES: %s\n", getName(aux->block->info)->nombre);
        }
        evalExpr(aux->block, getTipo(aux));
      }
    }
  }
}

int evalExpr(node *n, int tipoRet){
  if(n!=NULL){
    data_stack *data = n->info;

    if(data != NULL){
      int op = data->tipoOp;
      string *s = getName(data);
      char cAux[32];
      strcpy(cAux, s->nombre);
      //printf("ENCONTRAMOS A: %s CON TIPO OP: %d\n", cAux, op);
      if(op == VARR || op == CONSTANTEE || op == PARAMETRO){
        //printf("EL TIPO DE LA VARIABLE %s ES: %d\n", cAux, getTipo(data));
        return (getTipo(data));
      }
      if(op == INVOCC){
        checkParams(n);
        return (getTipo(data));
      }

      else if (op == ASIGNACIONN){
        if(evalExpr(getNodeFst(n), tipoRet) == evalExpr(getNodeSnd(n), tipoRet)){
        }
        else{
          createNewError(getLinea(data), "Error de tipos en la asignacion: La expresion debe ser del mismo tipo que la variable ", WRONGTYPE);return WRONGTYPE;}
      }
      else if (op == RESTAA && (getNodeSnd(n) != NULL)){
        if((evalExpr(getNodeFst(n), tipoRet) == INTEGERR) && (evalExpr(getNodeSnd(n), tipoRet) == INTEGERR)){
          return INTEGERR;
        }
        else{
          createNewError(getLinea(data), "Los operandos de una resta deben ser de tipo integer", WRONGTYPE);return WRONGTYPE;}
      }
      else if (op == RESTAA && (getNodeSnd(n) == NULL)){
        if(evalExpr(getNodeFst(n), tipoRet) == INTEGERR){
          return INTEGERR;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en el opuesto: Se esperaba una expresion de tipo entero ", WRONGTYPE);return WRONGTYPE;}
      }
      else if ((op == DIVV) ||(op == PRODD) || (op == MODD) || (op == SUMAA)){
        if((evalExpr(getNodeFst(n), tipoRet) == INTEGERR) && (evalExpr(getNodeSnd(n), tipoRet) == INTEGERR)){
          return INTEGERR;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en una operacion aritmetica binaria: Se espera que los operandos sean de tipo integer ", WRONGTYPE);return WRONGTYPE;}
      }
      else if ((op == ANDD) || (op == ORR)){
        if((evalExpr(getNodeFst(n), tipoRet) == BOOLEAN) && (evalExpr(getNodeSnd(n), tipoRet) == BOOLEAN)){
          return BOOLEAN;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en una operacion logica binaria: Ambas expresiones deben ser de tipo bool ", WRONGTYPE);return WRONGTYPE;}
      }
      else if ((op == MAYORR) ||(op == MENORR) || (op == MENIGUALL) || (op == MAYIGUALL) || (op == IGUALDADD)){
        if((evalExpr(getNodeFst(n), tipoRet) == INTEGERR) && (evalExpr(getNodeSnd(n), tipoRet) == INTEGERR)){
          return BOOLEAN;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en una operacion aritmetica-logica binaria: Ambas expresiones deben ser de tipo integer ", WRONGTYPE);return WRONGTYPE;}
      }
      else if (op == NOTT){
        if(evalExpr(getNodeFst(n), tipoRet) == BOOLEAN){
          return BOOLEAN;
        }
        else{
          createNewError(getLinea(data), "Error de tipos en la negacion: La expresion debe ser de tipo bool ", WRONGTYPE);return WRONGTYPE;}
      }
      else if (op == IFTHENN || op == WHILEE){
        if(evalExpr(getNodeFst(n), tipoRet) == BOOLEAN){
          evalExpr(getNodeSnd(n), tipoRet);
          return BOOLEAN;
        }
        else{
        createNewError(getLinea(data), "Error de tipos en la condicion ", WRONGTYPE);return WRONGTYPE;}
      }
      else if (op == IFTHENELSEE){
        if(evalExpr(getNodeFst(n), tipoRet) == BOOLEAN){
          evalExpr(getNodeSnd(n), tipoRet);
          evalExpr(getNodeTrd(n), tipoRet);
          return BOOLEAN;
        }
        else{
        createNewError(getLinea(data), "Error de tipos en la condicion ", WRONGTYPE);return WRONGTYPE;}
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
        if( res == tipoRet){
        }
        else if(res != WRONGTYPE){
          createNewError(getLinea(data), "Error de tipos en el return: El tipo de la expresion del return debe ser igual al tipo de retorno de la funcion ", WRONGTYPE);return WRONGTYPE;}
      }
    }
    else{
      if(debug){printf("data == NULL en evalExpr\n");}
    }
  }
  return UNKNOW;
}

void checkParams(node *n){
  data_stack *data = buscar_func(toString(n->info->data->nombre));
  paramList *paramInvoc = n->info->params;
  formalParam *formal = data->formalParams;

  bool control = true;
  int nn = counActualParams(paramInvoc);
  if(data->nParams != nn){
    if(debug){
      printf("ERROR DESDE CHECKPARAMS cantidad de parametros\n");      
    }
    createError(getLinea(getNodeData(n)), INVOCPARAMS);
  }
  else{
    while((paramInvoc != NULL) && control){
      if(paramInvoc->parametro== NULL){
        paramInvoc = paramInvoc->next;
      }
      int res = evalExpr(paramInvoc->parametro, IGNORE);
      //printf("VAMOS A COMPARAR %s CON %s EN LA FUNCION: %s \n", formal->nombre, paramInvoc->parametro->info->data->nombre, data->data->nombre);
      //printf("EL RESULTADO ES: %d vs %d\n", res, formal->tipo);
      if((res != formal->tipo) && (res != UNKNOW)) {
        if(debug){
          printf("ERROR DESDE CHECKPARAMS tipos en la invocacion\n");      
        }
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

void deleteCalls(paramList *pl){
  if(pl!=NULL){
    eliminarArbol(pl->parametro);
    while(pl->next!=NULL){
      pl = pl->next;
      eliminarArbol(pl->parametro);
    }
  }
}

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

void eliminarArbol(node *n){
  if (n != NULL) {
    data_stack *data = n->info;
    if(data != NULL && debug){
      string *s = getName(data);
      char cAux[32];
      strcpy(cAux, s->nombre);
      printf("Nodo a eliminar: ");
      printf("Nombre: %s, Valor: %i, Tipo: %d\n", cAux, getValue(data), getTipo(data));

    }
    else{
      if(debug){
        printf("El data es NULL\n");
      }
    }
    eliminarArbol(getNodeFst(n));
    eliminarArbol(getNodeSnd(n));
    eliminarArbol(getNodeTrd(n));
    deleteCalls(data->params);
    treeSize = treeSize - 1;
    free(n);
  }
}


