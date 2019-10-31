/*************************************************************************
	> File Name: manager.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二  10/ 22 17:52:21 2019
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "../include/baseTools.h"
#include "../include/sigNet.h"

#define MSGLEN 100

using std::cin;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;
using std::string;
using std::move;

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
    
public:
    manager(string confPath) : serverCounter(0), sonPid(0) {
        unique_ptr<baseTools> b_temp (new baseTools(confPath));
        bt = move(b_temp);
        string str_temp = bt->getConf("num");
        if (str_temp.empty()) {
            cout << "conf error!" << endl;
            exit(1);
        }
        serverCounter = std::stoi(str_temp);
        unique_ptr<ServerNode[]> s_temp(new ServerNode[serverCounter]);
        servers = move(s_temp);
        string serverDis = bt->getConf("servers");
        initServers(serverDis);
        cout << "manager init Successful!" << endl;
    }
    ~manager() {}
    
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
            if ((n = send(connfd, checkMsg.c_str(), checkMsg.length(), 0)) < 0) cout << "send < 0" << endl;
            cout << "send over " << n << endl;
            servers[i].connfd = connfd;
            success++;
        }
        return success;
    }

    void disConnect() {

    }
 
    int Start() {
        if (getConnect()) {
            //sonPid = fork();
            //if (sonPid) return sonPid;
            sleep(3);
        } else return -1;


        string recvBuffer = "";
        //while (!isExit(recvBuffer)) {
        if (!isExit(recvBuffer)) { 
            recvBuffer.clear();
            cout << "I'm ready!" << endl;
            int len = recv(servers[0].connfd, (void *)recvBuffer.c_str(), MSGLEN, 0);
            if (len <= 0) return 0;
            cout << recvBuffer;
            servers[0].recvBuffer = recvBuffer;
        }
        //disConnect();
        return 0;
    }
    
    inline bool isExit(string order) {
        return order == "exit";
    }
 
    void sendOrder() {

        string sendBuffer;
        while (!isExit(sendBuffer)) {
            sendBuffer.clear();
            std::cout << ">> ";
            std::cin >> sendBuffer;
            int len = send(servers[0].connfd, sendBuffer.c_str(), sendBuffer.length(), 0);
            if (len <= 0) break;
        }
        return ;
    }

    int getSonPid() {
        return this->sonPid;
    }
};

int main() {
    unique_ptr<manager> daniel(new manager("conf/manager.conf"));
    daniel->showServers();
    daniel->Start();
    //cout << "pid = " << daniel->getSonPid() << endl;
    //if (daniel->getSonPid()) daniel->sendOrder();
    
    return monitor::byebye();
}
