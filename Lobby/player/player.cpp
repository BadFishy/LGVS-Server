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
		Sleep(1000); 
	}
	sendLOCK = 1;
	c->out("向客户端发送消息："+ str);
	const char *sendBuf = str.data();
	if (send(*sockConnect, sendBuf, strlen(sendBuf) + 1, 0) == SOCKET_ERROR) {
		c->err("发送失败");
		sendLOCK = 0;
		return false;
	}
	sendLOCK = 0;
	return true;
}

bool Player::recvch(char* ch) //char* ch 为此方法接收到的信息
{
	while (recvLOCK) {
		Sleep(1000);
	}
	recvLOCK = 1;
	c->out("从客户端接受消息中……");
	char recvBuf[1024] = "";
	if (recv(*sockConnect, recvBuf, 1024, 0) == -1)//TCP CLIENT端关闭后，服务器端的recv会一直返回-1，此时如果不退出，服务端recv会一直接收
	{
		c->err("接收失败");
		recvLOCK = 0;
		return false;
	}
	else {
		c->out("接收到该客户端发送的信息：" + (string)recvBuf);
		//ch = recvBuf;
	}
	memset(recvBuf, 0, sizeof(recvBuf));//把接收的数据清空
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
		//c->out("从客户端接受消息中……");
		char recvBuf[1024] = "";
		const char* timeout = "1";
		int ret = setsockopt(*sockConnect, SOL_SOCKET, SO_RCVTIMEO, timeout, sizeof(timeout));//设置超时时间为1s
		if (recv(*sockConnect, recvBuf, 1024, 0) == -1)//TCP CLIENT端关闭后，服务器端的recv会一直返回-1，此时如果不退出，服务端recv会一直接收
		{
			//c->err("接收失败");
			errnum++;
			//c->out("没有收到心跳包第" + to_string(errnum) + "次");
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
				sendstr("收到心跳包");				
			}
			else { 
				if ((string)recvBuf == "") {
					errnum++;
					//c->out("没有收到心跳包第" + to_string(errnum) + "次");
					if (errnum >= 5) {
						//c->out("没有收到心跳包第" + to_string(errnum) + "次");
						heartLOCK = 1;
						recvLOCK = 0;
						return false;
					}
				}
				//c->out("接收到该客户端的消息：" + (string)recvBuf);
				hearttimer++;
				if (hearttimer >= 10) {
					errnum++;
					if (errnum >= 5) {
						//c->out("没有收到心跳包第" + to_string(errnum) + "次");
						heartLOCK = 1;
						recvLOCK = 0;
						return false;
					}
				}
			}
			
		}
		memset(recvBuf, 0, sizeof(recvBuf));//把接收的数据清空
		recvLOCK = 0;
	}
	
	return false;
}
