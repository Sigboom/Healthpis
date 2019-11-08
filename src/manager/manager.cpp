/*************************************************************************
	> File Name: manager.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二  10/ 22 17:52:21 2019
 ************************************************************************/

#include "manager.h"
#include "myDoctor.cpp"

manager::manager(string confPath) : serverCounter(0), sonPid(0), stat(0) {
        try {
            bt = ([=](){return unique_ptr<baseTools> (new baseTools(confPath));})();
            serverCounter = stoi(bt->getConf("num"));
            servers = ([=](){return unique_ptr<ServerNode[]>(new ServerNode[serverCounter]);})();
            initServers(bt->getConf("servers"));
        } catch (int e) {
            throw confException(e);
        }
        initLocal();
        cout << "manager init Successful!" << endl;    
    }

manager::~manager() {} 

void manager::showServers() {
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
int manager::getConnect() {
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

void manager::disConnect(int connfd) {
    close(connfd);
    return ;
}

int manager::Start() {
    if (!getConnect()) return -1;
    //如果开启接收则打开注释
    sonPid = fork();
    if (sonPid) return sonPid;
    //return -1;

    string recvBuffer = "";
    string logPath = bt->getConf("logPath");
    int pos = 0;
    while (!isExit(recvBuffer)) {
    //if (!isExit(recvBuffer)) { 
        int len = recvMsg(servers[0].connfd, recvBuffer);
        if (len <= 0) exit(0);
        cout << recvBuffer << flush;
        servers[0].recvBuffer = recvBuffer;
        if ((pos = servers[0].recvBuffer.find("ans_101")) != string::npos) {
            string temp = servers[0].recvBuffer.substr(pos + 7);
            cout << "port(String): " << temp << endl;
            int filePort = stoi(temp);
            string filePath = logPath + servers[0].hostName + "/";
            cout << "log filePath: " << endl;
            recvFile(filePort, servers[0].hostIp, filePath);
        }
    }
    disConnect(servers[0].connfd);
    exit(0);
}

inline bool manager::isExit(string order) {
    return order == "exit" || order == "quit";
}

void manager::Local() {
    string buffer;
    while (true) {
        buffer.clear();
        cout << ">> ";
        cin >> buffer;
        trim(buffer);
        if (isExit(buffer)) break;
        mc->outPatient(buffer);
    }
    return ;
}

int manager::getSonPid() {
    return this->sonPid;
}

int manager::getStat() {
    return this->stat;
}

void manager::initServers(string serversDis) {
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

void manager::initLocal() {
    mc = ([](){return unique_ptr<mediCentre>(new mediCentre());})();
    mc->addDoctor(make_shared<myDoctor>());
    mc->addDoctor(make_shared<netDoctor>());
    return ;
}
