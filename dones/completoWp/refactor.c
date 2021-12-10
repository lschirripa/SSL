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
        printf("ingrese un calculo");
        scanf("%s", cadenaPrincipal);
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

    int tt[11][9] = {{1, 5, 2, 2, 4, 4, 0, 4, 15},
                     {4, 2, 2, 2, 4, 4, 0, 4, 14},
                     {4, 2, 2, 2, 4, 4, 3, 4, 11},
                     {1, 5, 2, 2, 4, 4, 0, 4, 15},
                     {4, 4, 4, 4, 4, 4, 0, 4, 14},
                     {4, 6, 6, 4, 4, 8, 0, 4, 14},
                     {4, 6, 6, 4, 4, 4, 7, 4, 12},
                     {1, 5, 2, 2, 4, 4, 0, 4, 15},
                     {4, 9, 9, 9, 9, 4, 0, 4, 14},
                     {4, 9, 9, 9, 9, 4, 10, 4, 13},
                     {1, 5, 2, 2, 4, 4, 0, 4, 15}};
    int estado = 0;
    int i = 0;
    char caracter;
    int contadorDecimal = 0, contadorOctal = 0, contadorHexa = 0;
    caracter = cadena[i];

    do
    {
        estado = tt[estado][columna1(caracter)];
        if (estado == 3)
        {
            contadorDecimal += 1;
        }
        else if (estado == 7)
        {
            contadorOctal += 1;
        }
        else if (estado == 10)
        {
            contadorHexa += 1;
        }
        else if (estado == 4)
        {
            printf("Hubo un error lexico en la cadena\n");
            return;
        }
        caracter = cadena[++i];
    } while (estado != 11 && estado != 12 && estado != 13 && estado != 14 && estado != 15);
    switch (estado)
    {
    case 11:
        contadorDecimal += 1;
        break;
    case 12:
        contadorOctal += 1;
        break;
    case 13:
        contadorHexa += 1;
        break;
    case 14:
        printf("Hubo un error lexico en la cadena\n");
        return;
    case 15:
        break;
    }
    printf("No hubo ningun error lexico y se reconocieron:\n");
    printf("%d numeros decimales\n", contadorDecimal);
    printf("%d numeros octales\n", contadorOctal);
    printf("%d numeros hexadecimales", contadorHexa);
    system("pause");
    return;
}

int columna1(char caracter)
{
    switch (caracter)
    {
    case '+':
        return 0;
        break;
    case '-':
        return 0;
        break;
    case '0':
        return 1;
        break;
    case '1':
        return 2;
        break;
    case '2':
        return 2;
        break;
    case '3':
        return 2;
        break;
    case '4':
        return 2;
        break;
    case '5':
        return 2;
        break;
    case '6':
        return 2;
        break;
    case '7':
        return 2;
        break;
    case '8':
        return 3;
        break;
    case '9':
        return 3;
        break;
    case 'A':
        return 4;
        break;
    case 'B':
        return 4;
        break;
    case 'C':
        return 4;
        break;
    case 'D':
        return 4;
        break;
    case 'E':
        return 4;
        break;
    case 'F':
        return 4;
        break;
    case 'x':
        return 5;
        break;
    case '&':
        return 6;
        break;
    case '\0':
        return 8;
        break;
    default:
        return 7;
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

    caracter = cadena[i];
    do
    {
        estado = tt[estado][columna2(caracter)];

        if (estado == 1)
        {
            numeros[cantidadNumeros] = numeros[cantidadNumeros] * 10 + numero(caracter);
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