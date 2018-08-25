/*************************************************************************
	> File Name: mynet.h
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  6/10 15:10:14 2018
 ************************************************************************/

#ifndef _MYNET_H
#define _MYNET_H

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <time.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <signal.h>
#include <unistd.h>

#define RETURN(a) {perror(#a); return 1;}
#define BREAK(a) {perror(#a); break;}
#define MAXLINE 4096 
#define PIPATH "../pihealthd.conf"
#define LOCALHOST "127.0.0.1"
#define true 1
#define false 0

int socket_create(int port);
int socket_connect(int port, char*host);
char *get_con_val(char *key_name);

int socket_create(int port) {
    int socketfd;
    struct sockaddr_in sock_addr;
    if ((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("socket_create");
        return -1;
    }

    sock_addr.sin_family = AF_INET; 
    sock_addr.sin_port = htons(port); 
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if (bind(socketfd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == -1) { 
        perror("bind");
        return -1;
    }   
    if(listen(socketfd, 10) == -1) {
        perror("listen");
        return -1;
    }
    return socketfd;
}

int socket_connect(int port, char*host) {
    int socketfd;
    struct sockaddr_in dest_addr;
    if ((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("socket_connect");
        return -1;
    }

    dest_addr.sin_family = AF_INET; 
    dest_addr.sin_port = htons(port); 
    dest_addr.sin_addr.s_addr = inet_addr(host); 
    
    if (connect(socketfd, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) == -1) { 
        perror("connect");
        return -1;
    } 
    
    return socketfd;
}

char *get_con_val(char *key_name) {
    FILE*fp;
    char*temp, arm[100], *ans = NULL;
    if (!(fp = fopen(PIPATH, "r"))) perror("fopen"), exit(1);
    while (fscanf(fp, "%s", arm) != EOF) {
        if ((temp = strtok(arm, "=")) && !strcmp(temp, key_name) && !ans) { 
            temp = strtok(NULL, "=");
            ans = (char *)malloc(sizeof(char) * strlen(temp));
            strcpy(ans, temp);
        }
    }
    fclose(fp);
    ans ? printf("get value success: %s->%s\n", key_name, ans) : printf("%s: can't get value\n", __func__);
    return ans; 
}

#endif
