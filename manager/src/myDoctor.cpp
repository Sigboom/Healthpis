/*************************************************************************
	> File Name: myDoctor.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 四 11/ 7 17:01:56 2019
 ************************************************************************/

#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include <dirent.h>

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
    string logPath;

public:
    fileDoctor(shared_ptr<mediCentre> mc): mc(mc) {
        logPath = mc->getLogPath();
    }
    
    void execute(string sym) {
        int id = stoi(sym);
        string sendBuffer = mc->getSendBuffer(id);
        string recvBuffer = mc->getRecvBuffer(id);
        regex sendExpr("^[0-9]+$"), recvExpr("^ans_[1-9][0-9][1-9] [1-9][0-9]*$");
        cout << "will send:" << sendBuffer << endl;
        cout << "will recv:" << recvBuffer << endl;
        if (regex_match(sendBuffer, sendExpr)) {
            int connfd = mc->getConnfd(id);
            mc->sendMsg(connfd, sendBuffer);
        } else if (regex_match(recvBuffer, recvExpr)) { 
            string temp = recvBuffer.substr(8);
            cout << "port(String): " << temp << endl;
            int filePort = stoi(temp);
            string filePath = logPath + mc->getHostName(id) + "/";
            mkdirPath(filePath);
            cout << "checked filePath: " << filePath << endl;
            mc->recvFile(filePort, mc->getHostIp(id), filePath);
        } else {
            getNextDoctor()->execute(sym);
        }
        return ;
    }

private:
    void mkdirPath(string path) {
        DIR *dir = NULL; 
        if ((dir = opendir(path.c_str())) == NULL) {
            string commend = "mkdir -p " + path;
            system(commend.c_str());
        }
        return;
    }
};

class serverDoctor: public doctor {
private:
    shared_ptr<mediCentre> mc;

public:
    serverDoctor(shared_ptr<mediCentre> mc): mc(mc) {
        addDoctor(make_shared<fileDoctor>(mc)); 
    }

    void execute(string sym) {
        int pos = 0;
        
        //send or recv msg or file
        if ((pos = sym.find(":")) != string::npos) {
            cout << "exec serverDoctor sym: " << sym << endl;
            string server = sym.substr(0, pos - 1);
            cout << "send or recv: " << sym[pos - 1] << endl;
            bool send = (sym[pos - 1] == '<');
            bool recv = (sym[pos - 1] == '>');
            string msg = sym.substr(pos + 1);
            trim(server);
            trim(msg);
            cout << "server: " << server << ", msg: " << msg << endl;
            try {
                int id = mc->catchStation(server);
                if (send) mc->setSendBuffer(id, msg); 
                if (recv) mc->setRecvBuffer(id, msg);
                stringstream ssTemp;
                ssTemp << id;
                dlist.front()->execute(ssTemp.str()); 
            } catch (serverException e) {
                e.show();
            }
            return ;
        }
        
        //long connect
        if (sym.find("connect ", 0, 8) != string::npos) {
            string station = sym.substr(8);
            connect(station);
            return ;
        }
        getNextDoctor()->execute(sym);
        return ;
    }

private:
    void s_connect(int id) {
        string hostName = mc->getHostName(id);
        string hostIp = mc->getHostIp(id);
        int port = mc->getPort(id);
        string checkMsg = "SYN";
        int connfd = -1;

        cout << "try to connect " << hostName << endl;
        if ((connfd = mc->socket_connect(port, hostIp.c_str())) == -1) {
            mc->setErrBuffer(id, "connect_server");
            mc->setState(id, -1);
            return ;
        }
        if (mc->sendMsg(connfd, checkMsg) <= 0) cout << "send < 0" << endl;
        if (mc->recvMsg(connfd, checkMsg) <= 0) {
            cout << "recv < 0" << endl;
            mc->setErrBuffer(id, "connect_server2");
        }
        mc->setConnfd(id, connfd);
        mc->setState(id, 0);
        cout << hostName << " connect successfully!" << endl;
        return ;
    }

    void connect(string station) {
        cout << "sigDoctor catch sym station: " << station << endl;
        if (station == "all") {
            int counter = mc->getCounter();
            for (int id = 0; id < counter; ++id) s_connect(id);
            return ;
        }
        int id = mc->catchStation(station);
        s_connect(id);
        return ;
    }
};

