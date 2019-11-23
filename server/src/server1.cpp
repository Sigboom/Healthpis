 /*************************************************************************
	> File Name: server1.cpp
	> Author: daniel
	> Mail: sigboom@163.com 
	> Created Time: 二 11/ 5 14:44:46 2019
 ************************************************************************/
#include "../include/server1.h"
#include "serverDoctor.cpp"

Server::Server(string confPath)
{
	try {
		mc = make_shared<mediCentre>("manager",confPath);
	}catch (confException e){
		e.show();
		cout << "Server init failed!" << endl;
		exit(1);
	}
	initServer(mc->getPort(0));
	cout << "Sever init Successful!" << endl;
	initDoctor();
}

Server::~Server(){};

void Server::initServer(int port)
{
	m_nSocketfd = socket_create(port);
}

/*

void Server::recvAndSendMessage(int connfd)
{
	while (true){
		int reVal;
		if ((reVal = recvMsg(connfd,m_sRecvBuffer,MSGLEN,0)) <= 0){
			cout << "RECV OVER" << endl;
			close(connfd);
			break;
		}
		m_nTempSocked = socket_create(0);
		m_nTempPort = getPort(m_nTempSocked);
		string str = handleRecv(m_sRecvBuffer,m_nTempPort);
		if (!m_sRecvNews.empty()){
			string sFileName;
			string sFilePath = "./script/"+m_sRecvNews.front();
 	 			m_sFilePath.push_back(sFilePath);
				int nSendValue = sendFile(m_nTempSocked,m_sFilePath);
		  		m_sRecvNews.pop();
			}else{
   				cout << "The Message is error!" << endl;
			}
		}	
	return ;
}*/

void Server::Start()
{
	if ((m_nConnfd = accept(m_nSocketfd,(struct sockaddr *)NULL,NULL)) < 0)
		return ;
	mc->setConnfd(0,m_nConnfd);
	cout << "-------------Connect Successfully---------" << endl;
	string recvBuffer = "";
	int id = 0;
	while(true){
        int len = recvMsg(m_nConnfd, recvBuffer);
        if (len <= 0) exit(0);
        cout << recvBuffer << endl;
        //string server = mc->getHostName(id);
        //mc->setRecvBuffer(id, recvBuffer);
        string sym =  recvBuffer;
        mc->outPatient(sym);
	}
}
inline bool Server::isExit(string order) {
    return order == "exit" || order == "quit";
}

void Server::initDoctor()
{
    mc->addDoctor(make_shared<recvDoctor>(mc));

}
