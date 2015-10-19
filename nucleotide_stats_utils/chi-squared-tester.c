/*
 * Copyright (C) 2015 Ted Meyer
 *
 * see LICENSING for details
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int generate(float probs[]);
float sample(float nucleotides[], char rr[], float c, float E);

#define HIST_SAMPLES 10000
#define HIST_STEP 1
#define HIST_BARS 30


int main(int argc, char **argv) {
    if (argc != 5) {
        puts("usage: chi-squared-tester pA(float) pT(float) pG(float) pC(float)");
        return 1;
    }
    srand(time(NULL));
    float atgc_prob[4] = {
             atof(argv[1])
            ,atof(argv[2])
            ,atof(argv[3])
            ,atof(argv[4])
    };

    char rr[2] = {generate(atgc_prob), generate(atgc_prob)};
    float c = 0;
    if (rr[0] == rr[1]) {
        c = 1.0 + 2.0*atgc_prob[rr[0]] - 3.0*atgc_prob[rr[1]]*atgc_prob[rr[1]];
    } else {
        c = 1 - 3.0*atgc_prob[rr[0]]*atgc_prob[rr[1]];
    }
    float E = (999.0) * atgc_prob[rr[0]] * atgc_prob[rr[1]];


    float samples[HIST_SAMPLES];
    for(int i=0; i<HIST_SAMPLES; i++) {
        samples[i] = sample(atgc_prob, rr, c, E);
    }

    int hist_bars[HIST_BARS] = {};

    for(int i=0;i<HIST_SAMPLES;i++) {
        int bar = samples[i] / HIST_STEP;
        if (bar > HIST_BARS) {
            puts("WARNING - DATA LOST");
        } else {
            hist_bars[bar]++;
        }
    }

    for(int i=0;i<HIST_BARS;i++) {
        printf("%05.2f | %i\n", (float)i*HIST_STEP, hist_bars[i]);
    }

}


int **get_transition_matrix(char *sample, int samplesize) {
    int **transitions = malloc(sizeof(int *) * 4);
        transitions[0] = calloc(sizeof(int), 4);
        transitions[1] = calloc(sizeof(int), 4);
        transitions[2] = calloc(sizeof(int), 4);
        transitions[3] = calloc(sizeof(int), 4);

    int ctr = 0;
    int *last = 0;
    while(samplesize --> 0) {
        int indx = sample[ctr++];
        if (indx != -1) {
            if (last != 0) {
                last[indx] ++;
            }
            last = transitions[indx];
        }
    }

    return transitions;
}


float sample(float nucleotides[], char rr[], float c, float E) {
    char random_sample[1000];
    for(int i=0; i<1000; i++) {
        random_sample[i] = generate(nucleotides);
    }
    int **transition_matrix = get_transition_matrix(random_sample, 1000);
    float O = transition_matrix[rr[0]][rr[1]];
    float X2c = ((O - E) * (O - E)) / (E * c);
    free(transition_matrix[0]);
    free(transition_matrix[1]);
    free(transition_matrix[2]);
    free(transition_matrix[3]);
    free(transition_matrix);

    return X2c;
}



// 0->A 1->T 2->G 3->C
int generate(float probs[]) {
    int random = rand();

    if ((random-=(probs[0] * RAND_MAX)) <= 0) {
        return 0;
    }
    if ((random-=(probs[1] * RAND_MAX)) <= 0) {
        return 1;
    }
    if ((random-=(probs[2] * RAND_MAX)) <= 0) {
        return 2;
    }
    if ((random-=(probs[3] * RAND_MAX)) <= 0) {
        return 3;
    }

    return -1;
}

