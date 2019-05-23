#include "player.h"
#include "room.h"


bool Player::start()
{
	
	c->out("创建玩家" + std::to_string(playernum) + "线程成功");
	//if (sendstr("test" + std::to_string(playernum)) == false) {
		//c->err("发送失败！");
		//return false;
	//}
	
	//char *recvbuf;
	//recvch();
	//c->out("接收到客户端发来的信息：" + (string)recvbuf);
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
	c->out("向客户端发送消息：" + (string)sendBuf);
	if (send(*sockConnect, sendBuf, strlen(sendBuf) + 1, 0) == SOCKET_ERROR) {
		c->err("向客户端发送消息失败");
		sendLOCK = 0;
		return false;
	}
	sendLOCK = 0;
	return true;
}

string Player::recvch(const char* time)
{

	setsockopt(*sockConnect, SOL_SOCKET, SO_RCVTIMEO, time, sizeof(time));//设置超时时间为1s
	while (recvLOCK) {
		Sleep(10);
	}
	recvLOCK = 1;
	//c->out("从客户端接受消息中……");
	char recvBuf[1024] = "";
	if (recv(*sockConnect, recvBuf, 1024, 0) == -1)//TCP CLIENT端关闭后，服务器端的recv会一直返回-1，此时如果不退出，服务端recv会一直接收
	{
		//c->err("从客户端接收消息失败");
		recvLOCK = 0;
		return "";
	}
	else {
		//c->out("接收到该客户端发送的信息：" + (string)recvBuf);
		recvLOCK = 0;
		return recvBuf;
	}
	memset(recvBuf, 0, sizeof(recvBuf));//把接收的数据清空
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
		//c->out("从客户端接受消息中……");
		string recvBuf = recvch("1");
		if (recvBuf == "")
		{
			//if (hearttime(5)) return -1;
		}
		else if (recvBuf == "heart") {
			sendstr("收到心跳包");
			lasttime = time(0);
		}
		else {
			c->out("接收到该客户端的消息：" + recvBuf);
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
	const char *sep = " "; //分割接收的数据
	char *p;
	string shou[5];
	p = strtok((char*)str.data(), sep);
	shou[0] = p;
	if (shou[0] == "wuziqi") {
		for (int i = 0; i < 3; i++) {
			shou[i] = p;
			p = strtok(NULL, sep);
		}
		c->out("五子棋识别号:" + shou[1] + " 主客：" + shou[2]);
		setRoomid(shou[1]);
		if (shou[2] == "0") {
			room->setRoomid(roomid);
			room->setZhu(ziji, roomid);
			for (int j = 0; j < 10; j++) {
				c->out("五子棋识别号:" + shou[1] + " 主机等待连接");
				if (room->getStep() == 3) {
					enemy = room->getKe(roomid);
					c->out("握手成功1");
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
				c->out("五子棋识别号:" + shou[1] + " 客机等待连接");
				if (room->getStep() == 3) {
					enemy = room->getZhu(roomid);
					c->out("握手成功2");
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

