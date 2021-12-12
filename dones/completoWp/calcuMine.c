#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int columna1(char);
void automata1(char *);
int columna2(char);
void automata2(char *);
void error(void);
int transformarAscii(char);

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
        // automata1(cadenaPrincipal);
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
                numerosDelCalculo[cantidadNumeros] = numerosDelCalculo[cantidadNumeros] * proxSigno;
                proxSigno = -1;
                operaciones[cantidadNumeros] = '+';
                cantidadNumeros += 1;
            }
            else
            {
                numerosDelCalculo[cantidadNumeros] = numerosDelCalculo[cantidadNumeros] * proxSigno;
                proxSigno = 1;
                operaciones[cantidadNumeros] = caracter;
                cantidadNumeros += 1;
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
        numerosDelCalculo[cantidadNumeros] = numerosDelCalculo[cantidadNumeros] * proxSigno;
        cantidadNumeros += 1;
        j = 0;
        cantOperacionesOriginal = cantidadNumeros - 1;

        printf("caracter: %c \n", caracter);
        for (int i = 0; i < cantidadNumeros; i++)
        {
            printf("numerosDelCalculo[%d]: %d \n", i, numerosDelCalculo[i]);
        }
        for (int i = 0; i < cantidadNumeros; i++)
        {
            printf("operaciones[%d]: %c \n", i, operaciones[i]);
        }
        printf("\n cantidadDeOperacionesOriginal: %d \n", cantOperacionesOriginal);
        printf("\n cantidadNumeros: %d \n", cantidadNumeros);
        printf("\n j = %d \n", j);
        printf("\n index = %d \n", index);
        printf("\n contador = %d \n", contador);

        do
        {
            j = 0;
            while (operaciones[j] != '*' && contador < cantOperacionesOriginal)
            {
                j++;
                contador++; //CAMBIO A LO ULTIMO
            }
            printf("\n $$$$$$$$$$$   WHILE OPERACIONES[i] != *  $$$$$$$$$$$ \n");
            printf("\n cantidadDeOperacionesOriginal: %d \n", cantOperacionesOriginal);
            printf("\n cantidadNumeros: %d \n", cantidadNumeros);
            printf("\n j = %d \n", j);
            printf("\n index = %d \n", index);
            printf("\n contador = %d \n", contador);
            printf("caracter: %c \n", caracter);
            for (int i = 0; i < cantidadNumeros; i++)
            {
                printf("numerosDelCalculo[%d]: %d \n", i, numerosDelCalculo[i]);
            }
            for (int i = 0; i < cantidadNumeros; i++)
            {
                printf("operaciones[%d]: %c \n", i, operaciones[i]);
            }

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
                printf("\n cantidadDeOperacionesOriginal: %d \n", cantOperacionesOriginal);
                printf("\n cantidadNumeros: %d \n", cantidadNumeros);
                printf("\n j = %d \n", j);
                printf("\n index = %d \n", index);
                printf("\n contador = %d \n", contador);
                printf("caracter: %c \n", caracter);
                for (int i = 0; i < cantidadNumeros; i++)
                {
                    printf("numerosDelCalculo[%d]: %d \n", i, numerosDelCalculo[i]);
                }
                for (int i = 0; i < cantidadNumeros; i++)
                {
                    printf("operaciones[%d]: %c \n", i, operaciones[i]);
                }
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

/// comment debug
// printf("caracter: %c \n", caracter);
// printf("cantidadNumeros: %d \n", cantidadNumeros);
// for (int i = 0; i < 5; i++)
// {
//     printf("numerosDelCalculo[%d]: %d \n", i, numerosDelCalculo[i]);
// }
// for (int i = 0; i < 5; i++)
// {
//     printf("operaciones[%d]: %c \n", i, operaciones[i]);
// }
// system("pause");

void debugger()
{
}