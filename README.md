Bienvenido a TDS-2018
================

Este es un proyecto de implementacion de un compilador para el lenguaje TDS2018.

Asignatura: Talle de Diseño de Software.

Grupo:
    |-- Gaido Maria Laureana.
    |-- Gonzalez Gabriel.


Getting Started
---------------

Herramientas utilizadas:

# Yacc.
# Lex.

Lenguaje Utilizado: C

Estructura del proyecto

```
Compiladores
|-- readme.md
|-- compiler
`-- data
    |-- cod_assembler.c
    |-- cod_intermedio.c
    |-- constantes.h
    |-- errors.h
    |-- indexT.h
    |-- lib.h
    |-- string.h
    |-- tds-compiler
    |-- tds-lexico.l
    |-- tds-sintaxis.tab.c
    |-- tds-sintaxis.tab.h
    |-- tds-sintaxis.y
`-- tests
    |`-- lexico-sintacticos
    |`-- semanticos
    |`-- tests-finales
```

* comandos
>  ./compiler
>  Ejecuta el compilador.
>
>  gcc -o simple assembler.s data/libaux.c
>  linkea el codigo assembler generado por el compilador con la libreria que contiene los prints.
>
>  ./run_tests
>  Corre los tests de la carpeta tests

Pasos para compilar un programa.

>  Ejecuta el compilador con ./compiler.
>  Seleccione la opcion numero 1 (compilar programa) del menu principal.
>  Ingrese la ruta del archivo (debe tener extension .tds). Ej: miPrograma.tds si se encuentra en el directorio principal del compilador.
>  Si no se encuentra alli, debera ingresar la ruta de la forma: carpeta1/.../carpetaN/miPrograma.tds
>  Una vez generado el codigo assembler, debera ejecutar el siguiente comando: gcc -o XXX assembler.s data/libaux.c reemplazando XXX por el nombre que desee.
>  Ejecute el programa de la siguiente forma: ./XXX  donde XXX es el nombre ingresado anteriormente.
