/*************************************************************************
	> File Name: doctor.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/14 23:44:05 2019
 ************************************************************************/

#include <typeinfo>
#include <iostream>
#include "../include/doctor.h"

using std::string;
using std::cout;
using std::endl;

void doctor::showDoctor() {
    cout << typeid(*this).name() << ": dlist.size()" << dlist.size() << endl;
    return ;
}

void doctor::addDoctor(shared_ptr<doctor> newDoctor) {
    if (dlist.size()) newDoctor->setNextDoctor(dlist.front());
    dlist.push_front(newDoctor);
    return ;
}

void doctor::setNextDoctor(shared_ptr<doctor> nextDoctor) {
    this->nextDoctor = nextDoctor;
    return ;
}

shared_ptr<doctor> &doctor::getNextDoctor() {
    return this->nextDoctor;
}

#include "../include/mediCentre.h"

sigDoctor::sigDoctor() {
    nextDoctor = make_shared<ExpDoctor>();
    addDoctor(nextDoctor);
}

sigDoctor::sigDoctor(shared_ptr<mediCentre> mc): mc(mc) {
    nextDoctor = make_shared<ExpDoctor>();
    addDoctor(nextDoctor);
}

void sigDoctor::connect(string station) {
    if (station == "all") {
        int counter = mc->getCounter();
        for (int i = 0; i < counter; ++i) {
            string hostIp = mc->getHostIp(i);
            int port = mc->getPort(i);
            string checkMsg = "SYN";
            int connfd = -1;
            
            if ((connfd = mc->socket_connect(port, hostIp.c_str())) == -1) {
                cout << "try" << i + 1 << endl;
                mc->setErrBuffer(i, "connect_server");
                mc->setState(i, -1);
                continue;
            }
            //cout << "ready for send " << checkMsg << endl;
            int n = 0;
            if ((n = mc->sendMsg(connfd, checkMsg)) < 0) cout << "send < 0" << endl;
            cout << "send over " << n << endl;
            mc->setConnfd(i, connfd);
            mc->setState(i, 1);
        }
    }
}

void sigDoctor::execute(string sym) {
    if (sym.find("connect ", 0, 8) != string::npos) {
        string station = sym.substr(8);
        connect(station);
    } else 
        dlist.front()->execute(sym);
    return ;
}

void ExpDoctor::execute(string sym) {
    cout << "symptom: " << sym  << " is unclear!" << endl;
    return ; 
}
