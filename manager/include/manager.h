/*************************************************************************
	> File Name: manager.h
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二 11/ 5 09:24:39 2019
 ************************************************************************/

#ifndef _MANAGER_H
#define _MANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "../../sigToolkit/include/sigToolkit.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class manager {
private:
    shared_ptr<mediCentre> mc;
    int sonPid;

public:
    manager(string confPath);
    ~manager();

    int Start();
    void Local();
    int showStations();
    
    int getConnect();
    void disConnect(int connfd);

    int getSonPid();
    int getStat();

private:
    void initDoctor();
};

#endif
