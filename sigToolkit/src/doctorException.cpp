/*************************************************************************
	> File Name: doctorException.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 日 11/17 14:13:23 2019
 ************************************************************************/

#include "../include/doctorException.h"

using std::string;
using std::cout;
using std::endl;

doctorException::doctorException() {
    msg = "no doctor can fix this sym!!";
}

void doctorException::show() {
    cout << msg << endl;
    return ;
}

