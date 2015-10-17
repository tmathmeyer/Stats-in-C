

all:
	gcc nucleotide-strip.c -o nucleotide-strip-invalid
	gcc nucleotide-freq-transmatrix.c -o nucleotide-freq-transmatrix


clean:
	rm nucleotide-freq-transmatrix
	rm nucleotide-strip-invalid
