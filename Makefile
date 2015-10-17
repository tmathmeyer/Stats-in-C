

all:
	gcc nucleotide-strip.c -o nucleotide-strip-invalid
	gcc nucleotide-freq-transmatrix.c -o nucleotide-freq-transmatrix
	gcc chi-squared-tester.c -o chi-squared-tester


clean:
	rm nucleotide-freq-transmatrix
	rm nucleotide-strip-invalid
	rm chi-squared-tester
