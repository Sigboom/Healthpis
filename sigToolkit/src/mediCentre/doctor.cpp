/*************************************************************************
	> File Name: doctor.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/ 7 11:15:25 2019
 ************************************************************************/

#include "patient.cpp"

using std::make_shared;

class doctor {
public:
    virtual ~doctor(){}
    virtual void execute() = 0;
};

class netDoctor: public doctor {
public:
    netDoctor(){}
    ~netDoctor(){}

    void execute() {
        /*
        sy.checknet();    
        int len = sendMsg(server.connfd, sy.getSym());
        if (len <= 0) return;
        return ;
        */
        cout << "execute netDoctor" << endl;
    }
};
