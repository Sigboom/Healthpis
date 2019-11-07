/*************************************************************************
	> File Name: mediCentre.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二 11/ 5 23:10:05 2019
 ************************************************************************/

#include <iostream>
#include <string>
#include <queue>
#include "manager.h"
#include "patient.cpp"

using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::queue;

class doctor {
public:
    virtual ~doctor(){}
    virtual void execute() = 0;
};

class netDoctor: public doctor {
private:
    symptom sy;
    unique_ptr<ServerNode> server;
public:
    netDoctor(symptom sy, unique_ptr<ServerNode> &server): sy(sy) {
        this->server = move(server);
    }

    void execute() {
        sy.checknet();    
        int len = sendMsg(server.connfd, sy.getSym());
        if (len <= 0) return;
        return ;
    }
};


class confDoctor: public doctor {
private:
    symptom sy;
public:
    confDoctor(symptom sy): sy(sy) {}
    void execute() {
        sy.checkconf();
        return ;
    }
};

class sigDoctor: public doctor {
private:
    patient pa;
public:
    sigDoctor(){}
    sigDoctor(patient pa): pa(pa) {}
    
    void execute() {
        pa.show();
        return ;
    }

    shared_ptr<doctor> check(patient pa) {
        string sym = pa.getSym();
        if (sym.find("send") != string::npos) {
            sym = sym.substr(4);
            return &(new netDoctor(*this, servers[0]));
        }
        return make_shared<sigDoctor>(*this);
    }
};

class outPatient {
private:
    queue<doctor> dq;
    sigDoctor doc;
public:
    outPatient() {}
    ~outPatient(){}

    void toRegister(patient pa) { 
        int pos = 0;
        shared_ptr<doctor> bookform = doc.check(pa);
        dp.push(bookform);
        return ;
    }

    void treat() {
        for(doctor *doc = dq.front(); !dq.empty(); dq.pop())
            doc->execute();
        return ;
    }
};


