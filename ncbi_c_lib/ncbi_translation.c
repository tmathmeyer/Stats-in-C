

#include "http.h"
#include <stdio.h>
#include <string.h>

#define QUERY_URL "http://www.ncbi.nlm.nih.gov/nuccore/%s?report=docsum&log$=seqview"
#define GENOME_URL "http://www.ncbi.nlm.nih.gov/sviewer/viewer.cgi?val=%s&dopt=fasta&sendto=t"
#define QUERY_URL_LEN 104

FILE *outfile = 0;
void genome_out(unsafe *str) {
    char query_url[QUERY_URL_LEN] = {0};
    snprintf(query_url, QUERY_URL_LEN, GENOME_URL, str);
    url_to_file(query_url, outfile);
}

void get_genome_uid(unsafe *line, int chars, int maxchars) {
    if ((line = strstr(line, "<meta name=\"ncbi_uidlist\" content=\"")) != NULL) {
        strstr(line+35, "\"")[0] = 0;
        genome_out(line+35);
    }
    (void)chars;
    (void)maxchars;
}

void get_genome_id(char *search) {
    char query_url[QUERY_URL_LEN] = {0};
    snprintf(query_url, QUERY_URL_LEN, QUERY_URL, search);
    stream(query_url, &get_genome_uid);
}


void usage() {
    puts("libncbi -q|--query QUERY [-f|--file FILE]");
}

void setargs(char *flag, char *arg, char **query, FILE **out) {
    if (!strcmp(flag, "-q")) {
        *query = arg;
        return;
    }

    if (!strcmp(flag, "--query")) {
        *query = arg;
        return;
    }

    if (!strcmp(flag, "-f")) {
        puts("-f not implemented");
        return;
    }

    if (!strcmp(flag, "--file")) {
        puts("--file not implemented");
        return;
    }

    (void)out;
}

int main(int argc, char **argv) {
    char *query = 0;
    outfile = stdout;

    switch(argc) {
        case 1:
            usage();
            return 1;
        case 5:
            setargs(argv[3], argv[4], &query, &outfile);
        case 3:
            setargs(argv[1], argv[2], &query, &outfile);
    }
    
    //NC_000913.3
    get_genome_id(query);
}
