/*
Lab Exercise 2:

This is the same as the previous exercise excep removing comment lines too.

2. Write a simple C code to remove spaces and new line enter characters and comment lines of a given input C program.

Input: A text file with a C program

Output: A text file of the above C program without any space between words and the whole program is in a single line. All comments to be removed from the input.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

int RemoveSpacesAndComments(char programtext[], int n, char contprogramtext[])
{
    int j = 0;
    bool commentSingle = false, commentMulti = false; // This declaration to check whether current running code is a comment or not.
    for (int i = 0; i < n; i++)
    {
        if (commentSingle == true)
        {
            if (programtext[i] == '\n')
            {
                commentSingle = false;
            }
            continue;
        }
        else if (commentMulti == true)
        {

            if ((programtext[i] == '*') && (programtext[i + 1] == '/'))
            {
                commentMulti = false;
                i++;
            }
            continue;
        }
        else
        { // Below Logic to by-pass single line comments.
            if ((programtext[i] == '/') && (programtext[i + 1] == '/'))
            {
                commentSingle = true;
                i++;
                continue;
            }
            if ((programtext[i] == '/') && (programtext[i + 1] == '*'))
            {
                commentMulti = true;
                i++;
                continue;
            }
            // Below condition helps to remove newLine , Tabspace and space.
            if ((programtext[i] == '\n') || (programtext[i] == ' ') || (programtext[i] == '\t'))
            {
                continue;
            }
            if (i == n)
            {
                printf("\n Shit!! error again");
            }
            contprogramtext[j++] = programtext[i];
        }
        // printf("%c", contprogramtext[j - 1]);
    }
    return j;
}

int main()
{
    FILE *program_input, *keyword_input, *output_fl;
    char keytext[1000], programtext[1000], contprogramtext[1000];
    long numlet;

    // Below part is reading program.
    program_input = fopen("program_input.txt", "r");
    int n;
    n = ReadFileIntoText(program_input, programtext);
    fclose(program_input);

    // Here n we get is length of program by character.
    printf("\n The length of program by character is : %d \n", n);

    // The content in the file is .
    for (int i = 0; i < n; i++)
    {
        // if (programtext[i] == '\n')
        // {
        //     printf("\n Newline Found! \n");
        // }
        printf("%c", programtext[i]);
    }
    int m;
    m = RemoveSpacesAndComments(programtext, n, contprogramtext);
    printf("\n The length of program by character after REMOVING spaces is : %d \n", m);
    for (int i = 0; i < m; i++)
    {
        printf("%c", contprogramtext[i]);
    }

    // Now writing into output file.
    output_fl = fopen("output.txt", "w");
    int results = fputs(contprogramtext, output_fl);
    fclose(output_fl);

    return 0;
}