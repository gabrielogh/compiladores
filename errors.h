#include <stdlib.h>
#include <string.h>
#include "constantes.h"

/*
 * Tipo utilizado para representar los errores.
 */
typedef struct errors{
 char desc[256];
 int line;
 int tipo;
} error;

/*
 * Tipo utilizado para representar una lista de errores para luego poder imprimirla.
 */
typedef struct errorLists{
  error *data;
  struct errorLists *next;
} errorList;

// VARIABLES GLOBALES.
errorList *headErrorList, *tailErrorList;
int errors;

//DEFINICION DE METODOS.
//Este metodo nos permite cargar un nuevo error.
error * createError(int linea, int tipo);

error * createNewError(int linea, char c[256], int tipo);

//Metodo utilizado para imprimir la lista de errores.
void printErrors();

//Metodo que se encarga de imprimir un error.
void printNodeError(error *data);

//Metodo utilizado para saber si hay errores generados.
bool noErrors();

//IMPLEMENTACION DE METODOS.

/*
 * Este metodo nos permite generar errores predeterminados.
 * linea: El numero de la linea donde se genero.
 * tipo: Identificador del error.
 */
error * createError(int linea, int tipo){
  error *newError = (error *) malloc(sizeof(error));
  errorList *newErrorList = (errorList *) malloc(sizeof(errorList));
  errorList *aux = headErrorList;
  switch(tipo) {

     case VAREXIST  :
        strcpy(newError->desc, "La variable ya existe");
        break;
    
     case FUNCEXIST  :
        strcpy(newError->desc, "La funcion ya existe");
        break;

     case UNDECLAREDVAR  :
        strcpy(newError->desc, "Variable no declarada");
        break;

     case UNDEFINEDFUNC  :
        strcpy(newError->desc, "Funcion no declarada");
        break;

     case SINTAX  :
        strcpy(newError->desc, "Error de sintaxis");
        break;

     case WRONGLEVEL  :
        strcpy(newError->desc, "No se encontro el nivel");
        break;
     case INVOCPARAMS  :
        strcpy(newError->desc, "Error al invocar la funcion: Numero de parametros incorrectos");
        break;
     case WRONGTYPE  :
        strcpy(newError->desc, "Error de tipos");
        break;
     default :
     strcpy(newError->desc, "Ups, algo flalo, y no tenemos idea de por que.");
  }
  newError->line = linea;
  newError->tipo = tipo;
  newErrorList->data = newError;
  newErrorList->next = NULL;
  if(headErrorList == NULL){
    headErrorList = newErrorList;
  }
  else{
    while(aux->next != NULL){
      aux = aux->next;
    }
    aux->next = newErrorList;
  }
  errors = errors +1;
  return newError;
}

/*
 * Este metodo nos permite generar errores personalizados, se utiliza para los semanticos.
 * linea: El numero de la linea donde se genero.
 * c[256]: Mensaje personalizado.
 * tipo: Identificador del error.
 */
error * createNewError(int linea, char c[256], int tipo){
  error *newError = (error *) malloc(sizeof(error));
  errorList *newErrorList = (errorList *) malloc(sizeof(errorList));
  errorList *aux = headErrorList;
  strcpy(newError->desc, c);
  newError->line = linea;
  newError->tipo = tipo;
  newErrorList->data = newError;
  newErrorList->next = NULL;
  if(headErrorList == NULL){
    headErrorList = newErrorList;
  }
  else{
    while(aux->next != NULL){
      aux = aux->next;
    }
    aux->next = newErrorList;
  }
  errors = errors +1;
  return newError;
}

/*
 * Este metodo nos permite imprimir un error de la lista de errores.
 * data: El error a imprimir
 */
void printNodeError(error *data){
  if(data != NULL){
    printf(KRED "ERROR en la linea: %d - %s\n", data->line, data->desc); printf(KNRM);
  }
  else{
    printf(KGRN "No hay error.\n"); printf(KNRM);
  }
}

/*
 * Este metodo nos permite imprimir la lista de errores utilizando a la printNodeError.
 */
void printErrors(){
  errorList *aux = (errorList *) malloc(sizeof(errorList));
  if(headErrorList!= NULL){
    printNodeError(headErrorList->data);
    aux = headErrorList;
    while(aux->next != NULL){
      aux = aux->next;
      printNodeError(aux->data);
    }
  }
}

/*
 * Este metodo nos permite verificar si se generaron errores en el codigo.
 */
bool noErrors(){
  if(headErrorList == NULL){
    return true;
  }
  else{
    return false;
  }
}
