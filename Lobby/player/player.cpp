#include "player.h"



bool Player::start()
{
	
	c->out("�������" + std::to_string(playernum) + "�̳߳ɹ�");
	sendstr("test" + std::to_string(playernum));
	//char *recvbuf;
	//recvch();
	//c->out("���յ��ͻ��˷�������Ϣ��" + (string)recvbuf);
	//delete c, sockConnect;
	
	return true;
}

bool Player::sendstr(string str)
{
	c->out("��ͻ��˷�����Ϣ��"+ str);
	const char *sendBuf = str.data();
	if (send(*sockConnect, sendBuf, strlen(sendBuf) + 1, 0) == SOCKET_ERROR) {
		c->err("����ʧ�ܣ������ǿͻ����ѹر�");
		return false;
	}

	return true;
}

bool Player::recvch(char* ch) //char* ch Ϊ�˷������յ�����Ϣ
{
	c->out("�ӿͻ��˽�����Ϣ�С���");
	char recvBuf[1024] = "";
	if (recv(*sockConnect, recvBuf, 1024, 0) == -1)//TCP CLIENT�˹رպ󣬷������˵�recv��һֱ����-1����ʱ������˳��������recv��һֱ����
	{
		c->err("����ʧ�ܣ������ǿͻ����ѹر�");
		return false;
	}
	else {
		c->out("���յ��ÿͻ��˷��͵���Ϣ��" + (string)recvBuf);
		ch = recvBuf;
	}
	memset(recvBuf, 0, sizeof(recvBuf));//�ѽ��յ��������
	return true;
}