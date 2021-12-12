/ ------------para el ` punto-- -------------- /

    int VerificarExpresion(char *expresion, int *res)
{
    static int tt[5][5] = {{4, 1, 2, 4, 4},  //E0-
                           {1, 1, 3, 3, 4},  //E1+
                           {4, 1, 4, 4, 4},  //E2
                           {1, 1, 4, 4, 4},  //E3
                           {4, 4, 4, 4, 4}}; //E4 - Rechazo
    int estado = 0;                          /* estado inicial */
    int c;                                   /* caracter */
    int absoluto = 0;                        /* contiene valor numerico absoluto de la cadena */
    int s = 1;                               /* signo del numero (decimal): 1 = +; -1 = - */
    int hasFactor = 0;                       /* flag para indicar existencia de factores */
    int aux = 1;                             /* factor de multiplicacion inicial */
    int sumaTotal = 0;                       /* resultado acumulador de expresion*/

    /* Mientras no se alcance el fin de cadena */
    for (int i = 0; i < strlen(expresion); ++i)
    {
        c = expresion[i];
        estado = tt[estado][obtenerColumnaExpresion(c)];
        // Evaluar nuevo estado y calcular segun operador
        switch (estado)
        {
        case 2:
            if (c == '-')
                s = -1;
            break;
        case 1:
            absoluto = 10 * absoluto + Valor(c);
            break;
        case 3:
            // Puede ser otro termino, sin factores para calcular producto:
            if (hasFactor == 0 && c != '*')
            {
                sumaTotal += s * absoluto; // Se suma el ultimo termino
                absoluto = 0;
                aux = 1;
                if (c == '-')
                    s = -1;
                else
                    s = 1;
            }
            // Puede ser otro termino, con factores previos para calcular prod.
            else if (hasFactor && c != '*')
            {
                aux *= absoluto;
                sumaTotal += s * aux; // Se calcula el producto y se suma
                absoluto = 0;
                aux = 1;
                hasFactor = 0;
                if (c == '-')
                    s = -1;
                else
                    s = 1;
            }
            // Puede ser un factor inicial/primero a la espera de otro.
            else if (hasFactor == 0 && c == '*')
            {
                aux *= absoluto;
                hasFactor = 1;
                absoluto = 0;
            }
            // Puede ser un factor, con otro ya existentes.
            else if (hasFactor && c == '*')
            {
                aux *= absoluto;
                absoluto = 0;
            }
            break;
        default /* error-rechazo */:
            break;
        }
    }
    // Finalizado el recorrido de la expresión:
    if (estado == 1)
    { /* estado final */
        // Sumar último termino al resultado de expresión
        if (hasFactor)
        {
            aux *= absoluto;
            sumaTotal += s * aux;
        }
        else
            sumaTotal += s * absoluto;
        *res = sumaTotal;
        return 1;
    }
    else
        return 0;
}

int Valor(int c)
{
    return (c - '0');
}

int obtenerColumnaExpresion(char c)
{
    switch (c)
    {
    case '0':
        return 0;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return 1;
    case '+':
    case '-':
        return 2;
    case '*':
        return 3;
    default: /* Otro caracter */
        return 4;
    }
}