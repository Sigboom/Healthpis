/*************************************************************************
	> File Name: server.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 三  8/28 21:07:07 2019
 ************************************************************************/

#include <iostream>
#include <string.h>
#include <string>
#include "conf.h"
#include "mynet.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace monitor {
    int hello() {
        std::cout << "Hello World!" << std::endl;
        return 0;
    }
}

class waiter {
public:
    waiter(string confPath) : port(port), socketfd(0), connfd(0){
        initialize();
        if ((socketfd = socket_create(port)) == -1) {
            err = "socket_create";
        }
        if (err.length()) {
            std::cout << err << std::endl;
        } else {
            std::cout << "Waiting for client's request" << std::endl;
        }
    }

    void initialize() {
        recv_buff.clear();
        send_buff.clear();
    }

    int accept_node() {
        if ((connfd = accept(socketfd, 
                        (struct sockaddr *)NULL, 
                        NULL)) == -1) {
            err = "accept";
            std::cout << err << std::endl;
            return -1;
        }
        int pid = fork();
        if (pid) return pid;
        
        while (!is_exit(recv_buff)) {
            recv_buff.clear();
            int len = recv(connfd, (void *)recv_buff.c_str(), MAXLINE, 0);
            if (len <= 0) break;
            std::cout << recv_buff;
        }
        return 0;
    }

    bool is_exit(std::string order) {
        return order == "exit";
    }

    void get_order() {
        while (!is_exit(send_buff)) {
            send_buff.clear();
            std::cin >> send_buff;
            int len = send(connfd, send_buff.c_str(), send_buff.length(), 0);
            if (len <= 0) break;
        }
        return ;
    }

    int call_runner() {
        return 0;
    }

    int have_rest() {
        return 0;
    }

    ~waiter() {
        close(connfd);
        close(socketfd);
    }
    
private:
    int port;
    int socketfd;
    int connfd;
    std::string err;
    std::string recv_buff, send_buff;
};

int main() {
    waiter *doni = new waiter("manager.conf");
    /*
    std::cout << "pid = " << doni->accept_node() << std::endl;
    doni->get_order();
    delete doni;
    */
    return monitor::hello();
}
