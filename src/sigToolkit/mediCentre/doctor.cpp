/*************************************************************************
	> File Name: doctor.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/ 7 11:15:25 2019
 ************************************************************************/

#include "patient.cpp"

using std::make_shared;

class doctor {
public:
    virtual ~doctor(){}
    virtual void execute() = 0;
};

class netDoctor: public doctor {
private:
    patient pa;
public:
    netDoctor(patient pa): pa(pa) {
    }

    void execute() {
        /*
        sy.checknet();    
        int len = sendMsg(server.connfd, sy.getSym());
        if (len <= 0) return;
        return ;
        */
        pa.show();
    }
};


class confDoctor: public doctor {
private:
    patient pa;
public:
    confDoctor(patient pa): pa(pa) {}
    void execute() {
        pa.checkconf();
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
            return make_shared<netDoctor>(pa);
        }
        return make_shared<sigDoctor>(pa);
    }
};

