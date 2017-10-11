//Çì´õÆÄÀÏµéÀÌ ¼±¾ğµÈ Çì´õÆÄÀÏ
//¸ğµç .cÆÄÀÏ¿¡ ¼±¾ğÇØÁÖÀÚ
#pragma once
//ÀüÃ³¸®±â
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
//SDL_Event UserEvent
#define TIMER 0
#define SOCKETHAPPEN 5

//Draw
#define PENCILCLICK 1
#define PENCILDRAG 2
#define ERASERCLICK 3
#define ERASERDRAG 4
#define STRONG 5
#define COLOR 6
#define NEW 7 
//Çì´õÆÄÀÏ
#include <math.h>
#include <stdio.h>				//Standard Input/Output
#include <stdlib.h>				//malloc »ç¿ë
#include <math.h>				//¼öÇĞ °ü·Ã ÇÔ¼ö
#include <process.h>			//Thread »ç¿ë ÇÔ¼ö
#include <Windows.h>			//Window api °ü·Ã ÇÔ¼ö
#include <signal.h>				//InterruptÃ³¸® ÇÔ¼ö
#include <time.h>				//½Ã°£ °ü·Ã ÇÔ¼ö
#include <stdbool.h>			//Bool »ç¿ë ÇÔ¼ö
#include <stdint.h>				//¿©·¯ typedef °ü·Ã Å¸ÀÔ ÇÔ¼ö
#include <direct.h>				//Æú´õ °ü·Ã ÇÔ¼ö
#include <WinInet.h>
#include "mysql/mysql.h"//MySQL ÇÔ¼öµé
#include <tchar.h>
#include "lib//iconv.h"
#include "SDL/SDL.h"			//SDL - ±âº» Çì´õÆÄÀÏ
#include "SDL/SDL_image.h"		//SDL - ÀÌ¹ÌÁö Çì´õÆÄÀÏ
#include "SDL/SDL_ttf.h"		//SDL - ÆùÆ®(ÅØ½ºÆ®) Çì´õÆÄÀÏ
#include "SDL/han2unicode.h"	//han2unicode - ±âº» 949 ¾ğ¾îµéÀ» uniocde·Î ¹Ù²ãÁÜ
#include "SDL/SDL_mixer.h"		//SDL - »ç¿îµå Çì´õÆÄÀÏ
//#include "vld/vld.h"

//¿À·ù ¹«½Ã
#pragma warning (disable : 4244)
#pragma warning (disable : 4047)
#pragma warning (disable : 4267)

#pragma comment (lib, "lib/libiconv.lib")
#pragma comment (lib, "lib/SDL2")			//±×·¡ÇÈ ¶óÀÌºê·¯¸® 1
#pragma comment (lib, "lib/SDL2main")		//±×·¡ÇÈ ¶óÀÌºê·¯¸® 2 
#pragma comment (lib, "lib/SDL2_image")		//±×·¡ÇÈ ¶óÀÌºê·¯¸® 3
#pragma comment (lib, "lib/SDL2_ttf")		//±×·¡ÇÈ ¶óÀÌºê·¯¸® 4
#pragma comment (lib, "lib/SDL2_mixer.lib")	//±×·¡ÇÈ »ç¿îµå ¶óÀÌºê·¯¸® 5
#pragma comment (lib, "ws2_32.lib")			//¼ÒÄÏ ¶óÀÌºê·¯¸®
#pragma comment (lib, "lib/libmysql.lib")	//MySQL ¶óÀÌºê·¯¸®
#pragma comment (lib, "wininet")

#define nullptr 0 //c++¿¡¸¸ ÀÖ´Â nullptr  0À¸·Î ÁöÁ¤
#define CHOP(x) x[strlen(x) - 1] = ' '	//fgets¸¦ ¾²¸é ¿£ÅÍµµ ¹è¿­¿¡³²À½. ¿£ÅÍ¸¦ ¹è¿­¿¡¼­ »èÁ¦ÇØÁÖ´Â°Í
#define CLS system("cls")	//ÄÜ¼Ö È­¸é Áö¿ì±â
#define setcolor(X, Y) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), X | (Y << 4)) //ÄÜ¼Ö Ãâ·Â ±Û¾¾ ¼³Á¤
#define RESET(X) ZeroMemory(X, sizeof(X))	//ÃÊ±âÈ­ memset()ÀÌ¶û °°À½
#define MouseUP_Wait SDL_PollEvent(&event); while (event.type == SDL_MOUSEBUTTONDOWN)SDL_PollEvent(&event)
#define PORT 5555
#define MAXPEOPLE 4
//MouseUp_Wait = PutMenuë¥??¬ìš©? ë•Œ ë§ˆìš°??ë²„íŠ¼???´ë¦­?˜ìë§ì ?˜ì–´ê°€ê¸??Œë¬¸??ë°©ì?ë¥??´ì¤Œ.
//MouseUp_Wait = PutMenu¸¦ »ç¿ëÇÒ¶§ ¸¶¿ì½º ¹öÆ°À» Å¬¸¯ÇÏÀÚ¸»ÀÚ ³Ñ¾î°¡±â ¶§¹®¿¡ ¹æÁö¸¦ ÇØÁÜ.

//typedef
typedef unsigned short Unicode;	//han2unicode¸¦ ¾µ¶§, unsigned short ÇüÀ» »ç¿ëÇÔ. ½±°Ô »ç¿ëÇÏ±âÀ§ÇØ typedef ÇØÁÜ

								//struct ±¸Á¶Ã¼
typedef struct Hitmind_User {	//HitMind_User ±¸Á¶Ã¼ÀÌ´Ù. Á¢¼ÓÀÚÀÇ Á¤º¸¸¦ ÀúÀåÇÔ
	int ownnum;		//ownnum : °íÀ¯¹øÈ£
	char id[30];	//id :  ·Î±×ÀÎÇÒ¶§ id
	char password[42]; //password : ·Î±×ÀÎÇÒ¶§ ºñ¹Ğ¹øÈ£
	char name[30]; //name : »ç¿ëÀÚÀÇ ÀÌ¸§
	int level;		//level : Á¢¼ÓÀÚÀÇ ·¹º§
	int money;		//money : Á¢¼ÓÀÚÀÇ µ·
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
º¯¼ö¿¡ ´ëÇÑ ¼³¸í:
ÀÌ include.hÇì´õÆÄÀÏÀº ¿©·¯ ±ºµ¥¿¡¼­ »ç¿ëÀ»ÇÔ.
±×·¯¹Ç·Î °°Àº º¯¼ö¸¦ °øÀ¯ÇÒ‹š¿¡´Â Àü¿ªº¯¼öÀÎ staticÀ» »ç¿ëÇØ Áà¾ßÇÔ
*/



//// ¼ÒÄÏ¿ë Àü¿ªº¯¼ö
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
static int BGmusic = 30;     //¹è°æÀ½¾Ç Å©±â
static int Sound = 30;       //È¿°úÀ½
static int Full = 0;
//---------------ÄÜ¼Ö ÇÔ¼ö----------------
//³ªÀÇ IP¸¦ ¹Ş¾Æ¿Èa
char * GetDefaultMyIP();
//ÃÊ±â ¼³Á¤°ª¿¡ ¸Â°Ô ÇÁ·Î±×·¥À» ½ÇÇà ÇÔ
void settings(int *x, int *y, int *music, int *sound, int *full);
//¼³Á¤º¯°æ
void changesetting(int bgmusic, int sound, int x, int y, int full);

int wstrcmp(wchar_t *First, char *second);
void HitMind_Timer(Hit_Timer *arg);
void soundplay();
//¿ÜºÎ ip¸¦ ¹Ş¾Æ¿È
char * GetExternalIP();
//---------------±×·¡ÇÈ ÇÔ¼ö--------------
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
//SDL - ÅØ½ºÆ®¸¦ Ãâ·ÂÇÏ´ÂÇÔ¼ö
int PutText_Unicode_Limit(SDL_Renderer * renderer, Unicode * unicode, unsigned int x, unsigned int y, int size, int Limit, SDL_Color color);
int TTF_DrawText(SDL_Renderer *Renderer, TTF_Font* Font, wchar_t* sentence, int x, int y, SDL_Color color);
//SDL - PutMenuÇÔ¼ö ¹öÆ°À» Ãß°¡ÇÔ. ¸¶¿ì½º¸¦ °¡Á®´ÙµÇ¸é Ä¿Áö´Â È¿°ú¿Í Å¬¸¯ÇÏ¸é 1À» ¸®ÅÏ, ¾Æ´Ï¸é 0À» ¸®ÅÏÇÔ
int PutButton(SDL_Renderer * renderer, char * sentence, int x, int y, int size, int r, int g, int b, SDL_Event * event);
//SDL - PutText ÅØ½ºÆ®¸¦ Ãâ·ÂÇÔ.
int PutText(SDL_Renderer * renderer, char * sentence, unsigned int x, unsigned int y, int size, int r, int g, int b, int m);
//SDL - LoadTexture ÀÌ¹ÌÁö¸¦ ºÒ·¯¿È ÀÎÀÚ°ª : ·»´õ·¯, ÆÄÀÏ °æ·Î
SDL_Texture * LoadTexture(SDL_Renderer * Renderer, const char *file);
//SDL - RenderTexture ÀÌ¹ÌÁö¸¦ ·»´õ·¯¿¡ Ãâ·ÂÇÔ Rect·Î x, y, h, w¸¦ ¼³Á¤ °¡´É
void RenderTexture(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Rect * Rect);
//SDL -  LoadTextureEx ÀÌ¹ÌÁö¸¦ Æ¯º°ÇÏ°Ô ºÒ·¯¿È ÀÎÀÚ°ª : ·»´õ·¯, ÆÄÀÏ °æ·Î, r, g, b ÇØ´ç »ö±òÀ» ¾ø¾Ú
SDL_Texture * LoadTextureEx(SDL_Renderer * Renderer, const char *file, int r, int g, int b);
//SDL - RenderTextureEX ÅØ½ºÃÄ¸¦ Æ¯º°ÇÏ°Ô Ãâ·ÂÇÔ ÀÎÀÚ°ª : ·»´õ·¯, ÀÌ¹ÌÁö, À§Ä¡, °¢µµ
void RenderTextureEx(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Rect * Rect, int angle);
int hancheck(int unicode);
void DrawRect(SDL_Renderer * renderer, int r, int g, int b, int x, int y, int w, int h);
char* UNICODE2UTF8(wchar_t* unicode, int len);
wchar_t* UTF82UNICODE(char* UTF8, int len);
int UTF82EUCKR(char *outBuf, int outLength, char *inBuf, int inLength);
int hannum(wchar_t unicode[], int len);
//SDL - RenderTextureXYWH ÀÌ¹ÌÁö¸¦ ºÒ·¯¿À´Âµ¥ Rect¸¦ ¹Ì¸® »ı¼ºÇÒ ÇÊ¿ä°¡ ¾ø½¿
void RenderTextureXYWH(SDL_Renderer* Renderer, SDL_Texture * Texture, double xx, double yy, double ww, double hh);
//SDL - PutText_Unicode Unicode¸ğµå·Î ±ÛÀÚ¸¦ Ãâ·ÂÇÑ´Ù. 
void SDL_DrawRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius, int strong);
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
void FillUpRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius);
void SDL_DrawUpRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius, int strong);
void DrawUpRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius, int strong);
int ChangeColor(SDL_Event * event, SDL_Color * color, SDL_Rect rect, SOCKET sending, int MeTurn);
void CreateCanvas(Canvas * Canvas, SDL_Renderer * Renderer, int x, int y, int w, int h, int strong);
int UpdateCanvas(Canvas * Canvas, SDL_Event * event, SOCKET sending);
//SDL - PutButtonImage ÀÌ¹ÌÁö ¹öÆ°À» ¸¸µç´Ù ±âÁ¸Àº TextureÀÇ ÀÌ¹ÌÁö¸¦, ¸¶¿ì½º¸¦ ¿Ã¸®¸é MouseOnImage·Î º¯ÇÑ´Ù
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
//---------------MySql ÇÔ¼ö---------------
int GetRoomUser(MYSQL * cons, User * friends, SDL_Renderer * renderer);
//ÀÎÁö Ã¼Å©ÇÏ´Â ÇÔ¼ö
Hit_User *IsAutoLogin(MYSQL *cons);
int getUesrStatus(MYSQL *cons, char arr[30][30]);
int User_Signin_sql(MYSQL *cons, wchar_t *id, wchar_t *password, wchar_t * nickname, wchar_t *answer);
//Password_Change ºñ¹Ğ¹øÈ£¸¦ º¯°æÇÏ´Âµ¥ ÇÊ¿äÇÑ ÇÔ¼ö. Àß¸øµÇ¸é -1, ´äº¯ Àß¸øµÇ¸é 0 ¾÷µ¥ÀÌÆ®½ÇÆĞ -2 ¼º°ø 1
int Password_Change_sql(MYSQL *cons, wchar_t *id, wchar_t *newpassword, wchar_t *answer);
//_beginthreadex¿ë ÇÔ¼ö. ¾²·¹µå·Î mysql¿¡ ¿¬°áÇÔ
void Thread_MySQL(Connect_status *type);
//Ã³À½ MySQL¿¡ ¿¬°áÇÔ
MYSQL * Mysql_Connect(char *ip);
//wstr·Î Äõ¸®¹®À» ½ÇÇàÇÔ
int Mysql_wstr_query(MYSQL *cons, wchar_t * query);
//ì£¼ì œì¤‘ì— ?œë¤?¼ë¡œ ?˜ë‚˜ë¥?ë¶ˆëŸ¬?€ ë¬¸ì?´ë¡œ ë°˜í™˜
char * Get_Random_Topic(MYSQL *cons);	
//?„ì´?”ì? ?¨ìŠ¤?Œë“œë¡?ë¡œê·¸?¸í•¨
Hit_User *User_Login_sql(MYSQL *cons, char * id, char *password);	
//---------------Socket ÇÔ¼ö--------------
void OpenServer(SockParam *param);
// ¼­¹ö ¿°
void connectServer(SockParam *param);
// ¼­¹ö¿¡ ¿¬°áÇÔ param->serverip ¹Ù²ãÁà¾ß µÊ
void HandleClient(SockParam *param);
// ¼­¹ö°¡ Å¬¶óÀÌ¾ğÆ® °ü¸®ÇÔ
void sendall(SockParam *param);
// ¼­¹ö°¡ ¿¬°áµÈ Å¬¶óÀÌ¾ğÆ®ÇÑÅ× ÆĞÅ¶ Àü¼ÛÇÔ
void Clientrecv(SockParam *param);
// Å¬¶óÀÌ¾ğÆ®°¡ ¼­¹ö°¡ º¸³½ ÆĞÅ¶¹ŞÀ½
void hostChange(SockParam *param);

//ÁÖÁ¦Áß¿¡ ·£´ıÀ¸·Î ÇÏ³ª¸¦ ºÒ·¯¿Í ¹®ÀÚ¿­·Î ¹İÈ¯
char * Get_Random_Topic(MYSQL *cons);
//¹æ ¸ñ·ÏÀ» ºÒ·¯¿È
int Get_Room_List(MYSQL *cons, Hit_Room * rooms);
//¾ÆÀÌµğ¿Í ÆĞ½º¿öµå·Î ·Î±×ÀÎÇÔ
Hit_User *User_Login_sql(MYSQL *cons, char * id, char *password);
//ÀüÃ¼ Ã¤ÆÃÀ» Ãß°¡ÇÔ
int InsertChating_all(MYSQL *cons, char * username, wchar_t* message,int messagelength);
//ÀüÃ¼ Ã¤ÆÃÀ» ºÒ·¯¿È
int ReadChating_all(MYSQL *cons, Chating * chatings);
//¹æÀ» ¸¸µë, ¹æÀÌ¸§, ºñ¹Ğ¹øÈ£, ¸ğµå, ¹®Á¦ °³¼ö, ¹®Á¦ ½Ã°£ ÀÌ ÇÊ¿äÇÔ
int Create_Room_sql(MYSQL *cons, wchar_t * roomname, wchar_t * rompass, int mode, int question, int timer);
