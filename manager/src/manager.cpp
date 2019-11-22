/*************************************************************************
	> File Name: manager.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二  10/ 22 17:52:21 2019
 ************************************************************************/

#include "../include/manager.h"
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

int manager::showStations() {
    return mc->showStations();
}

//子进程连接配置文件中所有服务器
int manager::getConnect() {
    cout << "Connect servers..." << endl;
    mc->outPatient("connect all");
    return mc->showStations();
}

void manager::disConnect(int id) {
    int connfd = mc->getConnfd(id);
    close(connfd);
    cout << mc->getHostName(id) << " disconnect." << endl;
    return ;
}

int manager::Start() {
    int temp = getConnect();
    cout << "temp:" << temp << endl;
    if (!temp) return -1;
    //如果开启接收则打开注释
    sonPid = fork();
    cout << "sonPid:" << sonPid << endl;
    if (sonPid) return sonPid;
    //return -1;

    //子进程应根据服务器数开辟多个线程
    
    cout << "fork over!" << endl;
    
    string recvBuffer = "";
    int id = 0;
    while (!isExit(recvBuffer)) {
        if (mc->recvMsg(mc->getConnfd(id), recvBuffer) <= 0) break;
        cout << "recvMsg: " << recvBuffer << endl;
        mc->setRecvBuffer(id, recvBuffer);
        mc->outPatient(mc->getHostName(id) + ">:" + recvBuffer);
    }
    disConnect(id);
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
