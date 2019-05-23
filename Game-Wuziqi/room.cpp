#include "room.h"



Room::Room()
{
	step = 0;
}


Room::~Room()
{
}

bool Room::setRoomid(string id)
{
	{
		while (step != 0) {
			Sleep(100);
		}
		roomid = id;
		step = 0;
	}
	return 0;
}

bool Room::setZhu(Player * aa, string id)
{
	{
		if (id == roomid) {
			zhu = aa;
			step += 1;
		}
	}
	return 0;
}

bool Room::setKe(Player * aa, string id)
{
	{
		if (id == roomid) {
			ke = aa;
			step += 2;
		}
	}
	return false;
}

Player * Room::getZhu(string id)
{
	{
		if (id == roomid)
			return zhu;
	}
	return false;
}

Player * Room::getKe(string id)
{
	{
		if (id == roomid)
			return ke;
	}
	return false;
}

int Room::getStep()
{
	return step;
}

bool Room::init()
{
	string roomid = 0;
	step = 0;
	return 0;
}
