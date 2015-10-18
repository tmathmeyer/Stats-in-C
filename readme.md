Run the command:
````
make
````
to generate three binaries:
 - chi-squared-tester (exercize 2.10)
 - nucleotide-freq-transmatrix (exercize 2.9)
 - nucleotide-strip-invalid (utility)


nucleotide-freq-transmatrix is run in either of the following ways
 - ./nucleotide-freq-transmatrix -f [GENOME_FILE]
 - cat [GENOME_FILE] | ./nucleotide-freq-transmatrix

 chi-squared-tester is run the following way
  - ./chi-squared-tester pA pT pG pC

where pA, pT, pG, and pC are all decimal numbers which together sum to 1
to run with an even distribution, one would execute:
./chi-squared-tester .25 .25 .25 .25


