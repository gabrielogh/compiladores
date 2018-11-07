#include "cod_intermedio.h"

FILE *asm_code;

#ifdef __linux__
#define sis  1
#elif __APPLE__
#define sis 2
#endif

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
  if(sis == 1){
    //printf("SISTEMA OPERATIVO LINUX\n");
    if(strcmp(intr->nombre,"main")== 0){
      fputs("    .globl  main\n", asm_code); 
    }
    char c[32];
    strcpy(c, intr->nombre);
    strcat(c, ":\n");
    fputs(c, asm_code);
    printf("%s:\n",intr->nombre);

    char p[32];
    strcpy(p, "  pushq  %rbp\n");
    fputs(p, asm_code);
    printf("%s\n", "  pushq  %rbp");
  }
  else if(sis == 2){
    //printf("SISTEMA OPERATIVO MAC\n");
    if(strcmp(intr->nombre,"main")== 0){
      fputs("    .globl  _main\n", asm_code); 
    }
    char c[32];
    strcpy(c, "_");
    strcat(c, intr->nombre);
    strcat(c, ":\n");
    fputs(c, asm_code);
    printf("_%s:\n",intr->nombre);

    char p[32];
    strcpy(p, "  pushq  %rbp\n");
    fputs(p, asm_code);

    char q[32];
    strcpy(q, "  .cfi_def_cfa_offset 16\n");
    fputs(q, asm_code);
    strcpy(q, "  .cfi_offset %rbp, -16\n");
    fputs(q, asm_code);
    printf("%s\n", "  pushq  %rbp");
  }
}

void generar_codigo_assembler(){
  crear_archivo();

  tresDirL *Listaux = head_td;

  if(Listaux != NULL){
    while(Listaux !=  NULL){
      crear_label_funcion(Listaux);
      cargar_instrcciones(Listaux->fst);
      fputs("\n", asm_code);
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
              if(sis == 1){
                char c[32];
                strcpy(c, "  call ");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
              }
              else{
                char c[32];
                strcpy(c, "  call _");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
              }
            break;
         case CALL_WITH_PARAMS  :
              if(sis == 1){
                char c[32];
                strcpy(c, "  call ");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
              }
              else{
                char c[32];
                strcpy(c, "  call _");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
              }
            
            break;
         case ASIGN_INSTRUCCION  :
            
            break;
         case CTE_INSTRUCCION  :
            
            break;
         case EQ_INSTRUCCION  :
            
            break;
         case ADD_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  addq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
              }            
            break;
         case SUB_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  subq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
              }            
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
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  imulq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
              }
            break;
         case DIV_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  idivq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
              } 
            
            break;
         case MOD_INSTRUCCION  :

            
            break;
         case AND_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  andq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
              } 
            break;
         case OR_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  orq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*4);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
              } 
            
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