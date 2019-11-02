/*************************************************************************
	> File Name: confException.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 六 11/ 2 10:24:09 2019
 ************************************************************************/

#ifndef _CONFEXCEPTION_H
#define _CONFEXCEPTION_H

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class confException {
private:
    string msg;
public:
    confException(int error) {
        switch(error) {
            case -1: msg = "can't find conf file!"; break;
            case -2: msg = "something error in conf file!"; break;
            case -3: msg = "no such key in conf file!"; break;
            default: msg = "understand error!!";
        }
    }

    void show() {
        cout << msg << endl;
        return ;
    }
};

#endif
