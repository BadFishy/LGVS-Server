#pragma once
#include "player/Player.h"
class Room
{
private:
	string roomid;
	Player *zhu;
	Player *ke;
	int step;
	//0 �Ѿ����������跿��ID
	//1 �����Ѿ����ӣ��ͷ�δ����
	//2 ����δ���ӣ��ͷ��Ѿ�����
	//3 �ͷ��Ѿ����ӣ������Ѿ�����

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

