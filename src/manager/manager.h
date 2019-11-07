/*************************************************************************
	> File Name: manager.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二 11/ 5 09:24:39 2019
 ************************************************************************/

#ifndef _MANAGER_H
#define _MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "../../sigToolkit/include/sigToolkit.h"

using std::cin;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;
using std::string;
using std::flush;
using std::stoi;

namespace monitor {
    int byebye() {
        std::cout << "Bye~Bye~" << std::endl;
        return 0;
    }
}

typedef struct ServerNode {
    string hostName;
    string hostIp;
    int port;
    string recvBuffer;
    string sendBuffer;
    string errBuffer;
    int connfd;
} ServerNode;

class manager : public sigNet {
private:
    unique_ptr<ServerNode[]> servers;
    unique_ptr<baseTools> bt;
    unique_ptr<outPatient> op;
    int serverCounter;
    int sonPid;
    int stat;

public:
    manager(string confPath);
    ~manager();

    int Start();
    void Local();
    
    void showServers();
    int getConnect();
    void disConnect(int connfd);
    inline bool isExit(string order);

    int getSonPid();
    int getStat();

private:
    void initServers(string serversDis);
};

#endif
