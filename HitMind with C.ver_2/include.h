//헤더파일들이 선언된 헤더파일
//모든 .c파일에 선언해주자
#pragma once
//전처리기
#define	_CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MOTION 0
#define BUTTONDOWN 1
#define BUTTONUP 2
#define HORIZONTAL 1
#define VERTICAL 2
#define ERASER 1
#define PENCIL 2
#define DEACTIVATED 0
#define HIGHLIGHT 1
#define ACTIVATED 2

//SocketHappen
#define WaitRoomStartEvent 20
#define InGameStartEvent 77
#define MasterExitEvent 22
#define UserHappenEvent 1
#define NewTopicEvent 17
#define ChangeHostEvent 12
#define ConnectErrorEvent -1
#define InGamePassButton 15
#define CurrectAnswerEvent 8
#define SocketChattingEvent 33
#define TimeOutEvent 35
#define MatchEndEvent 25
//SDL_Event UserEvent
#define TIMER 0
#define SOCKETHAPPEN 55

//Draw
#define PENCILCLICK 1
#define PENCILDRAG 2
#define ERASERCLICK 3
#define ERASERDRAG 4
#define STRONG 5
#define COLOR 6
#define NEW 7 
//헤더파일
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
#include <WinInet.h>
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
#pragma comment (lib, "wininet")

#define nullptr 0 //c++에만 있는 nullptr  0으로 지정
#define CHOP(x) x[strlen(x) - 1] = ' '	//fgets를 쓰면 엔터도 배열에남음. 엔터를 배열에서 삭제해주는것
#define CLS system("cls")	//콘솔 화면 지우기
#define setcolor(X, Y) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), X | (Y << 4)) //콘솔 출력 글씨 설정
#define RESET(X) ZeroMemory(X, sizeof(X))	//초기화 memset()이랑 같음
#define MouseUP_Wait SDL_PollEvent(&event); while (event.type == SDL_MOUSEBUTTONDOWN)SDL_PollEvent(&event)
#define PORT 5555
#define MAXPEOPLE 4
//MouseUp_Wait = PutMenu瑜??ъ슜?좊븣 留덉슦??踰꾪듉???대┃?섏옄留먯옄 ?섏뼱媛�湲??뚮Ц??諛⑹?瑜??댁쨲.
//MouseUp_Wait = PutMenu를 사용할때 마우스 버튼을 클릭하자말자 넘어가기 때문에 방지를 해줌.

//typedef
typedef unsigned short Unicode;	//han2unicode를 쓸때, unsigned short 형을 사용함. 쉽게 사용하기위해 typedef 해줌

								//struct 구조체
typedef struct Hitmind_User {	//HitMind_User 구조체이다. 접속자의 정보를 저장함
	int ownnum;		//ownnum : 고유번호
	char id[30];	//id :  로그인할때 id
	char password[42]; //password : 로그인할때 비밀번호
	char name[30]; //name : 사용자의 이름
	int level;		//level : 접속자의 레벨
	int money;		//money : 접속자의 돈
	char ownip[42];
	int pass_length;
	char profile[60];
}Hit_User;
typedef struct Connect_Status {
	void * arg;
	bool ishappen;
}Connect_status;
typedef struct HitMind_WaitRoom {
	int ownnum;
	char name[30];
	char password[35];
	char mode[10];
	int question;
	int time;
	int people;
	int max_people;
	char ip[20];

}Hit_Room;
typedef struct Warning_Message {
	int ison;
	char message[128];
	int x;
	int y;
	double size;
	int r;
	int g;
	int b;
}Warning_M;
typedef struct Canvas {
	SDL_Renderer * Renderer;
	SDL_Color  Color;
	SDL_Rect Rect;
	int Strong;
	int Flag;
	int Click;
	SDL_Point Last;
}Canvas,View;
typedef struct SDL_Slider {
	SDL_Texture * BoxTexture;
	SDL_Texture * BarTexture;
	SDL_Rect Box;
	SDL_Rect Bar;
	float Start;
	float End;
	int * Value;
	int Click;
	int Flag;
}Slider;

typedef struct MYSQL_CHATING {
	int ownnum;
	char name[30];
	char message[512];
	char time[30];
}Chating;
typedef struct SOCKET_CHATING {
	char name[30];
	char message[512];
}SOCKCHAT;
typedef struct Button {
	SDL_Renderer *Renderer;
	SDL_Texture * ButtonTexture;
	SDL_Rect ButtonRect;
	SDL_Color Color;
	int Padding;
	int Flag;
}Button;
typedef struct User {
	SDL_Texture* Profile;
	SDL_Texture* Status;
	char Nickname[20];
	int Master;
	int Level;
	int Turn;
	int Count;
	int Th;
	int status;
	int ownnum;
}User;
typedef struct sql_notice {
	int ownnum;
	char content[200];
	char time[20];
}Notice;
typedef struct Text {
	SDL_Renderer *Renderer;
	SDL_Rect Limit;
	SDL_Rect Rect;
	SDL_Color Color;
	char sentence[128];
	int size; 
	int size_fixed;
	int m;
}Text;
typedef struct HitMind_Time {
	unsigned int time;
	int * event;
	unsigned int now;
}Hit_Timer;

typedef struct Socket_Parameters {
	WSADATA wsadata;
	SOCKET Slisten_socket;
	SOCKET Sconnect_socket[MAXPEOPLE];
	SOCKET Clisten_socket;
	SOCKET Cconnect_socket;
	SOCKADDR_IN listen_addr;
	SOCKADDR_IN connect_addr;
	uintptr_t Serverthread[MAXPEOPLE];
	uintptr_t Clientthread;
	char playerinfo[MAXPEOPLE][30];
	char message[200];
	char chat_message[256];
	char serverip[50];
	char nextserverip[50];
	int sockethappen;
	int endhappen;
	int num;
	char * topic;
	Hit_User * myuser;
	User * gameuser;
	uintptr_t *s;
	uintptr_t *c;
}SockParam;

typedef struct RoomX {
	int button;
	int number;
	int name;
	int mode;
	int question;
	int time;
	int people;
	int rock;
}roomX;
SDL_Event ViewEvent;

/*
변수에 대한 설명:
이 include.h헤더파일은 여러 군데에서 사용을함.
그러므로 같은 변수를 공유할떄에는 전역변수인 static을 사용해 줘야함
*/



//// 소켓용 전역변수
//static WSADATA wsaData;
//static SOCKET Slisten_socket, Sconnect_socket[8];
//static SOCKET Clisten_socket, Cconnect_socket;
//static SOCKADDR_IN listen_addr, connect_addr;
//static int sockaddr_in_size;
//static char message[200];
//static uintptr_t Serverthread[8];
//static uintptr_t Clientthread;
//static char playerinfo[8][30];

 int Display_X;
 int Display_Y;
 char ServerIp[20];
int BGmusic;     //배경음악 크기
int Sound ;       //효과음
int Full ;
//---------------콘솔 함수----------------
//나의 IP를 받아옴a
char * GetDefaultMyIP();
//초기 설정값에 맞게 프로그램을 실행 함
void settings(int *x, int *y, int *music, int *sound, int *full);
//설정변경
void changesetting(int bgmusic, int sound, int x, int y, int full);

int wstrcmp(wchar_t *First, char *second);
void HitMind_Timer(Hit_Timer *arg);
void soundplay();
//외부 ip를 받아옴
char * GetExternalIP();
//---------------그래픽 함수--------------
int HeightOfText(char * name, int Limit_w, SDL_Renderer * renderer, char * sentence, int size, int m);
void Viewing(View * View, int code, void* data1, void* data2);
void Streaming(int code, int x, int y, int Strong, SOCKET sending);
void PushUserEvent(char receive[]);
int PutText_ln(char * name, int Limit_w, int Limit_y,int Limit_h,SDL_Renderer * renderer, char * sentence, int x, int y, int size, int r, int g, int b, int m);
void HitMind_TTF_Init();
void HitMind_TTF_Close();
void HitMind_TTF2_Init();
void HitMind_TTF2_Close();
void Timer(unsigned int time);
void UpdateUserInfo(User* Player, User * Me, char *Topics, SDL_Rect UserRect, Text * CountText, Text * TopicText, int NowTopic, int MaxTopic);
//SDL - 텍스트를 출력하는함수
int PutText_Unicode_Limit(SDL_Renderer * renderer, Unicode * unicode, unsigned int x, unsigned int y, int size, int Limit, SDL_Color color);
int TTF_DrawText(SDL_Renderer *Renderer, TTF_Font* Font, wchar_t* sentence, int x, int y, SDL_Color color);
//SDL - PutMenu함수 버튼을 추가함. 마우스를 가져다되면 커지는 효과와 클릭하면 1을 리턴, 아니면 0을 리턴함
int PutButton(SDL_Renderer * renderer, char * sentence, int x, int y, int size, int r, int g, int b, SDL_Event * event);
//SDL - PutText 텍스트를 출력함.
int PutText(SDL_Renderer * renderer, char * sentence, unsigned int x, unsigned int y, int size, int r, int g, int b, int m);
//SDL - LoadTexture 이미지를 불러옴 인자값 : 렌더러, 파일 경로
SDL_Texture * LoadTexture(SDL_Renderer * Renderer, const char *file);
//SDL - RenderTexture 이미지를 렌더러에 출력함 Rect로 x, y, h, w를 설정 가능
void RenderTexture(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Rect * Rect);
//SDL -  LoadTextureEx 이미지를 특별하게 불러옴 인자값 : 렌더러, 파일 경로, r, g, b 해당 색깔을 없앰
SDL_Texture * LoadTextureEx(SDL_Renderer * Renderer, const char *file, int r, int g, int b);
//SDL - RenderTextureEX 텍스쳐를 특별하게 출력함 인자값 : 렌더러, 이미지, 위치, 각도
void RenderTextureEx(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Rect * Rect, int angle);
int hancheck(int unicode);
void DrawRect(SDL_Renderer * renderer, int r, int g, int b, int x, int y, int w, int h);
char* UNICODE2UTF8(wchar_t* unicode, int len);
wchar_t* UTF82UNICODE(char* UTF8, int len);
int UTF82EUCKR(char *outBuf, int outLength, char *inBuf, int inLength);
int hannum(wchar_t unicode[], int len);
//SDL - RenderTextureXYWH 이미지를 불러오는데 Rect를 미리 생성할 필요가 없슴
void RenderTextureXYWH(SDL_Renderer* Renderer, SDL_Texture * Texture, double xx, double yy, double ww, double hh);
//SDL - PutText_Unicode Unicode모드로 글자를 출력한다. 
int Get_Notice_sql(MYSQL *cons, Notice * notice);
void SDL_DrawRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius, int strong);
void SDL_DrawRectXYWH(SDL_Renderer *renderer, int x, int y, int w, int h, int r, int g, int b);
void SDL_FillRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius);
void FillRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius);
void DrawRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius, int strong);
int PutText_Unicode(SDL_Renderer * renderer, Unicode * unicode, unsigned int x, unsigned int y, int size, SDL_Color color,int m);
void CreateSlider(Slider * Slider, SDL_Texture * BoxTexture, SDL_Texture * BarTexture, int Bar_x, int Bar_y, int Bar_w, int Bar_h, int Box_w, int Box_h, int *Value, float Start, float End, float Default, int Flag);
void DrawSlider(SDL_Renderer *Renderer, Slider * Slider);
int UpdateSlider(Slider* Slider, SDL_Event *event);
void ScoreSort(User * users);
int PutRoundButton(SDL_Renderer* Renderer, int r, int g, int b, int put_r, int put_g, int put_b, int rect_r, int rect_g, int rect_b, int x, int y, int w, int h, int radius, int strong, SDL_Event *event, int * happen);
void SDL_FillUpRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius);
void SDL_Screenshot(const char *filename, SDL_Renderer * Renderer, SDL_Rect* rect);
void FillUpRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius);
void SDL_DrawUpRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius, int strong);
void DrawUpRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius, int strong);
int ChangeColor(SDL_Event * event, SDL_Color * color, SDL_Rect rect, SOCKET sending, int MeTurn);
void CreateCanvas(Canvas * Canvas, SDL_Renderer * Renderer, int x, int y, int w, int h, int strong);
int UpdateCanvas(Canvas * Canvas, SDL_Event * event, SOCKET sending);
//SDL - PutButtonImage 이미지 버튼을 만든다 기존은 Texture의 이미지를, 마우스를 올리면 MouseOnImage로 변한다
int PutButtonImage(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, int x, int y, int w, int h, SDL_Event * event, int *happen);
int PutButtonImageText(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, int x, int y, int w, int h, int ww, int hh, char *texts, SDL_Event * event, int *happen);
int PutButtonImage_click(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, int x, int y, int w, int h, SDL_Event * event, int *happen);
void MoveSlider_value(Slider *Slider, int value);
void Re_Load(SDL_Window *window, SDL_Renderer *renderer, int dis_x, int dis_y, int bg_music, int music, int isfull);
void SDL_FillRectXYWH(SDL_Renderer *renderer, int x, int y, int w, int h, int r, int g, int b);
void CreateButton(Button * Button, SDL_Renderer *Renderer, SDL_Texture *ButtonTexture, int Padding, int x, int y, int w, int h, int r, int g, int b, int a);
int UpdateButton(Button * Button, SDL_Event * event);
void DrawButton(Button * Button);
void FillCircle(SDL_Renderer * Renderer, int Center_x, int Center_y, int radius);
void Line(SDL_Renderer* Renderer, float x1, float y1, float x2, float y2);
void PrintNotice(SDL_Renderer * renderer, MYSQL*cons);
void LineThick(SDL_Renderer* Renderer, int Thick,float x1, float y1, float x2, float y2);
void LineCircle(SDL_Renderer*Renderer, int Thick, float x1, float y1, float x2, float y2);
void swap(float *a, float * b);
void PrintUserInfo(SDL_Renderer* Renderer, User *User, SDL_Rect UserRect);
void CenterArrange(Text * Text);
void CreateText(Text* Text, SDL_Renderer * Renderer, char *sentence, int x, int y, int w, int h, int r, int g, int b, int size, int m);
void RenderText( Text * Text);
void PushSocketEvent(void);
void Put_Text_Center(SDL_Renderer* Renderer, char *sentence, int x, int y, int w, int h, int r, int g, int b, int size, int m);
int PutButtonWithImage(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, SDL_Texture * MouseClickImage,int x, int y, int w, int h, SDL_Event * event, int *Flag);
int RoomX_Setting(roomX *roomx, int Display_x);
//---------------MySql 함수---------------
int GetRoomUser(MYSQL * cons, User * friends, SDL_Renderer * renderer);
//인지 체크하는 함수
Hit_User *IsAutoLogin(MYSQL *cons);
int getUesrStatus(MYSQL *cons, char arr[30][30]);
int User_Signin_sql(MYSQL *cons, wchar_t *id, wchar_t *password, wchar_t * nickname, wchar_t *answer);
//Password_Change 비밀번호를 변경하는데 필요한 함수. 잘못되면 -1, 답변 잘못되면 0 업데이트실패 -2 성공 1
int Password_Change_sql(MYSQL *cons, wchar_t *id, wchar_t *newpassword, wchar_t *answer);
//_beginthreadex용 함수. 쓰레드로 mysql에 연결함
void Thread_MySQL(Connect_status *type);
//처음 MySQL에 연결함
int Get_Version_sql(MYSQL *cons, char * message);
MYSQL * Mysql_Connect(char *ip);
//wstr로 쿼리문을 실행함
int Mysql_wstr_query(MYSQL *cons, wchar_t * query);
//二쇱젣以묒뿉 ?쒕뜡?쇰줈 ?섎굹瑜?遺덈윭?� 臾몄옄?대줈 諛섑솚
char * Get_Random_Topic(MYSQL *cons);	
//?꾩씠?붿? ?⑥뒪?뚮뱶濡?濡쒓렇?명븿
Hit_User *User_Login_sql(MYSQL *cons, char * id, char *password);	

int Insert_Topic_sql(MYSQL *cons, char *my_name, wchar_t * topic);
//---------------Socket 함수--------------
void OpenServer(SockParam *param);
// 서버 염
void connectServer(SockParam *param);
// 서버에 연결함 param->serverip 바꿔줘야 됨
void HandleClient(SockParam *param);
// 서버가 클라이언트 관리함
void sendall(SockParam *param);
// 서버가 연결된 클라이언트한테 패킷 전송함
void Clientrecv(SockParam *param);
// 클라이언트가 서버가 보낸 패킷받음
void hostChange(SockParam *param);

//주제중에 랜덤으로 하나를 불러와 문자열로 반환
char * Get_Random_Topic(MYSQL *cons);
//방 목록을 불러옴
int Get_Room_List(MYSQL *cons, Hit_Room * rooms);
//아이디와 패스워드로 로그인함
Hit_User *User_Login_sql(MYSQL *cons, char * id, char *password);
//전체 채팅을 추가함
int InsertChating_all(MYSQL *cons, char * username, wchar_t* message,int messagelength);
//전체 채팅을 불러옴
int ReadChating_all(MYSQL *cons, Chating * chatings);
//방을 만듬, 방이름, 비밀번호, 모드, 문제 개수, 문제 시간 이 필요함
int Create_Room_sql(MYSQL *cons, wchar_t * roomname, wchar_t * rompass, int mode, int question, int timer);
//int addChat(SOCKCHAT *Chatlist[],char *data, char *name,int currentnum);
//void PrintInChatting(SDL_Renderer * renderer, SOCKCHAT * Chatlist[], int first);