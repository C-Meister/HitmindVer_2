//헤더파일들이 선언된 헤더파일
//모든 .c파일에 선언해주자
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>				//수학 관련 함수
#include <process.h>			//Thread 사용 함수
#include <Windows.h>			//Window api 관련 함수
#include <signal.h>				//Interrupt처리 함수
#include <time.h>				
#include <stdbool.h>			//Bool 사용 함수
#include <stdint.h>				//여러 typedef 관련 타입 함수
#include <direct.h>				//폴더 관련 함수
#include <crtdbg.h>
#include <mmsystem.h>			//사운드 관련
#include <Digitalv.h>

#include <mysql/mysql.h>		//MySQL 함수들

#include "SDL/SDL.h"			//SDL - 기본 헤더파일
#include "SDL/SDL_image.h"		//SDL - 이미지 헤더파일
#include "SDL/SDL_ttf.h"		//SDL - 폰트(텍스트) 헤더파일
#include "SDL/han2unicode.h"	//han2unicode - 기본 949 언어들을 uniocde로 바꿔줌
#include "SDL/SDL_mixer.h"		//SDL - 사운드 헤더파일




#pragma comment (lib, "lib/SDL2")			//그래픽 라이브러리 1
#pragma comment (lib, "lib/SDL2main")		//그래픽 라이브러리 2 
#pragma comment (lib, "lib/SDL2_image")		//그래픽 라이브러리 3
#pragma comment (lib, "lib/SDL2_ttf")		//그래픽 라이브러리 4
#pragma comment (lib, "lib/SDL2_mixer.lib")	//그래픽 사운드 라이브러리 5
#pragma comment (lib, "winmm.lib")			//사운드
#pragma comment (lib, "ws2_32.lib")			//소켓 라이브러리
#pragma comment (lib, "lib/libmysql.lib")	//MySQL 라이브러리

#define CLS system("cls")	//콘솔 화면 지우기
#define setcolor(X, Y) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), X | (Y << 4)) //콘솔 출력 글씨 설정
#define RESET(X) ZeroMemory(X, sizeof(X))	//초기화 memset()이랑 같음


//---------------콘솔 함수----------------



//---------------그래픽 함수--------------


//---------------MySql 함수---------------



//---------------Socket 함수--------------