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
		Sleep(1000); 
	}
	sendLOCK = 1;
	c->out("��ͻ��˷�����Ϣ��"+ str);
	const char *sendBuf = str.data();
	if (send(*sockConnect, sendBuf, strlen(sendBuf) + 1, 0) == SOCKET_ERROR) {
		c->err("����ʧ��");
		sendLOCK = 0;
		return false;
	}
	sendLOCK = 0;
	return true;
}

bool Player::recvch(char* ch) //char* ch Ϊ�˷������յ�����Ϣ
{
	while (recvLOCK) {
		Sleep(1000);
	}
	recvLOCK = 1;
	c->out("�ӿͻ��˽�����Ϣ�С���");
	char recvBuf[1024] = "";
	if (recv(*sockConnect, recvBuf, 1024, 0) == -1)//TCP CLIENT�˹رպ󣬷������˵�recv��һֱ����-1����ʱ������˳��������recv��һֱ����
	{
		c->err("����ʧ��");
		recvLOCK = 0;
		return false;
	}
	else {
		c->out("���յ��ÿͻ��˷��͵���Ϣ��" + (string)recvBuf);
		//ch = recvBuf;
	}
	memset(recvBuf, 0, sizeof(recvBuf));//�ѽ��յ��������
	recvLOCK = 0;
	return true;
}

bool Player::heart()
{
	int hearttimer = 0;
	int errnum = 0;
	while (1) {
		Sleep(1000);
		while (recvLOCK) { Sleep(1); }
		recvLOCK = 1;
		//c->out("�ӿͻ��˽�����Ϣ�С���");
		char recvBuf[1024] = "";
		const char* timeout = "1";
		int ret = setsockopt(*sockConnect, SOL_SOCKET, SO_RCVTIMEO, timeout, sizeof(timeout));//���ó�ʱʱ��Ϊ1s
		if (recv(*sockConnect, recvBuf, 1024, 0) == -1)//TCP CLIENT�˹رպ󣬷������˵�recv��һֱ����-1����ʱ������˳��������recv��һֱ����
		{
			//c->err("����ʧ��");
			errnum++;
			//c->out("û���յ���������" + to_string(errnum) + "��");
			if (errnum >= 10) {
				heartLOCK = 1;
				recvLOCK = 0;
				return false;
			}
		}
		else {
			if ((string)recvBuf == "heart") {
				errnum = 0;
				hearttimer = 0;
				sendstr("�յ�������");				
			}
			else { 
				if ((string)recvBuf == "") {
					errnum++;
					//c->out("û���յ���������" + to_string(errnum) + "��");
					if (errnum >= 5) {
						//c->out("û���յ���������" + to_string(errnum) + "��");
						heartLOCK = 1;
						recvLOCK = 0;
						return false;
					}
				}
				//c->out("���յ��ÿͻ��˵���Ϣ��" + (string)recvBuf);
				hearttimer++;
				if (hearttimer >= 10) {
					errnum++;
					if (errnum >= 5) {
						//c->out("û���յ���������" + to_string(errnum) + "��");
						heartLOCK = 1;
						recvLOCK = 0;
						return false;
					}
				}
			}
			
		}
		memset(recvBuf, 0, sizeof(recvBuf));//�ѽ��յ��������
		recvLOCK = 0;
	}
	
	return false;
}
