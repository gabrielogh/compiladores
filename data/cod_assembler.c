#include "cod_intermedio.h"
#include <dirent.h>

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

void crear_global(tresDirL *instr);

void mov_a_rax(tresDir *auxInstr);

//IMPLEMENTACION DE METODOS.

/*
 * Esta funcion genera el archivo donde se cargara el codigo assembler generado.
 * El nombre del archivo es estatico, no es parametro del sistema.
 */
void crear_archivo(){
  char name[64];
  char aux[32];

  DIR * dirp;
  struct dirent * entry;

  dirp = opendir("asm");
  while ((entry = readdir(dirp)) != NULL) {
    if (entry->d_type == DT_REG) {
      files++;
    }
  }
  closedir(dirp);

  strcpy(name, "asm/program");
  sprintf(aux,"%d", files);
  strcat(name, aux);
  strcat(name, ".s");
  asm_code = fopen(name,"w+");
  if(asm_code == NULL){
    printf("%s\n","Error al crear el archivo" );
  }
}


/*
 * Esta funcion genera el label de cada funcion del programa segun el sistema operativo.
 * *intr: Instruccion que representa una funcion.
 */
void crear_label_funcion(tresDirL *intr){
  char c[256];
  char aux[256];
  char p[256];
  if(sis == 1){
    if(strcmp(intr->nombre,"main")== 0){ fputs("    .globl  main\n", asm_code);}
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

    if((intr->stackSize%2)!=0){ intr->stackSize = intr->stackSize + 1;}
    strcpy(p, "  enter $");
    sprintf(aux,"%d", (intr->stackSize)*8);
    strcat(p, aux);
    strcat(p, ", $0\n");
    fputs(p, asm_code);
  }
  else if(sis == 2){
    if(strcmp(intr->nombre,"main")== 0){ fputs("    .globl  _main\n", asm_code);}

    strcpy(c, "_");
    strcat(c, intr->nombre);
    strcat(c, ":");
    strcat(c, "                      ## -- Begin function ");
    strcat(c, intr->nombre);
    strcat(c, "\n");
    fputs(c, asm_code);

    fputs("  .cfi_startproc\n", asm_code);

    if((intr->stackSize%2)!=0){ intr->stackSize = intr->stackSize + 1;}
    strcpy(p, "  enter $");
    sprintf(aux,"%d", (intr->stackSize)*8);
    strcat(p, aux);
    strcat(p, ", $0\n");
    fputs(p, asm_code);
  }
}

/*
 * Funcion principal que genera el codigo assembler.
 * Esta funcion utiliza a crear_archivo(), crear_label_funcion(), cargar_instrcciones().
 */
void generar_codigo_assembler(){
  if(sis == 1){
    printf("%s\n", "Generando codigo Assembler para LINUX.... ");
  }
  else{
    printf("%s\n", "Generando codigo Assembler para MAC.... ");
  }
  crear_archivo();
  tresDirL *Listaux = head_td;
  if(Listaux != NULL){
    while(Listaux !=  NULL){
      if(!(Listaux->is_gv)){
        crear_label_funcion(Listaux);
        cargar_instrcciones(Listaux->fst);
        fputs("  leave\n", asm_code);
        fputs("  retq                      ## -- End function\n", asm_code);
        fputs("  .cfi_endproc\n", asm_code);
        fputs("\n", asm_code);
        if(Listaux->next!=NULL){
          if(Listaux->next->is_gv){
            fputs("\n", asm_code);
          }
        }
      }
      else{
        crear_global(Listaux);
      }
      Listaux = Listaux->next;
    }
    fclose(asm_code);
    printf(KGRN "%s\n", "Codigo Assembler generado. "); printf(KNRM);
  }
}

/*
 * Esta funcion carga una variable global (se cargan al final del archivo)
 * *instr: instruccion que representa a una  varible global.
 */
void crear_global(tresDirL *instr){
  char c[256];
  if(sis == 2){
    strcpy(c, "  .comm _");
  }
  else{
    strcpy(c, "  .comm ");
  }
  strcat(c, instr->nombre);
  strcat(c, ",8,8                  ## @");
  strcat(c, instr->nombre);
  strcat(c, "\n");
  fputs(c, asm_code);
}

/*
 * Esta funcion recorre y genera el codigo assembler todas las instrucciones de cada funcion.
 * *instr: Puntero al primer elemento de la lista de instrucciones de una funcion.
 */
void cargar_instrcciones(tresDir *instr){
  char c[64];
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
        case MOV:
             mov_a_rax(auxInstr);
            break;

         default :
         break;
      }
      auxInstr = auxInstr->next;
    }
  }
}

/*
 * Esta funcion auxiliar utilizada para mover resultados al %rax
 * *instr: instruccion.
 */
void mov_a_rax(tresDir *auxInstr){
  char res[64];
  char aux[64];
  if(auxInstr->res->global){
    strcpy(res, "  movq  _");
    strcat(res, auxInstr->res->nombre);
    strcat(res, "(%rip), %rax\n");
    fputs(res, asm_code);
  }
  else{
    strcpy(res, "  movq  -");
    sprintf(aux,"%d", (auxInstr->res->offset)*8);
    strcat(res, aux);
    strcat(res, "(%rbp), %rax\n");
    fputs(res, asm_code);
  }
}

/*
 * Esta funcion genera el codigo assembler correspondiente a la carga de parametros formales desde sus registros al stack reservado
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void cargar_param(tresDir *auxInstr){
  char res[64];
  char aux[64];
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

/*
 * Esta funcion genera el codigo assembler correspondiente a la carga de parametros actuales a sus registros
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void cargar_actual_params(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->op1->nParam;
  switch (parametro){
    case 1:
          if(!(auxInstr->op1->const_var)){
            if(auxInstr->op1->global){
              strcpy(res, "  movq  _");
              strcat(res, auxInstr->op1->nombre);
              strcat(res, "(%rip), %rdi\n");
            }
            else{ 
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->op1->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  %rax, -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rdi\n");
            }
          }
          else{
            strcpy(res, "  movq  $");sprintf(aux, "%d", auxInstr->op1->valor);strcat(res, aux);strcat(res, ", %rdi\n");
          }
          fputs(res, asm_code);
    break;
    case 2:
          if(!(auxInstr->op1->const_var)){
            if(auxInstr->op1->global){
              strcpy(res, "  movq  _");
              strcat(res, auxInstr->op1->nombre);
              strcat(res, "(%rip), %rsi\n");
            }
            else{ 
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->op1->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  %rax, -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rsi\n");
            }
          }
          else{
            strcpy(res, "  movq  $");sprintf(aux, "%d", auxInstr->op1->valor);strcat(res, aux);strcat(res, ", %rsi\n");
          }
          fputs(res, asm_code);
    break;
    case 3:
          if(!(auxInstr->op1->const_var)){
            if(auxInstr->op1->global){
              strcpy(res, "  movq  _");
              strcat(res, auxInstr->op1->nombre);
              strcat(res, "(%rip), %rdx\n");
            }
            else{ 
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->op1->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  %rax, -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rdx\n");
            }
          }
          else{
            strcpy(res, "  movq  $");sprintf(aux, "%d", auxInstr->op1->valor);strcat(res, aux);strcat(res, ", %rdx\n");
          }
          fputs(res, asm_code);
    break;
    case 4:
          if(!(auxInstr->op1->const_var)){
            if(auxInstr->op1->global){
              strcpy(res, "  movq  _");
              strcat(res, auxInstr->op1->nombre);
              strcat(res, "(%rip), %rci\n");
            }
            else{ 
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->op1->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  %rax, -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rci\n");
            }
          }
          else{
            strcpy(res, "  movq  $");sprintf(aux, "%d", auxInstr->op1->valor);strcat(res, aux);strcat(res, ", %rci\n");
          }
          fputs(res, asm_code);
    break;
    case 5:
          if(!(auxInstr->op1->const_var)){
            if(auxInstr->op1->global){
              strcpy(res, "  movq  _");
              strcat(res, auxInstr->op1->nombre);
              strcat(res, "(%rip), %r8\n");
            }
            else{ 
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->op1->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  %rax, -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %r8\n");
            }
          }
          else{
            strcpy(res, "  movq  $");sprintf(aux, "%d", auxInstr->op1->valor);strcat(res, aux);strcat(res, ", %r8\n");
          }
          fputs(res, asm_code);
    break;
    case 6:
          if(!(auxInstr->op1->const_var)){
            if(auxInstr->op1->global){
              strcpy(res, "  movq  _");
              strcat(res, auxInstr->op1->nombre);
              strcat(res, "(%rip), %r9\n");
            }
            else{ 
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->op1->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  %rax, -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %r9\n");
            }
          }
          else{
            strcpy(res, "  movq  $");sprintf(aux, "%d", auxInstr->op1->valor);strcat(res, aux);strcat(res, ", %r9\n");
          }
          fputs(res, asm_code);
    break;
    default:
          if(!(auxInstr->op1->const_var)){
            if(auxInstr->op1->global){
              strcpy(res, "  pushq  _");
              strcat(res, auxInstr->op1->nombre);
              strcat(res, "(%rip)\n");
            }
            else{ 
              strcpy(res, "  movq  -");sprintf(aux, "%d", (auxInstr->op1->offset)*8);strcat(res, aux);strcat(res, "(%rbp), %rax\n");
              fputs(res, asm_code);
              strcpy(res, "  movq  %rax, -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
              fputs(res, asm_code);
              strcpy(res, "  pushq  -");sprintf(aux, "%d", (auxInstr->res->offset)*8);strcat(res, aux);strcat(res, "(%rbp)\n");
            }
          }
          else{
            strcpy(res, "  pushq  $");sprintf(aux, "%d", auxInstr->op1->valor);strcat(res, aux);
          }
          fputs(res, asm_code);
    break;
  }
}

/* YA NO SE USA.
 * Esta funcion genera el codigo assembler correspondiente a una constante.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_constante_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
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

/* OPTIMIZAR EL USO DE LOS JUMP - OWNER: NO ONE
 * Esta funcion genera el codigo assembler correspondiente a la condicion (de terminacion en este caso) de un while.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_while_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->res->const_var)){
    if(auxInstr->res->global){
      strcpy(res, "  cmpl  $0, _");
      strcat(res, auxInstr->res->nombre);
      strcat(res, "(%rip)\n");
      fputs(res, asm_code);
    }
    else{
  	  strcpy(res, "  cmpl  $0, -");
  	  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  	  strcat(res, aux);
  	  strcat(res, "(%rbp)\n");
  	  fputs(res, asm_code);
    }
  }
  else{
  	strcpy(res, "  cmpl  $0, $");
	  sprintf(aux,"%d", auxInstr->res->valor);
	  strcat(res, aux);
    strcat(res, "\n");
	  fputs(res, asm_code);
  }
  strcpy(res, "  je ");
  strcat(res, auxInstr->op2->nombre);
  strcat(res, "\n");
  fputs(res, asm_code);
}

/* OPTIMIZAR EL USO DE LOS JUMP - OWNER: NO ONE
 * Esta funcion genera el codigo assembler correspondiente a la condicion de un if.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_if_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->res->const_var)){
    if(auxInstr->res->global){
      strcpy(res, "  cmpl  $0, _");
      strcat(res, auxInstr->res->nombre);
      strcat(res, "(%rip)\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  cmpl  $0, -");
      sprintf(aux,"%d", (auxInstr->res->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp)\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  cmpl  $0, ");
    sprintf(aux,"%d", auxInstr->res->valor);
    strcat(res, aux);
    strcat(res, "\n");
    fputs(res, asm_code);
  }
  strcpy(res, "  je ");
  strcat(res, auxInstr->op2->nombre);
  strcat(res, "\n");
  fputs(res, asm_code);
}

/* OPTIMIZAR EL USO DE LOS JUMP - OWNER: NO ONE
 * Esta funcion genera el codigo assembler correspondiente a la condicion de un if then else.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_if_else_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->res->const_var)){
    if(auxInstr->res->global){
      strcpy(res, "  cmpl  $0, _");
      strcat(res, auxInstr->res->nombre);
      strcat(res, "(%rip)\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  cmpl  $0, -");
      sprintf(aux,"%d", (auxInstr->res->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp)\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  cmpl  $0, ");
    sprintf(aux,"%d", auxInstr->res->valor);
    strcat(res, aux);
    strcat(res, "\n");
    fputs(res, asm_code);
  }

  strcpy(res, "  je ");
  strcat(res, auxInstr->op2->nombre);
  strcat(res, "\n");
  fputs(res, asm_code);
}

/*
 * Esta funcion genera el codigo assembler correspondiente a un return (resultado en el RAX).
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_return_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  if(auxInstr->res->global){
    strcpy(res, "  movq _");
    strcat(res, auxInstr->res->nombre);
    strcat(res, "(%rip), %rax\n");
    fputs(res, asm_code);
  }
  else{
    int parametro = auxInstr->res->nParam;
    strcpy(res, "  movq  -");
    sprintf(aux,"%d", (auxInstr->res->offset)*8);
    strcat(res, aux);
    strcat(res, "(%rbp), %rax\n");
    fputs(res, asm_code);
  }
}

/* OPTIMIZAR LAURY. VERIFICAR CONSTANTES
 * Esta funcion genera el codigo assembler correspondiente a la negacion logica.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_not_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
  	  strcpy(res, "  movq  -");
  	  sprintf(aux,"%d", (auxInstr->op1->offset)*8);
  	  strcat(res, aux);
  	  strcat(res, "(%rbp), %rax\n");
  	  fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  movq  $");
	  sprintf(aux,"%d", (auxInstr->op1->valor));
	  strcat(res, aux);
	  strcat(res, ", %rax\n");
	  fputs(res, asm_code);
  }
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

/* OPTIMIZADA POR GABRIEL.
 * Esta funcion genera el codigo assembler correspondiente a la operacion logica OR.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_or_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  movq  -");
      sprintf(aux,"%d", (auxInstr->op1->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  movq  $");
    sprintf(aux,"%d", auxInstr->op1->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }
  if(!(auxInstr->op2->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  orq _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  orq  -");
      sprintf(aux,"%d", (auxInstr->op2->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  orq  $");
    sprintf(aux,"%d", auxInstr->op2->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }
  strcpy(res, "  movq  %rax, -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);
}

/* OPTIMIZADA POR GABRIEL
 * Esta funcion genera el codigo assembler correspondiente a la operacion logica AND.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_and_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  movq  -");
      sprintf(aux,"%d", (auxInstr->op1->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  movq  $");
    sprintf(aux,"%d", auxInstr->op1->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }
  if(!(auxInstr->op2->const_var)){
    if(auxInstr->op2->global){
      strcpy(res, "  andq _");
      strcat(res, auxInstr->op2->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  andq  -");
      sprintf(aux,"%d", (auxInstr->op2->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  andq  $");
    sprintf(aux,"%d", auxInstr->op2->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }
  strcpy(res, "  movq  %rax, -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);
}

/* OPTIMIZAR LAURY. VERIFICAR CONSTANTES
 * Esta funcion genera el codigo assembler correspondiente a la operacion aritmetica MOD.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_mod_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq  _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
  	  strcpy(res, "  movq -");
  	  sprintf(aux,"%d", (auxInstr->op1->offset)*8);
  	  strcat(res, aux);
  	  strcat(res, "(%rbp), %rax\n");
  	  fputs(res, asm_code);
    }
  }
  else{
  	strcpy(res, "  movq $");
	  sprintf(aux,"%d", (auxInstr->op1->valor));
	  strcat(res, aux);
	  strcat(res, ", %rax\n");
	  fputs(res, asm_code);
  }
  fputs("  cqto\n",asm_code);
  if(!(auxInstr->op2->const_var)){
    if(auxInstr->op2->global){
      strcpy(res, "  idivq  _");
      strcat(res, auxInstr->op2->nombre);
      strcat(res, "(%rip)\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  idivq -");
      sprintf(aux,"%d", (auxInstr->op2->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp)\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  movq $");
    sprintf(aux,"%d", (auxInstr->op2->valor));
    strcat(res, aux);
    strcat(res, ", %rbx\n");

  	strcpy(res, "  idivq %rbx\n");
		fputs(res, asm_code);
  }
  strcpy(res, "  movq %rdx, -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);
}

/* OPTIMIZAR LAURY. VERIFICAR CONSTANTES
 * Esta funcion genera el codigo assembler correspondiente a la operacion aritmetica DIVISION.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_div_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq  _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
  	  strcpy(res, "  movq  -");
  	  sprintf(aux,"%d", (auxInstr->op1->offset)*8);
  	  strcat(res, aux);
  	  strcat(res, "(%rbp), %rax\n");
  	  fputs(res, asm_code);
    }
  }
	else{
		strcpy(res, "  movq  $");
	  sprintf(aux,"%d", (auxInstr->op1->valor));
	  strcat(res, aux);
	  strcat(res, ", %rax\n");
	  fputs(res, asm_code);
  }
  if(!(auxInstr->op2->const_var)){
    if(auxInstr->op2->global){
      strcpy(res, "  idivq  _");
      strcat(res, auxInstr->op2->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  idivq  -");
      sprintf(aux,"%d", (auxInstr->op2->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
  	strcpy(res, "  idivq  $");
	  sprintf(aux,"%d", (auxInstr->op2->valor));
	  strcat(res, aux);
	  strcat(res, ", %rax\n");
	  fputs(res, asm_code);
  }
  strcpy(res, "  movq  %rax, -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);
}

/* OPTIMIZAR LAURY. VERIFICAR CONSTANTES
 * Esta funcion genera el codigo assembler correspondiente a la operacion aritmetica PRODUCTO
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void create_prod_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq  _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  movq  -");
      sprintf(aux,"%d", (auxInstr->op1->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
	}
	else{
	  strcpy(res, "  movq  $");
	  sprintf(aux,"%d", (auxInstr->op1->valor));
	  strcat(res, aux);
	  strcat(res, ", %rax\n");
	  fputs(res, asm_code);	
	}
	if(!(auxInstr->op2->const_var)){
    if(auxInstr->op2->global){
      strcpy(res, "  imulq  _");
      strcat(res, auxInstr->op2->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  imulq  -");
      sprintf(aux,"%d", (auxInstr->op2->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
  	strcpy(res, "  imulq  $");
	  sprintf(aux,"%d", (auxInstr->op2->valor));
	  strcat(res, aux);
	  strcat(res, ", %rax\n");
	  fputs(res, asm_code);
  }

  strcpy(res, "  movq  %rax, -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);
}

/* OPTIMIZAR LAURY. VERIFICAR CONSTANTES
 * Esta funcion genera el codigo assembler correspondiente a la operacion aritmetica unaria OPUESTO.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_opuesto_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq  _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  movq  -");
      sprintf(aux,"%d", (auxInstr->op1->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
  	strcpy(res, "  movq  $");
	  sprintf(aux,"%d", (auxInstr->op1->valor));
	  strcat(res, aux);
	  strcat(res, ", %rax\n");
	  fputs(res, asm_code);
  }
  strcpy(res, "  negq %rax\n");
  fputs(res, asm_code);

  strcpy(res, "  movq  %rax, -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);
}

/* OPTIMIZADA POR GABRIEL.
 * Esta funcion genera el codigo assembler correspondiente a la operacion aritmetica MENOR (<).
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_menor_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq  _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  movq  -");
      sprintf(aux,"%d", (auxInstr->op1->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  movq  $");
    sprintf(aux,"%d", auxInstr->op1->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }
  if(!(auxInstr->op2->const_var)){
    if(auxInstr->op2->global){
      strcpy(res, "  cmpq  _");
      strcat(res, auxInstr->op2->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  cmpq  -");
      sprintf(aux,"%d", (auxInstr->op2->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  cmpq  $");
    sprintf(aux,"%d", auxInstr->op2->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }
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

/* OPTIMIZAR LAURY. VERIFICAR CONSTANTES
 * Esta funcion genera el codigo assembler correspondiente a la operacion aritmetica MAYOR (>).
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_mayor_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq  _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  movq -");
      sprintf(aux,"%d", (auxInstr->op1->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
  	strcpy(res, "  movq $");
	  sprintf(aux,"%d", (auxInstr->op1->valor));
	  strcat(res, aux);
	  strcat(res, ", %rax\n");
	  fputs(res, asm_code);
  }
  if(!(auxInstr->op2->const_var)){
    if(auxInstr->op2->global){
      strcpy(res, "  cmpq  _");
      strcat(res, auxInstr->op2->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  cmpq  -");
      sprintf(aux,"%d", (auxInstr->op2->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else {
  	strcpy(res, "  cmpq $");
	  sprintf(aux,"%d", auxInstr->op2->valor);
	  strcat(res, aux);
    strcat(res, ", %rax\n");
	  fputs(res, asm_code);
  }
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

/* OPTIMIZADA POR GABRIEL
 * Esta funcion genera el codigo assembler correspondiente a la operacion aritmetica RESTA.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_sub_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq  _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  movq  -");
      sprintf(aux,"%d", (auxInstr->op1->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  movq  $");
    sprintf(aux,"%d", auxInstr->op1->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }
  if(!(auxInstr->op2->const_var)){
    if(auxInstr->op2->global){
      strcpy(res, "  subq  _");
      strcat(res, auxInstr->op2->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  subq  -");
      sprintf(aux,"%d", (auxInstr->op2->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  subq  $");
    sprintf(aux,"%d", auxInstr->op2->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }
  strcpy(res, "  movq  %rax, -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);
}

/* OPTIMIZADA POR GABRIEL.
 * Esta funcion genera el codigo assembler correspondiente a la operacion aritmetica SUMA.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_add_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq  _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  movq  -");
      sprintf(aux,"%d", (auxInstr->op1->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  movq  $");
    sprintf(aux,"%d", auxInstr->op1->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }
  if(!(auxInstr->op2->const_var)){
    if(auxInstr->op2->global){
      strcpy(res, "  addq  _");
      strcat(res, auxInstr->op2->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  addq  -");
      sprintf(aux,"%d", (auxInstr->op2->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  addq  $");
    sprintf(aux,"%d", auxInstr->op2->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }
  strcpy(res, "  movq  %rax, -");
  sprintf(aux,"%d", (auxInstr->res->offset)*8);
  strcat(res, aux);
  strcat(res, "(%rbp)\n");
  fputs(res, asm_code);
}

/* OPTIMIZADA POR GABRIEL.
 * Esta funcion genera el codigo assembler correspondiente a la operacion aritmetica IGUALDAD.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_equals_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq  _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  movq  -");
      sprintf(aux,"%d", (auxInstr->op1->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp), %rax\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  movq  $");
    sprintf(aux,"%d", auxInstr->op1->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }
  if(!(auxInstr->op2->const_var)){
    if(auxInstr->op2->global){
      strcpy(res, "  movq  _");
      strcat(res, auxInstr->op2->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  cmpq  %rax, -");
      sprintf(aux,"%d", (auxInstr->op2->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp)\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  cmpq  $");
    sprintf(aux,"%d", auxInstr->op2->valor);
    strcat(res, aux);
    strcat(res, ", %rax\n");
    fputs(res, asm_code);
  }

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

/* OPTIMIZADA POR GABRIEL.
 * Esta funcion genera el codigo assembler correspondiente a la operacion ASIGNACION.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_asignacion_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  int parametro = auxInstr->res->nParam;
  if(!(auxInstr->op1->const_var)){
    if(auxInstr->op1->global){
      strcpy(res, "  movq  %rax, _");
      strcat(res, auxInstr->op1->nombre);
      strcat(res, "(%rip), %rax\n");
      fputs(res, asm_code);
    }
    else{
      strcpy(res, "  movq  %rax, -");
      sprintf(aux,"%d", (auxInstr->res->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp)\n");
      fputs(res, asm_code);
    }
  }
  else{
    strcpy(res, "  movq  $");
    sprintf(aux,"%d", auxInstr->op1->valor);
    strcat(res, aux);
    if(auxInstr->res->global){
      strcat(res, ", _");
      strcat(res, auxInstr->res->nombre);
      strcat(res, "(%rip)\n");
    }
    else{
      strcat(res, ", -");
      sprintf(aux,"%d", (auxInstr->res->offset)*8);
      strcat(res, aux);
      strcat(res, "(%rbp)\n");   
    }
    fputs(res, asm_code);
  }
}

/*
 * Esta funcion genera el codigo assembler correspondiente a la invocacion de uan funcion.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_call_cp_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  char c[64];
  int parametro = auxInstr->res->nParam;
  if(sis == 1){
    strcpy(c, "  callq  ");
    strcat(c, auxInstr->op1->nombre);
    strcat(c, "\n");
    fputs(c, asm_code);
  }
  else{
    strcpy(c, "  callq  _");
    strcat(c, auxInstr->op1->nombre);
    strcat(c, "\n");
    fputs(c, asm_code);
  }
  if(auxInstr->op1->tipo != VOIDD){
    strcpy(c, "  movq %rax, -");
    sprintf(aux,"%d", (auxInstr->res->offset)*8);
    strcat(c, aux);
    strcat(c, "(%rbp)\n");
    fputs(c, asm_code);
  }
}

/* IDEM A LA ANTERIOR...ESTA DE GUSTO.
 * Esta funcion genera el codigo assembler correspondiente a la invocacion de uan funcion.
 * *auxInstr: Instruccion en formato codigo de tres direcciones.
 */
void crear_call_sp_instruccion(tresDir *auxInstr){
  char res[64];
  char aux[64];
  char c[64];
  int parametro = auxInstr->res->nParam;
  if(sis == 1){
    strcpy(c, "  callq ");
    strcat(c, auxInstr->op1->nombre);
    strcat(c, "\n");
    fputs(c, asm_code);
  }
  else{
    strcpy(c, "  callq _");
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