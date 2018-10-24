#include "indexT.h"
#include "string.h"

typedef struct data_stacks data_stack;
typedef struct stacks stack;
typedef struct nodeAuxs nodeAux;
typedef struct Formalparams paramList;
typedef struct data_generic data_gen;

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

/* Tipo de nodo auxiliar, se utiliza debideo a que desde este archivo no es posible visualizar el tipo Struct node.
 * El Struct nodeAux contiene exactamente la misma estructura que el Struct node de el archivo lib.h.
 * *info: Es un struct que representa la informacion del nodo.
 * *fst: Nodo que representa el primer hijo en caso de tenerlo, sino es NULL.
 * *snd: Nodo que representa el segundo hijo en caso de tenerlo, sino es NULL.
 * *trd: Nodo que representa el tercer hijo en caso de tenerlo, sino es NULL.
 */
typedef struct nodeAuxs{ 
    data_stack *info;
    struct nodeAuxs *fst;
    struct nodeAuxs *snd;
    struct nodeAuxs *trd;
}nodeAux;

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
  nodeAux *block;
  paramList *params;
  struct data_stacks *next;
} data_stack;

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


/* Tipo utilizado para representar los parametros de las funciones.
 * *parametro: Expresion que representa el parametro, puede ser una invocacion a otro metodo, una expresion matematica, booleana, etc.
 * *next: Puntero al proximo parametro.
 */
typedef struct Formalparams{
  nodeAux *parametro;
  struct Formalparams *next;
} paramList;


//VARIABLES GLOBALES
stack *current, *inicial;
int niveles;

//DECLARACIONES DE METODOS:


//Busca un ID en un nivel y retorna un data_struct o NULL si no encuentra nada.
data_stack * buscar_id(stack *s, char c[32]);

//Busca un nivel por su ID y lo retorna o retorna NULL si no encuentra nada.
stack * buscar_niv(stack *s, int n);

//Busca una funcion por su ID en el primer nivel y retorna un data_struct o NULL si no encuentra nada.
data_stack * buscar_func(string *s);

//Busca una variable por su ID en un nivel y si no lo encuentra, busca en los niveles que lo contengan (utilizada para saber si una variable esta declarada).
data_stack * buscar_por_niveles(stack *s, char c[32]);

//Inserta un dato en el nivel actual.
void insertar(data_stack *d);

//Inicializa la pila con el primer nivel vacio y la tabla de index.
void init();

//Cierra un nivel desde la tabla de INDEX, pero no en la pila.
void crear_nivel();

//Devuelve el tope de la pila, es decir el nivel corriente
stack * tope();

//Crea el data_stack para ser usado en otras funciones.
data_stack * crearDataStack(string *s, int tipo, int valor, int tipoOp, int linea, nodeAux *block, paramList *params, bool es_func);


//Retorna el valor del campo value de un data_gen contenido en un data_stack.
int getValue(data_stack *d);

//Retorna el valor del campo tipo de un data_gen contenido en un data_stack.
int getTipo(data_stack *d);

//Esta funcion nos permite obtener el ID del bloque que nos contiene inmediatamente, utilizando la tabla de Index.
int getParent();

//Se utiliza para obtener los parametros de una funcion.
paramList * getStackInfo(stack *s);

//Se utiliza para recuperar la informacion de un nodo.
data_stack * getNodeAuxData(nodeAux *n);

//Se utiliza para para imprimir cada dato de un nivel.
void printDataStack(data_stack *d, int id, int padre);

//Se utiliza para obtener el nombre de un data_gen.
string * getName(data_stack *d);

int countParams(paramList *pl);

//IMPLEMENTACION DE METODOS.

/*
 * Esta funcion nos permite obtener los datos de un nodeAux.
 */
data_stack * getNodeAuxData(nodeAux *n){
  return n->info;
}

/*
 * Esta funcion nos permite obtener el primer hijo de un nodeAux.
 */
nodeAux * getFstAux(nodeAux *n){
  return n->fst;
}

/*
 * Esta funcion nos permite obtener el segundo hijo de un nodeAux.
 */
nodeAux * getSndAux(nodeAux *n){
  return n->snd;
}

/*
 * Esta funcion nos permite obtener el tercer hijo de un nodeAux.
 */
nodeAux * getTrdAux(nodeAux *n){
  return n->trd;
}

/*
 * Esta funcion nos permite obtener el campo valor de un Struc data_stack.
 */
int getValue(data_stack *d){
  if(debug){
    printf("ENTRAMOS A GETVALUE con: %d\n", d->data->valor);
  }
  data_gen *aux = d->data;
  return aux->valor;
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

int getLinea(data_stack *d){
  return d->data->linea;
}

paramList * getParams(data_stack *d){
  return d->params;
}

int getOp(data_stack *d){
  return d->data->tipo;
}

data_gen * getDataGen(data_stack *d){
  return d->data;
}

string * getName(data_stack *d){
  string *s;
  if(d != NULL){
    char res[32];
    strcpy(res, getDataGen(d)->nombre);
    s = toString(res);
    return s;
  }
  printf("DATA STACK NULL EN GETNAME\n");
  s = (string *) malloc(sizeof(string));
  strcpy(s->nombre, "NULL");
  return s;

}
/*
 * Esta funcion nos permite obtener el campo info de un Struct data_stack.
 */
paramList * getStackInfo(stack *s){
  if(debug){
    printf("ENTRAMOS A GETSTACKINFO\n");
  }
  return s->info->params;
}

/*
 * Esta funcion inicializa el scope, creando el primer nivel que contendra a los demas.
 */
void init(){
  if(debug){
    printf("ENTRAMOS A INIT\n");
  }
  treeSize = 0;
  current = (stack *) malloc(sizeof(stack));
  inicial = (stack *) malloc(sizeof(stack));
  current->next = NULL;
  current->parent = -1;
  current->info = NULL;
  current->id = 1;
  inicial = current;
  niveles = 1;
  initIndexList();
  if(debug){
    printf("Nivel inicial ID: %d\n", inicial->id);
  }
}

/*
 * Esta funcion devuelve el tope de la pila.
 */
stack * tope(){
  if(debug){
    printf("ENTRAMOS A TOPE\n");
  }
  return current;
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
 * Esta funcion imprime un nodo de un determinado nivel del stack.
 * id: ID del bloque al que pertenece
 * padre: ID del bloque que lo contiene inmediatamente.
 * *d: Dato del nivel a imprimir.
 */
void printDataStack(data_stack *d, int id, int padre){
  int var = sizeof(d->data->nombre);
  printf(" ----------------------------- \n");

  printf("| ID nivel:   | %d             |\n", id);


  if(padre <10 && padre > 0){
    printf("| ID Padre:   | %d             |\n", padre);
  }
  else if((padre >9 && padre < 100) || (padre < 0)){
    printf("| ID Padre:   | %d            |\n", padre);
  }
  else if((padre > 99 && padre < 1000)){
    printf("| ID Padre:   | %d             |\n", padre);
  }

  printf("| Es funcion: | %d             |\n", d->es_funcion);

  printf("| Nombre:     | %s\n", d->data->nombre);

  if(d->data->valor <10 && d->data->valor > 0){
    printf("| Valor:      | %d             |\n", d->data->valor);
  }
  else if((d->data->valor >9 && d->data->valor<100) || (d->data->valor < 0)){
    printf("| Valor:      | %d            |\n", d->data->valor);
  }
  else if((d->data->valor > 99 && d->data->valor < 1000)){
    printf("| Valor:      | %d           |\n", d->data->valor);
  }
  printf("| Tipo:       | %d             |\n", d->data->tipo);
  if(d->data->linea <10){
    printf("| Linea:      | %d             |\n", d->data->linea);
  }
  else if(d->data->linea >9 && d->data->linea<100){
    printf("| Linea:      | %d            |\n", d->data->linea);
  }
  else if((d->data->linea > 99 && d->data->linea < 1000)){
    printf("| Linea:      | %d           |\n", d->data->linea);
  }
  printf(" ----------------------------- \n");
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
  printf("STACK:\n");
  stack *s = (stack *) malloc(sizeof(stack));
  s = inicial;
  if(s == NULL){
    if(debug){
      printf("STACK VACIO.\n");
    }
  }
  else{
    if(debug){
      printf("STACK NO VACIO.\n");
      printf("Nivel INICIAL:\n");
    }
    printLevel(s->info, s->id, s->parent);
    s = s->next;
    while(s != NULL){
      printLevel(s->info, s->id, s->parent);
      s = s->next;
    }
  }
  printf("\n");
}

/*
 * Buscamos las fnciones por su ID en el primer nivel, ya que es donde se declaran, no se admiten declaraciones de funciones anidadas.
 * c: ID de la funcion a buscar
 * return: data_Stack si encuentra el ID, NULL si no lo encuentra.
 */
data_stack * buscar_func(string *s){
  if(debug){
    printf("ENTRAMOS A BUSCAR FUNCION - Vamos a mostrar el stack.\n");
    printStack();
  }
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
 * Este metodo inserta una funcion en el primer nivel de la pila (ya que solo se pueden declarar al inicio del codigo).
 * *d: Informacion de la funcion representada en un data_stack.
 */
void insertar_funcion(data_stack *d){
  if(debug){
    char s[32];
    strcpy(s, getName(d)->nombre);
    printf("ENTRAMOS A INSERTAR FUNCION: %s\n", s);
    printf("EL CUERPO ES NULL?? %d\n", d->block == NULL);
  }
  data_stack *newD = (data_stack *) malloc(sizeof(data_stack));
  newD = d;
  newD->block = (nodeAux *)malloc(sizeof(nodeAux));
  newD->block = d->block;
  newD->next = NULL;
  newD->nParams = countParams(d->params);

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
      res = newD;
      aux->info = newD;
    }
    if(debug){
      printf("Funcion '%s' insertada con exito\n", d->data->nombre);
      printf("MOSTRANDO NIVEL INICIAL: \n");
      printLevel(aux->info, aux->id, aux->parent);
    }

  }
}

int countParams(paramList *pl){
  int params = 0;
  paramList *aux = pl;
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
 * Esta funcion inserta informacion en el nivel corriente.
 * *d: Es un Struct que representa la informacion necesaria.
 */
void insertar(data_stack *d){
  if(debug){
    printf("ENTRAMOS A INSERTAR EN LA TABLA\n");
  }
  data_stack *newD = (data_stack *) malloc(sizeof(data_stack));
  newD = (data_stack *)d;
  newD->next = NULL;

  stack *aux = tope();
  data_stack *res = buscar_id(aux, d->data->nombre);
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
 * Esta funcion nos permite crear un data_Stack.
 * *s: String que representa un identificador o un nombre para un nodo.
 * tipo: Tipo de la variable o tipo del valor de retorno si es una funcion.
 * valor: En caso de tenerlo.
 * linea: Numero de linea.
 * *block: Bloque de la funcion. Es NULL si no es una funcion.
 * *params: Lista de parametros si es una funcion, sino es NULL.
 * es_func: Booleano que nos dice si debemos crear una funcion o no.
 */
data_stack * crearDataStack(string *s, int tipo, int valor, int tipoOp, int linea, nodeAux *block, paramList *params, bool es_func){
  if(true){
    printf("ENTRAMOS A CREATE DATA STACK\n");
  }
    //printf("ENTRAMOS A CREATE DATA STACK\n");

  data_gen *auxGen = (data_gen *) malloc(sizeof(data_gen));
  strcpy(auxGen->nombre, s->nombre);
  auxGen->tipo = tipo;
  auxGen->valor = valor;
  auxGen->linea = linea;
  data_stack *aux = (data_stack *) malloc(sizeof(data_stack));
  aux->data = auxGen;
  aux->tipoOp = tipoOp;
  aux->block = block;
  aux->params = params;
  aux->es_funcion = es_func;
  if(block!=NULL){
    printf("NOMBRE : %s\n", s->nombre);
  printf("EL BLOQUE ES NULL? : %d\n", block==NULL);
  printDataStack(block->info, 1, -1);
  }

  return aux;
}

/*
 * Esta funcion nos permite obtener el ultimo tipo de variable cargado, se utiliza en la definicion de multiples variables del mismo tipo
 * Ej-> integer x, y, z;
 */
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

