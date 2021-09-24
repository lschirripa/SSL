#include <stdio.h>
#include <string.h>

int main()
{
    int a;
    char b[50];
    char c[100];
    
    printf("ingrese un entero: \n ");
    scanf("%i", &a);
    fflush(stdin);
    printf("ingrese un texto: \n ");
    scanf("%s", b);
    fflush(stdin);
    printf("ingrese un texto con espacios: \n ");
    gets(c);

    printf("\n el num que ingresaste es: %i", a);
    printf("\n el texto que ingresaste es: %s", b);
    printf("\n el texto con espacios que ingresaste es: ");

    puts(c);

    return 0;
}