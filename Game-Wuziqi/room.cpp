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
			if (id == roomid)return 0;
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

		if (id == roomid) {
			step -= 1;
			return zhu;
		}
	return false;
}

Player * Room::getKe(string id)
{
		if (id == roomid) {
			step -= 2;
			return ke;
		}
	return false;
}

int Room::getStep()
{
	return step;
}

bool Room::over()
{
	if (step == 0) {
		roomid = "0";
		return true;
	}
}

bool Room::shibai()
{
	step = 0;
	roomid = "0";
	return true;
}

