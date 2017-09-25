//������ϵ��� ����� �������
//��� .c���Ͽ� ����������
#pragma once
//��ó����
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
//�������
#include <math.h>
#include <stdio.h>				//Standard Input/Output
#include <stdlib.h>				//malloc ���
#include <math.h>				//���� ���� �Լ�
#include <process.h>			//Thread ��� �Լ�
#include <Windows.h>			//Window api ���� �Լ�
#include <signal.h>				//Interruptó�� �Լ�
#include <time.h>				//�ð� ���� �Լ�
#include <stdbool.h>			//Bool ��� �Լ�
#include <stdint.h>				//���� typedef ���� Ÿ�� �Լ�
#include <direct.h>				//���� ���� �Լ�
#include "mysql/mysql.h"//MySQL �Լ���
#include <tchar.h>
#include "lib//iconv.h"
#include "SDL/SDL.h"			//SDL - �⺻ �������
#include "SDL/SDL_image.h"		//SDL - �̹��� �������
#include "SDL/SDL_ttf.h"		//SDL - ��Ʈ(�ؽ�Ʈ) �������
#include "SDL/han2unicode.h"	//han2unicode - �⺻ 949 ������ uniocde�� �ٲ���
#include "SDL/SDL_mixer.h"		//SDL - ���� �������
//#include "vld/vld.h"

//���� ����
#pragma warning (disable : 4244)
#pragma warning (disable : 4047)
#pragma warning (disable : 4267)

#pragma comment (lib, "lib/libiconv.lib")
#pragma comment (lib, "lib/SDL2")			//�׷��� ���̺귯�� 1
#pragma comment (lib, "lib/SDL2main")		//�׷��� ���̺귯�� 2 
#pragma comment (lib, "lib/SDL2_image")		//�׷��� ���̺귯�� 3
#pragma comment (lib, "lib/SDL2_ttf")		//�׷��� ���̺귯�� 4
#pragma comment (lib, "lib/SDL2_mixer.lib")	//�׷��� ���� ���̺귯�� 5
#pragma comment (lib, "ws2_32.lib")			//���� ���̺귯��
#pragma comment (lib, "lib/libmysql.lib")	//MySQL ���̺귯��

#define nullptr 0 //c++���� �ִ� nullptr  0���� ����
#define CHOP(x) x[strlen(x) - 1] = ' '	//fgets�� ���� ���͵� �迭������. ���͸� �迭���� �������ִ°�
#define CLS system("cls")	//�ܼ� ȭ�� �����
#define setcolor(X, Y) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), X | (Y << 4)) //�ܼ� ��� �۾� ����
#define RESET(X) ZeroMemory(X, sizeof(X))	//�ʱ�ȭ memset()�̶� ����
#define MouseUP_Wait SDL_PollEvent(&event); while (event.type == SDL_MOUSEBUTTONDOWN)SDL_PollEvent(&event)
#define PORT 5555
#define MAXPEOPLE 8
//MouseUp_Wait = PutMenu�??�용?�때 마우??버튼???�릭?�자말자 ?�어가�??�문??방�?�??�줌.
//MouseUp_Wait = PutMenu�� ����Ҷ� ���콺 ��ư�� Ŭ�����ڸ��� �Ѿ�� ������ ������ ����.

//typedef
typedef unsigned short Unicode;	//han2unicode�� ����, unsigned short ���� �����. ���� ����ϱ����� typedef ����

								//struct ����ü
typedef struct Hitmind_User {	//HitMind_User ����ü�̴�. �������� ������ ������
	int ownnum;		//ownnum : ������ȣ
	char id[30];	//id :  �α����Ҷ� id
	char password[42]; //password : �α����Ҷ� ��й�ȣ
	char name[30]; //name : ������� �̸�
	int level;		//level : �������� ����
	int money;		//money : �������� ��
	char ownip[42];
	int pass_length;
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
	int size;
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
}Canvas;
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
	char playerinfo[8][30];
	char message[200];
	char serverip[50];
	int num;
}SockParam;


typedef struct MYSQL_CHATING {
	int ownnum;
	char name[30];
	char message[128];
	char time[30];
}Chating;
typedef struct Button {
	SDL_Renderer *Renderer;
	SDL_Texture * ButtonTexture;
	SDL_Rect ButtonRect;
	SDL_Color Color;
	int Padding;
	int Flag;
}Button;

/*
������ ���� ����:
�� include.h��������� ���� �������� �������.
�׷��Ƿ� ���� ������ �����ҋ����� ���������� static�� ����� �����
*/



//// ���Ͽ� ��������
//static WSADATA wsaData;
//static SOCKET Slisten_socket, Sconnect_socket[8];
//static SOCKET Clisten_socket, Cconnect_socket;
//static SOCKADDR_IN listen_addr, connect_addr;
//static int sockaddr_in_size;
//static char message[200];
//static uintptr_t Serverthread[8];
//static uintptr_t Clientthread;
//static char playerinfo[8][30];


static int Display_X = 1920;
static int Display_Y = 1080;
static int BGmusic = 30;     //������� ũ��
static int Sound = 30;       //ȿ����
static int Full = 0;
//---------------�ܼ� �Լ�----------------
//���� IP�� �޾ƿ�
char * GetDefaultMyIP();
//�ʱ� �������� �°� ���α׷��� ���� ��
void settings(int *x, int *y, int *music, int *sound, int *full);
//��������
void changesetting(int bgmusic, int sound, int x, int y, int full);

int wstrcmp(wchar_t *First, char *second);

void soundplay();
//---------------�׷��� �Լ�--------------
void HitMind_TTF_Init();
void HitMind_TTF_Close();
//SDL - �ؽ�Ʈ�� ����ϴ��Լ�
void TTF_DrawText(SDL_Renderer *Renderer, TTF_Font* Font, wchar_t* sentence, int x, int y, SDL_Color color);
//SDL - PutMenu�Լ� ��ư�� �߰���. ���콺�� �����ٵǸ� Ŀ���� ȿ���� Ŭ���ϸ� 1�� ����, �ƴϸ� 0�� ������
int PutButton(SDL_Renderer * renderer, char * sentence, int x, int y, int size, int r, int g, int b, SDL_Event * event);
//SDL - PutText �ؽ�Ʈ�� �����.
int PutText(SDL_Renderer * renderer, char * sentence, unsigned int x, unsigned int y, int size, int r, int g, int b);
//SDL - LoadTexture �̹����� �ҷ��� ���ڰ� : ������, ���� ���
SDL_Texture * LoadTexture(SDL_Renderer * Renderer, const char *file);
//SDL - RenderTexture �̹����� �������� ����� Rect�� x, y, h, w�� ���� ����
void RenderTexture(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Rect * Rect);
//SDL -  LoadTextureEx �̹����� Ư���ϰ� �ҷ��� ���ڰ� : ������, ���� ���, r, g, b �ش� ������ ����
SDL_Texture * LoadTextureEx(SDL_Renderer * Renderer, const char *file, int r, int g, int b);
//SDL - RenderTextureEX �ؽ��ĸ� Ư���ϰ� ����� ���ڰ� : ������, �̹���, ��ġ, ����
void RenderTextureEx(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Rect * Rect, int angle);
int hancheck(int unicode);
char* UNICODE2UTF8(wchar_t* unicode, int len);
wchar_t* UTF82UNICODE(char* UTF8, int len);
int UTF82EUCKR(char *outBuf, int outLength, char *inBuf, int inLength);
int hannum(wchar_t unicode[], int len);
//SDL - RenderTextureXYWH �̹����� �ҷ����µ� Rect�� �̸� ������ �ʿ䰡 ����
void RenderTextureXYWH(SDL_Renderer* Renderer, SDL_Texture * Texture, double xx, double yy, double ww, double hh);
//SDL - PutText_Unicode Unicode���� ���ڸ� ����Ѵ�. 
void SDL_DrawRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius, int strong);
void SDL_FillRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius);
void FillRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius);
void DrawRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius, int strong);
int PutText_Unicode(SDL_Renderer * renderer, Unicode * unicode, unsigned int x, unsigned int y, int size, SDL_Color color);
void CreateSlider(Slider * Slider, SDL_Texture * BoxTexture, SDL_Texture * BarTexture, int Bar_x, int Bar_y, int Bar_w, int Bar_h, int Box_w, int Box_h, int *Value, float Start, float End, float Default, int Flag);
void DrawSlider(SDL_Renderer *Renderer, Slider * Slider);
int UpdateSlider(Slider* Slider, SDL_Event *event);
int PutRoundButton(SDL_Renderer* Renderer, int r, int g, int b, int put_r, int put_g, int put_b, int rect_r, int rect_g, int rect_b, int x, int y, int w, int h, int radius, int strong, SDL_Event *event, int * happen);
void SDL_FillUpRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius);
void FillUpRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius);
void SDL_DrawUpRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius, int strong);
void DrawUpRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius, int strong);
int ChangeColor(SDL_Event * event, SDL_Color * color, SDL_Rect rect);
void CreateCanvas(Canvas * Canvas, SDL_Renderer * Renderer, int x, int y, int w, int h, int strong);
int UpdateCanvas(Canvas* Canvas, SDL_Event * event);
//SDL - PutButtonImage �̹��� ��ư�� ����� ������ Texture�� �̹�����, ���콺�� �ø��� MouseOnImage�� ���Ѵ�
int PutButtonImage(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, int x, int y, int w, int h, SDL_Event * event, int *happen);
int PutButtonImage_click(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, int x, int y, int w, int h, SDL_Event * event, int *happen);
void MoveSlider_value(Slider *Slider, int value);
void Re_Load(SDL_Window *window, SDL_Renderer *renderer, int dis_x, int dis_y, int bg_music, int music, int isfull);
void SDL_FillRectXYWH(SDL_Renderer *renderer, int x, int y, int w, int h, int r, int g, int b);
void CreateButton(Button * Button, SDL_Renderer *Renderer, SDL_Texture *ButtonTexture, int Padding, int x, int y, int w, int h, int r, int g, int b, int a);
int UpdateButton(Button * Button, SDL_Event * event);
void DrawButton(Button * Button);
void FillCircle(SDL_Renderer * Renderer, int Center_x, int Center_y, int radius);
void ConnectCircle(SDL_Renderer * Renderer, int Last_x, int Last_y, double dx, double dy, double length, int radius);
//---------------MySql �Լ�---------------
//�ڵ� �α������� üũ�ϴ� �Լ�
Hit_User *IsAutoLogin(MYSQL *cons);
int getUesrStatus(MYSQL *cons, char arr[30][30]);
int User_Signin_sql(MYSQL *cons, wchar_t *id, wchar_t *password, wchar_t * nickname, wchar_t *answer);
//Password_Change ��й�ȣ�� �����ϴµ� �ʿ��� �Լ�. ���̵� �߸��Ǹ� -1, �亯 �߸��Ǹ� 0 ������Ʈ���� -2 ���� 1
int Password_Change_sql(MYSQL *cons, wchar_t *id, wchar_t *newpassword, wchar_t *answer);
//_beginthreadex�� �Լ�. ������� mysql�� ������
void Thread_MySQL(Connect_status *type);
//ó�� MySQL�� ������
MYSQL * Mysql_Connect(char *ip);

//주제중에 ?�덤?�로 ?�나�?불러?� 문자?�로 반환
char * Get_Random_Topic(MYSQL *cons);	
//?�이?��? ?�스?�드�?로그?�함
Hit_User *User_Login_sql(MYSQL *cons, char * id, char *password);	
//---------------Socket ?�수--------------
void OpenServer(SockParam *param);
// ?�레???�버?�용 - �??�버)�??�다
void connectServer(SockParam *param);
// ?�레???�라?�언???�용 - �??�버)???�결???�자�?: IP주소
void HandleClient(SockParam *param);
// ?�레???�버?�용 - ?�라?�언?�에게서 ?�이?��? 계속 받아?�다 ?�자�?: ?�라?�언??번호 
void sendall(SockParam *param);
// ?�버?�용 - 모든 ?�라?�언?�에�??�이?��? 보낸???�자�?: ?�송???�이?? ?�버???�라?�언??번호
// ?�버???�라?�언??번호??sendall ?�때 ?�기 ?�신?�게??보내지 ?�기 ?�해 만든�?
void Clientrecv(SockParam *param);
// ?�레???�라?�언???�용 - ?�버?�게???�이?��? 받아?�다

//�����߿� �������� �ϳ��� �ҷ��� ���ڿ��� ��ȯ
char * Get_Random_Topic(MYSQL *cons);
//�� ����� �ҷ���
int Get_Room_List(MYSQL *cons, Hit_Room * rooms);
//���̵�� �н������ �α�����
Hit_User *User_Login_sql(MYSQL *cons, char * id, char *password);
//��ü ä���� �߰���
int InsertChating_all(MYSQL *cons, char * username, wchar_t* message);
//��ü ä���� �ҷ���
int ReadChating_all(MYSQL *cons, Chating * chatings);
//���� ����, ���̸�, ��й�ȣ, ���, ���� ����, ���� �ð� �� �ʿ���
int Create_Room_sql(MYSQL *cons, wchar_t * roomname, wchar_t * rompass, int mode, int question, int timer);
//---------------Socket �Լ�--------------
void OpenServer();
// ������,�������� - ��(����)�� ����
void connectServer(char *serverIP);
// ������,Ŭ���̾�Ʈ ���� - ��(����)�� ������ ���ڰ� : IP�ּ�
void HandleClient(int num);
// ������,�������� - Ŭ���̾�Ʈ���Լ� �����͸� ��� �޾ƿ´� ���ڰ� : Ŭ���̾�Ʈ ��ȣ 
void sendall(char *lmessage, int c);
// �������� - ��� Ŭ���̾�Ʈ���� �����͸� ������ ���ڰ� : ������ ������, ������ Ŭ���̾�Ʈ ��ȣ
// ������ Ŭ���̾�Ʈ ��ȣ�� sendall �Ҷ� �ڱ� �ڽſ��Դ� ������ �ʱ� ���� �����
void Clientrecv();
// ������,Ŭ���̾�Ʈ ���� - �������Լ� �����͸� �޾ƿ´�

