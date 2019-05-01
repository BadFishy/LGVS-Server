#pragma once
#include "server/Server.h"

class Player
{
private:
	Log *c;
	DB *db;
	SOCKET *sockConnect;
	
public:
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
};

