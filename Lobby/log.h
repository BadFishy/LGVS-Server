#pragma once
#pragma comment(lib, "WS2_32")
#include <string>
#include <winsock2.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include "config.h"

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
		strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
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

	int out(string str) {
		string nowtime = getTime();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//������ɫ
		ofstream file(filepath, ios::app);
		file << "[" << nowtime << "]" << qz << str << endl;
		cout << "[" << nowtime << "]" << qz << str << " [" << filepath << "]" << endl;
		return 0;
	};

	int err(string str) {
		string nowtime = getTime();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//���ú�ɫ
		ofstream file(filepath, ios::app);
		ofstream erro(erropath, ios::app);
		file << "[" << nowtime << "]" << qz << "Error:" << str << endl;
		erro << "[" << nowtime << "]" << qz << "Error:" << str << endl;
		cout << "[" << nowtime << "]" << qz << "Error:" << str << " [" << filepath << "]" << endl;
		return 0;
	};
};
