/*************************************************************************
	> File Name: mediCentre.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/ 7 11:25:08 2019
 ************************************************************************/

#ifndef _MEDICENTRE_H
#define _MEDICENTRE_H

#include <iostream>
#include <string>
#include <queue>

using std::string;
using std::queue;
using std::shared_ptr;

class doctor;

class patient {
protected:
    string symptom;
public:
    patient(){}
    patient(string talk): symptom(talk) {}
    virtual ~patient(){}
    
    virtual shared_ptr<doctor> askDoctor() = 0;
    
    string getSym() {
        return this->symptom;
    }

    void setSym(string sym) {
        this->symptom = sym;
        return ;
    }
};

class doctor {
public:
    virtual ~doctor(){}
    virtual void execute() = 0;
};

class outPatient {
private:
    queue<shared_ptr<doctor> > dq;
    
public:
    outPatient();
    ~outPatient();

    void toRegister(shared_ptr<patient> pa);
    void treat();
};
#endif
