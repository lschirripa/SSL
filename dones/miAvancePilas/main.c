#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "pila.c"
char contenedor[100];
int indexContenedor = 0;

int main()
{
    Pila p;
    inicpila(&p);
    /*
    push(&p, 5);
    push(&p, 6);
    push(&p, 7);
    push(&p, 8);
    mostrar(&p);
    */

    char input[30] = {0};
    int index = 0;
    printf("Ingrese calculo > ");
    scanf("%s", &input);

    for (int i = 0; i >= strlen(input); i++)
    {
        ejecutarTransicion(&p, input[index]);
    }
}

int reportarError(error)
{
    printf("%s", error);
    return 1;
};

enum simbolos
{
    NUMERO,
    MAS,
    MENOS,
    POR
};

char determinarSimbolo(char lectura)
{
    switch (lectura)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return NUMERO;
    case '+':
        return MAS;
    case '-':
        return MENOS;
    case '*':
        return POR;
    default:
        reportarError("Input invalido");
    }
};

void ejecutarTransicion(Pila *p, char lectura)
{
    if (determinarSimbolo(lectura) == NUMERO)
    {
        contenedor[indexContenedor] = lectura;
        indexContenedor++;
        if (!pilavacia(&p))
        {
            contenedor[indexContenedor] = pop(&p);
            indexContenedor++;
        }
    }
    else
    {
        if (pilavacia(&p))
            push(&p, lectura);
        else
            reportarError("Calculo invalido");
    }

    calcular();
};

void calcular();
{
    for (int i = 0;; i++)
};
