/*************************************************************************
	> File Name: serverException.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 三 11/13 22:32:26 2019
 ************************************************************************/

#ifndef _SERVEREXCEPTION_H
#define _SERVEREXCEPTION_H

#include <iostream>
#include <string>

using std::string;

class serverException {
private:
    string msg;
public:
    serverException();
    void show();
};

#endif

