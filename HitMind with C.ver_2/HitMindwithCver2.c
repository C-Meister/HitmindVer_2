/*
HitMind With C.ver_2
조원: 킹상호, 갓상희, 엠퍼럴수한, 제너럴민석
콘솔따윈없다

*/

#include <stdio.h>

#include "SDL/SDL.h"			//SDL - 그래픽 헤더파일
#include "SDL/SDL_image.h"		
#include "SDL/SDL_ttf.h"
#include "SDL/han2unicode.h"
#include "mysql/mysql.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL.h"
#include "lib/iconv.h"
#define nullptr 0
// 라이브러리 선언문 라이브러리파일은 따로 추가안해도 됩니다.
// #pragma comment 는 visual studio에서만 사용 가능 *솔루션 플렛폼을 64비트로 해주세요
#pragma comment (lib, "lib/libmysql.lib")	//mysql라이브러리
#pragma comment (lib, "lib/SDL2")			//그래픽 라이브러리 1
#pragma comment (lib, "lib/SDL2main")		//그래픽 라이브러리 2 
#pragma comment (lib, "lib/SDL2_image")		//그래픽 라이브러리 3
#pragma comment (lib,"lib/SDL2_ttf")
#pragma comment (lib, "lib/SDL2_mixer.lib")	//그래픽 사운드 라이브러리 4
int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	mysql_init(NULL);
	return 0;
}

