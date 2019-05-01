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
		c->out("�ȴ��û�������...");
		SOCKET sockConnect = accept(sock, (SOCKADDR*)&addrClient, &len);
		Log *login_user = new Log("login", (string)inet_ntoa(addrClient.sin_addr));
		//c->out ("��[" + (string)inet_ntoa(addrClient.sin_addr) + "]��������") ;
		login_user->out("��������");
		playernum++;
		Player *player = new Player(sockConnect, login_user, playernum);
		
		login_user->out("�������"+ std::to_string(playernum) +"ר���߳�...");
		thread player_thread(player_server, player);	//�������ר���߳�
	}
	return 0;
}

int Server::init()
{
	//1.����SOCKET�⣬�汾Ϊ2.0
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 0);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		c->err("Socket2.0��ʼ��ʧ�ܣ�Exit!");
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0)
	{
		WSACleanup();
		return 0;
	}

	//2.�����׽���,���ڼ���
	//SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		c->err("Socket ����ʧ�ܣ�Exit!");
		return -1;
	}

	//3.��
	SOCKADDR_IN myaddr; //sockaddr_in�൱��sockaddr�ṹ
	memset(&myaddr, 0, sizeof(myaddr));//��ʼ��  ���� 
	myaddr.sin_family = AF_INET;//ֻ��Ϊ���ֵ
	myaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//��u_long��ת��Ϊ�����ֽ�����
	myaddr.sin_port = htons(port);// ��u_short��ת��Ϊ�����ֽ�����

	bind(sock, (SOCKADDR*)&myaddr, sizeof(myaddr));//���׽���

	//4.���ü���
	listen(sock, 5);
	//cout << "��ʼ����10099�˿�..." << endl;
	c->out("��ʼ����" + to_string(port) + "�˿�...");
	return 0;
}
