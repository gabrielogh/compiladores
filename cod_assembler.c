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

void cargar_param(tresDir *auxInstr);

void cargar_actual_params(tresDir *auxInstr);

//IMPLEMENTACION DE METODOS.

void crear_archivo(){
  asm_code = fopen("assembler.s","w");
  if(asm_code == NULL){
    printf("%s\n","Error al crear el archivo assembler.s" );
  }
}

void crear_label_funcion(tresDirL *intr){
  char c[256];
  char aux[256];
  char p[256];
  if(sis == 1){
    if(strcmp(intr->nombre,"main")== 0){
      fputs("    .globl  main\n", asm_code);
      fputs("    .type  main, @function\n", asm_code);
    }
    strcpy(c, "    .type  ");
    strcat(c, intr->nombre);
    strcat(c, ", @function\n");
    fputs(c, asm_code);
    printf("%s", c);

    strcpy(c, intr->nombre);
    strcat(c, ":");
    strcat(c, "                      ## -- Begin function ");
    strcat(c, intr->nombre);
    strcat(c, "\n");
    fputs(c, asm_code);
    printf("_%s:\n",intr->nombre);


    strcpy(p, "  pushq  %rbp\n");
    fputs(p, asm_code);
    printf("%s\n", "  pushq  %rbp");
    printf("\n");
  }
  else if(sis == 2){
    if(strcmp(intr->nombre,"main")== 0){
      fputs("    .globl  _main\n", asm_code);
    }
    strcpy(c, "_");
    strcat(c, intr->nombre);
    strcat(c, ":");
    strcat(c, "                      ## -- Begin function ");
    strcat(c, intr->nombre);
    strcat(c, "\n");
    fputs(c, asm_code);
    printf("_%s:\n",intr->nombre);

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
      printf("\n");
      if(sis == 2){
        fputs("  leaq  L_.str(%rip), %rdi\n", asm_code);
        fputs("  movq  %rax, %rsi\n", asm_code);
        fputs("  movq  $0, %rax\n", asm_code);
        fputs("  callq _printf\n", asm_code);
      }
      fputs("  leave\n", asm_code);
      printf("  leave\n");
      fputs("  ret                      ## -- End function\n", asm_code);
      printf("  ret                      ## -- End function\n");
      printf("\n");
      fputs("\n", asm_code);
      Listaux = Listaux->next;
    }
    if(sis == 2){
      char comillas[1];
      comillas[0] = 34;
      char msg[128];
      fputs("  .section  __TEXT,__cstring,cstring_literals)\n", asm_code);
      fputs("L_.str:                                 ## @.str\n", asm_code);
      strcpy(msg, "  .asciz  ");
      strcat(msg, comillas);
      strcat(msg, "resultado: %d");
      strcat(msg, "\\");
      strcat(msg, "n");
      strcat(msg, comillas);
      strcat(msg, "\n");
      printf("%s\n", msg);
      fputs(msg, asm_code);
      fputs("L_.str.1:                               ## @.str.1\n", asm_code);
    }

    printf(KGRN "%s\n", "Codigo Assembler generado. "); printf(KNRM);
  }

}

void cargar_instrcciones(tresDir *instr){
  char c[32];
  char aux[32];
  char res[32];
  tresDir *auxInstr = instr;
  if(auxInstr != NULL){
    while(auxInstr != NULL){
      int op = auxInstr->op;
      switch(op) {

         case JMP  :
            printf("JMP\n");
            strcpy(c, "  jmp ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            printf("%s\n", c);
            break;

         case JE  :
            printf("JE\n");
            strcpy(c, "  je ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            printf("%s\n", c);
            break;

         case JLE  :
            printf("JLE\n");
            strcpy(c, "  jle ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            printf("%s\n", c);
            break;

         case JGE  :
            printf("JGE\n");
            strcpy(c, "  jge ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            printf("%s\n", c);
            break;

         case CARGAR_PARAMS  :
              printf("CARGAR_PARAMS\n");
              cargar_param(auxInstr);
            break;

         case CALL  :
              printf("CALL\n");
              if(sis == 1){
                strcpy(c, "  call ");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
                printf("%s", c);
              }
              else{
                strcpy(c, "  call _");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
                printf("%s", c);
              }
            break;

         case CALL_WITH_PARAMS  :
              printf("CALL_WITH_PARAMS\n");
              if(sis == 1){
                strcpy(c, "  call  ");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
                printf("%s", c);
              }
              else{
                strcpy(c, "  call  _");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
                printf("%s", c);
              }
            break;

         case ASIGN_INSTRUCCION  :
              printf("ASIGN_INSTRUCCION\n");
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), ");
              strcat(res, "%rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);
              printf("EN LA ASIGNACION EL OFFSET ES DE %d\n", auxInstr->res->offset);
            break;

         case CTE_INSTRUCCION  :
              printf("CTE_INSTRUCCION\n");
              strcpy(res, "  movq  $");
              sprintf(aux,"%d", (auxInstr->op1->valor));
              strcat(res, aux);
              strcat(res, ", -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);
            break;

         case EQ_INSTRUCCION  :
              printf("EQ_INSTRUCCION\n");
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  cmpq  %rax, -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  sete %dl\n");
              fputs(res, asm_code);

              strcpy(res, "  andb $1, %dl\n");
              fputs(res, asm_code); 

              strcpy(res, "  movzbl %dl, %esi\n");
              fputs(res, asm_code);

              strcpy(res, "  movq  %rsi, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);
            break;

         case ADD_INSTRUCCION  :
              printf("ADD_INSTRUCCION\n");
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
            break;

         case SUB_INSTRUCCION  :
              printf("SUB_INSTRUCCION\n");
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
            break;

         case MAY_INSTRUCCION  :
              printf("MAY_INSTRUCCION\n");
              strcpy(res, "  movq -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  cmpq -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

            break;

         case MEN_INSTRUCCION  :
            
            break;

         case NEG_INSTRUCCION  :
              printf("NEG_INSTRUCCION\n");
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  negq  -");
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);
            break;

         case NOT_INSTRUCCION  :
              printf("NOT_INSTRUCCION\n");
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  xorq  -");
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  andq  -");
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);
            break;

         case OPUESTO_INSTRUCCION  :
              printf("OPUESTO_INSTRUCCION\n");
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  negq %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);
            break;

         case PROD_INSTRUCCION  :
              printf("PROD_INSTRUCCION\n");
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
            break;

         case DIV_INSTRUCCION  :
              printf("DIV_INSTRUCCION\n");
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
            break;
         case MOD_INSTRUCCION  :
              printf("MOD_INSTRUCCION\n");
              strcpy(res, "  movq -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              fputs("  cqto\n",asm_code);
              printf("  cqto\n");

              strcpy(res, "  idivq -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  movq %rdx, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);
            
            break;

         case AND_INSTRUCCION  :
              printf("ADD_INSTRUCCION\n");
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
            break;

         case OR_INSTRUCCION  :
              printf("OR_INSTRUCCION\n");
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
            break;

         case RETURN_INSTRUCCION  :
              printf("RETURN_INSTRUCCION\n");
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);
            break;

         case ELSE_INSTRUCCION  :
            printf("ELSE_INSTRUCCION\n");
            strcpy(c, auxInstr->res->nombre);
            strcat(c, ":\n");
            fputs(c, asm_code);
            printf("%s:\n", auxInstr->res->nombre); 
            break;

         case END_IF  :
            printf("END_IF\n");
            strcpy(c, auxInstr->res->nombre);
            strcat(c, ":\n");
            fputs(c, asm_code);
            printf("%s:\n", auxInstr->res->nombre);
            break;

         case END_ELSE  :
            printf("END_ELSE\n");
            strcpy(c, auxInstr->res->nombre);
            strcat(c, ":\n");
            fputs(c, asm_code);
            printf("%s:\n", auxInstr->res->nombre);
            break;

        case LABEL_WHILE_INSTRUCCION  :
            printf("LABEL_WHILE_INSTRUCCION\n");
            strcpy(c, auxInstr->res->nombre);
            strcat(c, ":\n");
            fputs(c, asm_code);
            printf("%s:\n", auxInstr->res->nombre);
            break;

        case LABEL_END_WHILE_INSTRUCCION  :
            printf("LABEL_END_WHILE_INSTRUCCION\n");
            strcpy(c, auxInstr->res->nombre);
            strcat(c, ":\n");
            fputs(c, asm_code);
            printf("%s:\n", auxInstr->res->nombre);
            break;

        case CARGAR_ACTUAL_PARAMS  :
              printf("CARGAR_ACTUAL_PARAMS\n");
              cargar_actual_params(auxInstr);
            break;

         default :
         break;
      }
      auxInstr = auxInstr->next;
    }
  }
}

void cargar_param(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
  switch (parametro){
    case 1:
          strcpy(res, "  movq  %rdi, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 2:
          strcpy(res, "  movq  %rsi, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 3:
          strcpy(res, "  movq  %rdx, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 4:
          strcpy(res, "  movq  %rcx, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 5:
          strcpy(res, "  movq  %r8, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 6:
          strcpy(res, "  movq  %r9, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
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
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
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
  switch (parametro){
    case 1:
          strcpy(res, "  movq  -");
          sprintf(aux, "%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rdi\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 2:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rsi\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 3:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rdx\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 4:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rcx\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 5:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %r8\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 6:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %r9\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    default:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rdi\n");
          fputs(res, asm_code);
          printf("%s", res);

          strcpy(res, "  pushq %rdi\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
  }
}

