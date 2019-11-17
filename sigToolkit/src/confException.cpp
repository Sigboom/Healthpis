/*************************************************************************
	> File Name: confException.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 日 11/ 3 00:05:00 2019
 ************************************************************************/

#include "../include/confException.h"

using std::string;
using std::cout;
using std::endl;

confException::confException(int error) {
    switch(error) {
        case -1: msg = "can't find conf file!"; break;
        case -2: msg = "something error in conf file!"; break;
        case -3: msg = "no such key in conf file!"; break;
        case -4: msg = "no such value in conf file!"; break;
        default: msg = "understand error!!";
    }
}

confException::confException(std::invalid_argument error) {
    cout << "stationType in configure is wrong!" << endl;
    cout << "it is like:" << endl;
    cout << "stationType=[ stationName:0.0.0.0:0 ]" << endl;
}

void confException::show() {
    cout << msg << endl;
    return ;
}

