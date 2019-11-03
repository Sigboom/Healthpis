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
        default: msg = "understand error!!";
    }
}

void confException::show() {
    cout << msg << endl;
    return ;
}

