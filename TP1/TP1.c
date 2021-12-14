#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int columna1(char);
void scanner(char *);
int columna2(char);
void calculadora(char *);
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
        scanner(cadenaPrincipal);
    }
    else if (numeroOpcion == 2)
    {
        printf("ingrese un calculo\n");
        scanf("%s", cadenaPrincipal);
        calculadora(cadenaPrincipal);
    }
    else
    {
        printf("ERROR! debe ingresar solamente 1 o 2 para invocar al scanner o a la calculadora respectivamente\n");
        system("pause");
    }
}

void scanner(char *cadena)
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
    int contadorE27 = 0, contadorE6 = 0, contadorE5 = 0, contadorDecimal = 0, contadorOctal = 0, contadorHexa = 0;
    caracter = cadena[i];
    int tamanioCadena = strlen(cadena);

    while (caracter != '\0')
    {

        estado = tt[estado][columna1(caracter)];
        // printf("\n caracter:%c\n", caracter);
        //  printf("\n estado:%d\n", estado);
        if (estado == 2)
        {
            contadorE27 += 1;
        }
        else if (estado == 7)
        {
            contadorE27 += 1;
        }
        else if (estado == 6)
        {
            contadorE6 += 1;
        }
        else if (estado == 5)
        {
            contadorE5 += 1;
        }
        else if (estado == 9)
        {
            printf("Error lexico en la cadena ingresada\n");
            return;
        }
        else if (caracter == '&')
        {
            if (contadorE27 > 0)
            {
                contadorDecimal++;
                resetContadores(&contadorE27, &contadorE6, &contadorE5);
            }

            else if (contadorE6 > 0)
            {
                contadorOctal++;
                resetContadores(&contadorE27, &contadorE6, &contadorE5);
            }
            else if (contadorE5 > 0)
            {
                contadorHexa++;
                resetContadores(&contadorE27, &contadorE6, &contadorE5);
            }
        }

        caracter = cadena[++i];
    }
    if (caracter == '\0')
    {
        if (contadorE27 > 0)
        {
            contadorDecimal++;
            resetContadores(&contadorE27, &contadorE6, &contadorE5);
        }

        else if (contadorE6 > 0)
        {
            contadorOctal++;
            resetContadores(&contadorE27, &contadorE6, &contadorE5);
        }
        else if (contadorE5 > 0)
        {
            contadorHexa++;
            resetContadores(&contadorE27, &contadorE6, &contadorE5);
        }
    }

    printf("se reconocieron:\n");
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

void resetContadores(int *contadorE27, int *contadorE6, int *contadorE5)
{
    *contadorE27 = 0;
    *contadorE6 = 0;
    *contadorE5 = 0;
}

void calculadora(char *cadena)
{
    int tt[4][4] = {{1, 3, 3, 3},
                    {1, 2, 2, 2},
                    {1, 3, 3, 3},
                    {3, 3, 3, 3}};

    int estado = 0;
    int i = 0;
    char caracter;
    int numerosDelCalculo[50];
    int posicionNum = 0;
    char operaciones[49];
    int cantOperaciones = 0;
    int contador = 0;
    int resultado = 0;
    int j = 0, aux = 0;
    int signoSiguiente = 1;

    for (j = 0; j < 50; j++)
        numerosDelCalculo[j] = 0;

    caracter = cadena[i];

    do
    {
        estado = tt[estado][columna2(caracter)];

        if (estado == 1)
        {
            numerosDelCalculo[posicionNum] = numerosDelCalculo[posicionNum] * 10 + transformarAscii(caracter);
        }
        else if (estado == 2)
        {
            if (caracter == '-')
            {
                aplicarSigno(&posicionNum, &signoSiguiente, numerosDelCalculo, operaciones);
            }
            else
            {
                aplicarSigno2(&posicionNum, &signoSiguiente, numerosDelCalculo, operaciones, &caracter);
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

        aplicarUltSigno(&posicionNum, &signoSiguiente, numerosDelCalculo, operaciones, &j, &cantOperaciones);
        //       debug(&cantOperaciones, &posicionNum, &j, &aux, &contador, &caracter, numerosDelCalculo, operaciones);

        do
        {
            j = 0;
            while (operaciones[j] != '*' && contador < cantOperaciones)
            {
                j++;
                contador++; //CAMBIO A LO ULTIMO
            }
            //printf("\n $$$$$$$$$$$   WHILE OPERACIONES[i] != *  $$$$$$$$$$$ \n");
            //            debug(&cantOperaciones, &posicionNum, &j, &aux, &contador, &caracter, numerosDelCalculo, operaciones);

            if (operaciones[j] == '*')
            {
                aux = j;
                while (j < (posicionNum - 2))
                {
                    operaciones[j] = operaciones[j + 1]; //LA POSICION DONDE ESTA EL *, VA A SER REEMPLAZADA POR SU SIGUIENTE
                    j++;
                }
                j = aux;
                numerosDelCalculo[j] = numerosDelCalculo[j] * numerosDelCalculo[j + 1]; //j SIGUE SIENDO LA POSICION DEL PRIMER NUMERO A MULTIPLICAR, Y LO MULTIPLICA POR SU SIGUIENTE
                j++;
                while (j < (posicionNum - 1))
                {
                    numerosDelCalculo[j] = numerosDelCalculo[j + 1]; // LO MISMO CON LOS NUMEROS, EL 2D0 NUMERO A MULTIPLICAR, LO TRANSFORMA A SU SIGUIENTE
                    j++;
                }
                posicionNum = posicionNum - 1;
                //printf("\n $$$$$$$$$$$   ENCONTRO UN *  $$$$$$$$$$$ \n");
                //              debug(&cantOperaciones, &posicionNum, &j, &aux, &contador, &caracter, numerosDelCalculo, operaciones);
            }

            contador++;
        } while (contador < cantOperaciones);
        j = 0;
        resultado = numerosDelCalculo[0];
        while (j < (posicionNum - 1))
        {
            resultado = resultado + numerosDelCalculo[j + 1]; //VA SUMANDO EL V[0] CON SUS SIGUIENTES HASTA EL POSICION NUM CORRECTO
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
        return 3;
        break;
    }
}

int transformarAscii(char caracter)
{
    return (caracter - '0');
}

void debug(int *cantOperaciones, int *posicionNum, int *j, int *aux, int *contador, char *caracter, int numerosDelCalculo[], char operaciones[])
{

    printf("\n cantidadDeOperacionesOriginal: %d \n", *cantOperaciones);
    printf("\n posicionNum: %d \n", *posicionNum);
    printf("\n j = %d \n", j);
    printf("\n aux = %d \n", *aux);
    printf("\n contador = %d \n", *contador);
    printf("caracter: %c \n", *caracter);
    for (int i = 0; i < *posicionNum; i++)
    {
        printf("numerosDelCalculo[%d]: %d \n", i, numerosDelCalculo[i]);
    }
    for (int i = 0; i < *posicionNum; i++)
    {
        printf("operaciones[%d]: %c \n", i, operaciones[i]);
    }
}

void aplicarSigno(int *posicionNum, int *signoSiguiente, int numerosDelCalculo[*posicionNum], char operaciones[*posicionNum])
{
    numerosDelCalculo[*posicionNum] = numerosDelCalculo[*posicionNum] * (*signoSiguiente);
    *signoSiguiente = -1;
    operaciones[*posicionNum] = '+';
    *posicionNum += 1;
}

void aplicarSigno2(int *posicionNum, int *signoSiguiente, int numerosDelCalculo[*posicionNum], char operaciones[*posicionNum], char *caracter)
{
    numerosDelCalculo[*posicionNum] = numerosDelCalculo[*posicionNum] * (*signoSiguiente);
    *signoSiguiente = 1;
    operaciones[*posicionNum] = *caracter;
    *posicionNum += 1;
}

void aplicarUltSigno(int *posicionNum, int *signoSiguiente, int numerosDelCalculo[*posicionNum], char operaciones[*posicionNum], int *j, int *cantOperaciones)
{
    numerosDelCalculo[*posicionNum] = numerosDelCalculo[*posicionNum] * *signoSiguiente;
    *posicionNum += 1;
    *j = 0;
    *cantOperaciones = *posicionNum - 1;
}