/*
 * Copyright (C) 2015 Ted Meyer
 *
 * see LICENSING for details
 *
 */

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

    int precision = 4;
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
            total_nucleotides++;
            probabilities[indx] ++;
            if (last != 0) {
                last[indx] ++;
            }
            last = transitions[indx];
        }
    }

    printf("P(A=%.*f, T=%.*f, G=%.*f, C=%.*f)\n\n"
            ,precision
            ,((float)probabilities[0])/total_nucleotides
            ,precision
            ,((float)probabilities[1])/total_nucleotides
            ,precision
            ,((float)probabilities[2])/total_nucleotides
            ,precision
            ,((float)probabilities[3])/total_nucleotides);




    printf("       A      T      G      C\n");
    printf("  _____________________________\n");
    printf("A | %.*f %.*f %.*f %.*f\n"
            ,precision
            ,((float)transitions[0][0])/total_nucleotides
            ,precision
            ,((float)transitions[0][1])/total_nucleotides
            ,precision
            ,((float)transitions[0][2])/total_nucleotides
            ,precision
            ,((float)transitions[0][3])/total_nucleotides);

    printf("T | %.*f %.*f %.*f %.*f\n"
            ,precision
            ,((float)transitions[1][0])/total_nucleotides
            ,precision
            ,((float)transitions[1][1])/total_nucleotides
            ,precision
            ,((float)transitions[1][2])/total_nucleotides
            ,precision
            ,((float)transitions[1][3])/total_nucleotides);
    
    printf("G | %.*f %.*f %.*f %.*f\n"
            ,precision
            ,((float)transitions[2][0])/total_nucleotides
            ,precision
            ,((float)transitions[2][1])/total_nucleotides
            ,precision
            ,((float)transitions[2][2])/total_nucleotides
            ,precision
            ,((float)transitions[2][3])/total_nucleotides);

    printf("C | %.*f %.*f %.*f %.*f\n"
            ,precision
            ,((float)transitions[3][0])/total_nucleotides
            ,precision
            ,((float)transitions[3][1])/total_nucleotides
            ,precision
            ,((float)transitions[3][2])/total_nucleotides
            ,precision
            ,((float)transitions[3][3])/total_nucleotides);
}

