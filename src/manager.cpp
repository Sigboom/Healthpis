/*************************************************************************
	> File Name: client.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二  9/ 3 17:52:21 2019
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "conf.h"
#include "mynet.h"

using std::cin;
using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;
using std::string;

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

class manager {
private:
    string confPath;
    unique_ptr<ServerNode[]> servers;
    int serverCounter;
    int pid;
    
public:
    manager(string confPath) : serverCounter(0), confPath(confPath){
        //cout << getConf("num") << endl;
        serverCounter = std::stoi(getConf("num"));
        unique_ptr<ServerNode[]> m_temp(new ServerNode[serverCounter]);
        servers = std::move(m_temp);
        string serverDis = getConf("servers");
        initServers(serverDis);
        cout << "manager init Successful!" << endl;
    }
    ~manager() {}
    
    void initServers(string serverDis) {
        vector<string> serversData = split(serverDis, ",");
        int counter = 0;
        for(vector<string>::iterator iter = serversData.begin(); iter != serversData.end(); ++iter) {
            vector<string> serverData = split(*iter, ":");
            servers[counter].hostName = serverData[0];
            servers[counter].hostIp = serverData[1];
            servers[counter].port = stoi(serverData[2]);
            counter++;
        }
    }

    vector<string> split(const string &str,const string &pattern) {
        vector<string> resVec;
        if (str.empty()) return resVec;
        //方便截取最后一段数据
        std::string strs = str + pattern;
        size_t pos = strs.find(pattern), size = strs.size();
        while (pos != string::npos) {
            std::string x = strs.substr(0,pos);
            resVec.push_back(x);
            strs = strs.substr(pos+1, size);
            pos = strs.find(pattern);
        }
        return resVec;
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
        cout << "Connect servers..." << endl;
        for (int i = 0; i < serverCounter; ++i) {
            string hostIp = servers[i].hostIp;
            int port = servers[i].port;
            string checkMsg = "SYN";
            int connfd = -1;
            
            if ((connfd = socket_connect(port, hostIp.c_str())) == -1) {
                servers[i].errBuffer = "connect_server";
                return -1;
            }
            send(connfd, checkMsg.c_str(), checkMsg.length(), 0);
            servers[i].connfd = connfd;
        }
        return 0;
    }

    void disConnect() {

    }
    
    int Start() {
        if (getConnect() == -1) return -1;
        //pid = fork();
        //if (pid) return pid;

        string recvBuffer = "";
        while (!isExit(recvBuffer)) {
            recvBuffer.clear();
            cout << "I'm ready!" << endl;
            int len = recv(servers[0].connfd, (void *)recvBuffer.c_str(), MAXLINE, 0);
            if (len <= 0) break;
            cout << recvBuffer;
            servers[0].recvBuffer = recvBuffer;
        }
        //disConnect();
        return 0;
    }
    
    bool isExit(string order) {
        return order == "exit";
    }
/* 
    void sendOrder() {
        while (!is_exit(send_buff)) {
            send_buff.clear();
            std::cout << ">> ";
            std::cin >> send_buff;
            int len = send(connfd, send_buff.c_str(), send_buff.length(), 0);
            if (len <= 0) break;
        }
        return ;
    }
*/
    int getpid() {
        return this->pid;
    }
};

int main() {
    unique_ptr<manager> daniel(new manager("servers.conf"));
    daniel->showServers();
    daniel->Start();
    cout << "pid = " << daniel->getpid() << endl;
    //if (daniel->getpid()) daniel->sendOrder();
    
    return monitor::byebye();
}
