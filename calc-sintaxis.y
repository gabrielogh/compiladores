%{
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cod_intermedio.h"

extern int yylineno;

%}
 
%union { int i; char *s; struct strings *st; struct nodes *n; struct nodeParams *np; struct Formalparams *pl; struct actualParams *ap;struct stacks *stk;}
 
%token<i> INT
%token<st> ID

%token<i> INTEGER
%token<i> BEGINN
%token<i> END
%token<i> EXTERN
%token<i> IF
%token<i> THEN
%token<i> ELSE
%token<i> WHILE
%token<i> BOOL
%token<i> RETURN
%token<i> VOID
%token<i> PROGRAM
%token<i> FALSE
%token<i> TRUE
%token<i> ASIGNACION
%token<i> SUMA
%token<i> RESTA
%token<i> DIV
%token<i> PROD
%token<i> MOD
%token<i> IGUALDAD
%token<i> MENIGUAL
%token<i> MAYIGUAL
%token<i> MENOR
%token<i> MAYOR
%token<i> AND
%token<i> OR
%token<i> NOT
%token<i> MAIN
%token<i> PARA
%token<i> PARC
%token<i> PCOMA
%token<i> COMA

%type<i> dec_var
%type<i> dec_vars
%type<n> expr
%type<ap> expr_list
%type<i> dec_method
%type<i> dec_methods
%type<n> block
%type<n> block_type
%type<n> block_def
%type<n> statement
%type<n> statements
%type<n> method_call
%type<pl> param_list
%type<n> literal
%type<i> type
%type<i> integer
%type<i> bool

%type<n> main
%type<n> program_block


%nonassoc ASIGNACION IGUALDAD MAYOR MENOR MENIGUAL MAYIGUAL
%left AND OR SUMA RESTA PROD DIV MOD
%right NEG

 
%%

prog: {init();} PROGRAM BEGINN program_block END {  //printIndexList();
                                                    //printStack();
                                                    printf("Iniciando chequeo Sintactico...\n");
                                                    if(noErrors()){
                                                      printf(KGRN "%s\n", "Chequeo Sintactico satisfactorio. "); printf(KNRM);
                                                      if(testType == 1){
                                                        printf("Iniciando chequeo Semantico...\n");
                                                        checkFunctions(inicial);
                                                      }
                                                      if(noErrors() && (testType == 1)){
                                                        printf(KGRN "%s\n", "Chequeo Semantico satisfactorio. "); printf(KNRM);
                                                        printf(KGRN "%s\n", "Generando codigo intermedio.... "); printf(KNRM);
                                                        generar_codigo();

                                                      }
                                                      else if (!noErrors() && (testType == 1)){
                                                      printf(KRED "%s\n", "TODO MAL, TU CODIGO NO SIRVE, TIENE ERRORES SEMANTICOS: "); printf(KNRM);
                                                      printErrors();
                                                      }
                                                    }
                                                    else{
                                                      printf(KRED "%s\n", "TODO MAL, TU CODIGO NO SIRVE, TIENE ERRORES SINTATICOS: "); printf(KNRM);
                                                      printErrors();
                                                    }

                                                    printf("Tamaño del arbol antes de eliminar: %d\n", treeSize);
                                                    deleteFuncitonBlocks();
                                                    printf("Tamaño del arbol luego de eliminar: %d\n", treeSize);
                                                 }
;

program_block: main                              {insertar_funcion(crearDataStack(toString("main"), VOIDD, -1, INSERTFUNC, yylineno, $1, NULL, true)); $$ = $1;} 
             | dec_vars PCOMA dec_methods main   {insertar_funcion(crearDataStack(toString("main"), VOIDD, -1, INSERTFUNC, yylineno, $4, NULL, true)); $$ = $4;}
             | dec_vars PCOMA main               {insertar_funcion(crearDataStack(toString("main"), VOIDD, -1, INSERTFUNC, yylineno, $3, NULL, true)); $$ = $3;} 
             | dec_methods main                  {insertar_funcion(crearDataStack(toString("main"), VOIDD, -1, INSERTFUNC, yylineno, $2, NULL, true)); $$ = $2;}
;

main: VOID MAIN PARA PARC block                  {$$ = $5;}

dec_vars : dec_var                               {}
         | dec_vars PCOMA dec_var                {}
;


dec_var: type ID                                 {insertar(crearDataStack(getNombre($2), $1, 0, VARR, yylineno, NULL, NULL, false));}

       | dec_var COMA ID                         {insertar(crearDataStack(getNombre($3), lastType(), 0, VARR, yylineno, NULL, NULL, false));} 
;

dec_methods: dec_method                              {}
           | dec_methods dec_method                  {}
;

dec_method: type ID PARA param_list PARC block_type  {insertar_funcion(crearDataStack(getNombre($2), $1, -1, INSERTFUNC, yylineno, $6, fstParam, true));cerrar_nivel(); resetParams();}

          | VOID ID PARA param_list PARC block_type  {insertar_funcion(crearDataStack(getNombre($2), VOIDD, -1, INSERTFUNC, yylineno, $6, fstParam, true));cerrar_nivel(); resetParams();}

          | type ID PARA PARC block_type             {insertar_funcion(crearDataStack(getNombre($2), $1, -1, INSERTFUNC, yylineno, $5, NULL, true));}

          | VOID ID PARA PARC block_type             {insertar_funcion(crearDataStack(getNombre($2), VOIDD, -1, INSERTFUNC, yylineno, $5, NULL, true));}
;

param_list: type ID                     { crear_nivel();
                                          insertar(crearDataStack(getNombre($2), $1, -1, PARAMETRO, yylineno, NULL, NULL, false));
                                          $$ = getFormalParams();
                                        }
          | param_list COMA type ID     { insertar(crearDataStack(getNombre($4), $3, -1, PARAMETRO, yylineno, NULL, NULL, false));
                                          $$ = $1;
                                        }
;

block_type: block                                   {  $$=$1;} 
          | EXTERN PCOMA                            {  $$ = createNode(createNodeParam(toString("BLOCKNULL"), -1, -1, -1, BLOCKNULL, NULL, NULL, NULL, false, NULL, yylineno));} 
;

block:{crear_nivel();} block_def                    { cerrar_nivel();
                                                      $$ = createNode(createNodeParam(toString("BLOCK"), 0, BLOCK, NONRETT, BLOCK, $2, NULL, NULL, false, NULL, yylineno));
                                                    } 
;

block_def: BEGINN END                               {$$ = createNode(createNodeParam(toString("EMPTYBLOCK"), -1, -1, -1, EMPTYBLOCK, NULL, NULL, NULL, false, NULL, yylineno));} 
         | BEGINN dec_vars PCOMA END                {$$ = createNode(createNodeParam(toString("BLOCKSINSTATEMENTS"), -1, -1, -1, BLOCKSINSTATEMENTS, NULL, NULL, NULL, false, NULL, yylineno));} 
         | BEGINN statements END                    {$$ = $2;} 
         | BEGINN dec_vars PCOMA statements END     {$$ = $4;} 
;

statements: statement                               { $$ = $1;}
          | statements statement                    { $$ = createNode(createNodeParam(toString("STATEMENTS"), 0, UNKNOW, NONRETT, STATEMENTS, $1, $2, NULL, false, NULL, yylineno));}
;

statement: ID ASIGNACION expr PCOMA                     { nodeParam *node = createNodeParam(toString("ASIGNACIONN"), 0, UNKNOW, NONRET, ASIGNACIONN, $3, createNode(createNodeParam(getNombre($1), 0, 0, NONRETT, VARR, NULL, NULL, NULL, false, NULL, yylineno)), NULL, false, NULL,  yylineno);
                                                          $$ = createNode(node);
                                                        } 
         | method_call PCOMA                            { $$ = $1;}

         | IF PARA expr PARC THEN block                 { $$ = createNode(createNodeParam(toString("IFTHEN"), 0, UNKNOW, NONRETT, IFTHENN, $3, $6, NULL, false, NULL, yylineno));}

         | IF PARA expr PARC THEN block ELSE block      { $$ = createNode(createNodeParam(toString("IFTHENELSE"), 0, UNKNOW, NONRETT, IFTHENELSEE, $3, $6, $8, false, NULL, yylineno));}

         | WHILE expr block                             { $$ = createNode(createNodeParam(toString("WHILE"), 0, UNKNOW, NONRETT, WHILEE, $2, $3, NULL, false, NULL, yylineno));}

         | RETURN expr PCOMA                            { $$ = createNode(createNodeParam(toString("RETURN"), 0, UNKNOW, getTipo(getNodeData($2)), RETURNN, $2, NULL, NULL, false, NULL, yylineno));} 

         | RETURN PCOMA                                 { $$ = createNode(createNodeParam(toString("RETURN"), 0, UNKNOW, VOIDD, RETURNN, NULL, NULL, NULL, false, NULL, yylineno));}

         | PCOMA                                        { $$ = createNode(createNodeParam(toString("PCOMA"), -1, -1, -1, PCOMA, NULL, NULL, NULL, false, NULL, yylineno));} 

         | block                                        { $$ = $1;}
;


type: INTEGER                           { $$ = INTEGERR;}
    | BOOL                              { $$ = BOOLEAN;}
;


method_call: ID PARA PARC               { data_stack *datas = buscar_func(getNombre($1));
                                          if(datas == NULL){
                                            printNodeError(createError(yylineno, UNDEFINEDFUNC));
                                            exit(0);
                                          }
                                          data_gen *d = datas->data;
                                          $$ = createNode(createNodeParam(getNombre($1), 0, d->tipo, 0, INVOCC, NULL, NULL, NULL, true, NULL, yylineno));
                                        }

           | ID PARA expr_list PARC     { data_stack *datas = buscar_func(getNombre($1));
                                          if(datas == NULL){
                                            printNodeError(createError(yylineno, UNDEFINEDFUNC));
                                            exit(0);
                                          }
                                          data_gen *d = datas->data;
                                          $$ = createNode(createNodeParam(getNombre($1), 0, d->tipo, 0, INVOCC, NULL, NULL, NULL, true, $3, yylineno));
                                        } 
;

expr_list: expr                         { paramList *param = (paramList *) malloc(sizeof(paramList)); newCall(param, $1); $$ = param;} 
         | expr_list COMA expr          { newCall($1, $3); $$ = $1;} 
;

expr:  ID                         { $$ = createNode(createNodeParam(getNombre($1), 0, 0, NONRETT, VARR, NULL, NULL, NULL, false, NULL, yylineno));} 

     | method_call                { $$ = $1;} 
     
     | literal                    { $$ = $1;} 

     | expr SUMA expr             { $$ = createNode(createNodeParam(toString("SUMA"), 0, INTEGERR, NONRETT, SUMAA,$1, $3, NULL, false, NULL, yylineno));}

     | expr RESTA expr            { $$ = createNode(createNodeParam(toString("RESTA"), 0, INTEGERR, NONRETT, RESTAA, $1, $3, NULL, false, NULL, yylineno));}

     | expr PROD expr             { $$ = createNode(createNodeParam(toString("PROD"), 0, INTEGERR, NONRETT, PRODD, $1, $3, NULL, false, NULL, yylineno));}

     | expr DIV expr              { $$ = createNode(createNodeParam(toString("DIV"), 0, INTEGERR, NONRETT, DIVV, $1, $3, NULL, false, NULL, yylineno));}

     | expr MOD expr              { $$ = createNode(createNodeParam(toString("MOD"), 0, INTEGERR, NONRETT, MODD, $1, $3, NULL, false, NULL, yylineno));}

     | expr MAYOR expr            { $$ = createNode(createNodeParam(toString("MAYOR"), 0, BOOLEAN, NONRETT, MAYORR, $1, $3, NULL, false, NULL, yylineno));}

     | expr MENOR expr            { $$ = createNode(createNodeParam(toString("MENOR"), 0, BOOLEAN, NONRETT, MENORR, $1, $3, NULL, false, NULL, yylineno));}

     | expr IGUALDAD expr         { $$ = createNode(createNodeParam(toString("IGUALDAD"), 0, BOOLEAN, NONRETT, IGUALDADD, $1, $3, NULL, false, NULL, yylineno));}

     | expr MENIGUAL expr         { $$ = createNode(createNodeParam(toString("MENIGUAL"), 0, BOOLEAN, NONRETT, MENIGUALL, $1, $3, NULL, false, NULL, yylineno));}

     | expr MAYIGUAL expr         { $$ = createNode(createNodeParam(toString("MAYIGUAL"), 0, BOOLEAN, NONRETT, MAYIGUALL, $1, $3, NULL, false, NULL, yylineno));}

     | expr AND expr              { $$ = createNode(createNodeParam(toString("AND"), 0, BOOLEAN, NONRETT, ANDD, $1, $3, NULL, false, NULL, yylineno));}

     | expr OR expr               { $$ = createNode(createNodeParam(toString("OR"), 0, BOOLEAN, NONRETT, ORR, $1, $3, NULL, false, NULL, yylineno));}

     | RESTA expr %prec NEG       { $$ = createNode(createNodeParam(toString("OPUESTO"), 0, INTEGERR, NONRETT, RESTAA, $2, NULL, NULL, false, NULL, yylineno));}

     | NOT expr   %prec NEG       { $$ = createNode(createNodeParam(toString("NOT"), 0, BOOLEAN, NONRETT, NOTT, $2, NULL, NULL, false, NULL, yylineno));}

     | PARA expr PARC             { $$ = $2;} 
;

literal: integer  { $$ = createNode( createNodeParam(toString("int"), $1, INTEGERR, NONRETT, CONSTANTEE, NULL, NULL, NULL, false, NULL, yylineno));}

       | bool     { $$ = createNode(createNodeParam(toString("bool"), $1, BOOLEAN, NONRETT, CONSTANTEE, NULL, NULL, NULL, false, NULL, yylineno));}
;

integer: INT  {$$ = $1;}
;


bool: TRUE   {$$ = 1;}
    | FALSE  {$$ = 0;}
;

%%