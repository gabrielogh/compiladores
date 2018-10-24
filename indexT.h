typedef struct indexTable indexT;

/* Tipo utilizado para representar los niveles del scope mediente una lista doblemente enlazada. La idea es que el nivel anterior sea el padre del actual.
 * id: Id del nivel.
 * *next: Proximo nivel (Hijo).
 * *prev: Nivel anterior (Padre).
 * linea: Numero de linea.
 */
typedef struct indexTable{
  int id;
  struct indexTable *next;
  struct indexTable *prev;
}indexT;


//DEFINICION DE METODOS.

//Obtenemos el siguiente elemento de la lista doblemente enlazada.
indexT * getIndexNext(indexT *param);

//Obtenemos el elemento anterior al actual.
indexT * getIndexPrev(indexT *param);

//Esta funcion retorna el ID de un index.
int getIndexId(indexT *param);

//Metodo que permite modificar el campo ID del Struct indexT.
void setIndexId();

//Metodo que permite modificar el camo Next del Struct indexT.
void setIndexNext(indexT *param, indexT *n);

//Metodo que permite modificar el campo Prev del Struct indexT.
void setIndexPrev(indexT *param, indexT *p);

//Elimina la tabla de index, liberando la memoria utilizada.
void eliminarTabla();

//Imprime la lista de Index.
void printIndexList();

//Inserta un nuevo index en la tabla.
void insertar_index(int niv);

//Este metodo nos permite representar el cierre de un nivel de forma simple.
void cerrar_nivel();

//Metodo que nos permite obtener el campo Next de un Struct indexT.
indexT * getIndexNext(indexT *param);

//Metodo que nos permite obtener el campo Prev de un Struct indexT.
indexT * getIndexPrev(indexT *param);

//VARIABLES GLOBALES.
indexT *tablaFst, *tablaLast;


//IMPLEMENTACION DE METODOS.

/*
 * Este metodo inicializa la lista de index con el primer nivel.
 */
void initIndexList(){
  tablaFst = (indexT *) malloc(sizeof(indexT));
  tablaLast = (indexT *) malloc(sizeof(indexT));
  setIndexId(tablaFst, 1);
  setIndexNext(tablaFst, NULL);
  setIndexPrev(tablaFst, NULL);
  tablaLast = tablaFst;
}

/*
 * Este metodo nos permite visualizar la lista de indexs para verificar que la cantidad de niveles abiertos sea la correcta.
 */
void printIndexList(){
  printf("--------------------\n");
  printf("   TABLA DE INDEX: \n");
  if(tablaFst != NULL){
    printf("   | ID | %d   |\n", tablaFst->id);
    indexT *aux = tablaFst;
    while(aux->next != NULL){
      aux = aux->next;
      printf("   | ID | %d  |\n", aux->id);
    }
    printf("--------------------\n");
    eliminarTabla();
  }
  else{
    printf("TABLA DE INDEX VACIA.\n");
  }
}

/*
 * Este metodo inserta un nuevo index que representa al nuevo nivel abierto.
 * niv: ID del nuevo nivel.
 */
void insertar_index(int niv){
  if(debug){
    printf("ENTRAMOS A INSERTAR INDEX CON: %d\n", niv);
  }
  indexT *aux = (indexT *) malloc(sizeof(indexT));
  aux->id = niv;
  aux->next = NULL;
  aux->prev = tablaLast;
  tablaLast->next = aux;
  tablaLast = aux;
  if(debug){
    printf("SALIMOS DE INSERTAR INDEX\n");
  }
}

/*
 * Este metodo elimina la memoria utilizada por la tabla de Index, elemento a elemento.
 * Se recorre la lista desde el final hacia el inicio, pero podria ser en el orden inverso, ya que es una lista doble.
 */
void eliminarTabla(){
  indexT *aux = tablaLast;
  if(aux != NULL){
    if(tablaLast->prev != NULL){
      tablaLast = tablaLast->prev;
      tablaLast-> next = NULL;
    }
    free(aux);
  }
  while(tablaLast->prev != NULL){
    indexT *aux = tablaLast;
    tablaLast = tablaLast->prev;
    tablaLast-> next = NULL;
    free(aux);
  }
  tablaFst = NULL;
}

/*
 * Esta funcion retrocede un elemento en la tabla de index, permitiendo retroceder al bloque que lo contiene (al primero que lo contiene).
 */
void cerrar_nivel(){
  if(debug){
    printf("ENTRAMOS A CERRAR NIVEL\n");
    printf("SE CERRO EL NIVEL: %d\n", tablaLast->id);
  }
  indexT *aux = tablaLast;
  tablaLast = tablaLast->prev;
}

/*
 * Metodo que retorna el siguiente elemento.
 * *param: Nodo actual.
 */
indexT * getIndexNext(indexT *param){
  return param->next;
}

/*
 * Metodo que retorna el elemento anterior.
 * *param: Nodo actual.
 */
indexT * getIndexPrev(indexT *param){
  return param->prev;
}

/*
 * Metodo que retorna el ID de un indexT.
 * *param: Nodo actual.
 */
int getIndexId(indexT *param){
  return param->id;
}

/*
 * Metodo que setea el valor del campo ID.
 * *param: Nodo actual.
 */
void setIndexId(indexT *param, int n){
  param->id = n;
}

/*
 * Metodo que setea el valor del campo Next.
 * *param: Nodo actual.
 */
void setIndexNext(indexT *param, indexT *n){
  param->next = n;
}

/*
 * Metodo que setea el valor del campo Prev.
 * *param: Nodo actual.
 */
void setIndexPrev(indexT *param, indexT *p){
  param->prev = p;
}
