%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h> 

#include "calc-sintaxis.tab.h"
#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"

void error(char *c);
int debugL;
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
    //system("@cls||clear");
    debugL = 0;
	++argv,--argc;
	if (argc > 0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;
	yyparse();

}
