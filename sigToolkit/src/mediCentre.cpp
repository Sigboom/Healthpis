/*************************************************************************
	> File Name: mediCentre.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五 11/ 8 18:33:18 2019
 ************************************************************************/

#include <typeinfo>
#include "../include/mediCentre.h"

using std::cout;
using std::endl;

void doctor::show() {
    cout << typeid(*this).name()<< endl;
    return ;
}

void doctor::setNextDoctor(shared_ptr<doctor> nextDoctor) {
    this->nextDoctor = nextDoctor;
    return ;
}

shared_ptr<doctor> &doctor::getNextDoctor() {
    return this->nextDoctor;
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
        cout << "symptom: " << sym  << " is unclear!" << endl;
    return ;
}

mediCentre::mediCentre(string stationType, string confPath) {
    dList.push_front(make_shared<sigDoctor>());
    try {
        bt = ([=](){return unique_ptr<baseTools> (new baseTools(confPath));})();
        stationCounter = initStation(bt->getConf(stationType));
    } catch (int e) {
        throw confException(e);
    }
}

int mediCentre::initStation(string stationDes) { 
    vector<string> stationData = bt->split(stationDes, ",");
    stations = ([=](){return unique_ptr<StationNode[]>(new StationNode[stationData.size()]);})();
    int i = 0;
    for(vector<string>::iterator iter = stationData.begin(); iter != stationData.end(); ++iter) {
        vector<string> stationDes = bt->split(*iter, ":");
        stations[i].hostName = stationData[0];
        stations[i].hostIp = stationData[1];
        stations[i].port = stoi(stationData[2]);
        ++i;
    }
    return stationData.size();
}

int mediCentre::showStation() {
    int counter = 0;
    cout << "Stations num is " << stationCounter << endl;
    cout << "Stations: [ " << endl;
    for(int i = 0; i < stationCounter; ++i) {
        cout << "    hostName: " << stations[i].hostName << endl;
        cout << "    hostIp(port): " << stations[i].hostIp << ":" << stations[i].port << endl;
        if (stations[i].recvBuffer.empty()) cout << "    recvBuffer is empty" << endl;
        else cout << "    recvBuffer: " << stations[i].recvBuffer << endl;
        if (stations[i].sendBuffer.empty()) cout << "    sendBuffer is empty" << endl;
        else cout << "    sendBuffer: " << stations[i].sendBuffer << endl;
        cout << "stat: " << stations[i].state << endl;
        if (!stations[i].state) counter++;
    }
    cout << "]" << endl;
    return counter;
}

void mediCentre::addDoctor(shared_ptr<doctor> newDoctor) {
    newDoctor->setNextDoctor(dList.front());
    dList.push_front(newDoctor);
    return ;
}

void mediCentre::showDoctor() {
    cout << "There are " << dList.size() << " doctors in you Sigpital!" << endl;
    for (auto it = dList.begin(); it != dList.end(); ++it)
        (*it)->show();
    return ;
}

void mediCentre::outPatient(string sym) {
    dList.front()->execute(sym);
    return ;
}

int mediCentre::catchStation(string stationName) {
    for (int id = 0; id < stationCounter; ++id) {
        if (stationName == stations[id].hostName) {
            return id;
        }
    }
    throw serverException();
    return -1;
}

void mediCentre::setSendBuffer(int id, string msg) {
    stations[id].sendBuffer = msg;
    return ;
}

void mediCentre::setErrBuffer(int id, string msg) {
    stations[id].errBuffer = msg;
    return ;
}

void mediCentre::setState(int id, int stat) {
    stations[id].state = stat;
    return ;
}

string mediCentre::getSendBuffer(int id) {
    return stations[id].sendBuffer;
}

int mediCentre::getCounter() {
    return this->stationCounter;
}

int mediCentre::getPort(int id) {
    return stations[id].port;
}

string mediCentre::getHostIp(int id) {
    return stations[id].hostIp;
}

void mediCentre::setConnfd(int id, int connfd) {
    stations[id].connfd = connfd;
    return ;
}
