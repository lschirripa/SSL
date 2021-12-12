#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int columna1(char);
void automata1(char *);
int columna2(char);
void automata2(char *);
void error(void);
int numero(char);

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

void error(void)
{
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
    int contadorDecimal = 0, contadorOctal = 0, contadorHexa = 0;
    caracter = cadena[i];

    while (caracter != '\0')
    {
        estado = tt[estado][columna1(caracter)];
        if (estado == 2)
        {
            contadorDecimal += 1;
            printf("1decimal");
        }
        if (estado == 7)
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
        caracter = cadena[++i];
    }
    printf("No hubo ningun error lexico i se reconocieron:\n");
    printf("%d numeros decimales\n", contadorDecimal);
    printf("%d numeros octales\n", contadorOctal);
    printf("%d numeros hexadecimales\n", contadorHexa);
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

void automata2(char *cadena)
{
    int tt[4][6] = {{3, 3, 3, 1, 3, 4},
                    {2, 2, 2, 1, 3, 4},
                    {3, 3, 3, 1, 3, 5},
                    {3, 3, 3, 3, 3, 5}};
    int estado = 0;
    int i = 0;
    char caracter;
    int numeros[30];
    int cantidadNumeros = 0;
    char operaciones[29];
    int cantOperacionesOriginal = 0, contador = 0;
    int resultado = 0;
    int j = 0, index = 0;
    int proxSigno = 1;

    for (j = 0; j < 30; j++)
        numeros[j] = 0;

    caracter = cadena[i]; // 1. Se lee el primer carácter de la cadena
    do                    // a. Se actualiza el estado.

    {
        estado = tt[estado][columna2(caracter)]; //a. Se actualiza el estado.

        if (estado == 1)
        {
            numeros[cantidadNumeros] = numeros[cantidadNumeros] * 10 + numero(caracter); // el estado es 1, significa qué se acaba de leer un número (qué puede ser parte de un número más grande), por lo tanto se transforma ese carácter enun número, se desplaza al número más grande i se suman ambos números.
        }
        else if (estado == 2)
        {
            if (caracter == '-')
            {
                numeros[cantidadNumeros] = numeros[cantidadNumeros] * proxSigno;
                proxSigno = -1;
                operaciones[cantidadNumeros] = '+';
                cantidadNumeros += 1;
            }
            else
            {
                numeros[cantidadNumeros] = numeros[cantidadNumeros] * proxSigno;
                proxSigno = 1;
                operaciones[cantidadNumeros] = caracter;
                cantidadNumeros += 1;
            }
        }
        else if (estado == 3)
        {
            printf("Se detecto un error lexico en la cadena\n");
            return;
        }

        caracter = cadena[++i];

    } while (estado != 4 && estado != 5);
    switch (estado)
    {
    case 4:
        printf("Cadena sin error lexico\n");
        numeros[cantidadNumeros] = numeros[cantidadNumeros] * proxSigno;
        cantidadNumeros += 1;
        j = 0;
        cantOperacionesOriginal = cantidadNumeros - 1;

        do
        {
            j = 0;
            while (operaciones[j] != '*' && contador < cantOperacionesOriginal)
            {
                j++;
                contador++;
                printf("\n j: %d , contador: %d \n", j, contador);
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
                numeros[j] = numeros[j] * numeros[j + 1];
                j++;
                while (j < (cantidadNumeros - 1))
                {
                    numeros[j] = numeros[j + 1];
                    j++;
                }
                cantidadNumeros = cantidadNumeros - 1;
            }
            contador++;
        } while (contador < cantOperacionesOriginal);
        j = 0;
        resultado = numeros[0];
        while (j < (cantidadNumeros - 1))
        {
            resultado = resultado + numeros[j + 1];
            j++;
        }
        printf("Resultado = %d\n", resultado);
        return;
    case 5:
        printf("Cadena con error lexico");
        return;
    default:
        return;
    }
}

int columna2(char caracter)
{
    switch (caracter)
    {
    case '+':
        return 0;
        break;
    case '-':
        return 1;
        break;
    case '*':
        return 2;
        break;
    case '0':
        return 3;
        break;
    case '1':
        return 3;
        break;
    case '2':
        return 3;
        break;
    case '3':
        return 3;
        break;
    case '4':
        return 3;
        break;
    case '5':
        return 3;
        break;
    case '6':
        return 3;
        break;
    case '7':
        return 3;
        break;
    case '8':
        return 3;
        break;
    case '9':
        return 3;
        break;
    case '\0':
        return 5;
        break;
    default:
        return 4;
        break;
    }
}

int numero(char caracter)
{
    return (caracter - '0');
}