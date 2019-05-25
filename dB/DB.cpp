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

//��ѯ����
bool DB::QueryDatabase(const char* q) {
	char query[150];    //��ѯ���
	//�����ݸ�ʽ��������ַ���
	sprintf_s(query, "select * from %s", q);
	//���ñ����ʽ
	mysql_query(&mysql, "set names gbk");

	if (mysql_query(&mysql, query)) {
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else {
		printf("query success\n");
	}

	res = mysql_store_result(&mysql);
	if (!res) {
		printf("Couldn't get result from %s\n", mysql_error(&mysql));
		return false;
	}

	printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));

	// ��ȡ����
	int j = mysql_num_fields(res);

	//�洢�ֶ���Ϣ
	char *str_field[32];

	//��ȡ�ֶ���
	for (int i = 0; i < j; i++) {
		str_field[i] = mysql_fetch_field(res)->name;
	}

	//��ӡ�ֶ�
	for (int i = 0; i < j; i++)
		printf("%10s\t", str_field[i]);
	printf("\n");

	//��ӡ��ѯ���
	//MYSQL_ROW mysql_fetch_row(MYSQL_RES *result)
	//Fetches the next row from the result set
	while (column = mysql_fetch_row(res)) {
		for (int i = 0; i < j; i++)
			printf("%10s\t", column[i]);
		printf("\n");
	}
	return true;
}

string DB::cha(const char* q)
{
	char query[150];    //��ѯ���
//�����ݸ�ʽ��������ַ���
	sprintf_s(query, "select * from %s", q);
	//���ñ����ʽ
	mysql_query(&mysql, "set names gbk");

	if (mysql_query(&mysql, query)) {
		//printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else {
		//printf("query success\n");
	}

	res = mysql_store_result(&mysql);
	if (!res) {
		//printf("Couldn't get result from %s\n", mysql_error(&mysql));
		return false;
	}

	//printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));

	// ��ȡ����
	int j = mysql_num_fields(res);
	
	int hang = 0;
	// ��ȡ����
	string bak = std::to_string(mysql_num_rows(res));
	while (column = mysql_fetch_row(res)) {
		for (int i = 0; i < j; i++)
			bak += "," + (string)column[i];
	}
	return bak;
}

string DB::sou(const char* q)
{
	char query[150];    //��ѯ���
//�����ݸ�ʽ��������ַ���
	sprintf_s(query, "%s", q);
	//���ñ����ʽ
	mysql_query(&mysql, "set names gbk");

	if (mysql_query(&mysql, query)) {
		//printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else {
		//printf("query success\n");
	}

	res = mysql_store_result(&mysql);
	if (!res) {
		//printf("Couldn't get result from %s\n", mysql_error(&mysql));
		return false;
	}

	//printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));

	// ��ȡ����
	int j = mysql_num_fields(res);

	int hang = 0;
	// ��ȡ����
	string bak = std::to_string(mysql_num_rows(res));
	while (column = mysql_fetch_row(res)) {
		for (int i = 0; i < j; i++)
			bak += "," + (string)column[i];
	}
	return bak;
}

