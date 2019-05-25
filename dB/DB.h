#pragma once
#include "log/log.h"
#include <stdio.h>  
//#include <WinSock.h>  //һ��Ҫ������� 
#include "mysql.h"  
#include <Windows.h>  
//�������������Ҳ�����ڹ���--������������  
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

	MYSQL_FIELD *fd;    //�ֶ�������
	char field[32][32]; //���ֶ�����ά����
	MYSQL_RES *res;     //�е�һ����ѯ�����
	MYSQL_ROW column;   //�����е���
	

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
		host = config->Read<string>("DB_host");	//�������ݿ��ַ
		user = config->Read<string>("DB_user");	//�������ݿ��û���
		psw = config->Read<string>("DB_password");	//�������ݿ��û�����
		table = config->Read<string>("DB_name");	//�������ݿ���
		port = stoi(config->Read<string>("DB_port"));	//�������ݿ�˿�,sringתint
	};

	

	~DB();

	bool connectDB();
	bool runSQL(const char* query);
	bool cunzaiDB(string, string, string);
	bool tongshicunzaiDB(string, string, string, string, string);
	bool QueryDatabase(const char* query);
	string cha(const char* query);
};

