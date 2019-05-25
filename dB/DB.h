#pragma once
#include "log/log.h"
#include <stdio.h>  
//#include <WinSock.h>  //一定要包含这个 
#include "mysql.h"  
#include <Windows.h>  
//包含附加依赖项，也可以在工程--属性里面设置  
#pragma comment(lib,"wsock32.lib") 
#pragma comment(lib,"libmysql.lib")


class DB
{
private:
	Log *c;
	MYSQL mysql;
	string host;
	string user;
	string psw;
	string table;
	int	port;

	MYSQL_FIELD *fd;    //字段列数组
	char field[32][32]; //存字段名二维数组
	MYSQL_RES *res;     //行的一个查询结果集
	MYSQL_ROW column;   //数据行的列
	

public:
	DB(string host_in = "127.0.0.1", string user_in = "LGVS", string psw_in = "password", string table_in = "LGVS", int port_in = 3306) {
		c = new Log("DataBase");
		host = host_in;
		user = user_in;
		psw = psw_in;
		table = table_in;
		port = port_in;
	};

	DB(Config* config) {
		c = new Log("DataBase");
		host = config->Read<string>("DB_host");	//加载数据库地址
		user = config->Read<string>("DB_user");	//加载数据库用户名
		psw = config->Read<string>("DB_password");	//加载数据库用户密码
		table = config->Read<string>("DB_name");	//加载数据库名
		port = stoi(config->Read<string>("DB_port"));	//加载数据库端口,sring转int
	};

	

	~DB();

	bool connectDB();
	bool runSQL(const char* query);
	bool cunzaiDB(string, string, string);
	bool tongshicunzaiDB(string, string, string, string, string);
	bool QueryDatabase(const char* query);
	string cha(const char* query);
};

