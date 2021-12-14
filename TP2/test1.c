#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *cad;
    cad = malloc(sizeof(char) * 128);

    printf("introduce la cadena \n");
    fgets(cad, 128, stdin);
    int len = strlen(cad) - 1;
    printf("la cantidad es %d \n", len);
    maximosCaracteres(len);
}

int maximosCaracteres(len)
{

    if (len > 32)
    {
        printf("Error sintactico: La longitud maxima de los identificadores es de 32 caracteres");
    }
    else
    {
        printf("buena bro");
    }
}

/*
int yyerror(void){
	printf("Error léxico: caracter inválido.")
	exit(-1);
}


int maximosCaracteres(char *cad){

	if strlen(cad) > 32{
	printf("Error sintactico: La longitud maxima de los identificadores es de 32 caracteres");
    exit(-1);

}
}

*/
