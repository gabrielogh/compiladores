//VARIABLES GLOBALES.
int treeSize, testType;

//COLORES
#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"
#define KGRN  "\x1B[32m"

//TIPOS DE ERRORES 100-199.
#define VAREXIST 100
#define FUNCEXIST 101
#define UNDECLAREDVAR 102
#define UNDEFINEDFUNC 103
#define SINTAX 104
#define WRONGLEVEL 105
#define WRONGTYPE 106
#define INVOCPARAMS 107
#define EVALERROR 108
#define WRONGTYPEPARAM 109
#define UNKNOW 999

//TOKENS 1-99.
#define INTEGERR 1
#define BEGINNN 2
#define ENDD 3
#define IFTHENN 4
#define IFTHENELSEE 5
#define EXTERNN 6
#define WHILEE 7
#define BOOLEAN 8
#define RETURNN 9
#define VOIDD 10
#define PROGRAMM 11
#define FALSEE 12
#define TRUEE 13
#define ASIGNACIONN 14
#define SUMAA 15
#define RESTAA 16
#define DIVV 17
#define PRODD 18
#define MODD 19
#define IGUALDADD 20
#define MENIGUALL 21
#define MAYIGUALL 22
#define MENORR 23
#define MAYORR 24
#define ANDD 25
#define ORR 26
#define NOTT 27
#define MAINN 28
#define PARAA 29
#define PARCC 30
#define PCOMAA 31
#define COMAA 32
#define IDD 33
#define INVOCC 34
#define PARENTESISS 35
#define CONSTANTEE 36
#define NONRET 37
#define STATEMENTS 38
#define INTT 39
#define BOOLL 40
#define PARAMETRO 41
#define NONRETT 42
#define VARR 43
#define INSERTLIST 44
#define INSERTFUNC 45
#define DECVAR 46
#define BLOCK 47
#define IGNORE 48
#define EMPTYBLOCK 49
#define BLOCKSINSTATEMENTS 50
#define BLOCKNULL 51

//CODIGO DE TRES DIRECCIONES. 200-299
#define JMP 200
#define MOV 201
#define CMP 202
#define CARGAR_PARAMS 203
#define IF_INSTRUCCION 204
#define IF_ELSE_INSTRUCCION 205
#define WHILE_INSTRUCCION 206
#define CALL 207
#define CALL_WITH_PARAMS 208
#define ASIGN_INSTRUCCION 209
#define CTE_INSTRUCCION 210
#define EQ_INSTRUCCION 211
#define ADD_INSTRUCCION 212
#define SUB_INSTRUCCION 213
#define MAY_INSTRUCCION 214
#define MEN_INSTRUCCION 215
#define NEG_INSTRUCCION 216
#define NOT_INSTRUCCION 217
#define OPUESTO_INSTRUCCION 218
#define PROD_INSTRUCCION 219
#define DIV_INSTRUCCION 220
#define MOD_INSTRUCCION 221
#define AND_INSTRUCCION 222
#define OR_INSTRUCCION 223
#define RETURN_INSTRUCCION 224
#define ELSE_INSTRUCCION 225
#define END_IF 226
#define END_ELSE 227
#define LABEL_WHILE_INSTRUCCION 228
#define LABEL_END_WHILE_INSTRUCCION 229
#define CARGAR_ACTUAL_PARAMS 230


