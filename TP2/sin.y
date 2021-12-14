%{
    #include <string.h>
	  #include<stdio.h>
    #include<stdlib.h>
    extern int yylex(void);
    extern void yyerror(char*);
    extern int yyleng;
    int lineNumber=0;
    void errorMaxCaracteres();


%}


%union{
   char* cadena;
   int num;
} 

%token INICIO FIN SUMA RESTA ASIGNACION PARENTESIS_A PARENTESIS_C PUNTOYCOMA LEER ESCRIBIR COMA
%token <cadena> IDENTIFICADOR
%token <num> CONSTANTE

%start startProgram

%%

startProgram:       IDENTIFICADOR {lineNumber++;yyerror("el programa debe comenzar con la palabra 'inicio'")} | 
                    CONSTANTE {lineNumber++;yyerror("el programa debe comenzar con la palabra 'inicio'")} | 
                    INICIO {lineNumber++;} sentencias   FIN {printf("compilacion exitosa");lineNumber++;};

sentencias:        	sentencias sentencia {lineNumber++;} | sentencia {lineNumber++;} ;

sentencia:         	LEER PARENTESIS_A listaDeIds PARENTESIS_C PUNTOYCOMA| ESCRIBIR PARENTESIS_A listaDeExpresiones PARENTESIS_C PUNTOYCOMA | IDENTIFICADOR {errorMaxCaracteres();} ASIGNACION expresion PUNTOYCOMA;

listaDeExpresiones:	expresion COMA listaDeExpresiones | expresion;

listaDeIds:		    IDENTIFICADOR COMA listaDeIds | IDENTIFICADOR;

expresion:   		primaria | expresion operador primaria;

primaria:           IDENTIFICADOR | CONSTANTE {if ($<num>1 > 100) yyerror("Las constantes no deben ser mayores a 100");} | PARENTESIS_A expresion PARENTESIS_C;

operador:           SUMA | RESTA;

%%
int main() {
  yyparse();
}

int yywrap()  {
  return 1;  
}

void yyerror (char *s){
printf ("Error en la linea %d: %s\n",lineNumber,s);
lineNumber++;
}

void errorMaxCaracteres(){
  if(yyleng>32) {yyerror("El identificador posee mas de 32 caracteres");} else {printf("identificador detectado \n");lineNumber++;}
}

