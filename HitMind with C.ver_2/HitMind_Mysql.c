#include "include.h"

//mysql���� �Լ���


void Thread_MySQL(Connect_status *type)
{
	(MYSQL *)type->arg = Mysql_Connect("10.80.162.92");
	type->ishappen = true;
}

MYSQL * Mysql_Connect(char *ip)		//Mysql_Connect�Լ�	���ڰ�:ip�ּ� ��ȯ��:MySQL����ü
{
	/*
		MySQL - ���񼭹�
		ip = 10.80.162.92
		���� �̸�: hitmind
		��й�ȣ : hituser
		��� ���� hitmind_2 DB�� ������ �ο���
	*/
	MYSQL *cons = mysql_init(NULL);		//MySQL�� �ʱ�ȭ �Ѵ�.
	if (cons == NULL)
	{
		printf("\nMySQL�ʱ�ȭ ����...\n���� ���� : %s\n", mysql_error(cons));	//mysql_error() ���� ������ ��ȯ��
		exit(1);
	}
	if (mysql_real_connect(cons, ip, "hitmind", "hituser", NULL, 0, NULL, 0) == NULL)	//MySQL�� ������
	{
		char sqlip[30];
		printf("\nMySQL ���� ����...\n���� ���� : %s\n", mysql_error(cons));
		printf("ip�� �ٽ� ���� �ּ���...\n->");
		scanf("%s", sqlip);
		return Mysql_Connect(sqlip);		//����Լ��� ȣ��(�ٽ� ������)
	}
	else
	{
		printf("\n%s ���� ����...\n", ip);
		mysql_set_character_set(cons, "euckr");	//DB�� ĳ���� ���¤� euckr(�⺻ �ܼ�)�� �ٲ�
		mysql_select_db(cons, "hitmind_2");		//hitmind_2 DB�� ������
	}
	return cons;	//���ᰪ�� ��ȯ
}

char * Get_Random_Topic(MYSQL *cons)
{
	MYSQL_ROW sql_row;	//sql_row �� typedef�� char **�� �Ȱ���
	mysql_query(cons, "select top from topic order by rand() limit 1");		//�� ��ɾ�� topic ���̺��� ������ �� �ϳ��� �ҷ���
	sql_row = mysql_fetch_row(mysql_store_result(cons));	//mysql_store_result�� ���� ������ �� fetch_row�� ���� char **������ ��ȯ��Ŵ
	return sql_row[0];	//char **���� ù��°�� ��ȯ
}
Hit_User *IsAutoLogin(MYSQL *cons)
{
	char query[128];
	sprintf(query, "select name from User where auto_login = '%s'", GetDefaultMyIP());	//�ش� id�� �̸��� ã�´�
	mysql_query(cons, query);
	MYSQL_ROW rows;
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows == 0)		//������
	{
		return 0;		//0�� ������
	}
	else
	{
		Hit_User *My_User = (Hit_User *)calloc(1, sizeof(Hit_User));	//�޸𸮸� �Ҵ��� calloc�� �Ҵ��� �� 0���� ä��
		//hitmind_2 DB�� User���̺� ��
		/*
			rows[0] = ownnum (���� ��ȣ) ����� ���� �ٸ�
			rows[1] = name (����� �̸�)
			rows[2] = id (�α��� ���̵�)
			rows[3] = password (�α��� ��й�ȣ)
			rows[4] = ����
			rows[5] = ��
			rows[6] = auto_login (ip�� ������)
		*/
		My_User->ownnum = atoi(rows[0]);
		strcpy(My_User->id, rows[2]);
		strcpy(My_User->name, rows[1]);
		My_User->level = atoi(rows[4]);
		My_User->money = atoi(rows[5]);
		strcpy(My_User->ownip, rows[6]);
		//�Ҵ��� ������ ���� ������ ������
		return My_User;		//����
	}
}
Hit_User *User_Login_sql(MYSQL *cons, char * id, char *password)	//���̵�� ��й�ȣ�� �α�����
{
	/*
	��ȯ�� 
	Hit_User ���� = ����
	0 = �α��� ����
	*/
	char query[128];
	sprintf(query, "select name from User where id = '%s'", id);	//�ش� id�� �̸��� ã�´�
	mysql_query(cons, query);
	MYSQL_ROW rows;
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows == 0)		//������
	{
		return -1;		//0�� ������
	}
	sprintf(query, "select * from User where id = '%s' and password = password('%s')", id, password);	//�ش� id �� password�� �´� ���� ã�Ƴ�
	mysql_query(cons, query);
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows == 0)	//���� ������ 0�� ����
		return 0;
	else
	{
		Hit_User *My_User = (Hit_User *)calloc(1, sizeof(Hit_User));	//�޸𸮸� �Ҵ��� calloc�� �Ҵ��� �� 0���� ä��
		//hitmind_2 DB�� User���̺� ��
		/*
			rows[0] = ownnum (���� ��ȣ) ����� ���� �ٸ�
			rows[1] = name (����� �̸�)
			rows[2] = id (�α��� ���̵�)
			rows[3] = password (�α��� ��й�ȣ)
			rows[4] = ����
			rows[5] = ��
			rows[6] = auto_login (ip�� ������)
		*/ 
		My_User->ownnum = atoi(rows[0]);
		strcpy(My_User->id, rows[2]);
		strcpy(My_User->name, rows[1]);
		My_User->level = atoi(rows[4]);
		My_User->money = atoi(rows[5]);
		strcpy(My_User->ownip, rows[6]);
		//�Ҵ��� ������ ���� ������ ������
		return My_User;		//����
	}

}