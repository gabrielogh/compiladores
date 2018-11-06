#include "cod_intermedio.h"

FILE *asm_code;

void generar_codigo_assembler();

void crear_archivo();


void crear_archivo(){
  asm_code = fopen("assembler.s","w");
  if(asm_code == NULL){
    printf("%s\n","Error al crear el archivo assembler.s" );
  }
}

void generar_codigo_assembler(){
  crear_archivo();

  tresDirL *aux = head_td;

  if( aux!= NULL){
    while (){
      
    }

  }

}