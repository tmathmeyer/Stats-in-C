
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    
    FILE *nucleotide_sequence = 0;
    
    if (argc == 1) {
        nucleotide_sequence = stdin;
    }
    if (argc == 3) {
        if (!strncmp(argv[1], "-f", 2)) {
            nucleotide_sequence = fopen(argv[2], "r");
        }
    }

    if (!nucleotide_sequence) {
        puts("usage:");
        puts("\tnucleotide-freq-transmatrix -f FILE(input)");
        puts("\tnucleotide-freq-transmatrix");
        return 1;
    }

    int lookup[256] = {-1};
    lookup['A'] = 0;
    lookup['T'] = 1;
    lookup['G'] = 2;
    lookup['C'] = 3;

    int total_nucleotides = 0;
    int transitions[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    int probabilities[4] = {0,0,0,0};
    char read = 0;
    int *last = 0;
    
    while((read = getc(nucleotide_sequence)) != EOF) {
        int indx = lookup[read];
        if (indx != -1) {
            probabilities[indx] ++;
            if (last != 0) {
                last[indx] ++;
            }
            last = transitions[indx];
        }
    }

    printf("P(A=%i, T=%i, G=%i, C=%i\n"
            ,probabilities[0]
            ,probabilities[1]
            ,probabilities[2]
            ,probabilities[3]);


}

