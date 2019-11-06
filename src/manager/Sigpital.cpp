/*************************************************************************
	> File Name: Sigpital.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二 11/ 5 09:36:05 2019
 ************************************************************************/

#include "manager.cpp"

int main() {
    try {
        unique_ptr<manager> daniel(new manager("conf/manager.conf"));
        daniel->showServers();
        daniel->Start();
        cout << "pid = " << daniel->getSonPid() << endl;
        daniel->Local();
    } catch (confException e) {
        e.show();
    }
    return monitor::byebye();
}

