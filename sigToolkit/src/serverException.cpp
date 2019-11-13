/*************************************************************************
	> File Name: serverException.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 三 11/13 22:33:32 2019
 ************************************************************************/

#include "../include/serverException.h"

using std::string;
using std::cout;
using std::endl;

serverException::serverException() {
    msg = "server can't find!!";
}

void serverException::show() {
    cout << msg << endl;
    return ;
}

