/*************************************************************************
	> File Name: mediCentre.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 五 11/ 8 18:33:18 2019
 ************************************************************************/

#include <typeinfo>
#include "../include/mediCentre.h"

using std::cout;
using std::endl;

void doctor::show() {
    cout << typeid(*this).name()<< endl;
    return ;
}

void doctor::setNextDoctor(shared_ptr<doctor> nextDoctor) {
    this->nextDoctor = nextDoctor;
    return ;
}

shared_ptr<doctor> doctor::getNextDoctor() {
    return this->nextDoctor;
}

void sigDoctor::execute(string sym) {
    cout << "symptom: " << sym  << " is unclear!" << endl;
    return ;
}


mediCentre::mediCentre() {
    dList.push_front(make_shared<sigDoctor>());
}

void mediCentre::addDoctor(shared_ptr<doctor> newDoctor) {
    newDoctor->setNextDoctor(dList.front());
    dList.push_front(newDoctor);
    return ;
}

void mediCentre::showDoctor() {
    cout << "There are " << dList.size() << " doctors in you Sigpital!" << endl;
    for (auto it = dList.begin(); it != dList.end(); ++it)
        (*it)->show();
    return ;
}

void mediCentre::outPatient(string sym) {
    dList.front()->execute(sym);
    return ;
}
