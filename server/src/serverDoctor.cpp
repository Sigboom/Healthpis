/*************************************************************************
	> File Name: serverDoctor.cpp
	> Author: daniel
	> Mail: sigboom@163.com 
	> Created Time: 六 11/ 9 16:07:28 2019
 ************************************************************************/

#include <iostream>
#include <string>
#include "../../sigToolkit/include/sigToolkit.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

class serverDoctor : public doctor
{
	private:
		shared_ptr<mediCentre> mc;
		int m_nTempSocket;
		int m_nTempPort;
	public:
		serverDoctor(shared_ptr<mediCentre> mc) : mc(mc){
			m_nTempSocket =mc->socket_create(0);
			m_nTempPort = getPort(m_nTempSocket);
			cout <<"m_nTempPort:"<< m_nTempPort << endl;
		}

		int getPort(int socketfd)
		{
			struct sockaddr_in sockAddr;
			socklen_t nlen = (socklen_t)sizeof(sockAddr);
			int temp,port;
			temp = getsockname(socketfd,(struct sockaddr*)&sockAddr,&nlen);
			port = ntohs(sockAddr.sin_port);
			cout << "port" << port << endl;
			return port;
		}
		void execute(string sys){
			int connfd = mc->getConnfd(0);
			int len = sys.size();
			if (1 == len){
 				int num = stoi(sys)*100+1; 
				for (int i = num;i < num+9;i++)
				{
 					string fileName = to_string(i);
					int status;
					string  sPath = "../script/"+fileName;
					status = system(sPath.c_str());
					if(status < 0)
					{
						continue;
					};
					string sPort = to_string(m_nTempPort);
					string sendBuff = "ans_"+fileName+" "+sPort;
					mc->sendMsg(connfd,sendBuff);
					string sFilePath = "../script/"+fileName+"s";
					mc->sendFile(m_nTempSocket,sFilePath);
				}
			}else{
 				string  sPort = to_string( m_nTempPort);
				string sendBuff = "ans_"+sys+" "+sPort;
				mc->sendMsg(connfd,sendBuff);
				string  sPath = "../script/"+sys;
				system(sPath.c_str());
				string sFilePath = "../script/"+sys+"s";
				mc->sendFile(m_nTempSocket,sFilePath); 

			}
		}
};


class HandleRecvDoctor : public doctor
{
	private:
		shared_ptr<mediCentre> mc;

	public:
		HandleRecvDoctor(shared_ptr<mediCentre> mc) :mc(mc){
			addDoctor(make_shared<serverDoctor>(mc));
		}
		void execute(string sys){
			
			cout << "sym: " << sys<<endl;
			int id = stoi(sys);
			string recvBuff = mc->getRecvBuffer(0);
			cout << "12345678"<<endl;
			int len = recvBuff.size();
			cout << recvBuff <<endl;
			int connfd = mc->getConnfd(0);
			if ( 0 == len){
				string erBF = "The Message is NULL";
				mc->sendMsg(connfd,erBF);
				return; 
			}
			if ("SYN" == recvBuff){
				string sBF = "ACK";
				mc->sendMsg(connfd,sBF);
				cout << "Send Message" <<endl;
				return ;
			}
			if ("exit" == recvBuff || "quit" == recvBuff){
				return;
			}
			if (recvBuff[len-1] > '9' && recvBuff[len-1] < '0'){
				dlist.front()->execute( recvBuff.substr(0,1)); 
			}else{
				dlist.front()->execute(recvBuff); 
			}

		} 
};


class recvDoctor : public doctor{
private:
	shared_ptr<mediCentre> mc;
public:
	recvDoctor(shared_ptr<mediCentre> mc): mc(mc) {
		addDoctor(make_shared<HandleRecvDoctor>(mc)); 
	}
	
	void execute(string sym){
		mc->setRecvBuffer(0,sym);
		dlist.front()->execute("0");
	}



};
