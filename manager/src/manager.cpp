/*************************************************************************
	> File Name: manager.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二  10/ 22 17:52:21 2019
 ************************************************************************/

#include "../include/manager.h"
#include "../include/serverDoctor.h"

manager::manager(string confPath) : sonPid(0) {
    try {
       mc = make_shared<mediCentre>("servers", confPath);
    } catch (confException e) {
        e.show();
        cout << "manager init failed!" << endl;    
        exit(1);
    }
#ifdef SIG_INIT
    cout << "mc init over!" << endl;
#endif
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
    int status = 0;
    while (status != EXIT) {
        if (mc->recvMsg(mc->getConnfd(id), recvBuffer) <= 0) break;
        cout << "recvMsg: " << recvBuffer << endl;
        mc->setRecvBuffer(id, recvBuffer);
        status = mc->outPatient(mc->getHostName(id) + ">:" + recvBuffer);
    }
    disConnect(id);
    exit(0);
}

void manager::Local() {
    string buffer;
    while (true) {
        buffer.clear();
        cout << ">> ";
        mc->getline(cin, buffer);
        if (!buffer.length()) continue;
        trim(buffer);
        if(mc->outPatient(buffer) == EXIT) break;
    }
    return ;
}

int manager::getSonPid() {
    return this->sonPid;
}

void manager::initDoctor() {
    mc->addDoctor(make_shared<serverDoctor>(mc));
    return ;
}
