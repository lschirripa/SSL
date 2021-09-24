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
    default: // es digito o letra
        return 1;
    }
}

int EsPalabra(const char *cadena)
{
    static int tt[4][3] =
        {
            {2, 1, 1},
            {3, 1, 1},
            {3, 1, 3},
            {3, 3, 3}};
    int e;          // estado actual
    unsigned int i; //recorre la cadena
    for (e = 0, i = 0; cadena[i] != '\0' && e != 3; i++)
        e = tt[e][Columna(cadena[i])];
    return e == 1;
}