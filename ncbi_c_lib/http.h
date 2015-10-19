/*
 * Copyright (C) 2015 Ted Meyer
 *
 * see LICENSING for details
 *
 */

#ifndef _HTTP_H_
#define _HTTP_H_

#include <stdio.h>

#define STREAMING_BUFFER_SIZE 2048
#define HTTP_STATUS_CLIENT_ERROR 400
#define NCBI_HOST "www.ncbi.nlm.nih.gov"
#define unsafe char

int get_socket(int port_number, char* ip);
char *generate_header(char *url, char *host);
int hostname_to_ip(char *hostname , char *ip);
int socket_gets(int sockfd, char *buffer, int buflen);
int stream(char *url, void (* each_line)(unsafe *, int, int));
int url_to_file(char *url, FILE *file);

#endif
