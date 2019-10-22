/*************************************************************************
	> File Name: master.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  6/10 20:27:36 2018
 ************************************************************************/

#include "mynet.h"
//#include "master_conf.h"

void get_client_conf(int argc, char **argv, char *host, int *port);
    
int main() {
    int key;
    
    char host[16];
    int port;
    get_client_conf(key, host, &port);
    int socketfd;
    if ((socketfd = socket_connect(port, host)) < 0) RETURN(socket_connect); 
    printf("long connect succeed!\n");
    
    while (true) {
        int n = 0;
        char buffer[MAXLINE];
        bzero(buffer, sizeof(buffer));
        scanf("%s", buffer);
        if ((n = send(socketfd, buffer, strlen(buffer), 0)) < 0) RETURN(send);
        int pid = fork();
        if (pid < 0) RETURN(fork);
        if (pid == 0) {
            int filefd = 0;
            if ((filefd = socket_connect(FILE_PORT, host)) < 0) RETURN(socket_connect); 
            printf("short connect succeed!\n");
            while ((n = recv(filefd, buffer, MAXLINE, 0)) > 0) {
                fputs(buffer, stdout);
                bzero(buffer, sizeof(buffer));
            }
            close(filefd);
            return 0;
        } 
    }
    close(socketfd);
    return 0;
}

void get_client_conf(int argc, char **argv, char *host, int *port) {
    strcpy(host, LOCALHOST);
    *port = CLIENT_PORT;
    switch (argc) {
        case 3: *port = atoi(argv[2]);
        case 2: strcpy(host, argv[1]);
        case 1: break;
        default: perror("client_conf");
    }
    return ;
}

