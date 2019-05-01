#include "player.h"

int LOCK = 0;

bool Player::start()
{
	while(LOCK){}
	LOCK = 1;
	c->out("创建玩家" + std::to_string(playernum) + "线程成功");
	sendstr("test" + std::to_string(playernum));
	//char *recvbuf;
	//recvch();
	//c->out("接收到客户端发来的信息：" + (string)recvbuf);
	//closesocket(*sockConnect);
	//c->out("断开连接");
	//delete c, sockConnect;
	LOCK = 0;

	return true;
}

bool Player::sendstr(string str)
{
	c->out("向客户端发送消息："+ str);
	const char *sendBuf = str.data();
	if (send(*sockConnect, sendBuf, strlen(sendBuf) + 1, 0) == SOCKET_ERROR) {
		c->err("发送失败，可能是客户端已关闭");
		return false;
	}

	return true;
}

bool Player::recvch(char* ch) //char* ch 为此方法接收到的信息
{
	c->out("从客户端接受消息中……");
	char recvBuf[1024] = "";
	if (recv(*sockConnect, recvBuf, 1024, 0) == -1)//TCP CLIENT端关闭后，服务器端的recv会一直返回-1，此时如果不退出，服务端recv会一直接收
	{
		c->err("接收失败，可能是客户端已关闭");
		return false;
	}
	else {
		c->out("接收到该客户端发送的信息：" + (string)recvBuf);
		ch = recvBuf;
	}
	memset(recvBuf, 0, sizeof(recvBuf));//把接收的数据清空
	return true;
}