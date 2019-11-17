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

class confException {
private:
    string msg;
public:
    confException(int error);
    confException(std::invalid_argument error);
    void show();
};

#endif
