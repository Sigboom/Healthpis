/*************************************************************************
	> File Name: myDoctor.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/ 7 17:01:56 2019
 ************************************************************************/

#include <boost/regex.hpp>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using boost::regex;
using boost::regex_match;
using std::stringstream;

class myDoctor:public doctor {
public:
    void execute(string sym) {
        if (sym == "myDoctor") cout << "execute myDoctor!" << endl;
        else getNextDoctor()->execute(sym);
        return ;
    }
};

class netDoctor: public doctor {
public:
    void execute(string sym) {
        /*
        sy.checknet();    
        int len = sendMsg(server.connfd, sy.getSym());
        if (len <= 0) return;
        return ;
        */
        if (sym == "net") cout << "execute netDoctor" << endl;
        else getNextDoctor()->execute(sym);
        return ;
    }
};

class fileDoctor: public doctor {
private:
    shared_ptr<mediCentre> mc;

public:
    fileDoctor(shared_ptr<mediCentre> mc): mc(mc) {}
    
    void execute(string sym) {
        int id = stoi(sym);
        string buffer = mc->getSendBuffer(id);
        regex expr("^[0-9]*$");
        if (regex_match(buffer, expr)) {
            int connfd = mc->getConnfd(id);
            mc->sendMsg(connfd, buffer);
        } else {
            getNextDoctor()->execute(sym);
        }
        return ;
    }
};

class serverDoctor: public doctor {
private:
    list<shared_ptr<doctor> > dList;     
    shared_ptr<mediCentre> mc;

public:
    serverDoctor(shared_ptr<mediCentre> mc): mc(mc) {
        dList.push_front(make_shared<sigDoctor>(mc)); 
        dList.push_front(make_shared<fileDoctor>(mc)); 
    }

    void addDoctor(shared_ptr<doctor> newDoctor) {
        newDoctor->setNextDoctor(dList.front());
        dList.push_front(newDoctor);
        return ;
    }
    
    void execute(string sym) {
        int pos = 0;
        if ((pos = sym.find(":")) != string::npos) {
            cout << "exec serverDoctor" << endl;
            string server = sym.substr(0, pos);
            string msg = sym.substr(pos + 1);
            trim(server);
            trim(msg);
            try {
                int id = mc->catchStation(server);
                mc->setSendBuffer(id, msg); 
                stringstream ssTemp;
                ssTemp << id;
                dList.front()->execute(ssTemp.str()); 
            } catch (serverException e) {
                e.show();
            }
        } else {
            getNextDoctor()->execute(sym);
        }
        return ;
    }
};

