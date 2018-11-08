#include "cod_intermedio.h"

FILE *asm_code;

#ifdef __linux__
#define sis  1
#elif __APPLE__
#define sis 2
#endif

//DECLARACION DE METODOS.

void generar_codigo_assembler();

void crear_archivo();

void crear_label_funcion(tresDirL *intr);

void cargar_instrcciones(tresDir *instr);

//IMPLEMENTACION DE METODOS.

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
    printf("\n");
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
    printf("%s", q);

    strcpy(q, "  .cfi_offset %rbp, -16\n");
    fputs(q, asm_code);
    printf("%s", q);
    printf("%s\n", "  pushq  %rbp");
    printf("\n");
  }
}

void generar_codigo_assembler(){
  if(sis == 1){
    printf(KGRN "%s\n", "Generando codigo Assembler para LINUX.... "); printf(KNRM);
  }
  else{
    printf(KGRN "%s\n", "Generando codigo Assembler para MAC.... "); printf(KNRM);
  }
  crear_archivo();
  tresDirL *Listaux = head_td;

  if(Listaux != NULL){
    while(Listaux !=  NULL){
      crear_label_funcion(Listaux);
      cargar_instrcciones(Listaux->fst);
      fputs("\n", asm_code);
      printf("\n");
      Listaux = Listaux->next;
    }
    printf(KGRN "%s\n", "Codigo Assembler generado. "); printf(KNRM);
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
            if(true){
              int parametro = auxInstr->res->nParam;
              switch (parametro){
                case 1:
                    if(true){
                      char res[32];
                      char aux[32];
                      strcpy(res, "  movq %rdi, -");
                      sprintf(aux,"%d", (auxInstr->res->offset)*8);
                      strcat(res, aux);
                      strcat(res, "(%rbp)\n");
                      fputs(res, asm_code);
                      printf("%s", res);
                    }
                break;
                case 2:
                    if(true){
                      char res[32];
                      char aux[32];
                      strcpy(res, "  movq %rsi, -");
                      sprintf(aux,"%d", (auxInstr->res->offset)*8);
                      strcat(res, aux);
                      strcat(res, "(%rbp)\n");
                      fputs(res, asm_code);
                      printf("%s", res);
                    }
                break;
                case 3:
                    if(true){
                      char res[32];
                      char aux[32];
                      strcpy(res, "  movq %rdx, -");
                      sprintf(aux,"%d", (auxInstr->res->offset)*8);
                      strcat(res, aux);
                      strcat(res, "(%rbp)\n");
                      fputs(res, asm_code);
                      printf("%s", res);
                    }
                break;
                case 4:
                    if(true){
                      char res[32];
                      char aux[32];
                      strcpy(res, "  movq %rcx, -");
                      sprintf(aux,"%d", (auxInstr->res->offset)*8);
                      strcat(res, aux);
                      strcat(res, "(%rbp)\n");
                      fputs(res, asm_code);
                      printf("%s", res);
                    }
                break;
                case 5:
                    if(true){
                      char res[32];
                      char aux[32];
                      strcpy(res, "  movq %r8, -");
                      sprintf(aux,"%d", (auxInstr->res->offset)*8);
                      strcat(res, aux);
                      strcat(res, "(%rbp)\n");
                      fputs(res, asm_code);
                      printf("%s", res);
                    }
                break;
                case 6:
                    if(true){
                      char res[32];
                      char aux[32];
                      strcpy(res, "  movq %r9, -");
                      sprintf(aux,"%d", (auxInstr->res->offset)*8);
                      strcat(res, aux);
                      strcat(res, "(%rbp)\n");
                      fputs(res, asm_code);
                      printf("%s", res);
                    }
                break;
                default:
                    if(true){
                      char res[32];
                      char aux[32];
                      strcpy(res, "  movq ");
                      sprintf(aux,"%d", (auxInstr->res->offset)*8);
                      strcat(res, aux);
                      strcat(res, "(%rbp), %rax\n");
                      fputs(res, asm_code);
                      printf("%s", res);

                      strcpy(res, "  movq  %rax, -");
                      sprintf(aux,"%d", (auxInstr->res->offset)*8);
                      strcat(res, aux);
                      strcat(res, "(%rbp)\n");
                      fputs(res, asm_code);
                      printf("%s", res);
                    }
                break;
              }
            }
            break;

         case IF_INSTRUCCION  :
            
            break;

         case IF_ELSE_INSTRUCCION  :
            
            break;
         case WHILE_INSTRUCCION  :
            if(true){
              char c[32];
              strcpy(c, "  cmpl $0, -4(%rbp)\n");
              fputs(c, asm_code);
              printf("%s\n", "  cmpl $0, -4(%rbp)\n");

              strcpy(c, "  je ");
              strcat(c, auxInstr->op2->nombre);
              strcat(c, "\n");
              fputs(c, asm_code);
              printf("%s\n", c);
            }
            break;
         case CALL  :
              if(sis == 1){
                char c[32];
                strcpy(c, "  call ");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
                printf("%s", c);
              }
              else{
                char c[32];
                strcpy(c, "  call _");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
                printf("%s", c);
              }
            break;
         case CALL_WITH_PARAMS  :
              if(sis == 1){
                char c[32];
                strcpy(c, "  call ");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
                printf("%s", c);
              }
              else{
                char c[32];
                strcpy(c, "  call _");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
                printf("%s", c);
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
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  addq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
                printf("%s", res);
              }            
            break;
         case SUB_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  subq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
                printf("%s", res);
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
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  imulq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
                printf("%s", res);
              }
            break;
         case DIV_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  idivq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
                printf("%s", res);
              } 
            
            break;
         case MOD_INSTRUCCION  :

            
            break;
         case AND_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  andq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
                printf("%s", res);
              } 
            break;
         case OR_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  orq -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  movq %rax, -");
                sprintf(aux,"%d", (auxInstr->res->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
                printf("%s", res);
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
            if(true){
              char c[32];
              strcpy(c, auxInstr->res->nombre);
              strcat(c, ":\n");
              fputs(c, asm_code);
              printf("%s:\n", auxInstr->res->nombre);

            }
            break;
        case LABEL_END_WHILE_INSTRUCCION  :
            if(true){
              char c[32];
              strcpy(c, auxInstr->res->nombre);
              strcat(c, ":\n");
              fputs(c, asm_code);
              printf("%s:\n", auxInstr->res->nombre);

            }
            break;
        case CARGAR_ACTUAL_PARAMS  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq $");
                sprintf(aux,"%d", auxInstr->res->valor);
                strcat(res, aux);
                sprintf(aux,"%d", (auxInstr->res->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
                printf("%s", res);
              }
            break;
         default :
         break;
      }
      auxInstr = auxInstr->next;
    }
  }
}
