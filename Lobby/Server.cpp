#include "pch.h"
#include "Server.h"
#include "Player.h"


void player_server(Player *player) {
	player->start();
	
}

int Server::start()
{
	while (1) {
		len = sizeof(SOCKADDR);
		c->out("等待用户连接中...");
		SOCKET sockConnect = accept(sock, (SOCKADDR*)&addrClient, &len);
		Log *login_user = new Log("login", (string)inet_ntoa(addrClient.sin_addr));
		//c->out ("与[" + (string)inet_ntoa(addrClient.sin_addr) + "]建立连接") ;
		login_user->out("建立连接");
		playernum++;
		Player *player = new Player(sockConnect, login_user, playernum);
		
		login_user->out("创建玩家"+ std::to_string(playernum) +"专用线程...");
		thread player_thread(player_server, player);	//创建玩家专用线程
	}
	return 0;
}

int Server::init()
{
	//1.启动SOCKET库，版本为2.0
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 0);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		c->err("Socket2.0初始化失败，Exit!");
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0)
	{
		WSACleanup();
		return 0;
	}

	//2.创建套接字,用于监听
	//SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		c->err("Socket 创建失败，Exit!");
		return -1;
	}

	//3.绑定
	SOCKADDR_IN myaddr; //sockaddr_in相当于sockaddr结构
	memset(&myaddr, 0, sizeof(myaddr));//初始化  清零 
	myaddr.sin_family = AF_INET;//只能为这个值
	myaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//将u_long型转换为网络字节序列
	myaddr.sin_port = htons(port);// 将u_short型转换为网络字节序列

	bind(sock, (SOCKADDR*)&myaddr, sizeof(myaddr));//绑定套接字

	//4.设置监听
	listen(sock, 5);
	//cout << "开始监听10099端口..." << endl;
	c->out("开始监听" + to_string(port) + "端口...");
	return 0;
}
