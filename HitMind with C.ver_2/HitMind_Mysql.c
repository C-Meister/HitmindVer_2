#include "include.h"

//mysql���� �Լ���
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