#include "player.h"



bool Player::start()
{
	
	c->out("�������" + std::to_string(playernum) + "�̳߳ɹ�");
	if (sendstr("test" + std::to_string(playernum)) == false) {
		//c->err("����ʧ�ܣ�");
		return false;
	}
	
	//char *recvbuf;
	//recvch();
	//c->out("���յ��ͻ��˷�������Ϣ��" + (string)recvbuf);
	//delete c, sockConnect;
	
	return true;
}

bool Player::sendstr(string str)
{
	while (sendLOCK) { 
		Sleep(100); 
	}
	sendLOCK = 1;
	//c->out("��ͻ��˷�����Ϣ��"+ str);
	const char *sendBuf = str.data();
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
		Sleep(100);
	}
	recvLOCK = 1;
	c->out("�ӿͻ��˽�����Ϣ�С���");
	char recvBuf[1024] = "";
	if (recv(*sockConnect, recvBuf, 1024, 0) == -1)//TCP CLIENT�˹رպ󣬷������˵�recv��һֱ����-1����ʱ������˳��������recv��һֱ����
	{
		c->err("�ӿͻ��˽�����Ϣʧ��");
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

int Player::heart()
{
	int hearttimer = 0;
	int errnum = 0;
	while (1) {
		Sleep(1000);
		//c->out("�ӿͻ��˽�����Ϣ�С���");
		string recvBuf = recvch("1");
		if (recvBuf == "")
		{
			hearttimer++;
		}
		else {
			/********************************************/
			if (recvBuf == "heart") {
				errnum = 0;
				hearttimer = 0;
				sendstr("�յ�������");				
			}
			/********************************************/
			else if (recvBuf == ""){
				hearttimer++;
			}
			/********************************************/
			else {
					c->out("���յ��ÿͻ��˵���Ϣ��" + recvBuf);
					hearttimer++;
				}
			/********************************************/
		}
		if (hearttimer >= 5) {
			errnum++;
		}
		if (errnum >= 5) {
			return 0;
		}
	}
	return -1;
}
