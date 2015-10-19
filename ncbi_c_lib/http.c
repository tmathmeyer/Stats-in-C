/*
 * Copyright (C) 2015 Ted Meyer
 *
 * see LICENSING for details
 *
 */

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "http.h"

int get_socket(int port_number, char* ip) {
    int sockfd = 0;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_number);

    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0) {
        perror ("inet_pton error occured");
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error : Connect Failed");
        return -1;
    }

    return sockfd;
}

char *generate_header(char *url, char *host) {
    char *header =
        "GET %s "
        "HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Cache-Control: no-cache\r\n"
        "Accept: text/html,application/xhtml+xml,"
        "application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"
        "Pragma: no-cache\r\n"
        "Accept-Language: en-US,en;q=0.8,ru;q=0.6,el;q=0.4\r\n\r\n";
    char *filled_header = malloc(2048); // this should be big enough i think
    memset(filled_header, 0, 2048);
    snprintf(filled_header, 2048, header, url, host);
    return filled_header;
}

int hostname_to_ip(char *hostname , char *ip) {
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( hostname ) ) == NULL) {
        return 0;
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++) {
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 1;
    }

    return 0;
}

int socket_gets(int sockfd, char *buffer, int buflen) {
    char buf;
    int r = 0;
    while(--buflen && read(sockfd, &buf, 1)) {
        *(buffer++) = buf;
        if (buf == '\n') {
            break;
        }
        r++;
    }
    *buffer = 0;
    return r;
}

int url_to_file(char *url, FILE *file) {
    char ip[17] = {0};
    char *bufferline, *header;
    int sockfd, ctr;
    
    if (!hostname_to_ip(NCBI_HOST, ip)) {
        return HTTP_STATUS_CLIENT_ERROR;
    }
    
    bufferline = calloc(sizeof(char), STREAMING_BUFFER_SIZE);
    sockfd = get_socket(80, ip);

    if (sockfd < 0) {
        perror("error, could not open socket");
        free(bufferline);
        return 0;
    }
    
    header = generate_header(url, NCBI_HOST);
    if (write(sockfd, header, strlen(header)) < 0) {
        shutdown(sockfd, 0);
        free(bufferline);
        free(header);
        close(sockfd);
        return HTTP_STATUS_CLIENT_ERROR;
    }

    char each;
    while((ctr = read(sockfd, &each, 1))) {
        switch(each) {
            case 'A':
            case 'T':
            case 'G':
            case 'C':
                fputc(each, file);
        }
    }

    free(header);
    shutdown(sockfd, 0);
    close(sockfd);
    free(bufferline);

    return 200;
}

int stream(char *url, void (* each_line)(char *, int, int)) {
    char ip[17] = {0};
    char *bufferline, *header;
    int sockfd, ctr;
    
    if (!hostname_to_ip(NCBI_HOST, ip)) {
        return HTTP_STATUS_CLIENT_ERROR;
    }
    
    bufferline = calloc(sizeof(char), STREAMING_BUFFER_SIZE);
    sockfd = get_socket(80, ip);

    if (sockfd < 0) {
        perror("error, could not open socket");
        free(bufferline);
        return 0;
    }
    
    header = generate_header(url, NCBI_HOST);
    if (write(sockfd, header, strlen(header)) < 0) {
        shutdown(sockfd, 0);
        free(bufferline);
        free(header);
        close(sockfd);
        return HTTP_STATUS_CLIENT_ERROR;
    }

    
    while((ctr = socket_gets(sockfd, bufferline, STREAMING_BUFFER_SIZE))) {
        each_line(bufferline, ctr, STREAMING_BUFFER_SIZE);
    }

    free(header);
    shutdown(sockfd, 0);
    close(sockfd);
    free(bufferline);
    return 1;
}

