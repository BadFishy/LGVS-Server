#include "player.h"
#include "room.h"


bool Player::start()
{
	
	c->out("�������" + std::to_string(playernum) + "�̳߳ɹ�");
	//if (sendstr("test" + std::to_string(playernum)) == false) {
		//c->err("����ʧ�ܣ�");
		//return false;
	//}
	
	//char *recvbuf;
	//recvch();
	//c->out("���յ��ͻ��˷�������Ϣ��" + (string)recvbuf);
	//delete c, sockConnect;
	
	return true;
}

bool Player::sendstr(string str)
{
	while (sendLOCK) { 
		Sleep(10); 
	}
	sendLOCK = 1;
	
	char sendBuf[64];
	int i;
	for (i=0; i < str.length(); i++) {
		sendBuf[i] = str[i];
	}
	sendBuf[i] = '\0';
	c->out("��ͻ��˷�����Ϣ��" + (string)sendBuf);
	if (send(*sockConnect, sendBuf, strlen(sendBuf) + 1, 0) == SOCKET_ERROR) {
		c->err("��ͻ��˷�����Ϣʧ��");
		sendLOCK = 0;
		return false;
	}
	sendLOCK = 0;
	return true;
}

string Player::recvch(const char* time)
{

	setsockopt(*sockConnect, SOL_SOCKET, SO_RCVTIMEO, time, sizeof(time));//���ó�ʱʱ��Ϊ1s
	while (recvLOCK) {
		Sleep(10);
	}
	recvLOCK = 1;
	//c->out("�ӿͻ��˽�����Ϣ�С���");
	char recvBuf[1024] = "";
	if (recv(*sockConnect, recvBuf, 1024, 0) == -1)//TCP CLIENT�˹رպ󣬷������˵�recv��һֱ����-1����ʱ������˳��������recv��һֱ����
	{
		//c->err("�ӿͻ��˽�����Ϣʧ��");
		recvLOCK = 0;
		return "";
	}
	else {
		//c->out("���յ��ÿͻ��˷��͵���Ϣ��" + (string)recvBuf);
		recvLOCK = 0;
		return recvBuf;
	}
	memset(recvBuf, 0, sizeof(recvBuf));//�ѽ��յ��������
	recvLOCK = 0;
	return "";
}


bool Player::hearttime(int s) {
	time_t nowtime = time(0);
	if (nowtime - lasttime >= s) {
		return true;
	}
	//lasttime = nowtime;
	return false;
}


int Player::heart()
{
	int hearttimer = 0;
	int errnum = 0;
	lasttime = time(0);
	while (1) {
		Sleep(10);
		//c->out("�ӿͻ��˽�����Ϣ�С���");
		string recvBuf = recvch("1");
		if (recvBuf == "")
		{
			//if (hearttime(5)) return -1;
		}
		else if (recvBuf == "heart") {
			sendstr("�յ�������");
			lasttime = time(0);
		}
		else {
			c->out("���յ��ÿͻ��˵���Ϣ��" + recvBuf);
			lasttime = time(0);
			fenge(recvBuf);
		}
	}
	return -1;
}
Room *room = new Room();

int Player::fenge(string s)
{
	string str = s;
	const char *sep = " "; //�ָ���յ�����
	char *p;
	string shou[5];
	p = strtok((char*)str.data(), sep);
	shou[0] = p;
	if (shou[0] == "wuziqi") {
		for (int i = 0; i < 3; i++) {
			shou[i] = p;
			p = strtok(NULL, sep);
		}
		c->out("������ʶ���:" + shou[1] + " ���ͣ�" + shou[2]);
		setRoomid(shou[1]);
		if (shou[2] == "0") {
			room->setRoomid(roomid);
			room->setZhu(ziji, roomid);
			for (int j = 0; j < 10; j++) {
				c->out("������ʶ���:" + shou[1] + " �����ȴ�����");
				if (room->getStep() == 3) {
					enemy = room->getKe(roomid);
					c->out("���ֳɹ�1");
					//room->init();
					return 0;
				}
				Sleep(1000);
			}
			room->init();
			return -1;
		}
		if (shou[2] == "1") {
			//room->setRoomid(roomid);
			room->setKe(ziji, roomid);
			for (int j = 0; j < 10; j++) {
				c->out("������ʶ���:" + shou[1] + " �ͻ��ȴ�����");
				if (room->getStep() == 3) {
					enemy = room->getZhu(roomid);
					c->out("���ֳɹ�2");
					//room->init();
					return 1;
				}
				Sleep(1000);
			}
			room->init();
			return -1;
		}
	}
	s += " ";
	if (shou[0] == "add") {
		c->out(s);
		enemy->sendstr(s);
	}

	if (shou[0] == "win") {
		enemy->sendstr(s);
	}

	if (shou[0] == "agree") {
		enemy->sendstr(s);
	}

	if (shou[0] == "reject") {
		enemy->sendstr(s);
	}

	return -1;
}

