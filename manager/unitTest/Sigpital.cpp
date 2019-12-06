/*************************************************************************
	> File Name: Sigpital.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二 11/ 5 09:36:05 2019
 ************************************************************************/

#ifdef SIG_SERVER
    #define SIG_LOCAL
#endif
#ifdef SIG_LOCAL
    #define SIG_INIT
#endif

#ifndef SIG_INIT
#include <iostream>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::map;
using std::pair;

void unitDes(map<string, string> &unit) {
    unit.insert(pair<string, string> (
                "SIG_INIT",
                "Test for reading configure file."
                ));

    unit.insert(pair<string, string> (
                "SIG_LOCAL",
                "Test for running localhost."
                ));

    unit.insert(pair<string, string> (
                "SIG_SERVER",
                "Test for connecting servers."
                ));
    return ;
}

#else
#include "../include/manager.h"
#endif

namespace monitor {
    int byebye() {
        std::cout << "Bye~Bye~" << std::endl;
        return 0;
    }
}

int main() {
#ifdef SIG_INIT
    unique_ptr<manager> daniel(new manager("../conf/manager.conf"));
#ifdef SIG_SERVER
    daniel->Start();
    cout << "pid = " << daniel->getSonPid() << endl;
#endif
#ifdef SIG_LOCAL
    daniel->Local();
#endif
#else
    map<string, string> unit;
    unitDes(unit);
    cout << endl;
    cout << "please use \"$ make DEBUG=SIG_... \"" << endl;
    cout << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "| You can choose:"<< endl;
    for (auto it = unit.begin(); it != unit.end(); ++it) {
        cout << "|    " << it->first << ": " << it->second << "   " << endl;
    }
    cout << "---------------------------------------------------------" << endl;
#endif
    return monitor::byebye();
}

