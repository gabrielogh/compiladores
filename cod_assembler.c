#include "cod_intermedio.h"

FILE *asm_code;

void generar_codigo_assembler();

void crear_archivo();

void crear_label_funcion(tresDirL *intr);

void cargar_instrcciones(tresDir *instr);

void crear_archivo(){
  asm_code = fopen("assembler.s","w");
  if(asm_code == NULL){
    printf("%s\n","Error al crear el archivo assembler.s" );
  }
}

void crear_label_funcion(tresDirL *intr){
  char c[32];
  strcpy(c, intr->nombre);
  strcat(c, ":\n");
  fputs(c, asm_code);
  printf("%s:\n",intr->nombre);
}

void generar_codigo_assembler(){
  crear_archivo();

  tresDirL *Listaux = head_td;

  if(Listaux != NULL){
    while(Listaux !=  NULL){
      crear_label_funcion(Listaux);
      cargar_instrcciones(Listaux->fst);
      Listaux = Listaux->next;
    }

  }

}

void cargar_instrcciones(tresDir *instr){
  tresDir *auxInstr = instr;
  if(auxInstr != NULL){
    while(auxInstr != NULL){
      int op = auxInstr->op;
      switch(op) {

         case JMP  :
            
            break;

         case CARGAR_PARAMS  :
            
            break;

         case IF_INSTRUCCION  :
            
            break;

         case IF_ELSE_INSTRUCCION  :
            
            break;
         case WHILE_INSTRUCCION  :
            
            break;
         case CALL  :
            
            break;
         case CALL_WITH_PARAMS  :
            
            break;
         case ASIGN_INSTRUCCION  :
            
            break;
         case CTE_INSTRUCCION  :
            
            break;
         case EQ_INSTRUCCION  :
            
            break;
         case ADD_INSTRUCCION  :
            
            break;
         case SUB_INSTRUCCION  :
            
            break;
         case MAY_INSTRUCCION  :
            
            break;
         case MEN_INSTRUCCION  :
            
            break;
         case NEG_INSTRUCCION  :
            
            break;
         case NOT_INSTRUCCION  :
            
            break;
         case OPUESTO_INSTRUCCION  :
            
            break;
         case PROD_INSTRUCCION  :
            
            break;
         case DIV_INSTRUCCION  :
            
            break;
         case MOD_INSTRUCCION  :
            
            break;
         case AND_INSTRUCCION  :
            
            break;
         case OR_INSTRUCCION  :
            
            break;
         case RETURN_INSTRUCCION  :
            
            break;
         case ELSE_INSTRUCCION  :
            
            break;
         case END_IF  :
            
            break;
         case END_ELSE  :
            
            break;
        case LABEL_WHILE_INSTRUCCION  :
            
            break;
        case LABEL_END_WHILE_INSTRUCCION  :
            
            break;
        case CARGAR_ACTUAL_PARAMS  :
            
            break;
         default :
         break;
      }
      auxInstr = auxInstr->next;
    }
  }

}