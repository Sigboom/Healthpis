/*************************************************************************
	> File Name: master.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 三  8/28 21:07:07 2019
 ************************************************************************/

#include <iostream>
#include <string.h>
#include <string>
#include "mynet.h"

namespace monitor {
    int hello() {
        std::cout << "Hello World!" << std::endl;
        return 0;
    }
}

class waiter {
public:
    waiter(int port) : port(port), socketfd(0), connfd(0){
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
        
        while (is_exit(recv_buff)) {
            recv_buff.clear();
            int len = recv(connfd, recv_buff, MAXLINE, 0);
            if (len <= 0) break;
            std::cout << recv_buff;
        }
        return 0;
    }

    bool is_exit(std::string order) {
        return order != "exit";
    }

    int get_order() {
        while (is_exit(send_buff)) {
            send_buff.clear();
            std::cin >> send_buff;
            int len = send(connfd, send_buff, MAXLINE, 0);
            if (len <= 0) break;
        }
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
    int port = 5555;
    waiter *doni = new waiter(port);
    std::cout << "pid = " << doni->accept_node() << std::endl;
    doni->get_order();
    delete doni;
    return monitor::hello();
}
