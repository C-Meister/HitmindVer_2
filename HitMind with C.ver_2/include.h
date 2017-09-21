//헤더파일들이 선언된 헤더파일
//모든 .c파일에 선언해주자
#pragma once
//전처리기
#define	_CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//헤더파일
#include <math.h>
#include <stdio.h>				//Standard Input/Output
#include <stdlib.h>				//malloc 사용
#include <math.h>				//수학 관련 함수
#include <process.h>			//Thread 사용 함수
#include <Windows.h>			//Window api 관련 함수
#include <signal.h>				//Interrupt처리 함수
#include <time.h>				//시간 관련 함수
#include <stdbool.h>			//Bool 사용 함수
#include <stdint.h>				//여러 typedef 관련 타입 함수
#include <direct.h>				//폴더 관련 함수
#include "mysql/mysql.h"//MySQL 함수들
#include <tchar.h>
#include "lib//iconv.h"
#include "SDL/SDL.h"			//SDL - 기본 헤더파일
#include "SDL/SDL_image.h"		//SDL - 이미지 헤더파일
#include "SDL/SDL_ttf.h"		//SDL - 폰트(텍스트) 헤더파일
#include "SDL/han2unicode.h"	//han2unicode - 기본 949 언어들을 uniocde로 바꿔줌
#include "SDL/SDL_mixer.h"		//SDL - 사운드 헤더파일
//#include "vld/vld.h"

//오류 무시
#pragma warning (disable : 4244)
#pragma warning (disable : 4047)
#pragma warning (disable : 4267)

#pragma comment (lib, "lib/libiconv.lib")
#pragma comment (lib, "lib/SDL2")			//그래픽 라이브러리 1
#pragma comment (lib, "lib/SDL2main")		//그래픽 라이브러리 2 
#pragma comment (lib, "lib/SDL2_image")		//그래픽 라이브러리 3
#pragma comment (lib, "lib/SDL2_ttf")		//그래픽 라이브러리 4
#pragma comment (lib, "lib/SDL2_mixer.lib")	//그래픽 사운드 라이브러리 5
#pragma comment (lib, "ws2_32.lib")			//소켓 라이브러리
#pragma comment (lib, "lib/libmysql.lib")	//MySQL 라이브러리

#define nullptr 0 //c++에만 있는 nullptr  0으로 지정
#define CHOP(x) x[strlen(x) - 1] = ' '	//fgets를 쓰면 엔터도 배열에남음. 엔터를 배열에서 삭제해주는것
#define CLS system("cls")	//콘솔 화면 지우기
#define setcolor(X, Y) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), X | (Y << 4)) //콘솔 출력 글씨 설정
#define RESET(X) ZeroMemory(X, sizeof(X))	//초기화 memset()이랑 같음
#define MouseUP_Wait SDL_PollEvent(&event); while (event.type == SDL_MOUSEBUTTONDOWN)SDL_PollEvent(&event)
//MouseUp_Wait = PutMenu를 사용할때 마우스 버튼을 클릭하자말자 넘어가기 때문에 방지를 해줌.

//typedef
typedef unsigned short Unicode;	//han2unicode를 쓸때, unsigned short 형을 사용함. 쉽게 사용하기위해 typedef 해줌

//struct 구조체
typedef struct Hitmind_User {	//HitMind_User 구조체이다. 접속자의 정보를 저장함
	int ownnum;		//ownnum : 고유번호
	char id[30];	//id :  로그인할때 id
	char password[40]; //password : 로그인할때 비밀번호
	char name[30]; //name : 사용자의 이름
	int level;		//level : 접속자의 레벨
	int money;		//money : 접속자의 돈
	char ownip[30];
}Hit_User;
typedef struct Connect_Status {
	void * arg;
	bool ishappen;
}Connect_status;
typedef struct Warning_Message {
	int ison;
	char message[128];
	int x;
	int y;
	int size;
	int r;
	int g;
	int b;
}Warning_M;
typedef struct SDL_Slider {
	SDL_Rect Box;
	SDL_Rect Bar;
	float Start;
	float End;
	int Click;
}Slider;

/*
	변수에 대한 설명:
	이 include.h헤더파일은 여러 군데에서 사용을함.
	그러므로 같은 변수를 공유할떄에는 전역변수인 static을 사용해 줘야함
*/
static int Display_X = 1920;	//해상도 - X
static int Display_Y = 1080;	//해상도 - Y
static int BGmusic = 30;     //배경음악 크기
static int Sound = 30;       //효과음
static int Full = 0;

//---------------콘솔 함수----------------
//나의 IP를 받아옴
char * GetDefaultMyIP();
//초기 설정값에 맞게 프로그램을 실행 함
void settings(int *x, int *y, int *music, int *sound, int *full);
//설정변경
void changesetting(int bgmusic, int sound, int x, int y);
//---------------그래픽 함수--------------
//SDL - 텍스트를 출력하는함수
void TTF_DrawText(SDL_Renderer *Renderer, TTF_Font* Font, wchar_t* sentence, int x, int y, SDL_Color color);		
//SDL - PutMenu함수 버튼을 추가함. 마우스를 가져다되면 커지는 효과와 클릭하면 1을 리턴, 아니면 0을 리턴함
int PutButton(SDL_Renderer * renderer, char * sentence, int x, int y, int size, int r, int g, int b, SDL_Event * event);
//SDL - PutText 텍스트를 출력함.
int PutText(SDL_Renderer * renderer, char * sentence, unsigned int x, unsigned int y, int size, int r, int g, int b);
//SDL - LoadTexture 이미지를 불러옴 인자값 : 렌더러, 파일 경로
SDL_Texture * LoadTexture(SDL_Renderer * Renderer, const char *file);
//SDL - RenderTexture 이미지를 렌더러에 출력함 Rect로 x, y, h, w를 설정 가능
void RenderTexture(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Rect * Rect);
//SDL -  LoadTextureEx 이미지를 특별하게 불러옴 인자값 : 렌더러, 파일 경로, r, g, b 해당 색깔을 없앰
SDL_Texture * LoadTextureEx(SDL_Renderer * Renderer, const char *file, int r, int g, int b);
//SDL - RenderTextureEX 텍스쳐를 특별하게 출력함 인자값 : 렌더러, 이미지, 위치, 각도
void RenderTextureEx(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Rect * Rect, int angle);
int hancheck(int unicode);
char* UNICODE2UTF8(wchar_t* unicode, int len);
wchar_t* UTF82UNICODE(char* UTF8, int len);
int UTF82EUCKR(char *outBuf, int outLength, char *inBuf, int inLength);
int hannum(wchar_t unicode[], int len);
//SDL - RenderTextureXYWH 이미지를 불러오는데 Rect를 미리 생성할 필요가 없슴
void RenderTextureXYWH(SDL_Renderer* Renderer, SDL_Texture * Texture, double xx, double yy, double ww, double hh);
//SDL - PutText_Unicode Unicode모드로 글자를 출력한다. 
void SDL_DrawRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius,int strong);
void SDL_FillRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius);
void FillRoundRect(SDL_Renderer* Renderer, int r,int g, int b, int x, int y, int w, int h, int radius);
void DrawRoundRect(SDL_Renderer* Renderer, int r, int g ,int b, int x, int y, int w, int h, int radius, int strong);
int PutText_Unicode(SDL_Renderer * renderer, Unicode * unicode, unsigned int x, unsigned int y, int size, SDL_Color color);
void CreateSlider(Slider * Slider,int Bar_x, int Bar_y,int Bar_w, int Bar_h, int Box_w,int Box_h, float Start, float End, float Default);
void DrawSlider(SDL_Renderer *Renderer, SDL_Texture *BoxTexture, SDL_Texture * BarTexture, Slider * Slider);
int UpdateSlider(Slider* Slider, int x, int y, int flag);
int PutRoundButton(SDL_Renderer* Renderer, int r, int g, int b, int put_r, int put_g, int put_b, int rect_r, int rect_g, int rect_b, int x, int y, int w, int h, int radius, int strong, SDL_Event *event);
void SDL_FillUpRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius);
void FillUpRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius);
void SDL_DrawUpRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius, int strong);
void DrawUpRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius, int strong);
//SDL - PutButtonImage 이미지 버튼을 만든다 기존은 Texture의 이미지를, 마우스를 올리면 MouseOnImage로 변한다
int PutButtonImage(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, int x, int y, int w, int h, SDL_Event * event);
//---------------MySql 함수---------------
//자동 로그인인지 체크하는 함수
Hit_User *IsAutoLogin(MYSQL *cons);

int User_Signin_sql(MYSQL *cons, wchar_t *id, wchar_t *password, wchar_t * nickname, wchar_t *answer);
//Password_Change 비밀번호를 변경하는데 필요한 함수. 아이디 잘못되면 -1, 답변 잘못되면 0 업데이트실패 -2 성공 1
int Password_Change_sql(MYSQL *cons, wchar_t *id, wchar_t *newpassword, wchar_t *answer);
//_beginthreadex용 함수. 쓰레드로 mysql에 연결함
void Thread_MySQL(Connect_status *type);
//처음 MySQL에 연결함
MYSQL * Mysql_Connect(char *ip);
//주제중에 랜덤으로 하나를 불러와 문자열로 반환
char * Get_Random_Topic(MYSQL *cons);	
//아이디와 패스워드로 로그인함
Hit_User *User_Login_sql(MYSQL *cons, char * id, char *password);	
//---------------Socket 함수--------------