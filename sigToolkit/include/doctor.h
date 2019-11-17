/*************************************************************************
	> File Name: doctor.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/14 23:26:49 2019
 ************************************************************************/

#ifndef _DOCTOR_H
#define _DOCTOR_H

#include <iostream>
#include <list>
#include <string>

using std::list;
using std::shared_ptr;
using std::make_shared;
using std::string;

class mediCentre;

class doctor {
protected:
    list<shared_ptr<doctor> > dlist;
    shared_ptr<doctor> nextDoctor;

public:
    virtual ~doctor(){};
    
    virtual void showDoctor();
    virtual void execute(string sym) = 0;
    void addDoctor(shared_ptr<doctor> newDoctor);

    void setNextDoctor(shared_ptr<doctor> nextDoctor);
    shared_ptr<doctor> &getNextDoctor();
};


class sigDoctor: public doctor {
public:
    void execute(string sym);
};

#endif
