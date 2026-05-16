//Carlos David Cruz Santiesteban 379909
// Practica 1: Cola de impresion en C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

int val_int(int ri, int rf, const char *msge);
char *my_gets(char *cadena, int tamano);
char *val_str(char *cadena, int n);

int val_int(int ri, int rf, const char *msge)
{
    int num;
    char xnum[30];
    do
    {
        printf("%sENTRE %d Y %d: ", msge, ri, rf);
        my_gets(xnum, 30);
        num = atoi(xnum);
        if (num < ri || num > rf)
        {
            printf("INCORRECTO\n");
        }
    } while (num < ri || num > rf);

    return num;
}

char *my_gets(char *cadena, int tamano)
{
    size_t longitud;
    fflush(stdin);
    fgets(cadena, tamano, stdin);
    if (cadena)
    {
        longitud = strlen(cadena);
        if (longitud > 0)
        {
            if (cadena[longitud - 1] == '\n')
            {
                cadena[longitud - 1] = '\0';
            }
        }
        return cadena;
    }
    return NULL;
}

char *val_str(char *cadena, int n)
{
    int caract, i = 0;

    do
    {
        caract = getch();

        if (caract == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
            continue;
        }

        if (caract == 32)
        {
            printf("%c", 32);
            cadena[i] = caract;
            i++;
            continue;
        }

        if (caract >= 97)
        {
            if (caract <= 127)
            {
                caract = caract - 32;
            }
        }

        if (caract >= 65)
        {
            if (caract <= 91)
            {
                cadena[i] = caract;
                printf("%c", caract);
                i++;
            }
        }
    } while (caract != 13 && n > i);

    cadena[i] = '\0';

    printf("\n");

    return cadena;
}