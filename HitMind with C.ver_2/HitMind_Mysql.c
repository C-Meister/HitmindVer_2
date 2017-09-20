#include "include.h"

//mysql관련 함수들


void Thread_MySQL(Connect_status *type)
{
	(MYSQL *)type->arg = Mysql_Connect("10.80.162.92");
	type->ishappen = true;
}

MYSQL * Mysql_Connect(char *ip)		//Mysql_Connect함수	인자값:ip주소 반환값:MySQL구조체
{
	/*
		MySQL - 상희서버
		ip = 10.80.162.92
		유저 이름: hitmind
		비밀번호 : hituser
		사용 권한 hitmind_2 DB만 권한을 부여함
	*/
	MYSQL *cons = mysql_init(NULL);		//MySQL을 초기화 한다.
	if (cons == NULL)
	{
		printf("\nMySQL초기화 실패...\n오류 원인 : %s\n", mysql_error(cons));	//mysql_error() 에러 원인을 반환함
		exit(1);
	}
	if (mysql_real_connect(cons, ip, "hitmind", "hituser", NULL, 0, NULL, 0) == NULL)	//MySQL에 연결함
	{
		char sqlip[30];
		printf("\nMySQL 연결 실패...\n오류 원인 : %s\n", mysql_error(cons));
		printf("ip를 다시 적어 주세요...\n->");
		scanf("%s", sqlip);
		return Mysql_Connect(sqlip);		//재귀함수의 호출(다시 연결함)
	}
	else
	{
		printf("\n%s 연결 성공...\n", ip);
		mysql_set_character_set(cons, "euckr");	//DB의 캐릭터 세승ㄹ euckr(기본 콘솔)로 바꿈
		mysql_select_db(cons, "hitmind_2");		//hitmind_2 DB를 선택함
	}
	return cons;	//연결값을 반환
}

char * Get_Random_Topic(MYSQL *cons)
{
	MYSQL_ROW sql_row;	//sql_row 는 typedef로 char **와 똑같음
	mysql_query(cons, "select top from topic order by rand() limit 1");		//이 명령어는 topic 테이블에서 랜덤된 값 하나를 불러옴
	sql_row = mysql_fetch_row(mysql_store_result(cons));	//mysql_store_result로 값을 저장한 뒤 fetch_row로 값을 char **값으로 변환시킴
	return sql_row[0];	//char **값의 첫번째를 반환
}
Hit_User *IsAutoLogin(MYSQL *cons)
{
	char query[128];
	sprintf(query, "select name from User where auto_login = '%s'", GetDefaultMyIP());	//해당 id의 이름을 찾는다
	mysql_query(cons, query);
	MYSQL_ROW rows;
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows == 0)		//없으면
	{
		return 0;		//0을 리턴함
	}
	else
	{
		Hit_User *My_User = (Hit_User *)calloc(1, sizeof(Hit_User));	//메모리를 할당함 calloc은 할당한 후 0으로 채움
		//hitmind_2 DB에 User테이블 값
		/*
			rows[0] = ownnum (고유 번호) 사용자 마다 다름
			rows[1] = name (사용자 이름)
			rows[2] = id (로그인 아이디)
			rows[3] = password (로그인 비밀번호)
			rows[4] = 레벨
			rows[5] = 돈
			rows[6] = auto_login (ip를 저장함)
		*/
		My_User->ownnum = atoi(rows[0]);
		strcpy(My_User->id, rows[2]);
		strcpy(My_User->name, rows[1]);
		My_User->level = atoi(rows[4]);
		My_User->money = atoi(rows[5]);
		strcpy(My_User->ownip, rows[6]);
		//할당한 공간에 유저 정보를 복사함
		return My_User;		//리턴
	}
}
Hit_User *User_Login_sql(MYSQL *cons, char * id, char *password)	//아이디와 비밀번호로 로그인함
{
	/*
	반환값 
	Hit_User 정보 = 성공
	0 = 로그인 실패
	*/
	char query[128];
	sprintf(query, "select name from User where id = '%s'", id);	//해당 id의 이름을 찾는다
	mysql_query(cons, query);
	MYSQL_ROW rows;
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows == 0)		//없으면
	{
		return -1;		//0을 리턴함
	}
	sprintf(query, "select * from User where id = '%s' and password = password('%s')", id, password);	//해당 id 와 password에 맞는 값을 찾아냄
	mysql_query(cons, query);
	rows = mysql_fetch_row(mysql_store_result(cons));
	if (rows == 0)	//값이 없으면 0을 리턴
		return 0;
	else
	{
		Hit_User *My_User = (Hit_User *)calloc(1, sizeof(Hit_User));	//메모리를 할당함 calloc은 할당한 후 0으로 채움
		//hitmind_2 DB에 User테이블 값
		/*
			rows[0] = ownnum (고유 번호) 사용자 마다 다름
			rows[1] = name (사용자 이름)
			rows[2] = id (로그인 아이디)
			rows[3] = password (로그인 비밀번호)
			rows[4] = 레벨
			rows[5] = 돈
			rows[6] = auto_login (ip를 저장함)
		*/ 
		My_User->ownnum = atoi(rows[0]);
		strcpy(My_User->id, rows[2]);
		strcpy(My_User->name, rows[1]);
		My_User->level = atoi(rows[4]);
		My_User->money = atoi(rows[5]);
		strcpy(My_User->ownip, rows[6]);
		//할당한 공간에 유저 정보를 복사함
		return My_User;		//리턴
	}

}