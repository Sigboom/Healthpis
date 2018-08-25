/*************************************************************************
	> File Name: master.c
	> Author: Daniel
	> Mail: 292382967@qq.com
	> Created Time: 日  6/10 20:27:36 2018
 ************************************************************************/

#include "mynet.h"

int get_client_conf(int key, char *host_ip, int *port);
void itoa(int key, char *arm);
    
int main(int argc, char** argv) {
    char temp[100]; 
    int min_key = atoi(get_con_val("start"));
    int max_key = atoi(get_con_val("finnish"));
    int key = min_key, count = 0;
    
    while (true) {
        key = key < max_key ? key + 1 : 0;
        count < 5 ? ++count : wait(NULL), --count;
        int pid = fork();
        if (pid < 0) BREAK(pid);
        if (pid) continue; 
        char host_ip[16] = {0};
        int socketfd, port;
        if (get_client_conf(key, host_ip, &port)) RETURN(get_client_conf);
        if ((socketfd = socket_connect(port, host_ip)) < 0) RETURN(socket_connect); 
        printf("long connect succeed!\n");
        while (true) {
            int n = 0;
            char buffer[MAXLINE];
            bzero(buffer, sizeof(buffer));
            scanf("%s", buffer);
            if ((n = send(socketfd, buffer, strlen(buffer), 0)) < 0) RETURN(send);
            int pid = fork();
            if (pid < 0) RETURN(fork);
            if (pid) continue;
            int filefd = 0, file_port = atoi(get_con_val("flie_port"));
            if ((filefd = socket_connect(file_port, host_ip)) < 0) RETURN(socket_connect); 
            printf("short connect succeed!\n");
            while ((n = recv(filefd, buffer, MAXLINE, 0)) > 0) {
                fputs(buffer, stdout);
                bzero(buffer, sizeof(buffer));
            }
            close(filefd);
            return 0; 
        }
        close(socketfd);
    }
    return 0;
}

void itoa(int key, char *arm) {
    int i;
    for (i = 0; key; ++i, key /= 10) arm[i] = key - '0';
    arm[i] = '\0';
    return ;
}

int get_client_conf(int key, char *host_ip, int *port) {
    char temp[100] = {0}, tk[100] = {0};
    strcpy(temp, get_con_val("client_ip"));
    if (!strlen(temp)) RETURN(get_con_val:client_ip);
    itoa(key + 40, tk);
    strcat(temp, tk);
    strcpy(host_ip, temp);
    strcpy(temp, get_con_val("client_port")); 
    if (!strlen(temp)) RETURN(get_con_val:port);
    *port = atoi(temp);
    return 0;
}

