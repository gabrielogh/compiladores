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

void cargar_param(int fp);

void cargar_actual_params(tresDir *auxInstr);

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
      fputs("    .type  main, @function\n", asm_code);
    }
    char c[32];
    strcpy(c, "    .type  ");
    strcat(c, intr->nombre);
    strcat(c, ", @function\n");
    fputs(c, asm_code);
    printf("%s", c);

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
    char aux[32];
    strcpy(c, "_");
    strcat(c, intr->nombre);
    strcat(c, ":\n");
    fputs(c, asm_code);
    printf("_%s:\n",intr->nombre);

    char p[32];
    strcpy(p, "  enter $");
    sprintf(aux,"%d", (intr->stackSize)*8);
    strcat(p, aux);
    strcat(p, ", $0\n");
    fputs(p, asm_code);
    printf("%s", p);
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
            cargar_param(auxInstr->res->nParam);
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
                strcpy(c, "  call  ");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
                printf("%s", c);
              }
              else{
                char c[32];
                strcpy(c, "  call  _");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
                printf("%s", c);
              }
            
            break;
         case ASIGN_INSTRUCCION  :
            
            break;
         case CTE_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq  $");
                sprintf(aux,"%d", (auxInstr->op1->valor));
                strcat(res, aux);
                strcat(res, ",");
                sprintf(aux,"%d", (auxInstr->res->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp)\n");
                fputs(res, asm_code);
                printf("%s", res);
              }
            break;
         case EQ_INSTRUCCION  :
            
            break;
         case ADD_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq  -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  addq  -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
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
         case SUB_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq  -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  subq  -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
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
                strcpy(res, "  movq  -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  imulq  -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
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
         case DIV_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq  -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  idivq  -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
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
         case MOD_INSTRUCCION  :

            
            break;
         case AND_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq  -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  andq  -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
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
         case OR_INSTRUCCION  :
              if(true){
                char res[32];
                char aux[32];
                strcpy(res, "  movq  -");
                sprintf(aux,"%d", (auxInstr->op1->offset)*8);
                strcat(res, aux);
                strcat(res, "(%rbp), %rax\n");
                fputs(res, asm_code);
                printf("%s", res);

                strcpy(res, "  orq  -");
                sprintf(aux,"%d", (auxInstr->op2->offset)*8);
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
              cargar_actual_params(instr);
            break;
         default :
         break;
      }
      auxInstr = auxInstr->next;
    }
  }
}

void cargar_param(int parametro){
  char res[32];
  char aux[32];
  //printf("EL ID DEL PARAMETRO ES: %d\n", parametro);
  switch (parametro){
    case 1:
          strcpy(res, "  movq  %edi, -4(%rdi)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 2:
          strcpy(res, "  movq  %esi, -8(%rsi)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 3:
          strcpy(res, "  movq  %edx, -12(%rdx)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 4:
          strcpy(res, "  movq  %ecx, -16(%rcx)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 5:
          strcpy(res, "  movq  %r8d, -20(%r8)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 6:
          strcpy(res, "  movq  %r9d, -24(%r9)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    default:
          strcpy(res, "  movq  ");
          sprintf(aux,"%d", (parametro-5)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rax\n");
          fputs(res, asm_code);
          printf("%s", res);

          strcpy(res, "  movq  %rax, -");
          sprintf(aux,"%d", (parametro-5)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
  }
}

void cargar_actual_params(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
  //printf("EL ID DEL PARAMETRO ES: %d\n", parametro);
  switch (parametro){
    case 1:
          strcpy(res, "  movq  ");
          sprintf(aux, "%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "%(ebp), %rdi\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 2:
          strcpy(res, "  movq  ");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "%(ebp), %rsi\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 3:
          strcpy(res, "  movq  ");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "%(ebp), %rdx\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 4:
          strcpy(res, "  movq  ");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "%(ebp), %rcx\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 5:
          strcpy(res, "  movq  ");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "%(ebp), %r8\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 6:
          strcpy(res, "  movq  ");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "%(ebp), %r9\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    default:
          strcpy(res, "  movq  ");
          sprintf(aux,"%d", (parametro-5)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rax\n");
          fputs(res, asm_code);
          printf("%s", res);

          strcpy(res, "  movq  %rax, -");
          sprintf(aux,"%d", (parametro-5)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
  }
}



