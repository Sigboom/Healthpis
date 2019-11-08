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

using std::shared_ptr;
using std::make_shared;
using std::list;
using std::string;

class doctor {
private:
    shared_ptr<doctor> nextDoctor;
public:
    virtual ~doctor(){};
    virtual void show();
    //成功执行返回 1
    virtual void execute(string sym) = 0;
    void setNextDoctor(shared_ptr<doctor> nextDoctor);
    shared_ptr<doctor> getNextDoctor();
};


class sigDoctor: public doctor {
public:
    void execute(string sym);
};

class mediCentre {
private:
    list<shared_ptr<doctor> > dList;

public:
    mediCentre();

    void addDoctor(shared_ptr<doctor> newDoctor);    
    void showDoctor();

    void outPatient(string sym);
};

#endif
