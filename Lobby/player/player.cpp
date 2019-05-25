#include "player.h"



bool Player::start()
{
	
	c->out("�������" + std::to_string(playernum) + "�̳߳ɹ�");
	//if (sendstr("test" + std::to_string(playernum)) == false) {
	//	//c->err("����ʧ�ܣ�");
	//	return false;
	//}
	
	//char *recvbuf;
	//recvch();
	//c->out("���յ��ͻ��˷�������Ϣ��" + (string)recvbuf);
	//delete c, sockConnect;
	
	return true;
}

bool Player::sendstr(string str)
{
	/*while (sendLOCK) { 
		Sleep(10); 
	}*/
	sendLOCK = 1;
	c->out("��ͻ��˷�����Ϣ��"+ str);
	const char *sendBuf = (str).data();
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


bool Player::hearttime() {
	time_t nowtime = time(0);
	if (nowtime - lasttime >= 5) {
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
			if (hearttime()) {
				string update = "UPDATE `USER` SET `online` = '0',`home` = NULL, `ready` = '0' WHERE `USER`.`uid` = " + to_string(uid);
				db->runSQL(update.data());
				return 0;
			}
		}
		else if (recvBuf == "heart") {
			if (hid != 0) {
				string update = "UPDATE `USER` SET `home` = NULL, `ready` = '0' WHERE `USER`.`uid` = " + to_string(uid);
				db->runSQL(update.data());
			}
			//sendstr("�յ�������");
			lasttime = time(0);
		}
		else if (recvBuf == "class") {
			//c->out(db->cha("CLASS"));
			sendstr("f5,"+db->cha("CLASS"));
			//sendstr("CLASS");
			lasttime = time(0);
		}

		else {
			c->out("���յ��ÿͻ��˵���Ϣ��" + recvBuf);
			if(fenge(recvBuf)==-2)return -1;
			lasttime = time(0);
		}

	}
	return -1;
}

int Player::fenge(string s)
{
	string str = s;
	const char *sep = ","; //�ָ���յ�����
	char *p;
	string shou[5];
	p = strtok((char*)str.data(), sep);
	shou[0] = p;
	if (shou[0] == "rooms") {
		for (int i = 0; i < 2; i++) {
			shou[i] = p;
			p = strtok(NULL, sep);
		}
		sendstr("f5," + db->cha(("`HOME` WHERE `home_class` = " + shou[1]).data()));
		return 0;
	}

	else if (shou[0] == "lobby") {
		for (int i = 0; i < 2; i++) {
			shou[i] = p;
			p = strtok(NULL, sep);
		}
		if (db->tongshicunzaiDB("USER", "uid", shou[1], "online", "1")) {
			uid = stoi(shou[1]);
			sendstr("lobbyok," + db->sou(("SELECT `uid`, `username`, `regtime`, `lasttime`, `money` FROM `USER` WHERE `uid` = " + shou[1]).c_str()));
			return 0;
		}
			//db->runSQL("UPDATE `USER` SET `online` = '1' WHERE `USER`.`uid` = 1");
		sendstr("loss");
		return -2;
	}

	else if (shou[0] == "user") {
		for (int i = 0; i < 2; i++) {
			shou[i] = p;
			p = strtok(NULL, sep);
		}
		sendstr("user,"+ db->sou(("SELECT `uid`, `username`, `regtime`, `lasttime`, `money` FROM `USER` WHERE `uid` = " + shou[1]).c_str()));
		return 0;
	}

	else if (shou[0] == "home") {
		for (int i = 0; i < 2; i++) {
			shou[i] = p;
			p = strtok(NULL, sep);
		}
		string update = "UPDATE `USER` SET `home` = '" + shou[1] + "' WHERE `USER`.`uid` = " + to_string(uid);
		db->runSQL(update.data());
		hid = stoi(shou[1]);
		sendstr("f5," + db->sou(("SELECT `uid`, `username`, `regtime`, `money`, `ready` FROM `USER` WHERE `home` ="+shou[1]).c_str()));
		return 0;
	}

		else if (shou[0] == "ready") {
			for (int i = 0; i < 3; i++) {
				shou[i] = p;
				p = strtok(NULL, sep);
			}
			string update = "UPDATE `USER` SET `ready` = '" + shou[1] + "' WHERE `USER`.`uid` = " + to_string(uid);
			db->runSQL(update.data());
			sendstr("f5," + db->sou(("SELECT `uid`, `username`, `regtime`, `money`, `ready` FROM `USER` WHERE `home` =" + shou[2]).c_str()));
			return 0;
		}


		return -1;
}


