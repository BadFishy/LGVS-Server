#pragma once
#include "log/log.h"
#include <iostream>
#include <time.h>
#include "DB/DB.h"
#include "threadPool/threadPool.h"
//#include <thread>


class Server
{
	/**
	 *	Login�� ����
	 *	��������������������Ҫ������־ָ������(Log*)
	 *	ʹ�� start() ������½������
	 */
private:
	Log *c;
	DB *db;
	SOCKET sock;
	SOCKADDR_IN addrClient;
	int len;
	int port;
	
	
public:
	Server(Config* config, DB *db_in) {
		c = new Log("Lobby");
		port = config->Read<int>("LOBBY_port");	//���ص�½�������˿�
		db = db_in;
	};
	~Server();

	int playernum = 0;

	int start();
	int init();

};

