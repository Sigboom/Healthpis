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
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include "../include/baseTools.h"
#include "../include/sigNet.h"
#include "../include/confException.h"
#define MSGLEN 100

using std::cin;
using std::cout;
using std::string;
using std::queue;
using std::endl;
using std::unique_ptr;
using std::ostringstream;
using std::ifstream;
using std::initializer_list;

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
	int tempConnfd;
	string recvBuffer;
	string sendBuffer;
	int reVal;  // 返回值
	queue<string> recvNews;  // 数据接收队列
	initializer_list<string> filePath;
	
public:
	server(string confPath) {
		try {
			bt = ([=](){return unique_ptr<baseTools> (new baseTools(confPath));})();
		port = stoi(bt->getConf("port"));
		initServer(port);
		} catch(int e){
			throw confException(e);
		}
	}
	~server() {}
	void initServer(int port) {
		socketfd = socket_create(port);
	}

	string readFileIntoString(string fileName)
	{
		ifstream ifile(fileName);
		string buf,result;
		if (ifile.is_open()){
		while(!ifile.eof()){
			ifile >> buf;
			result += buf;
		}}
		return result;
	}
	
	int randPort()
	{
		int socketfd;
		socketfd = socket_create(0);
		struct sockaddr_in sockAddr;
		socklen_t  nlen = (socklen_t)sizeof(sockAddr);
		int temp,port;
		temp = getsockname(socketfd,(struct sockaddr*)&sockAddr,&nlen);
		port = ntohs(sockAddr.sin_port);
		cout << "port : " <<port << endl;
		return port;
	}
	
	int getPort(int socketfd)
	{
		struct sockaddr_in sockAddr;
		socklen_t  nlen = (socklen_t)sizeof(sockAddr);
		int temp,port;
		temp = getsockname(socketfd,(struct sockaddr*)&sockAddr,&nlen);
		port = ntohs(sockAddr.sin_port);
		cout << "port : " <<port << endl;
		return port;
	}
		
	void Start() {
		if ((connfd = accept(socketfd, (struct sockaddr *)NULL, NULL)) < 0) return ;
		cout << "-----------------Connect Successfully!----------------" << endl;

		int tempSocketfd;
		tempSocketfd = socket_create(0);
		int tempPort = getPort(tempSocketfd);
		while (true)
		{
			if ( (reVal = recvMsg(connfd, recvBuffer, MSGLEN,0)) <= 0)
			{	cout << "RECV OVER!"<<endl;
				break;
			}
			recvNews.push(recvBuffer);
			if (recvNews.front() == "SYN")
			{
  				recvNews.pop();
				//int tempPort = getPort(tempSocketfd);
				sendBuff = "ACK :"+tempPort;
				int sentVal = sendMsg(connfd,sendBuffer);
			}
			if (recvNews.front() == "exit" || recvNews.front() == "quit")
			{
 				recvNews.pop(); 
				close(connfd);
			}

			if (!recvNews.empty())
			{
 				 cout << "mag: "  << recvNews.front() << endl;
				cout << "----------------------------------ANSWER---------------------------" << endl;
				string sFileName = bt->getConf(recvNews.front());
				system(("./script/" + sFileName).c_str());
				string fn = "./script/"+recvNews.front();
				filePath.push(fn);
				int sendValue = h_sendFile(tempPort,filePath);
				//sendBuffer = readFileIntoString(fn);
				//int sentVal = sendMsg(connfd,sendBuffer);
				cout << "--------------------------------------------------------------------" << endl;
				recvNews.pop ();
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
	//server_one->Start();
	int port = server_one->randPort();
	return monitor::byebye();
}
