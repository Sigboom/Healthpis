/*************************************************************************
	> File Name: sigNet.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二 10/22 23:36:22 2019
 ************************************************************************/

#ifndef _SIGNET_H
#define _SIGNET_H

#include <iostream>
#include <string>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>

#define MSGLEN 512

using std::string;

class sigNet {
public:
    int socket_create(int port);
    int socket_connect(int port, string host);
    int recvMsg(int connfd, string &buffer, int msgLen = MSGLEN, int args = 0);
    int sendMsg(int connfd, string &buffer, int msglen = 0, int args = 0);
};

#endif
