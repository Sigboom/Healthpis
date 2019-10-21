/*************************************************************************
	> File Name: sigboom.cpp
	> Author: Doni Daniel
	> Mail: sigboom@163.com
	> Created Time: 一 10/21 11:21:50 2019
 ************************************************************************/

#include<iostream>
#include <fstream>
#include <string>

using std::endl;
using std::cout;
using std::string;
using std::ifstream;

class network {
public:
    int socket_create(int port) {
        int socketfd;
        struct sockaddr_in sock_addr;
        if ((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
            perror("socket_create");
            return -1;
        }

        sock_addr.sin_family = AF_INET; 
        sock_addr.sin_port = htons(port); 
        sock_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

        if (bind(socketfd, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == -1) { 
            perror("bind");
            return -1;
        }   
        if(listen(socketfd, 10) == -1) {
            perror("listen");
            return -1;
        }
        return socketfd;
    }

    int socket_connect(int port, const char *host) {
        int socketfd;
        struct sockaddr_in dest_addr;
        if ((socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
            perror("socket_connect");
            return -1;
        }

        dest_addr.sin_family = AF_INET; 
        dest_addr.sin_port = htons(port); 
        dest_addr.sin_addr.s_addr = inet_addr(host); 

        if (connect(socketfd, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) == -1) { 
            perror("connect");
            return -1;
        } 

        return socketfd;
    }
};

class sigboom {
public:
    network net;
protected: 
    string getConf(string key) {
        ifstream valueStream(confPath);
        string temp, res;
        if (valueStream.is_open()) {
            //cout << "valueStream is open!" << endl;
            while (!valueStream.eof()) {
                valueStream >> temp;
                int n = key.length() + 1;
                //找到对应key
                if (temp.find(key + "=") != string::npos) {
                    //cout << "catch key" << endl;
                    //消除空格
                    while (temp[n] == ' ') n++;
                    //cout << "check temp " << temp << endl;
                    //数组判定
                    if (temp[n] == '[') {
                        if (*(temp.end() - 1) == ']') res = temp.substr(n + 1, temp.length() - 1);
                        else if(*(temp.end() - 1) == ';' && *(temp.end() - 2) == ']')
                            res = temp.substr(n + 1, temp.length() - 2);
                        else {
                            while (!valueStream.eof()) {
                                res = temp.substr(n + 1);
                                valueStream >> temp;
                                if (*(temp.end() - 1) == ']') {
                                    res += temp.substr(0, temp.length() - 1);
                                    return res;
                                } else if(*(temp.end() - 1) == ';' && *(temp.end() - 2) == ']') {
                                    res += temp.substr(0, temp.length() - 2);
                                    return res;
                                } else res += temp;
                            }
                        }
                    } else res = temp.substr(n);
                    return res;
                }
            }
        } else {
            cout << "Error opening file" << endl;
            exit(1);
        }
        return res;
    }

private:
};
