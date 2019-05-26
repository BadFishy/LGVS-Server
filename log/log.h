#pragma once
#pragma comment(lib, "WS2_32")
#include <string>
#include <winsock2.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include "config/config.h"

using namespace std;


class Log
{
	/**
	 *	Log�� ����
	 *	�����ڿ���̨�����־�����������־�ļ���LGVS.log����
	 *	��������ΪLog�Ķ���ʱ����Ҫ�趨��־�ļ����������� Log abc��"filename"��
	 *	ʹ�� out("�ı�����") ���������־
	 *	ʹ�� err("�ı�����") ���������־
	 */
private:

	string filepath;
	string erropath;
	string qz;

	string getTime()
	{
		time_t timep;
		time(&timep);
		char tmp[64];
		struct tm now_time;
		localtime_s(&now_time,&timep);
		sprintf_s(tmp, "%d-%d-%d %d:%d:%d", now_time.tm_year + 1900, now_time.tm_mon + 1,
			now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
		//strftime(tmp, sizeof(tmp), );
		return tmp;
	}

public:
	Log(string filename ="LGVS",string ip = "") {
		string logpath = ".\\log\\" + filename;
		filepath = logpath;
		filepath += ".log";
		erropath = logpath;
		erropath += "_error.log";
		if (ip.length() != 0) {
			qz = "[";
			qz += (ip+"]");
		}
		else qz = ip;
	};

	int out(string str) ;

	int err(string str);
	
};
