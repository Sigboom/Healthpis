/*************************************************************************
	> File Name: server.cpp
	> Author: daniel
	> Mail: sigboom@163.com 
	> Created Time: 六 10/26 14:14:29 2019
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "../include/baseTools.h"
#include "../include/sigNet.h"

#define MSGLEN 100

using std::cin;
using std::cout;
using std::string;
using std::queue;
using std::endl;
using std::unique_ptr;
namespace monitor{
	int hello(){
		cout << "hello~hello~"<<endl;
		return 0;
	}
	int byebye(){
		cout << "bye~bye~"<<endl;
		return 0;
	}
}

class server : public sigNet {
private:
	unique_ptr<baseTools> bt;
	int port;
	int socketfd;
	int connfd;
	string recvBuffer;
	string sendBuffer;
	char buf[MSGLEN];  // 接收数据缓冲区
	//char sendBuf[MSGLEN];  // 返回给客户端的数据
	int reVal;  // 返回值
	queue<string> recvNews;  // 数据接收队列
	
public:
	server(string confPath) {
		unique_ptr<baseTools> temp_bt(new baseTools(confPath));
		bt = move(temp_bt);
		port = stoi(bt->getConf("port"));
		initServer(port);
	}
	~server() {}
	void initServer(int port) {
		socketfd = socket_create(port);
	}

	void Start() {
		if ((connfd = accept(socketfd, (struct sockaddr *)NULL, NULL)) < 0) return ;
		cout << "connect successfully!" << endl;
		int recvId;
		while (true)
		{
			if ( (reVal = recvMsg(connfd, recvBuffer, MSGLEN,0)) <= 0)
			{	cout << "RECV OVER!"<<endl;
				break;
			}
			recvNews.push(recvBuffer);
			if (!recvNews.empty())
			{
				cout << "mag: " << recvNews.front() << endl;
				sendBuffer = "ans_"+recvNews.front();
				int sentVal = sendMsg(connfd,sendBuffer);
				recvNews.pop();
			}else
			{
				cout << "The Message is error!" << endl;
			}
		}
		return ;
	}
};


int main(){
	unique_ptr<server> server_one(new server("conf/server.conf"));
	server_one->Start();
	return monitor::byebye();
}
