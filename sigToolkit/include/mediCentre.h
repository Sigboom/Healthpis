/*************************************************************************
	> File Name: mediCentre.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 六 11/ 9 00:59:43 2019
 ************************************************************************/

#ifndef _MEDICENTRE_H
#define _MEDICENTRE_H

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "baseTools.h"
#include "confException.h"
#include "serverException.h"
#include "sigNet.h"
#include "doctor.h"

using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::list;
using std::string;
using std::vector;

typedef struct StationNode {
    string hostName;
    string hostIp;
    int port;
    string recvBuffer;
    string sendBuffer;
    string errBuffer;
    int connfd;
    int state;
} StationNode;

class mediCentre: public sigNet {
private:
    shared_ptr<sigDoctor> sd;
    unique_ptr<baseTools> bt;
    unique_ptr<StationNode[]> stations;
    int stationCounter;
    
public:
    mediCentre(string stationType, string confPath);

    int catchStation(string stationName);
    
    void setSendBuffer(int id, string msg); 
    void setRecvBuffer(int id, string msg); 
    void setErrBuffer(int id, string msg);
    void setConnfd(int id, int connfd);
    void setState(int id, int stat);

    string getSendBuffer(int id);
    string getRecvBuffer(int id);
    string getHostName(int id);
    string getHostIp(int id);
    int getPort(int id);
    int getConnfd(int id);
    int getCounter();
    string getLogPath();

    int showStations();
    void addDoctor(shared_ptr<doctor> newDoctor);    
    void showDoctor();
    
    void outPatient(string sym);

private:
    int initStation(string stationDes);
};

#endif
