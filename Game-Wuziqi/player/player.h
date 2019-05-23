#pragma once
#include "server/Server.h"
#include <windows.h>

class Player
{
private:
	SOCKET *sockConnect;
	time_t lasttime;
public:
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
		delete c, sockConnect;
	};

	int playernum;
	bool start();
	bool sendstr(string str);
	string recvch(const char* timeout = "60000");
	bool hearttime();
	//timeout ms
	int heart();
	int sendLOCK = 0;
	int recvLOCK = 0;
};

