/*************************************************************************
	> File Name: sigNet.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二 10/22 23:15:01 2019
 ************************************************************************/

#include "../include/sigNet.h"

using std::cout;
using std::endl;
using std::string;

int sigNet::socket_create(int port) {
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

int sigNet::socket_connect(int port, string host) {
    int socketfd;
    struct sockaddr_in dest_addr;
    if ((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("socket_connect");
        return -1;
    }

    dest_addr.sin_family = AF_INET; 
    dest_addr.sin_port = htons(port); 
    dest_addr.sin_addr.s_addr = inet_addr(host.c_str()); 

    if (connect(socketfd, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) == -1) { 
        perror("connect");
        return -1;
    } 

    return socketfd;
}
