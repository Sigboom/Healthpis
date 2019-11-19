/*************************************************************************
	> File Name: serverDoctor.cpp
	> Author: daniel
	> Mail: sigboom@163.com 
	> Created Time: 六 11/ 9 16:07:28 2019
 ************************************************************************/

#include <iostream>
#include <string>
#include "../../sigToollkit/include/sigToolkit.h"

using std::cout;
using std::endl;
using std::string;

class serverDoctor : public doctor
{
	private:
		shared_ptr<mediCentre> mc;
		int m_nTempSocket;
		int m_nTempPort;
	public:
		serverDoctor(shared_ptr<mediCentre> mc) : mc(mc){
			m_nTempSocket = socket_create(0);
			m_nTempPort = getPort(tempSocket);	
	}

		int getPort(int socketfd)
		{
			struct sockaddr_in sockAddr;
			socklen_t nlen = (socklen_t)sizeof(sockAddr);
			int temp,port;
			temp = getsockname(socketfd,(struct sockaddr*)&sockAddr,&nlen);
			port = ntohs(sockAddr.sin_port);
			return port;
		}
		void execute(string sys){
			int len = sys.size();
			if (1 == len){
			for (int i = 101;i < 110;i++)
			{
				string fileName = to_string(i);
				system("./script/"+fileName);
				string sFilePath = "./script/"+fileName;
				mc->sendFile(m_nTempSocked,sFilePath);
			}
			}else{
				sys("./script/"+sys);
				string sFilePath = "./script/"+sys;
				mc->sendFile(m_nTempSocked,sFilePath);

			}
		}
}


class handleRecvDoctor : public doctor
{
	private:
		shared_ptr<mediCentre> mc;

	public:
		handleRecvDoctor(shared_ptr<mediCentre> mc) :mc(mc){}
		void execute(string sys){
			cout << "sym: " << sym<<endl;
			int id = stoi(sym);
			string recvBuff = mc->getSendBuffer(id);
			int len = recvBuff.size();
			int connfd = mc->getConnfd(0);
			if ( 0 == len){
				string erBF = "The Message is NULL";
				mc->sendMsg(connfd,erBF);
				return;
			}
			if ("SYN" == recvBuff){
				string sBF = "ACK";
				mc->sendMsg(connfd,sBF);
				return ;
			}
			if ("exit" == recvBuff || "quit" == recvBuff){
				return;
			}
			if (sys[len-1] > '9' && sys[len-1] < '0'){
				getNextDoctor()->execute(recvBuff[0]); 
			}else{
				getNextDoctor()->execute(recvBuff); 
			}

		} 
}
