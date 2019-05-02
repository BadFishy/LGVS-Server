#include "player.h"



bool Player::start()
{
	
	c->out("创建玩家" + std::to_string(playernum) + "线程成功");
	if (sendstr("test" + std::to_string(playernum)) == false) {
		//c->err("发送失败！");
		return false;
	}
	
	//char *recvbuf;
	//recvch();
	//c->out("接收到客户端发来的信息：" + (string)recvbuf);
	//delete c, sockConnect;
	
	return true;
}

bool Player::sendstr(string str)
{
	while (sendLOCK) { 
		Sleep(100); 
	}
	sendLOCK = 1;
	//c->out("向客户端发送消息："+ str);
	const char *sendBuf = str.data();
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
		Sleep(100);
	}
	recvLOCK = 1;
	c->out("从客户端接受消息中……");
	char recvBuf[1024] = "";
	if (recv(*sockConnect, recvBuf, 1024, 0) == -1)//TCP CLIENT端关闭后，服务器端的recv会一直返回-1，此时如果不退出，服务端recv会一直接收
	{
		c->err("从客户端接收消息失败");
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

int Player::heart()
{
	int hearttimer = 0;
	int errnum = 0;
	while (1) {
		Sleep(1000);
		//c->out("从客户端接受消息中……");
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
				sendstr("收到心跳包");				
			}
			/********************************************/
			else if (recvBuf == ""){
				hearttimer++;
			}
			/********************************************/
			else {
					c->out("接收到该客户端的消息：" + recvBuf);
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
