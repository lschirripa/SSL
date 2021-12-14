%{
	#include <string.h>
	#include<stdio.h>
    #include<stdlib.h>
	#include "sin.tab.h"
	extern void yyerror(char*);
	#define ERROR_LEXICO(mensaje) printf("[ERROR LEXICO] %s: %s\n", mensaje, yytext )
%}

DIGITO [0-9]
LETRA [a-zA-Z]

%%

[ \t\n]+               	;
"inicio"		{/*printf("se ha detectado una palabra reservada \n");*/return INICIO;};
"fin"			{/*printf("se ha detectado una palabra reservada \n");*/return FIN;};
"escribir"		{/*printf("se ha detectado una palabra reservada \n");*/return ESCRIBIR;};
"leer"			{/*printf("se ha detectado una palabra reservada \n");*/return LEER;};

{LETRA}({LETRA}|{DIGITO})*    {return IDENTIFICADOR;};
{DIGITO}+	       	          { yylval.num = atoi(yytext);return CONSTANTE;};
":="                       	  return ASIGNACION;
"+"                        	  return SUMA;
"-"                        	  return RESTA;
"("                           return PARENTESIS_A;
")"                        	  return PARENTESIS_C;
";"                        	  return PUNTOYCOMA;
","                        	  return COMA;
"//".*		       	;
. 		             	{ERROR_LEXICO("Caracter Invalido");};


%%



