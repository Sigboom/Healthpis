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

class sigNet {
public:
    //return  socketfd;
    int socket_create(int port);

    int socket_connect(int port, std::string host);
};

#endif
