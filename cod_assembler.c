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

void crear_constante_instruccion(tresDir *auxInstr);

void crear_while_instruccion(tresDir *auxInstr);

void crear_if_instruccion(tresDir *auxInstr);

void crear_if_else_instruccion(tresDir *auxInstr);

void crear_return_instruccion(tresDir *auxInstr);

void crear_not_instruccion(tresDir *auxInstr);

void crear_or_instruccion(tresDir *auxInstr);

void crear_and_instruccion(tresDir *auxInstr);

void crear_mod_instruccion(tresDir *auxInstr);

void crear_div_instruccion(tresDir *auxInstr);

void create_prod_instruccion(tresDir *auxInstr);

void crear_opuesto_instruccion(tresDir *auxInstr);

void crear_menor_instruccion(tresDir *auxInstr);

void crear_mayor_instruccion(tresDir *auxInstr);

void crear_sub_instruccion(tresDir *auxInstr);

void crear_add_instruccion(tresDir *auxInstr);

void crear_equals_instruccion(tresDir *auxInstr);

void crear_asignacion_instruccion(tresDir *auxInstr);

void crear_call_cp_instruccion(tresDir *auxInstr);

void crear_call_sp_instruccion(tresDir *auxInstr);


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

    fputs("  .cfi_startproc\n", asm_code);

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
      fputs("  leave\n", asm_code);
      fputs("  retq                      ## -- End function\n", asm_code);
      fputs("  .cfi_endproc\n", asm_code);
      fputs("\n", asm_code);
      Listaux = Listaux->next;
    }
    printf(KGRN "%s\n", "Codigo Assembler generado. "); printf(KNRM);
  }

}

void cargar_instrcciones(tresDir *instr){
  char c[32];
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

         case CARGAR_PARAMS  :
              cargar_param(auxInstr);
            break;

         case CALL  :
              crear_call_sp_instruccion(auxInstr);
            break;

         case CALL_WITH_PARAMS  :
              crear_call_cp_instruccion(auxInstr);
            break;

         case ASIGN_INSTRUCCION  :
              crear_asignacion_instruccion(auxInstr);
            break;

         case CTE_INSTRUCCION  :
              crear_constante_instruccion(auxInstr);
            break;

         case EQ_INSTRUCCION  :
              crear_equals_instruccion(auxInstr);
            break;

         case ADD_INSTRUCCION  :
              crear_add_instruccion(auxInstr);
            break;

         case SUB_INSTRUCCION  :
              crear_sub_instruccion(auxInstr);
            break;

         case MAY_INSTRUCCION  :
              crear_mayor_instruccion(auxInstr);
            break;

         case MEN_INSTRUCCION  :
              crear_menor_instruccion(auxInstr);          
            break;

         case OPUESTO_INSTRUCCION  :
              crear_opuesto_instruccion(auxInstr);
            break;

         case PROD_INSTRUCCION  :
              create_prod_instruccion(auxInstr);
            break;

         case DIV_INSTRUCCION  :
              crear_div_instruccion(auxInstr);
            break;
         case MOD_INSTRUCCION  :
              crear_mod_instruccion(auxInstr);
            break;

         case AND_INSTRUCCION  :
              crear_and_instruccion(auxInstr);
            break;

         case OR_INSTRUCCION  :
              crear_or_instruccion(auxInstr);
            break;

         case NOT_INSTRUCCION  :
              crear_not_instruccion(auxInstr);
            break;

         case RETURN_INSTRUCCION  :
              crear_return_instruccion(auxInstr);
            break;

         case IF_INSTRUCCION  :
              crear_if_instruccion(auxInstr);
            break;

         case IF_ELSE_INSTRUCCION  :
              crear_if_else_instruccion(auxInstr);
            break;

         case ELSE_INSTRUCCION  :
              strcpy(c, auxInstr->res->nombre);strcat(c, ":\n");
              fputs(c, asm_code);
            break;

         case END_IF  :
              strcpy(c, auxInstr->res->nombre);strcat(c, ":\n");
              fputs(c, asm_code);
            break;

         case END_ELSE  :
              strcpy(c, auxInstr->res->nombre);strcat(c, ":\n");
              fputs(c, asm_code);
            break;

        case LABEL_WHILE_INSTRUCCION  :
              strcpy(c, auxInstr->res->nombre);strcat(c, ":\n");
              fputs(c, asm_code);
            break;

        case WHILE_INSTRUCCION  :
            crear_while_instruccion(auxInstr);
            break;

        case LABEL_END_WHILE_INSTRUCCION  :
            strcpy(c, auxInstr->res->nombre);strcat(c, ":\n");
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
          strcpy(res, "  movq  %rdi, -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
    case 2:
          strcpy(res, "  movq  %rsi, -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
    case 3:
          strcpy(res, "  movq  %rdx, -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
    case 4:
          strcpy(res, "  movq  %rcx, -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
    case 5:
          strcpy(res, "  movq  %r8, -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
    case 6:
          strcpy(res, "  movq  %r9, -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
    default:
          strcpy(res, "  movq  ");sprintf(aux,"%d", (parametro-5)*8);strcat(res, aux);strcat(res, "(%rbp), %rax\n");
          fputs(res, asm_code);

          strcpy(res, "  movq  %rax, -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
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
          strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rdi\n");
          fputs(res, asm_code);
    break;
    case 2:
          strcpy(res, "  movq  -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rsi\n");
          fputs(res, asm_code);
    break;
    case 3:
          strcpy(res, "  movq  -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rdx\n");
          fputs(res, asm_code);
    break;
    case 4:
          strcpy(res, "  movq  -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rcx\n");
          fputs(res, asm_code);
    break;
    case 5:
          strcpy(res, "  movq  -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %r8\n");
          fputs(res, asm_code);
    break;
    case 6:
          strcpy(res, "  movq  -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %r9\n");
          fputs(res, asm_code);
    break;
    default:
          strcpy(res, "  pushq  -");sprintf(aux,"%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
    break;
  }
}

void crear_constante_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
  strcpy(res, "  movq  $");
  sprintf(aux,"%d", (auxInstr->op1->valor));
  strcat(res, aux);
  strcat(res, ", -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);
}

void crear_while_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
  strcpy(res, "  cmpl  $0, -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);

  strcpy(res, "  je ");
  strcat(res, auxInstr->op2->nombre);
  strcat(res, "\n");
  fputs(res, asm_code);
}

void crear_if_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
  strcpy(res, "  cmpl  $0, -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);

  strcpy(res, "  je ");
  strcat(res, auxInstr->op2->nombre);
  strcat(res, "\n");
  fputs(res, asm_code);
}

void crear_if_else_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
  strcpy(res, "  cmpl  $0, -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);

  strcpy(res, "  je ");
  strcat(res, auxInstr->op2->nombre);
  strcat(res, "\n");
  fputs(res, asm_code);
}

void crear_return_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
  strcpy(res, "  movq  -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp), %rax\n");
  fputs(res, asm_code);
}

void crear_not_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_or_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_and_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_mod_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_div_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void create_prod_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_opuesto_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_menor_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_mayor_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_sub_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_add_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_equals_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_asignacion_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_call_cp_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  char c[32];
  int parametro = auxInstr->res->nParam;
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
}

void crear_call_sp_instruccion(tresDir *auxInstr){
  char res[32];
  char aux[32];
  char c[32];
  int parametro = auxInstr->res->nParam;
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
}



