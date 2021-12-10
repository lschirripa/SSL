#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // char sentence[20];
    // printf("enter string\n");
    // gets(sentence);
    // printf("%s", sentence);

    char *inputText = malloc(50 * sizeof(char));
    scanf("%s", inputText);
    printf("This is your string %s \n", inputText);
    system("pause");
}
