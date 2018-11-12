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
    //printf("SISTEMA OPERATIVO LINUX\n");
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
    //printf("SISTEMA OPERATIVO MAC\n");
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
      fputs("  leave\n", asm_code);
      printf("  leave\n");
      fputs("  ret                      ## -- End function\n", asm_code);
      printf("  ret                      ## -- End function\n");
      printf("\n");
      fputs("\n", asm_code);
      Listaux = Listaux->next;
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
            strcpy(c, "  jmp ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            printf("%s\n", c);
            break;

         case JE  :
            strcpy(c, "  je ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            printf("%s\n", c);
            break;

         case JLE  :
            strcpy(c, "  jle ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            printf("%s\n", c);
            break;

         case JGE  :
            strcpy(c, "  jge ");
            strcat(c, auxInstr->res->nombre);
            strcat(c, "\n");
            fputs(c, asm_code);
            printf("%s\n", c);
            break;

         case CARGAR_PARAMS  :
              cargar_param(auxInstr);
            break;

         case IF_INSTRUCCION  :
             /* strcpy(c, "  cmpl $0, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(c, aux);
              strcat(c, "(%rbp)\n");
              fputs(c, asm_code);
              printf("%s\n", c);*/

             /* strcpy(c, "  je ");
              strcat(c, auxInstr->op2->nombre);
              strcat(c, "\n");
              fputs(c, asm_code);
              printf("%s\n", c);*/
            break;

         case IF_ELSE_INSTRUCCION  :
              /*strcpy(c, "  cmpl $0, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(c, aux);
              strcat(c, "(%rbp)\n");
              fputs(c, asm_code);
              printf("%s\n", c);*/
              /*
              strcpy(c, "  je ");
              strcat(c, auxInstr->op2->nombre);
              strcat(c, "\n");
              fputs(c, asm_code);
              printf("%s\n", c);*/
            break;

         case WHILE_INSTRUCCION  :/*
              strcpy(c, "  cmpl $0, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(c, aux);
              strcat(c, "(%rbp)\n");
              fputs(c, asm_code);
              printf("%s\n", c);

              strcpy(c, "  je ");
              strcat(c, auxInstr->op2->nombre);
              strcat(c, "\n");
              fputs(c, asm_code);
              printf("%s\n", c);*/
            break;

         case CALL  :
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
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), ");
              strcat(res, "(%rax)\n");
              fputs(res, asm_code);
              printf("%s", res);

              //printf("LE ASIGNAMOS %s a %s \n", auxInstr->op1->nombre, auxInstr->res->nombre);
              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);
            break;

         case CTE_INSTRUCCION  :
              strcpy(res, "  movq  $");
              sprintf(aux,"%d", (auxInstr->op1->valor));
              strcat(res, aux);
              strcat(res, ", ");
              sprintf(aux,"%d", (auxInstr->res->offset)*(-8));
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);
            break;

         case EQ_INSTRUCCION  :
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

              strcpy(res, "  movzbl %dl, %rax\n");
              fputs(res, asm_code);

              strcpy(res, "  movq  %rax, -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);
            break;

         case ADD_INSTRUCCION  :
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
              strcpy(res, "  movq -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);

              fputs("  cqto\n",asm_code);
              printf("  cqto\n");

              strcpy(res, "  idivq -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);

              strcpy(res, "  movq %rdx, -");
              sprintf(aux,"%d", (auxInstr->op1->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              printf("%s", res);
            
            break;

         case AND_INSTRUCCION  :
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
              strcpy(res, "  movq  -");
              sprintf(aux,"%d", (auxInstr->res->offset)*8);
              strcat(res, aux);
              strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              printf("%s", res);
            break;

         case ELSE_INSTRUCCION  :
            strcpy(c, auxInstr->res->nombre);
            strcat(c, ":\n");
            fputs(c, asm_code);
            printf("%s:\n", auxInstr->res->nombre); 
            break;

         case END_IF  :
            strcpy(c, auxInstr->res->nombre);
            strcat(c, ":\n");
            fputs(c, asm_code);
            printf("%s:\n", auxInstr->res->nombre);
            break;

         case END_ELSE  :
            strcpy(c, auxInstr->res->nombre);
            strcat(c, ":\n");
            fputs(c, asm_code);
            printf("%s:\n", auxInstr->res->nombre);
            break;

        case LABEL_WHILE_INSTRUCCION  :
            strcpy(c, auxInstr->res->nombre);
            strcat(c, ":\n");
            fputs(c, asm_code);
            printf("%s:\n", auxInstr->res->nombre);
            break;

        case LABEL_END_WHILE_INSTRUCCION  :
            strcpy(c, auxInstr->res->nombre);
            strcat(c, ":\n");
            fputs(c, asm_code);
            printf("%s:\n", auxInstr->res->nombre);
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
          //printf("Entramos a cargar el parametro formal numero %d\n", parametro);
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
          strcat(res, "%(ebp), %rdi\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 2:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "%(ebp), %rsi\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 3:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "%(ebp), %rdx\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 4:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "%(ebp), %rcx\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 5:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "%(ebp), %r8\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    case 6:
          strcpy(res, "  movq  -");
          sprintf(aux,"%d", (auxInstr->res->offset)*8);
          strcat(res, aux);
          strcat(res, "%(ebp), %r9\n");
          fputs(res, asm_code);
          printf("%s", res);
    break;
    default:
          printf("ENTRA A DEFAULT\n");
          strcpy(res, "  pushq -");
          sprintf(aux,"%d", (parametro-5)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
          //printf("parametro actual: %s", auxInstr->res->nombre);printf("%s", res);
          /*
          strcpy(res, "  movq  ");
          sprintf(aux,"%d", (parametro-5)*8);
          strcat(res, aux);
          strcat(res, "(%rbp), %rax\n");
          fputs(res, asm_code);
          printf("%s", res);

          strcpy(res, "  movq  %rax, ");
          sprintf(aux,"%d", (parametro-5)*8);
          strcat(res, aux);
          strcat(res, "(%rbp)\n");
          fputs(res, asm_code);
          printf("%s", res);*/
    break;
  }
}

