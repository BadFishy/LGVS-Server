#pragma once
#include "log/log.h"
#include <iostream>
#include <time.h>
#include "threadPool/threadPool.hpp"
//#include <thread>


class Server
{

private:
	Log *c;
	SOCKET sock;
	SOCKADDR_IN addrClient;
	int len;
	int port;
	
	
public:
	Server(Config* config) {
		c = new Log("Wuziqi");
		port = config->Read<int>("Wuziqi_port");	//���ص�½�������˿�
	};
	~Server();

	int playernum = 0;

	int start();
	int init();

};

