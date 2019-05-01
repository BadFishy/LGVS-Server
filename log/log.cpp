#include "log.h"

int suo = 0;

int Log::out(string str)
{

	
	string nowtime = getTime();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);//������ɫ
	ofstream file(filepath, ios::app);
	file << "[" << nowtime << "]" << qz << str << endl;
	cout << "[" << nowtime << "]" << qz << str << " [" << filepath << "]" << endl;
	suo = 0;
	return 0;
}

int Log::err(string str)
{
	//while (suo) {}
	//suo = 1;
	string nowtime = getTime();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);//���ú�ɫ
	ofstream file(filepath, ios::app);
	ofstream erro(erropath, ios::app);
	file << "[" << nowtime << "]" << qz << "Error:" << str << endl;
	erro << "[" << nowtime << "]" << qz << "Error:" << str << endl;
	cout << "[" << nowtime << "]" << qz << "Error:" << str << " [" << filepath << "]" << endl;
	suo = 0;
	return 0;
}
