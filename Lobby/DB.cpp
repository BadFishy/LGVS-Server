#include "DB.h"

bool DB::connectDB()
{
	{
		
		mysql_init(&mysql);
		if (!(mysql_real_connect(&mysql, host.data(), user.data(), psw.data(), table.data(), port, NULL, 0)))
			//�м�ֱ����������û��������룬���ݿ������˿ںţ�����дĬ��0����3306�ȣ���������д�ɲ����ٴ���ȥ  
		{
			
			string buffer = "�������ݿ�ʧ�ܣ�������룺" + (string)mysql_error(&mysql);
			c->err(buffer);
			return false;
		}
		else
		{
			c->out("���ݿ����ӳɹ���");
			return true;
		}

	}
	return false;
}

bool DB::runSQL(const char* query)
{
	if (mysql_query(&mysql, query))        //ִ��SQL���  
	{
		c->err("ѯ��ʧ�ܣ�" + (string)mysql_error(&mysql));
		return false;
	}
	else
	{
		c->out("����ɹ���");
		return true;
	}
	return false;
}

//��ѯ����
bool DB::cunzaiDB(string biao, string lie, string zhi)
{
	string que = "select * from "
		+ biao +" where "+ lie +" = '"
		+ zhi + "'";
	int res = mysql_query(&mysql, que.data());
	if (res == 0)
	{
		
		MYSQL_RES *result = mysql_store_result(&mysql);
		my_ulonglong rowCount = mysql_num_rows(result);
		if (rowCount == 0)
		{
			return false;//������
		}
		else
		{
			return true;//����
		}
	}
	return false;
}

bool DB::tongshicunzaiDB(string biao, string lie1, string zhi1, string lie2, string zhi2)
{
	string que = "select * from "
		+ biao + " where "
		+ lie1 + " = '"
		+ zhi1 + "' and "
		+ lie2 + " = '"
		+ zhi2 + "'";
	int res = mysql_query(&mysql, que.data());
	if (res == 0)
	{

		MYSQL_RES *result = mysql_store_result(&mysql);
		my_ulonglong rowCount = mysql_num_rows(result);
		if (rowCount == 0)
		{
			return false;//������
		}
		else
		{
			return true;//����
		}
	}
	return false;
}


