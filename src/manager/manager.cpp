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
       mc = make_shared<mediCentre>("servers", confPath);
    } catch (confException e) {
        e.show();
        cout << "manager init failed!" << endl;    
        exit(1);
    }
    initDoctor();
    cout << "manager init Successful!" << endl;    
}

manager::~manager() {} 

void manager::showStations() {
    mc->showStations();
    return;
}

//子进程连接配置文件中所有服务器
int manager::getConnect() {
    cout << "Connect servers..." << endl;
    mc->outPatient("connect all");
    return mc->showStations();
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

    //子进程应根据服务器数开辟多个线程
    string recvBuffer = "";
    int id = 0;
    while (!isExit(recvBuffer)) {
        int len = recvMsg(mc->getConnfd(id), recvBuffer);
        if (len <= 0) exit(0);
        cout << recvBuffer << flush;
        string server = mc->getHostName(id);
        mc->setRecvBuffer(id, recvBuffer);
        string sym = server + ">:" + recvBuffer;
        mc->outPatient(sym);
    }
    disConnect(mc->getConnfd(id));
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
        getline(cin, buffer);
        if (!buffer.length()) continue;
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
    mc->addDoctor(make_shared<serverDoctor>(mc));
    return ;
}
