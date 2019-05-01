#pragma once
#include "log.h"
#include <iostream>
#include <time.h>
#include "DB.h"
#include "threadPool.h"
//#include <thread>

class Server
{
	/**
	 *	Login类 介绍
	 *	用于玩家与大厅交流，需要输入日志指针类型(Log*)
	 *	使用 start() 启动登陆服务器
	 */
private:
	Log *c;
	DB *db;
	SOCKET sock;
	SOCKADDR_IN addrClient;
	int len;
	int port;
	threadPool pool;
	
public:
	Server(Config* config, DB *db_in) {
		c = new Log("Lobby");
		port = config->Read<int>("LOBBY_port");	//加载登陆服务器端口
		db = db_in;
	};
	~Server();

	int playernum = 0;

	int start();
	int init();

};

