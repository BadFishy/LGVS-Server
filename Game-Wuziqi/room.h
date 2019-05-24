#pragma once
#include "player/Player.h"
class Room
{
private:
	string roomid;
	Player *zhu;
	Player *ke;
	int step;
	//0 已经创建。赋予房间ID
	//1 主方已经连接，客方未连接
	//2 主方未连接，客方已经连接
	//3 客方已经连接，主方已经连接

public:
	Room() ;
	~Room();

	bool setRoomid(string id) ;

	bool setZhu(Player *aa, string id) ;
	bool setKe(Player *aa, string id) ;
	Player *getZhu(string id) ;
	Player *getKe(string id) ;
	int getStep();

	bool over() ;
	bool shibai();
};

