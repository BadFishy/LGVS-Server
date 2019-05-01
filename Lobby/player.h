#pragma once
class Player
{
private:
	Log *c;
	DB *db;
	SOCKET sockConnect;


public:
	Player(SOCKET sock, Log *userlog) {
		sockConnect = sock;
		c = userlog;
	};
	~Player();
};

