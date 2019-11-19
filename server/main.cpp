/*************************************************************************
	> File Name: main.cpp
	> Author: daniel
	> Mail: sigboom@163.com 
	> Created Time: 四 11/ 7 10:48:23 2019
 ************************************************************************/

#include "server1.cpp"

int main()
{
		unique_ptr<Server> serverOne(new Server("conf/server.conf"));
		serverOne->Start();
		serverOne->show();
		return 0;
}

