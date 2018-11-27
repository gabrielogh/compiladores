%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>

#include "tds-sintaxis.tab.h"
#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"

void error(char *c);
int debugL, testType;
%}

%option noyywrap
%option yylineno

letra [a-zA-z]
entero [0-9]

%x COMENTARIO

%%

"{"   {BEGIN(COMENTARIO);}
<COMENTARIO>[^}\n]*         {}

<COMENTARIO>\n              {}
<COMENTARIO><<EOF>>         {}
<COMENTARIO>"}"             {BEGIN(INITIAL);}


main                         { yylval.i = yylineno;
                                if(debugL){
                                  printf("main encontrado en la linea: %d\n",yylineno);
                                }
                                return MAIN;}

extern                       { yylval.i = yylineno;
                                if(debugL){
                                  printf("extern encontrado en la linea: %d\n",yylineno);
                                }
                                return EXTERN;}

program                      { yylval.i = yylineno;
                                if(debugL){
                                  printf("program encontrado en la linea: %d\n",yylineno);
                                }
                                return PROGRAM;}

begin                        {  yylval.i = yylineno;
                                if(debugL){
                                  printf("begin encontrado en la linea: %d\n",yylineno);
                                }
                                return BEGINN;}

if                           {  yylval.i = yylineno;
                                if(debugL){
                                  printf("if encontrado en la linea: %d\n",yylineno);
                                }
                                return IF;}

else                         {  yylval.i = yylineno;
                                if(debugL){
                                  printf("else encontrado en la linea: %d\n",yylineno);
                                }
                                return ELSE;}

then                         {  yylval.i = yylineno;
                                if(debugL){
                                  printf("then encontrado en la linea: %d\n",yylineno);
                                }
                                return THEN;}

end                          {  yylval.i = yylineno;
                                if(debugL){
                                  printf("end encontrado en la linea: %d\n",yylineno);
                                }
                                return END;}

while                        {  yylval.i = yylineno;
                                if(debugL){
                                  printf("while encontrado en la linea: %d\n",yylineno);
                                }
                                return WHILE;}

true                         {  yylval.i = yylineno;
                                if(debugL){
                                  printf("true encontrado en la linea: %d\n",yylineno);
                                }
                                return TRUE;}

false                        {  yylval.i = yylineno;
                                if(debugL){
                                  printf("false encontrado en la linea: %d\n",yylineno);
                                }
                                return FALSE;}

void                         {  yylval.i = yylineno;
                                if(debugL){
                                  printf("void encontrado en la linea: %d\n",yylineno);
                                }
                                return VOID;}

bool                          { yylval.i = yylineno;
                                if(debugL){
                                  printf("bool encontrado en la linea: %d\n",yylineno);
                                }
                                return BOOL;
                               }

integer                       { yylval.i = yylineno;
                                if(debugL){
                                  printf("integer encontrado en la linea: %d\n",yylineno);
                                }
                                return INTEGER;
                               }


return                        { yylval.i = yylineno;
                                if(debugL){
                                  printf("return encontrado en la linea: %d\n",yylineno);
                                }
                                return RETURN;
                               }

"="                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("'=' encontrado en la linea: %d\n",yylineno);
                                }
                                return ASIGNACION;
                               }

"+"                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("'+' encontrado en la linea: %d\n",yylineno);
                                }
                                return SUMA;
                               }

"-"                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("'-' encontrado en la linea: %d\n",yylineno);
                                }
                                return RESTA;
                               }

"*"                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("'*' encontrado en la linea: %d\n",yylineno);
                                }
                                return PROD;
                               }

"/"                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("'/' encontrado en la linea: %d\n",yylineno);
                                }
                                return DIV;
                               }

"%"                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("'%%' encontrado en la linea: %d\n",yylineno);
                                }
                                return MOD;
                              }

"<"                           { yylval.i = yylineno;
                                if(debugL){
                                  printf("'<' encontrado en la linea: %d\n",yylineno);
                                }
                                return MENOR;
                              }

">"                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("'>' encontrado en la linea: %d\n",yylineno);
                                }
                                return MAYOR;
                              }

"=="                          { yylval.i = yylineno;
                                if(debugL){
                                  printf("'==' encontrado en la linea: %d\n",yylineno);
                                }
                                return IGUALDAD;
                              }
"<="                          { yylval.i = yylineno;
                                if(debugL){
                                  printf("'<=' encontrado en la linea: %d\n",yylineno);
                                }
                                return MENIGUAL;
                              }

">="                          { yylval.i = yylineno;
                                if(debugL){
                                  printf("'>=' encontrado en la linea: %d\n",yylineno);
                                }
                                return MAYIGUAL;
                              }

"&&"                          { yylval.i = yylineno;
                                if(debugL){
                                  printf("'&&' encontrado en la linea: %d\n",yylineno);
                                }
                                return AND;
                              }

"||"                          { yylval.i = yylineno;
                                if(debugL){
                                  printf("'||' encontrado en la linea: %d\n",yylineno);
                                }
                                return OR;
                              }

"!"                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("'!' encontrado en la linea: %d\n",yylineno);
                                }
                                return NOT;
                              }

"("                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("'(' encontrado en la linea: %d\n",yylineno);
                                }
                                return PARA;}

")"                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("')' encontrado en la linea: %d\n",yylineno);
                                }
                                return PARC;}

","                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("',' encontrado en la linea: %d\n",yylineno);
                                }
                                return COMA;}

";"                            { yylval.i = yylineno;
                                if(debugL){
                                  printf("';' encontrado en la linea: %d\n",yylineno);
                                }
                                return PCOMA;}

"//".*\n                      


{entero}+                     { yylval.i = atoi(yytext);
                                if(debugL){
                                  printf("INT encontrado: '%d' en la linea: %d\n",atoi(yytext),yylineno);
                                }
                                return INT;}


{letra}({letra}|{entero})*    { yylval.s=(char *) malloc(sizeof(yytext)*yyleng);
                                strcpy(yylval.s,yytext);
                                if(debugL){
                                  printf("ID encontrado: '%s' en la linea %d\n",yytext,yylineno);
                                }
                                return ID;}

(\n)+                          ; /* ignore all the rest */
[ \t]+                       /* ignore whitespace */;

.                             { yylval.s=(char *) malloc(sizeof(yytext)*yyleng);
                                strcpy(yylval.s,yytext);
                                error(yytext);
                               }

%%

void error(char *c){
    printf(KRED "   ERROR SINTACTICO ");
    printf(KNRM "%s%d","linea: ",yylineno);
    printf(KRED " ---%s---\n", c);
    printf(KNRM);
}

void yyerror(){
    printf("->");
    printf(KRED " ERROR SINTACTICO ");
    printf(KNRM "%s%d\n","en la linea: ",yylineno);
    exit(-1);
}

int countFiles(){
  int files=0;
  DIR * dirp;
  struct dirent * entry;

  dirp = opendir("asm");
  while ((entry = readdir(dirp)) != NULL) {
    if (entry->d_type == DT_REG) {
      files++;
    }
  }
  closedir(dirp);
  return files;
}

void delay(int number_of_seconds) { 
  // Converting time into milli_seconds 
  int milli_seconds = 1000 * number_of_seconds; 

  // Stroing start time 
  clock_t start_time = clock(); 

  // looping till required time is not acheived 
  while (clock() < start_time + milli_seconds) 
      ; 
} 

int main(int argc,char *argv[]){
  system("@cls||clear");
  debugL = 0;
  int option;
  char ruta[64];
  char nombre[64];
  char aux[32];
  char command[256];
  char continuar; //ASCII = 83(S), 115(s).
  printf("                  ----------------------------------------------------------------\n");
  printf("                  *         Bienveido al compilador del lenguaje TDS2018         *\n");
  printf("                  ----------------------------------------------------------------\n");
  printf("--MENU: 'digite el numero de opcion deseada'.\n");
  printf("1) Compilar programa.\n");
  printf("2) Correr Tests.\n");
  scanf("%d", &option);
  if(option == 1){
    printf("Para compilar su programa debera ingresar la ruta del mismo.\n");
    printf("Se recomienda situar el archivo (debe tener extension .tds) en el mismo directorio del compilador, EJ:\n");
    printf("miPrograma.tds  o  tests/miPrograma.tds\n");
    printf("Ingrese la ruta\n");
    scanf("%s", ruta);
  }
  else if(option == 2){
    system("sh run_tests");
  }

  if(strcmp(ruta, "") != 0){
    printf("\n");
    yyin = fopen(ruta,"r");
    yyparse();

    strcpy(nombre, "asm/program");
    sprintf(aux,"%d", countFiles()-1);
    strcat(nombre, aux);
    strcat(nombre, ".s");
    
    strcpy(command, "gcc -o programa ");
    strcat(command, nombre);
    strcat(command, " data/libaux.c");

    printf("Ejecutando programa:\n");
    system(command);
    system("./programa");
  }
	else{
    printf("Error: El nombre del archivo no es correcto\n");
  }
  printf("Desea compilar otro programa?  S/N \n");
  
  scanf("%c", &continuar);
  scanf("%c", &continuar);
  system("@cls||clear");
  if((continuar == 83) || (continuar == 115)){
    system("./compiler");
  }
}
