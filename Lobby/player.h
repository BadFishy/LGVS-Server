#pragma once
class Player
{
private:
	Log *c;
	DB *db;
	SOCKET sockConnect;
	


public:
	Player(SOCKET sock, Log *userlog, int num) {
		sockConnect = sock;
		c = userlog;
		playernum = num;
	};
	~Player();

	int playernum;
	bool start();
	bool sendstr(string str);
	bool recvch(char* ch);
};

