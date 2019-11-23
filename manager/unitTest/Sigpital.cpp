/*************************************************************************
	> File Name: Sigpital.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二 11/ 5 09:36:05 2019
 ************************************************************************/

#include "../include/manager.h"

namespace monitor {
    int byebye() {
        std::cout << "Bye~Bye~" << std::endl;
        return 0;
    }
}

int main() {
    unique_ptr<manager> daniel(new manager("../conf/manager.conf"));
#ifndef SIG_INIT
    daniel->Start();
    cout << "pid = " << daniel->getSonPid() << endl;
    daniel->Local();
#else
    
#endif
    return monitor::byebye();
}

