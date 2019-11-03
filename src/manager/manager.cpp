/*************************************************************************
	> File Name: manager.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二  10/ 22 17:52:21 2019
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "../include/confException.h"
#include "../include/baseTools.h"
#include "../include/sigNet.h"

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
    int serverCounter;
    int sonPid;
    int stat;

public:
    manager(string confPath) : serverCounter(0), sonPid(0), stat(0) {
        try {
            bt = ([=](){return unique_ptr<baseTools> (new baseTools(confPath));})();
            serverCounter = stoi(bt->getConf("num"));
            servers = ([=](){return unique_ptr<ServerNode[]>(new ServerNode[serverCounter]);})();
            initServers(bt->getConf("servers"));
        } catch (int e) {
            throw confException(e);
        }
        cout << "manager init Successful!" << endl;    
    }
    ~manager() {} 

    void showServers() {
        cout << "servers num is " << serverCounter << endl;
        cout << "servers: [ " << endl;
        for(int i = 0; i < serverCounter; ++i) {
            cout << "    hostName: " << servers[i].hostName << endl;
            cout << "    hostIp(port): " << servers[i].hostIp << ":" << servers[i].port << endl;
            if (servers[i].recvBuffer.empty()) cout << "    recvBuffer is empty" << endl;
            else cout << "    recvBuffer: " << servers[i].recvBuffer << endl;
            if (servers[i].sendBuffer.empty()) cout << "    sendBuffer is empty" << endl;
            else cout << "    sendBuffer: " << servers[i].sendBuffer << endl;
        }
        cout << "]" << endl;
        return ;
    }

    //子进程连接配置文件中所有服务器
    int getConnect() {
        int success = 0; 
        cout << "Connect servers..." << endl;
        for (int i = 0; i < serverCounter; ++i) {
            string hostIp = servers[i].hostIp;
            int port = servers[i].port;
            string checkMsg = "SYN";
            int connfd = -1;
            
            if ((connfd = socket_connect(port, hostIp.c_str())) == -1) {
                cout << "try" << i + 1 << endl;
                servers[i].errBuffer = "connect_server";
                continue;
            }
            cout << "ready for send " << checkMsg << endl;
            int n = 0;
            if ((n = sendMsg(connfd, checkMsg)) < 0) cout << "send < 0" << endl;
            cout << "send over " << n << endl;
            servers[i].connfd = connfd;
            success++;
        }
        return success;
    }

    void disConnect(int connfd) {
        close(connfd);
        return ;
    }
 
    int Start() {
        if (!getConnect()) return -1;
        //如果开启接收则打开注释
        sonPid = fork();
        if (sonPid) return sonPid;
        //return -1;

        string recvBuffer = "";
        while (!isExit(recvBuffer)) {
        //if (!isExit(recvBuffer)) { 
            int len = recvMsg(servers[0].connfd, recvBuffer);
            if (len <= 0) exit(0);
            cout << recvBuffer << flush;
            servers[0].recvBuffer = recvBuffer;
        }
        disConnect(servers[0].connfd);
        exit(0);
    }
    
    inline bool isExit(string order) {
        return order == "exit";
    }
 
    void Local() {
        string sendBuffer;
        while (!isExit(sendBuffer)) {
            sendBuffer.clear();
            cout << ">> ";
            cin >> sendBuffer;
            //int len = sendMsg(servers[0].connfd, sendBuffer);
            //if (len <= 0) break;
            cout << sendBuffer << endl;
        }
        return ;
    }

    int getSonPid() {
        return this->sonPid;
    }

    int getStat() {
        return this->stat;
    }

private:
    void initServers(string serversDis) {
        //cout << "serversDis: " << serversDis << endl;
        vector<string> serversData = bt->split(serversDis, ",");
        int counter = 0;
        for(vector<string>::iterator iter = serversData.begin(); iter != serversData.end(); ++iter) {
            vector<string> serverData = bt->split(*iter, ":");
            servers[counter].hostName = serverData[0];
            servers[counter].hostIp = serverData[1];
            servers[counter].port = stoi(serverData[2]);
            counter++;
        }
    }
    
};

int main() {
    try {
        unique_ptr<manager> daniel(new manager("conf/manager.conf"));
        daniel->showServers();
        daniel->Start();
        cout << "pid = " << daniel->getSonPid() << endl;
        daniel->Local();
    } catch (confException e) {
        e.show();
    }
    return monitor::byebye();
}
