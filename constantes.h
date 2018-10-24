//VARIABLES GLOBALES.
int treeSize;

//COLORES
#define KRED  "\x1B[31m"
#define KNRM  "\x1B[0m"
#define KGRN  "\x1B[32m"

//TIPOS DE ERRORES.
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

//TOKENS.
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