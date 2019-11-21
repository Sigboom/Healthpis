/*************************************************************************
	> File Name: mediCentre.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五 11/ 8 18:33:18 2019
 ************************************************************************/

#include "../include/mediCentre.h"

using std::cout;
using std::endl;

mediCentre::mediCentre(string stationType, string confPath) {
    sd = make_shared<sigDoctor>();
    try {
        bt = ([=](){return unique_ptr<baseTools> (new baseTools(confPath));})();
        stationCounter = initStation(bt->getConf(stationType));
    } catch (int e) {
        throw confException(e);
    } catch (std::invalid_argument e) {
        throw confException(e);
    } catch (...) {
        cout << "some unknow exception in conf!" << endl;
    }
}

int mediCentre::initStation(string stationsDes) { 
    //cout << "get stationDes " << stationsDes << endl;
    if (stationsDes.size() == 0) throw -4;
    vector<string> stationDes = bt->split(stationsDes, ",");
    stations = ([=](){return unique_ptr<StationNode[]>(new StationNode[stationDes.size()]);})();
    int i = 0;
    for(vector<string>::iterator iter = stationDes.begin(); iter != stationDes.end(); ++iter) {
        vector<string> stationData = bt->split(*iter, ":");
        stations[i].hostName = stationData[0];
        stations[i].hostIp = stationData[1];
        stations[i].port = stoi(stationData[2]);
        ++i;
    }
    return stationDes.size();
}

int mediCentre::showStations() {
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
        cout << "    stat: " << stations[i].state << endl;
        if (stations[i].state == 0) counter++;
    }
    cout << "]" << endl;
    return counter;
}

void mediCentre::addDoctor(shared_ptr<doctor> newDoctor) {
    sd->addDoctor(newDoctor);
    return ;
}

void mediCentre::showDoctor() {
    sd->showDoctor();
    //cout << "There are " << dList.size() << " doctors in you Sigpital!" << endl;
    //for (auto it = dList.begin(); it != dList.end(); ++it)
    //    (*it)->show();
    return ;
}

void mediCentre::outPatient(string sym) {
    sd->execute(sym);
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

void mediCentre::setRecvBuffer(int id, string msg) {
    stations[id].recvBuffer = msg;
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

string mediCentre::getRecvBuffer(int id) {
    return stations[id].recvBuffer;
}

int mediCentre::getCounter() {
    //cout << "Successful getCounter:" << this->stationCounter << endl;
    return this->stationCounter;
}

int mediCentre::getPort(int id) {
    return stations[id].port;
}

string mediCentre::getHostName(int id) {
    return stations[id].hostName;
}

string mediCentre::getHostIp(int id) {
    return stations[id].hostIp;
}

string mediCentre::getLogPath() {
    return bt->getConf("logPath");
}

int mediCentre::getConnfd(int id) {
    return stations[id].connfd;
}

void mediCentre::setConnfd(int id, int connfd) {
    stations[id].connfd = connfd;
    return ;
}
