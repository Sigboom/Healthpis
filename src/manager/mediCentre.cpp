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

using std::string;
using std::unique_ptr;
using std::queue;

class doctor {
public:
    virtual void accept() = 0;
};

class netDoctor : public doctor {
public:
    netDoctor(string symptom) {}
    void accept();
};

class cofDoctor : public doctor {
    
};

class outPatient {
private:
    queue<doctor> dq;
public:
    outPatient(){}
    ~outPatient(){}

    void toRegister(string symptom, unique_ptr<ServerNode> &servers) { 
        int pos = 0;
        if ((pos = symptom.find("send")) != string::npos) {
            string temp = symptom.substr(pos + 4);
            dq.push((new netDoctor(temp)));
            int len = sendMsg(servers[0].connfd, temp);
            if (len <= 0) return;
        } else cout << symptom << endl;
        return ;
    }

    void treat() {
        doctor *doc = dq.front();
        dq.pop();
        doc->accept();
        return ;
    }
};


