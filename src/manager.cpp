/*************************************************************************
	> File Name: client.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 二  9/ 3 17:52:21 2019
 ************************************************************************/

#include <iostream>
#include <string>
#include "mynet.h"

namespace monitor {
    int byebye() {
        std::cout << "Bye~Bye~" << std::endl;
        return 0;
    }
}

class manager {
public:
    manager(std::string host, int port) : host(host), port(port), connfd(0){
        initialize();
    }

    void initialize() {
        recv_buff.clear();
        send_buff = "200";
    }

    int connect_server() {
        if ((connfd = socket_connect(port, host.c_str())) == -1) {
            err = "connect_server";
            std::cout << err << std::endl;
            return -1;
        }

        send(connfd, send_buff.c_str(), send_buff.length(), 0);
        
        int pid = fork();
        if (pid) return pid;
        
        while (!is_exit(recv_buff)) {
            recv_buff.clear();
            std::cout << "I' ready!" << std::endl;
            int len = recv(connfd, (void *)recv_buff.c_str(), MAXLINE, 0);
            if (len <= 0) break;
            std::cout << recv_buff;
        }
        return 0;
    }

    bool is_exit(std::string order) {
        return order == "exit";
    }
    
    void send_order() {
        while (!is_exit(send_buff)) {
            send_buff.clear();
            std::cout << ">> ";
            std::cin >> send_buff;
            int len = send(connfd, send_buff.c_str(), send_buff.length(), 0);
            if (len <= 0) break;
        }
        return ;
    }

private:
    std::string host;
    int port;
    int connfd;
    std::string recv_buff, send_buff;
    std::string err;
};

int main() {
    std::string host = "49.235.212.3";
    int port = 5555;
    manager *daniel = new manager(host, port);
    int pid = daniel->connect_server();
    std::cout << "pid = " << pid << std::endl;
    if (pid) { 
        daniel->send_order();
        delete daniel;
    }
    return monitor::byebye();
}
