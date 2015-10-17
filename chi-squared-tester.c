
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

    if (argc != 5) {
        puts("usage: chi-squared-tester P1(float) P2(float) P3(float) P4(float)");
        return 1;
    }

    float atgc_prob[4] = {
             atof(argv[1])
            ,atof(argv[2])
            ,atof(argv[3])
            ,atof(argv[4])
    };

}
