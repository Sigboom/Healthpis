/*************************************************************************
	> File Name: doctorException.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 日 11/17 14:11:53 2019
 ************************************************************************/

#ifndef _DOCTOREXCEPTION_H
#define _DOCTOREXCEPTION_H

#include <iostream>
#include <string>

using std::string;

class doctorException {
private:
    string msg;

public:
    doctorException();
    void show();
};

#endif
