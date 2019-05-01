#pragma once
#include "server/Server.h"
#include <windows.h>

class Player
{
private:
	SOCKET *sockConnect;
	
public:
	DB *db;
	Log *c;
	int playerdeteLOCK = 0;
	Player(SOCKET *sock, Log *userlog, int num) {
		sockConnect = sock;
		c = userlog;
		playernum = num;
	};
	~Player() {
		closesocket(*sockConnect);
		c->out("¶Ï¿ªÁ¬½Ó");
		delete c, db, sockConnect;
	};

	int playernum;
	bool start();
	bool sendstr(string str);
	bool recvch(char* ch = new char);
	bool heart();
	int heartLOCK = 0;
	int sendLOCK = 0;
	int recvLOCK = 0;
};

