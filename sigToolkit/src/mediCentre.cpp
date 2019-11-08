/*************************************************************************
	> File Name: mediCentre.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/ 7 11:14:49 2019
 ************************************************************************/

#include <queue>
#include "../include/mediCentre.h"

using std::queue;
using std::shared_ptr;

outPatient::outPatient() {}
outPatient::~outPatient(){}

void outPatient::toRegister(shared_ptr<patient> pa) {
    dq.push(pa->askDoctor());
    return ;
}

void outPatient::treat() {
    for(auto doc = dq.front(); !dq.empty(); dq.pop()) {
        doc->execute();
    }
    return ;
}

