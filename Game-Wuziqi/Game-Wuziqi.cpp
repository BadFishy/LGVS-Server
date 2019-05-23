// Game-Wuziqi.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "log/log.h"
#include <io.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include "server/server.h"
#include <thread>
#include <windows.h>


int init(Log*);//1. 初始化
void start_Wuziqi_server(Server *Wuziqi_server);

//2. 开启服务端
int start(Log *c)
{
	while (true) {

		string cmd;

		c->out("-------------!开始运行!--------------");
		c->out("凉糕对战平台（LGVS）服务端启动器");
		c->out("五子棋服务端");
		c->out("加载配置文件...");

		Config* config = new Config("config.ini");	//初始化Config类，加载配置文件

		c->out("启用五子棋服务器...");
		Server *Wuziqi_server = new Server(config);	//实例化大厅服务器
		Wuziqi_server->init();	//初始化登陆服务器

		thread lobby_thread(start_Wuziqi_server, Wuziqi_server);	//创建登录服务器线程

		while (true) {
			cin >> cmd;
		}
	}

}

int main()
{
	Log *c = new Log("Game-Wuziqi");
	while (true) {

		//1. 初始化
		if (init(c) == -1) {
			system("echo - 按任意键重新开始...");
			system("pause > nul");
		}

		//2. 开启服务端
		int kaishi = start(c);
		if (kaishi == -1) {
			system("echo - 按任意键重新开始...");
			system("pause > nul");
		}
		if (kaishi == 0) {
			system("echo - 按任意键关闭本窗口...");
			system("pause > nul");
			return 0;
		}
	}
	return 0;
}


//1. 初始化
int init(Log *c) {//初始化
	if (_access(".\\log", 0) == -1) {	//如果目录不存在
		system("mkdir .\\log");
		c->out("检测到没有日志目录，目前已经自动创建...");
		return 1;
	}
	if (_access(".\\config.ini", 0) == -1) {//如果配置文件不存在
		c->err("配置文件不存在！请修改config_origin.ini内的配置后将其更名为config.ini");
		//ofstream confout(".\\config.ini");
		return -1;
	}

	return 0;
}

void start_Wuziqi_server(Server *Wuziqi_server) {
	Wuziqi_server->start();
}