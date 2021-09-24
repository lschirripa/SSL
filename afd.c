#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char s1[100];
    printf("ingrese una cadena \n");
    scanf("%s", s1);

    if (!verifica(s1))
        printf("La cadena que ingreso tiene caracteres invalidos \n");
    else

        if (EsPalabra(s1))
        printf("La cadena %s pertenece al lenguaje", s1);
    else
        printf("La cadena %s NO pertenece al lenguaje", s1);

    return 0;
}

int verifica(char *s1)
{
    unsigned i;
    for (i = 0; s1[i] != '\0'; i++)
        if (!(isdigit(s1[i]) || s1[i] == '+' || s1[i] == '-' || s1[i] == 'a' || s1[i] == 'b' || s1[i] == 'c' || s1[i] == 'd' || s1[i] == 'e' || s1[i] == 'f'))
            return 0;
    return 1;
}

int Columna(int c)
{
    switch (c)
    {
    case '+':
        return 0;
    case '-':
        return 0;
    case '1':
        return 1;
    case '2':
        return 1;
    case '3':
        return 1;
    case '4':
        return 1;
    case '5':
        return 1;
    case '6':
        return 1;
    case '7':
        return 1;
    case '8':
        return 1;
    case '9':
        return 1;
    case '0':
        return 1;
    default: // si es letra
        return 2;
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