
    do
    {
        ch = fgetc(program_input);
        programtext[n++] = ch;
        printf("%c", ch);
    } while (ch != EOF);