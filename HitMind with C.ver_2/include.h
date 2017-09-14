//헤더파일들이 선언된 헤더파일
//모든 .c파일에 선언해주자
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <process.h>
#include <Windows.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <direct.h>
#include <crtdbg.h>
#include <mmsystem.h>
#include <Digitalv.h>

#include <mysql/mysql.h>

#include "SDL/SDL.h"			//SDL - 그래픽 헤더파일
#include "SDL/SDL_image.h"		
#include "SDL/SDL_ttf.h"
#include "SDL/han2unicode.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL.h"




#pragma comment (lib, "lib/SDL2")			//그래픽 라이브러리 1
#pragma comment (lib, "lib/SDL2main")		//그래픽 라이브러리 2 
#pragma comment (lib, "lib/SDL2_image")		//그래픽 라이브러리 3
#pragma comment (lib, "lib/SDL2_ttf")
#pragma comment (lib, "lib/SDL2_mixer.lib")	//그래픽 사운드 라이브러리 4
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "lib/libmysql.lib")

#define CLS system("cls")	//콘솔 화면 지우기
#define setcolor(X, Y) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), X | (Y << 4)) //콘솔 출력 글씨 설정
#define RESET(X) ZeroMemory(X, sizeof(X))


//---------------콘솔 함수----------------



//---------------그래픽 함수--------------


//---------------MySql 함수---------------



//---------------Socket 함수--------------