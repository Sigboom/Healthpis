/*************************************************************************
	> File Name: myPatient.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/ 7 17:01:56 2019
 ************************************************************************/

#include <iostream>
using namespace std;

class myDoctor:public doctor {
public:
    myDoctor(){}
    ~myDoctor(){}

    void execute() {
        cout << "execute myDoctor!" << endl;
        return ;
    }
};

class netDoctor: public doctor {
public:
    netDoctor(){}
    ~netDoctor(){}

    void execute() {
        /*
        sy.checknet();    
        int len = sendMsg(server.connfd, sy.getSym());
        if (len <= 0) return;
        return ;
        */
        cout << "execute netDoctor" << endl;
    }
};

class myPatient: public patient {
public:
    myPatient(string talk) {
        symptom = talk;
    }
    ~myPatient() {}

    shared_ptr<doctor> askDoctor() {
        return  make_shared<myDoctor>();
    }
};

