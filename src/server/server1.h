/*************************************************************************
	> File Name: server1.h
	> Author: daniel
	> Mail: sigboom@163.com 
	> Created Time: 二 11/ 5 14:46:02 2019
 ************************************************************************/
#ifndef _MANAGER_H
#define _MANAGER_H


#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "../../sigToolkit/include/sigToolkit.h"

#define MSGLEN 100

using std::cin;
using std::cout;
using std::string;
using std::queue;
using std::endl;
using std::unique_ptr;
using std::ostringstream;
using std::ifstream;

class Server : public sigNet {
	private
	public:
		Server(string confPath);
		~Server();

	public:
		void initServer(int port);
		string readFileIntoString(string fileName);
		void Start();
		int getPort(int socketfd);
		string handleRecv(string &recvData,int port);
		void recvAndSendMessage(int connfd);
	
		int m_nPort;
		int m_nSocketfd;
		int m_nConnfd;
		int m_nTempSocked;
		int m_nTempPort;
		int m_nTempConnfd;
		string m_sRecvBuffer;
		string m_sSendBuffer;
		queue<string> m_sRecvNews;
		unique_ptr<baseTools> m_pBt;
		vector<string> m_sFilePath;
		unique_ptr<medCentre> mc;
};

#endif
