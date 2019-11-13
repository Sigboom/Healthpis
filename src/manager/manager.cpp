/*************************************************************************
	> File Name: manager.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二  10/ 22 17:52:21 2019
 ************************************************************************/

#include "manager.h"
#include "myDoctor.cpp"

manager::manager(string confPath) : sonPid(0) {
    try {
       mc = make_shared<mediCentre>(new mediCentre("servers", confPath));
    } catch (confException e) {
        e.show();
    }
    initDoctor();
    cout << "manager init Successful!" << endl;    
}

manager::~manager() {} 

//子进程连接配置文件中所有服务器
int manager::getConnect() {
    cout << "Connect servers..." << endl;
    mc->outPatient("connect all");
    return mc->showStation();
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
    //string logPath = bt->getConf("logPath");
    int pos = 0;
    while (!isExit(recvBuffer)) {
        int len = recvMsg(servers[0].connfd, recvBuffer);
        if (len <= 0) exit(0);
        cout << recvBuffer << flush;
        string server = mc->getHostName(0);
        servers[0].recvBuffer = recvBuffer;
        string sym = server + ": " + recvBuffer;
        mc->outPatient(sym);
        
        //fileDoctor
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

void manager::initDoctor() {
    mc->addDoctor(make_shared<myDoctor>());
    mc->addDoctor(make_shared<netDoctor>());
    return ;
}
