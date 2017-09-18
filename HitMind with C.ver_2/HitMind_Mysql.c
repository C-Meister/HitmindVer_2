#include "include.h"

//mysql관련 함수들
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