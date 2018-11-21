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

    strcpy(c, intr->nombre);
    strcat(c, ":");
    strcat(c, "                      ## -- Begin function ");
    strcat(c, intr->nombre);
    strcat(c, "\n");
    fputs(c, asm_code);


    strcpy(p, "  pushq  %rbp\n");
    fputs(p, asm_code);
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

    strcpy(p, "  enter $");
    sprintf(aux,"%d", (intr->stackSize)*8);
    strcat(p, aux);
    strcat(p, ", $0\n");
    fputs(p, asm_code);
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
      /*if(sis == 2 && (strcmp(Listaux->nombre, "main")!=0)){
        fputs("  leaq  L_.str(%rip), %rdi\n", asm_code);
        fputs("  movq  %rax, %rsi\n", asm_code);
        fputs("  movq  $0, %rax\n", asm_code);
        fputs("  callq _printf\n", asm_code);
      }*/
      fputs("  leave\n", asm_code);
      fputs("  ret                      ## -- End function\n", asm_code);
      fputs("\n", asm_code);
      Listaux = Listaux->next;
    }
    /*if(sis == 2){
      char comillas[1];
      comillas[0] = 34;
      char msg[128];
      fputs("  .section  __TEXT,__cstring,cstring_literals\n", asm_code);
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
    }*/

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
            strcpy(c, "  jmp ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            break;

         case JNE  :
            strcpy(c, "  jne ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            break;

         case JE  :
            strcpy(c, "  je ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            break;

         case JLE  :
            strcpy(c, "  jle ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            break;

         case JGE  :
            strcpy(c, "  jge ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            break;

         case CARGAR_PARAMS  :
              cargar_param(auxInstr);
            break;

         case CALL  :
              if(sis == 1){
                strcpy(c, "  call ");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
              }
              else{
                strcpy(c, "  call _");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
              }
              strcpy(c, "  movq %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(c, aux);
              strcat(c, "(%rbp)\n");
              fputs(c, asm_code);
            break;

         case CALL_WITH_PARAMS  :
              if(sis == 1){
                strcpy(c, "  call  ");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
              }
              else{
                strcpy(c, "  call  _");
                strcat(c, auxInstr->op1->nombre);
                strcat(c, "\n");
                fputs(c, asm_code);
              }
              strcpy(c, "  movq %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(c, aux);
              strcat(c, "(%rbp)\n");
              fputs(c, asm_code);
            break;

         case ASIGN_INSTRUCCION  :
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), ");
              strcat(res, "%rax\n");
              fputs(res, asm_code);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
            break;

         case CTE_INSTRUCCION  :
              strcpy(res, "  movq  $");
              sprintf(aux,"%d", (auxInstr->op1->valor));
              strcat(res, aux);
              strcat(res, ", -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
            break;

         case EQ_INSTRUCCION  :
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  cmpq  %rax, -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);

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
            break;

         case ADD_INSTRUCCION  :
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  addq  -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
            break;

         case SUB_INSTRUCCION  :
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  subq  -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
            break;

         case MAY_INSTRUCCION  :
              strcpy(res, "  movq -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  cmpq %rax, -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);

              strcpy(res, "  setl %dl\n");
              fputs(res, asm_code);

              strcpy(res, "  andb $1, %dl\n");
              fputs(res, asm_code);

              strcpy(res, "  movzbl %dl, %esi\n");
              fputs(res, asm_code);

              strcpy(res, "  movq %rsi, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code); 
            break;

         case MEN_INSTRUCCION  :
              strcpy(res, "  movq -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  cmpq %rax, -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);

              strcpy(res, "  setg %dl\n");
              fputs(res, asm_code);

              strcpy(res, "  andb $1, %dl\n");
              fputs(res, asm_code);

              strcpy(res, "  movzbl %dl, %esi\n");
              fputs(res, asm_code);

              strcpy(res, "  movq %rsi, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);           
            break;

         case OPUESTO_INSTRUCCION  :
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  negq %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
            break;

         case PROD_INSTRUCCION  :
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  imulq  -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
            break;

         case DIV_INSTRUCCION  :
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  idivq  -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
            break;
         case MOD_INSTRUCCION  :
              strcpy(res, "  movq -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              fputs("  cqto\n",asm_code);

              strcpy(res, "  idivq -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);

              strcpy(res, "  movq %rdx, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
            
            break;

         case AND_INSTRUCCION  :
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  andq  -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
            break;

         case OR_INSTRUCCION  :
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  orq  -");
              sprintf(aux,"%d", (auxInstr->op2->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);

            break;

         case NOT_INSTRUCCION  :
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  xorq  $-1, %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  andq  $1, %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
            break;

         case RETURN_INSTRUCCION  :
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
            break;

         case IF_INSTRUCCION  :
              strcpy(res, "  cmpl  $0, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);

              strcpy(res, "  je ");
              strcat(res, auxInstr->op2->nombre);
              strcat(res, "\n");
              fputs(res, asm_code);
            break;

         case IF_ELSE_INSTRUCCION  :
              strcpy(res, "  cmpl  $0, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);

              strcpy(res, "  je ");
              strcat(res, auxInstr->op2->nombre);
              strcat(res, "\n");
              fputs(res, asm_code);
            break;

         case ELSE_INSTRUCCION  :
              strcpy(c, auxInstr->res->nombre);
              strcat(c, ":\n");
              fputs(c, asm_code);
            break;

         case END_IF  :
              strcpy(c, auxInstr->res->nombre);
              strcat(c, ":\n");
              fputs(c, asm_code);
            break;

         case END_ELSE  :
              strcpy(c, auxInstr->res->nombre);
              strcat(c, ":\n");
              fputs(c, asm_code);
            break;

        case LABEL_WHILE_INSTRUCCION  :
              strcpy(c, auxInstr->res->nombre);
              strcat(c, ":\n");
              fputs(c, asm_code);
            break;

        case WHILE_INSTRUCCION  :
            strcpy(res, "  cmpl  $0, -");
            sprintf(aux,"%d", (auxInstr->res->offset)*8);
            strcat(res, aux);
            strcat(res, "(%rbp)\n");
            fputs(res, asm_code);

            strcpy(res, "  je ");
            strcat(res, auxInstr->op2->nombre);
            strcat(res, "\n");
            fputs(res, asm_code);
            break;

        case LABEL_END_WHILE_INSTRUCCION  :
            strcpy(c, auxInstr->res->nombre);
            strcat(c, ":\n");
            fputs(c, asm_code);
            break;

        case CARGAR_ACTUAL_PARAMS  :
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
    break;
    case 2:
          strcpy(res, "  movq  %rsi, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
    case 3:
          strcpy(res, "  movq  %rdx, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
    case 4:
          strcpy(res, "  movq  %rcx, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
    case 5:
          strcpy(res, "  movq  %r8, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
    case 6:
          strcpy(res, "  movq  %r9, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
    default:
          strcpy(res, "  movq  ");
          sprintf(aux,"%d", (parametro-5)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rax\n");
          fputs(res, asm_code);

          strcpy(res, "  movq  %rax, -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
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
    break;
    case 2:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rsi\n");
          fputs(res, asm_code);
    break;
    case 3:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rdx\n");
          fputs(res, asm_code);
    break;
    case 4:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rcx\n");
          fputs(res, asm_code);
    break;
    case 5:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %r8\n");
          fputs(res, asm_code);
    break;
    case 6:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %r9\n");
          fputs(res, asm_code);
    break;
    default:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rdi\n");
          fputs(res, asm_code);

          strcpy(res, "  pushq %rdi\n");
          fputs(res, asm_code);
    break;
  }
}