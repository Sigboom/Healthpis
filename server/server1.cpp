 /*************************************************************************
	> File Name: server1.cpp
	> Author: daniel
	> Mail: sigboom@163.com 
	> Created Time: 二 11/ 5 14:44:46 2019
 ************************************************************************/
#include "server1.h"
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
}

Server::~Server(){};

void Server::initServer(int port)
{
	m_nSocketfd = socket_create(port);
}

int Server::getPort(int socketfd)
{
	struct sockaddr_in sockAddr;
	socklen_t nlen = (socklen_t)sizeof(sockAddr);
	int temp,port;
	temp = getsockname(socketfd,(struct sockaddr*)&sockAddr,&nlen);
	port = ntohs(sockAddr.sin_port);
	return port;
}

string Server::handleRecv(string &recvData,int port)
{
	int len = recvData.size();
	if ("SYN" == recvData){
		string sBF = "ACK"; 
		int sendVal = sendMsg(m_nConnfd,sBF);
		close(m_nTempSocked);
		return "SYN";
	}
	if ("exit" == recvData || "quit" == recvData){
		m_sRecvNews.pop();
		close(m_nTempConnfd);
		return "exit";
	}
		string sBF = "ans_" + recvData + port;
		int sendVal = sendMsg(m_nConnfd,sBF);
	if (recvData[len-1] < '0' && recvData[len-1] > '9'){	
		m_sRecvNews.push(""+recvData[0]);
		return ""+recvData[0];
	}
	else{
		m_sRecvNews.push(recvData);
		return recvData;
	}
}

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
}

void Server::Start()
{
	if ((m_nConnfd = accept(m_nSocketfd,(struct sockaddr *)NULL,NULL)) < 0)
		return ;
	mc->outPatient("connect all");
	cout << "-------------Connect Successfully---------" << endl;
	initDoctor();
}

void Server::initDoctor()
{
    mc->addDoctor(make_shared<handleRecvDoctor>());

}
