/*************************************************************************
	> File Name: client.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  6/10 15:03:23 2018
 ************************************************************************/

#include "mynet.h"
//#include "client_conf.h"

#define RETURN(a) {perror(#a); return 1;}
#define BREAK(a) {perror(#a); break;}
#define CLIENT_PORT 5555
#define FILE_PORT 6666
#define true 1
#define false 0

int catch_conn();
int send_file(int connfd, char *filename);

int main() {
    int socketfd, connfd, shortfd;
    if ((socketfd = socket_create(CLIENT_PORT)) < 0) RETURN(socket_create);
    if ((shortfd = socket_create(FILE_PORT)) < 0) RETURN(socket_create);
    while (true) {
        if (!(connfd = catch_conn(socketfd))) BREAK(catch_conn);
        while (true) {
            char buffer[MAXLINE];
            bzero(buffer, sizeof(buffer));
            int n;
            if ((n = recv(connfd, buffer, MAXLINE, 0)) < 0) BREAK(recv);
            if (n == 0) BREAK(recv_0);
            int pid = fork();
            if (pid < 0) RETURN(fork);
            if (pid == 0) {
                int filefd = 0;
                if (!(filefd = catch_conn(shortfd))) BREAK(catch_conn);
                if (!send_file(filefd, buffer)) BREAK(send_file);
                close(filefd);
                return 0;
            }
        }
    } 
    close(shortfd);
    close(socketfd); 
    return 0;
}

int catch_conn(int socketfd) {
    int connfd = 0;
    printf("~~~~~Waiting for client's request~~~~~\n"); 
    if ((connfd = accept(socketfd, (struct sockaddr*)NULL, NULL)) < 0) return 0;
    printf("~~~~~connect succeed!~~~~~\n");
    return connfd;
}

int send_file(int connfd, char *filename) {
    FILE *fp = NULL;
    if ((fp = fopen(filename, "r")) == NULL) return 0;
    int length = 0;
    char *buffer[MAXLINE];
    bzero(buffer, sizeof(buffer));
    while ((length = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
        if (send(connfd, buffer, length, 0) < 0) return 0;
        bzero(buffer, sizeof(buffer));
    }
    fclose(fp);
    printf("send over!\n");
    return 1;
}
