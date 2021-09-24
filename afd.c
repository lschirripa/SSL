#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char s1[50] = "";
    printf("ingrese una cadena \n");
    scanf("%s", s1);

    if (EsPalabra(s1))
        printf("La cadena s1 pertenece al lenguaje");
    else
        printf("La cadena s1 no pertenece al lenguaje");

    return 0;
}

int Columna(int c)
{
    switch (c)
    {
    case '+':
        return 2;
    case '-':
        return 2;
    case '1':
        return 2;
    case '2':
        return 2;
    case '3':
        return 2;
    case '4':
        return 2;
    case '5':
        return 2;
    case '6':
        return 2;
    case '7':
        return 2;
    case '8':
        return 2;
    case '9':
        return 2;
    case '0':
        return 2;
    case '0x':
        return 2;
    }
}

int EsPalabra(const char *cadena)
{
    static int tt[7][4] =
        {
            {5, 4, 2, 6},
            {3, 8, 8, 8},
            {3, 8, 8, 8},
            {4, 8, 8, 8},
            {5, 5, 8, 8},
            {7, 8, 8, 8},
            {7, 8, 8, 8}};
    int e;          // estado actual
    unsigned int i; //recorre la cadena
    for (e = 0, i = 0; cadena[i] != '\0' && e != 8; i++)
        e = tt[e][Columna(cadena[i])];
    return e == 2;
}

// int inicio = 1;
// int acepta = 3, acepta2 = 4, acepta3 = 5, acepta4 = 7;
// int noacepta = 6, noacepta2 = 2;
// int actual = inicio;
// int longitud = 0;
// char palabra[100];

// int fin = 0;
// int contador = 0;

// printf("ingrese la cadena: ");
// scanf("%s", palabra);

// while (fin == 0)
// {

// };