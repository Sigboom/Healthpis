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
using std::flush;

namespace monitor {
    int byebye() {
        std::cout << "Bye~Bye~" << std::endl;
        return 0;
    }
}

class manager : public sigNet {
private:
    shared_ptr<mediCentre> mc;
    int sonPid;

public:
    manager(string confPath);
    ~manager();

    int Start();
    void Local();
    
    int getConnect();
    void disConnect(int connfd);
    inline bool isExit(string order);

    int getSonPid();
    int getStat();

private:
    void initDoctor();
};

#endif
