/*
=========================
Lab Exercise 3:

3. Given a C program text file as input, write a C program and separate all Words and put all of them in an array.

For example if the text file has the following line "My name = Ramesh+Suresh" then the output will be

a[0]=My, a[1]=name, a[2]==, a[3]=Ramesh+Suresh

You can print the array as output on the screen.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ReadFileIntoText(FILE *ptr, char text[])
{
    if (ptr == NULL)
    {
        printf("\n File not Read..");
        return 0;
    }
    char ch;
    int n = 0;
    do
    {
        ch = fgetc(ptr);
        text[n++] = ch;
        // printf("%c", ch);
    } while (ch != EOF);
    return n;
}

int Separate(char programtext[], int n, char contprogramtext[][100])
{
    int j = 0;
    char word[100];
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        // Below condition helps to separate words when newLine , Tabspace and space are encountered.
        if ((programtext[i] == '\n') || (programtext[i] == ' ') || (programtext[i] == '\t'))
        {
            // The below condition is applied as Blank_spaces too were saved in arrays.
            if (j == 0)
            {
                continue;
                // $ character will ensure end of word .
            }
            contprogramtext[k][j] = '$';
            k++;
            continue;
            j = 0;
        }
        contprogramtext[k][j++] = programtext[i];
    }
    return k;
}

int main()
{
    FILE *program_input, *keyword_input, *output_fl;
    char keytext[1000], programtext[1000], contprogramtext[1000][100];
    long numlet;

    // Below part is reading program.
    program_input = fopen("program_input.txt", "r");
    int n;
    n = ReadFileIntoText(program_input, programtext);
    fclose(program_input);

    // Here n we get is length of program by character.
    printf("\n The length of program by character is : %d \n", n);

    // The content in the file is .
    int m;
    m = Separate(programtext, n, contprogramtext);
    int j;
    for (int i = 0; i < m; i++)
    {
        j = 0;
        printf("\n array[%d]", i + 1);
        while (contprogramtext[i][j] != '$')
        {
            printf("%c", contprogramtext[i][j]);
            j++;
        }
    }

    return 0;
}