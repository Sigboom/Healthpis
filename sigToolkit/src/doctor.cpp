/*************************************************************************
	> File Name: doctor.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/14 23:44:05 2019
 ************************************************************************/

#include <typeinfo>
#include <iostream>
#include "../include/doctor.h"

using std::string;
using std::cout;
using std::endl;

void doctor::showDoctor() {
    cout << typeid(*this).name() << ": dlist.size()" << dlist.size() << endl;
    return ;
}

void doctor::addDoctor(shared_ptr<doctor> newDoctor) {
    if (dlist.size()) newDoctor->setNextDoctor(dlist.front());
    dlist.push_front(newDoctor);
    return ;
}

void doctor::setNextDoctor(shared_ptr<doctor> nextDoctor) {
    this->nextDoctor = nextDoctor;
    return ;
}

#include "../include/doctorException.h"

shared_ptr<doctor> &doctor::getNextDoctor() {
    if (!this->nextDoctor) throw doctorException();
    return this->nextDoctor;
}

void sigDoctor::execute(string sym) {
    try {
        dlist.front()->execute(sym);
    } catch (doctorException e) {
        e.show();
    }
    return ;
}
