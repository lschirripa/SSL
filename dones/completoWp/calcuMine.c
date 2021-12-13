#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int columna1(char);
void automata1(char *);
int columna2(char);
void automata2(char *);
void error(void);
void resetContadores(int *, int *, int *);
int transformarAscii(char);
void aplicarSigno(int *, int *, int numerosDelCalculo[], char operaciones[]);
void aplicarSigno2(int *, int *, int numerosDelCalculo[], char operaciones[], char *);
void aplicarUltSigno(int *, int *, int numerosDelCalculo[], char operaciones[], int *, int *);
void debug(int *, int *, int *, int *, int *, char *, int numerosDelCalculo[], char operaciones[]);

int main()
{
    int numeroOpcion;
    char *cadenaPrincipal = malloc(50 * sizeof(char));
    printf("elija una opcion: \n1.SCANNER \n2.CALCULADORA\n");
    scanf("%d", &numeroOpcion);

    if (numeroOpcion == 1)
    {
        printf("ingrese una cadena\n");
        scanf("%s", cadenaPrincipal);
        automata1(cadenaPrincipal);
    }
    else if (numeroOpcion == 2)
    {
        printf("ingrese un calculo\n");
        scanf("%s", cadenaPrincipal);
        automata2(cadenaPrincipal);
    }
    else
    {
        printf("ERROR! debe ingresar solamente 1 o 2 para invocar al scanner o a la calculadora respectivamente\n");
        system("pause");
    }
}

void automata1(char *cadena)
{

    int tt[8][7] = {
        {3, 9, 1, 7, 7, 9, 9},
        {9, 9, 9, 2, 2, 9, 9},
        {2, 9, 9, 2, 2, 9, 0},
        {6, 4, 9, 9, 6, 9, 9},
        {5, 9, 9, 5, 5, 5, 9},
        {5, 9, 9, 5, 5, 5, 0},
        {6, 9, 9, 9, 6, 9, 0},
        {7, 9, 9, 7, 7, 9, 0},

    };
    int estado = 0;
    int i = 0;
    char caracter;
    int contadorDecimal = 0, contadorOctal = 0, contadorHexa = 0, contador1 = 0, contador2 = 0, contador3 = 0;
    caracter = cadena[i];
    int tamanioCadena = strlen(cadena);

    for (int y = 0; y <= (tamanioCadena); y++)
    {
        printf("\ntamanio cadena:%d\n", tamanioCadena);
        estado = tt[estado][columna1(caracter)];
        if (estado == 2)
        {
            contadorDecimal += 1;
            printf("1decimal");
        }
        else if (estado == 7)
        {
            contadorDecimal += 1;
            printf("1decimal");
        }
        else if (estado == 6)
        {
            contadorOctal += 1;
            printf("1octal");
        }
        else if (estado == 5)
        {
            contadorHexa += 1;
            printf("1hexa");
        }
        else if (estado == 9)
        {
            printf("Hubo un error lexico en la cadena\n");
            return;
        }
        else if (caracter == '&' || caracter == '\0')
        {
            if (contadorDecimal > 0)
            {
                contador1++;
                resetContadores(&contadorDecimal, &contadorOctal, &contadorHexa);
            }

            else if (contadorOctal > 0)
            {
                contador2++;
                resetContadores(&contadorDecimal, &contadorOctal, &contadorHexa);
            }
            else if (contadorHexa > 0)
            {
                contador3++;
                resetContadores(&contadorDecimal, &contadorOctal, &contadorHexa);
            }
        }

        caracter = cadena[++i];
    }

    printf("No hubo ningun error lexico y se reconocieron:\n");
    printf("%d numeros decimales\n", contador1);
    printf("%d numeros octales\n", contador2);
    printf("%d numeros hexadecimales\n", contador3);
    system("pause");
    return;
}

int columna1(char caracter)
{
    switch (caracter)
    {
    case '+':
        return 2;
        break;
    case '-':
        return 2;
        break;
    case '0':
        return 0;
        break;
    case '1':
        return 4;
        break;
    case '2':
        return 4;
        break;
    case '3':
        return 4;
        break;
    case '4':
        return 4;
        break;
    case '5':
        return 4;
        break;
    case '6':
        return 4;
        break;
    case '7':
        return 4;
        break;
    case '8':
        return 3;
        break;
    case '9':
        return 3;
        break;
    case 'A':
        return 5;
        break;
    case 'B':
        return 5;
        break;
    case 'C':
        return 5;
        break;
    case 'D':
        return 5;
        break;
    case 'E':
        return 5;
        break;
    case 'F':
        return 5;
        break;
    case 'x':
        return 1;
        break;
    case '&':
        return 6;
        break;
    default:
        return 9;
        break;
    }
}

void resetContadores(int *contadorDecimal, int *contadorOctal, int *contadorHexa)
{
    *contadorDecimal = 0;
    *contadorOctal = 0;
    *contadorHexa = 0;
}

void automata2(char *cadena)
{
    int tt[4][4] = {{1, 3, 3, 3},
                    {1, 2, 2, 2},
                    {1, 3, 3, 3},
                    {3, 3, 3, 3}};

    int estado = 0;
    int i = 0;
    char caracter;
    int numerosDelCalculo[50];
    int cantidadNumeros = 0;
    char operaciones[49];
    int cantOperacionesOriginal = 0;
    int contador = 0;
    int resultado = 0;
    int j = 0, index = 0;
    int proxSigno = 1;

    for (j = 0; j < 30; j++)
        numerosDelCalculo[j] = 0;

    caracter = cadena[i];

    do
    {
        estado = tt[estado][columna2(caracter)];

        if (estado == 1)
        {
            numerosDelCalculo[cantidadNumeros] = numerosDelCalculo[cantidadNumeros] * 10 + transformarAscii(caracter);
        }
        else if (estado == 2)
        {
            if (caracter == '-')
            {
                aplicarSigno(&cantidadNumeros, &proxSigno, numerosDelCalculo, operaciones);
            }
            else
            {
                aplicarSigno2(&cantidadNumeros, &proxSigno, numerosDelCalculo, operaciones, &caracter);
            }
        }
        else if (estado == 3)
        {
            printf("error lexico en la cadena ingresada\n");
            return;
        }
        caracter = cadena[++i];
    } while (caracter != '\0');

    if (caracter == '\0')
    {

        aplicarUltSigno(&cantidadNumeros, &proxSigno, numerosDelCalculo, operaciones, &j, &cantOperacionesOriginal);
        //       debug(&cantOperacionesOriginal, &cantidadNumeros, &j, &index, &contador, &caracter, numerosDelCalculo, operaciones);

        do
        {
            j = 0;
            while (operaciones[j] != '*' && contador < cantOperacionesOriginal)
            {
                j++;
                contador++; //CAMBIO A LO ULTIMO
            }
            printf("\n $$$$$$$$$$$   WHILE OPERACIONES[i] != *  $$$$$$$$$$$ \n");
            //            debug(&cantOperacionesOriginal, &cantidadNumeros, &j, &index, &contador, &caracter, numerosDelCalculo, operaciones);

            if (operaciones[j] == '*')
            {
                index = j;
                while (j < (cantidadNumeros - 2))
                {
                    operaciones[j] = operaciones[j + 1];
                    j++;
                }
                j = index;
                numerosDelCalculo[j] = numerosDelCalculo[j] * numerosDelCalculo[j + 1];
                j++;
                while (j < (cantidadNumeros - 1))
                {
                    numerosDelCalculo[j] = numerosDelCalculo[j + 1];
                    j++;
                }
                cantidadNumeros = cantidadNumeros - 1;
                printf("\n $$$$$$$$$$$   ENCONTRO UN *  $$$$$$$$$$$ \n");
                //              debug(&cantOperacionesOriginal, &cantidadNumeros, &j, &index, &contador, &caracter, numerosDelCalculo, operaciones);
            }

            contador++;
        } while (contador < cantOperacionesOriginal);
        j = 0;
        resultado = numerosDelCalculo[0];
        while (j < (cantidadNumeros - 1))
        {
            resultado = resultado + numerosDelCalculo[j + 1];
            j++;
        }
        printf("Resultado = %d\n", resultado);
    }
}

int columna2(char caracter)
{
    switch (caracter)
    {
    case '+':
        return 1;
        break;
    case '-':
        return 2;
        break;
    case '*':
        return 3;
        break;
    case '0':
        return 0;
        break;
    case '1':
        return 0;
        break;
    case '2':
        return 0;
        break;
    case '3':
        return 0;
        break;
    case '4':
        return 0;
        break;
    case '5':
        return 0;
        break;
    case '6':
        return 0;
        break;
    case '7':
        return 0;
        break;
    case '8':
        return 0;
        break;
    case '9':
        return 0;
        break;
    default:
        return 4;
        break;
    }
}

int transformarAscii(char caracter)
{
    return (caracter - '0');
}

void debug(int *cantOperacionesOriginal, int *cantidadNumeros, int *j, int *index, int *contador, char *caracter, int numerosDelCalculo[], char operaciones[])
{

    printf("\n cantidadDeOperacionesOriginal: %d \n", *cantOperacionesOriginal);
    printf("\n cantidadNumeros: %d \n", *cantidadNumeros);
    printf("\n j = %d \n", j);
    printf("\n index = %d \n", *index);
    printf("\n contador = %d \n", *contador);
    printf("caracter: %c \n", *caracter);
    for (int i = 0; i < *cantidadNumeros; i++)
    {
        printf("numerosDelCalculo[%d]: %d \n", i, numerosDelCalculo[i]);
    }
    for (int i = 0; i < *cantidadNumeros; i++)
    {
        printf("operaciones[%d]: %c \n", i, operaciones[i]);
    }
}

void aplicarSigno(int *cantidadNumeros, int *proxSigno, int numerosDelCalculo[*cantidadNumeros], char operaciones[*cantidadNumeros])
{
    numerosDelCalculo[*cantidadNumeros] = numerosDelCalculo[*cantidadNumeros] * (*proxSigno);
    *proxSigno = -1;
    operaciones[*cantidadNumeros] = '+';
    *cantidadNumeros += 1;
}

void aplicarSigno2(int *cantidadNumeros, int *proxSigno, int numerosDelCalculo[*cantidadNumeros], char operaciones[*cantidadNumeros], char *caracter)
{
    numerosDelCalculo[*cantidadNumeros] = numerosDelCalculo[*cantidadNumeros] * (*proxSigno);
    *proxSigno = 1;
    operaciones[*cantidadNumeros] = *caracter;
    *cantidadNumeros += 1;
}

void aplicarUltSigno(int *cantidadNumeros, int *proxSigno, int numerosDelCalculo[*cantidadNumeros], char operaciones[*cantidadNumeros], int *j, int *cantOperacionesOriginal)
{
    numerosDelCalculo[*cantidadNumeros] = numerosDelCalculo[*cantidadNumeros] * *proxSigno;
    *cantidadNumeros += 1;
    *j = 0;
    *cantOperacionesOriginal = *cantidadNumeros - 1;
}