typedef struct strings string;

/* Tipo utilizado para representar los Strings.
 * nombre: nombre es el valor del string
 * linea: Numero de linea.
 */
typedef struct strings{
  char nombre[32];
  int linea;
}string;

//DEFINICION DE METODOS.

//Retorna el char nombre[32] de un Struct string.
string * getNombre(string *d);

//Este metodo transforma un char array en un Struct string.
string * toString(char c[32]);

//IMPLEMENTACION DE METODOS.

/*
 * Esta funcion nos permite obtener el campo nombre de un Struct string.
 * NO SIRVE PARA NADA....LITERALMENTE
 */
string * getNombre(string *d){
  if(debug){
    printf("ENTRAMOS A GET NOMBRE\n ");
  }
  return d;
}

/*
 * Esta funcion nos permite convertir un char array en un Struct string.
 */
string * toString(char c[32]){
  if(debug){
    printf("ENTRAMOS A TOSTRING.\n");
  }
  string *s = (string *) malloc(sizeof(string));
  strcpy(s->nombre, c);
  return s;
}