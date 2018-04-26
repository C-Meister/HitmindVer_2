#include "include.h"

//mysql���� �Լ���


void Thread_MySQL(Connect_status *type)
{
	(MYSQL *)type->arg = Mysql_Connect(ServerIp);
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
		exit(1);
	}
	if (mysql_real_connect(cons, ip, "hitmind", "", NULL, 0, NULL, 0) == NULL)	//MySQL�� ������
	{
		
		////printf("\nMySQL ���� ����...\n���� ���� : %s\n", mysql_error(cons));
		////printf("ip�� �ٽ� ���� �ּ���...\n->");
		ShowWindow(GetConsoleWindow(), 1);
		printf("DB������ ������ �����Ͽ����ϴ�. setting.txt���Ͽ� Ip�� �ٲٰų� ���� �Է����ּ���\n->");
		scanf("%s", ServerIp);
		ShowWindow(GetConsoleWindow(), 0);
		changesetting(BGmusic, Sound, Display_X, Display_Y, Full);
		return Mysql_Connect(ServerIp);		//����Լ��� ȣ��(�ٽ� ������)
	}
	else
	{
		////printf("\n%s ���� ����...\n", ip);
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
	sprintf(query, "select * from User where auto_login = PASSWORD('%s')", GetDefaultMyIP());	//�ش� id�� �̸��� ã�´�
	////printf("%s\n", GetDefaultMyIP());
	mysql_query(cons, query);
	MYSQL_ROW rows;
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows == 0)		//������
	{
		return 0;		//0�� ������
	}
	else
	{
		Hit_User *My_User = (Hit_User *)malloc(sizeof(Hit_User));	//�޸𸮸� �Ҵ��� calloc�� �Ҵ��� �� 0���� ä��
		memset(My_User, 0, sizeof(My_User));
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
		strcpy(My_User->password, rows[3]);
		strcpy(My_User->name, rows[1]);
		My_User->level = atoi(rows[4]);
		My_User->money = atoi(rows[5]);
		My_User->pass_length = atoi(rows[8]);
		strcpy(My_User->profile, rows[10]);
		strcpy(My_User->ownip, rows[6]);
		//�Ҵ��� ������ ���� ������ ������
		return My_User;		//����
	}
}
int getUesrStatus(MYSQL *cons, char arr[30][30])
{
	MYSQL_RES *sql_result;
	MYSQL_ROW row;
	memset(arr, 0, sizeof(arr));
	mysql_query(cons, "select * from user where status != 0");
	sql_result = mysql_store_result(cons);
	int i = 0;
	
	while ((row = mysql_fetch_row(sql_result)) != NULL)
	{
		strcpy(arr[i], row[1]);
		arr[i][27] = atoi(row[4]);
		arr[i][28] = atoi(row[9]);
		i++;
	}
	mysql_free_result(sql_result);
	return i;
}
int User_Signin_sql(MYSQL *cons, wchar_t *id, wchar_t *password, wchar_t * nickname, wchar_t* answer)
{
	char char_id[128] = "";
	char query[384];
	char char_password[128] = "";
	char char_answer[128] = "";
	char char_nickname[128] = "";
	strcpy(query, UNICODE2UTF8(id, wcslen(id)));
	UTF82EUCKR(char_id, 128, query, 384);
	char_id[strlen(char_id)] = '\0';
	MYSQL_ROW rows;

	strcpy(query, UNICODE2UTF8(password, wcslen(password)));
	UTF82EUCKR(char_password, 128, query, 384);
	char_password[strlen(char_password)] = '\0';
	strcpy(query, UNICODE2UTF8(answer, wcslen(answer)));
	UTF82EUCKR(char_answer, 128, query, 384);
	char_answer[strlen(char_answer)] = '\0';
	strcpy(query, UNICODE2UTF8(nickname, wcslen(nickname)));
	UTF82EUCKR(char_nickname, 128, query, 384);
	char_nickname[strlen(char_nickname)] = 0;
	if (User_Login_sql(cons, char_id, char_password) != -1)
	{
		return 0;
	}
	sprintf(query, "select * from User where name = '%s'", char_nickname);	//�ش� id �� password�� �´� ���� ã�Ƴ�
	mysql_query(cons, query);
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows != 0)	//���� ������ 0�� ����
		return -2;
	sprintf(query, "insert into user (name, id, password, pass_find, password_length) values ('%s', '%s', PASSWORD('%s'), '%s', %zd)", char_nickname, char_id, char_password, char_answer, strlen(char_password));
	if (mysql_query(cons, query) != 0)
	{
		return -1;
	}
	return 1;
}
int Password_Change_sql(MYSQL *cons, wchar_t *id, wchar_t *newpassword, wchar_t *answer) {
	char char_id[128] = "";
	char query[384];
	char char_password[128] = "";
	char char_answer[128] = "";
	strcpy(query, UNICODE2UTF8(id, wcslen(id)));
	UTF82EUCKR(char_id, 128, query, 384);
	char_id[strlen(char_id)] = '\0';
	MYSQL_ROW rows;
	strcpy(query, UNICODE2UTF8(newpassword, wcslen(newpassword)));
	UTF82EUCKR(char_password, 128, query, 384);
	char_password[strlen(char_password)] = '\0';
	strcpy(query, UNICODE2UTF8(answer, wcslen(answer)));
	UTF82EUCKR(char_answer, 128, query, 384);
	char_answer[strlen(char_answer)] = '\0';

	sprintf(query, "select * from user where id = '%s'", char_id);
	mysql_query(cons, query);
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows == 0)
	{
		return -1;
	}
	sprintf(query, "select * from user where id = '%s' and pass_find = '%s'", char_id, char_answer);
	mysql_query(cons, query);
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows == 0)
	{
		return 0;
	}
	sprintf(query, "update user set password = PASSWORD('%s') where id = '%s' and pass_find = '%s'", char_password, char_id, char_answer);
	if (mysql_query(cons, query) != 0)
		return  -2;
	sprintf(query, "update user set password_length = %zd where id = '%s' and pass_find = '%s'", strlen(char_password), char_id, char_answer);
	if (mysql_query(cons, query) != 0)
		return  -2;
	return 1;
}
int Mysql_wstr_query(MYSQL *cons, wchar_t * query) {
	char char_query[128];
	char buff[384];
	strcpy(buff, UNICODE2UTF8(query, wcslen(query)));
	UTF82EUCKR(char_query, 128, buff, 384);
	char_query[strlen(char_query)] = 0;
	////printf("%s", char_query);
	return mysql_query(cons, char_query);
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
		return -1;		//-1�� ������
	}
	if (password[0] == '*') 
		sprintf(query, "select * from User where id = '%s' and password = '%s'", id, password);	//�ش� id �� password�� �´� ���� ã�Ƴ�
	else
	sprintf(query, "select * from User where id = '%s' and password = password('%s')", id, password);	//�ش� id �� password�� �´� ���� ã�Ƴ�
	mysql_query(cons, query);
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows == 0)	//���� ������ 0�� ����
		return 0;
	else
	{
		Hit_User *My_User = (Hit_User *)malloc(sizeof(Hit_User));	//�޸𸮸� �Ҵ��� calloc�� �Ҵ��� �� 0���� ä��
		memset(My_User, 0, sizeof(My_User));
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
		strcpy(My_User->password, rows[3]);
		My_User->level = atoi(rows[4]);
		My_User->money = atoi(rows[5]);
		My_User->pass_length = atoi(rows[8]);
		strcpy(My_User->ownip, rows[6]);
		strcpy(My_User->profile, rows[10]);
		//�Ҵ��� ������ ���� ������ ������
		return My_User;		//����
	}

}
int ReadChating_all(MYSQL *cons, Chating * chatings)
{
	MYSQL_RES * sql_result;
	MYSQL_ROW rows;
	memset(chatings, 0, sizeof(chatings));
	int i = 0; 
	mysql_query(cons, "select * from all_chating order by ownnum desc limit 30");
	sql_result = mysql_store_result(cons);
	while ((rows = mysql_fetch_row(sql_result)) != 0)
	{
		chatings[i].ownnum = atoi(rows[0]);
		strcpy(chatings[i].name, rows[1]);
		strcpy(chatings[i].message, rows[2]);
		strcpy(chatings[i].time, rows[3]);
		i++;
	}
	mysql_free_result(sql_result);
	return i;
}
int GetRoomUser(MYSQL * cons, User * friends, SDL_Renderer * renderer) {
	int i;
	char query[64];
	MYSQL_ROW rows;
	for (i = 0; i < 4; i++)
	{
		if (friends[i].status)
		{
			sprintf(query, "select * from user where ownnum = %d", friends[i].ownnum);
			mysql_query(cons, query);
			rows = mysql_fetch_row(mysql_store_result(cons));
			if (rows != 0)
			{
				strcpy(friends[i].Nickname, rows[1]);
				friends[i].Level = atoi(rows[4]);
				friends[i].Profile = LoadTextureEx(renderer, rows[10], 255, 255, 255);
			}
		}
	}
	return 1;
}

int InsertChating_all(MYSQL *cons, char * username, wchar_t* message,int messagelength) {
	char char_message[512]="";
	char query[850];
	strcpy(query, UNICODE2UTF8(message, messagelength));
	UTF82EUCKR(char_message, 512, query, 850);
	char_message[strlen(char_message)] = '\0';
	wchar_t UnicodeOfMessage[256] = L"";
	han2unicode(char_message, UnicodeOfMessage);
	if (hannum(message,messagelength)!=hannum(UnicodeOfMessage,wcslen(UnicodeOfMessage))) {
		strcpy(char_message, "[InValid Conversion]");
	}
	sprintf(query, "insert into all_chating (name, message) values ('%s', '%s')", username, char_message);
	if (mysql_query(cons, query) != 0)
		return 0;
	return 1;
}

int Get_Room_List(MYSQL *cons, Hit_Room * rooms) {
	MYSQL_RES * sql_result;
	MYSQL_ROW rows;
	int i = 0;
	mysql_query(cons, "select * from room");
	sql_result = mysql_store_result(cons);
	while ((rows = mysql_fetch_row(sql_result)) != 0) {
		rooms[i].ownnum = atoi(rows[0]);
		strcpy(rooms[i].ip, rows[1]);
		strcpy(rooms[i].name, rows[2]);
		strcpy(rooms[i].password, rows[3]);
		rooms[i].people = atoi(rows[4]);
		strcpy(rooms[i].mode, rows[5]);
		rooms[i].time = atoi(rows[6]);
		rooms[i].question = atoi(rows[7]);
		rooms[i].max_people = atoi(rows[8]);
		i++;
	}
	mysql_free_result(sql_result);
	return i;
}

int Create_Room_sql(MYSQL *cons, wchar_t * roomname, wchar_t * rompass, int mode, int question, int timer)
{
	char char_roomname[128] = { 0 , };
	char char_roompass[128] = { 0, };
	char query[384];
	strcpy(query, UNICODE2UTF8(roomname, wcslen(roomname)));
	UTF82EUCKR(char_roomname, 128, query, 384);
	char_roomname[strlen(char_roomname)] = '\0';

	strcpy(query, UNICODE2UTF8(rompass, wcslen(rompass)));
	UTF82EUCKR(char_roompass, 128, query, 384);
	char_roompass[strlen(char_roompass)] = '\0';

	MYSQL_ROW rows;
	sprintf(query, "select * from room where name = '%s'", char_roomname);
	mysql_query(cons, query);
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows != 0)
	{
		return -1;
	}
	char char_mode[10];
	if (mode == 1)
	{
		strcpy(char_mode, "�Ϲ�");
	}
	else if (mode == 2) {
		strcpy(char_mode, "���׽�Ʈ");
	}
	else
		strcpy(char_mode, "FPS");
	sprintf(query, "insert into room (ip, name, password , mode, time, question, max_people) values ('%s', '%s', '%s', '%s', %d, %d, 4)", GetDefaultMyIP(), char_roomname, char_roompass, char_mode, timer, question);
	if (mysql_query(cons, query) != 0)
	{
		return 0;
	}
	return 1;
}
int Get_Notice_sql(MYSQL *cons, Notice * notice) {
	MYSQL_RES * sql_result;
	MYSQL_ROW rows;
	int i = 0;
	mysql_query(cons, "select * from notice order by num desc limit 5");
	sql_result = mysql_store_result(cons);
	while ((rows = mysql_fetch_row(sql_result)) != 0)
	{
		notice[i].ownnum = atoi(rows[0]);
		strcpy(notice[i].content, rows[1]);
		strcpy(notice[i].time, rows[2]);
		i++;
	}
	mysql_free_result(sql_result);
	return i;
}
int Get_Version_sql(MYSQL *cons, char * message)
{
	mysql_query(cons, "select * from version order by thistime desc limit 1");
	MYSQL_ROW row;
	if ((row = mysql_fetch_row(mysql_store_result(cons))) == 0)
	{
		return 0;
	}
	else {
		sprintf(message, "���� ���� : %s - %s", row[0], row[1]);
		return 1;
	}
	return 0;
}
int Insert_Topic_sql(MYSQL *cons, char *my_name, wchar_t * topic)
{
	char char_message[256] = "";
	char query[512];
	strcpy(query, UNICODE2UTF8(topic, 256));
	UTF82EUCKR(char_message, 256, query, 512);
	char_message[strlen(char_message)] = 0;
	sprintf(query, "insert into topic (top, writer) values ('%s', '%s')", char_message, my_name);
	return mysql_query(cons, query);
}