

#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        puts("usage: nucleotide_cleaner FILE(input) FILE(output)");
        return 1;
    }
    FILE *in = fopen(argv[1], "r");
    FILE *ot = fopen(argv[2], "w");

    char read;
    while((read = getc(in)) != EOF) {
        if (read != '\n') {
            fputc(read, ot);
        }
    }
    fclose(in);
    fclose(ot);

    return 0;
}

