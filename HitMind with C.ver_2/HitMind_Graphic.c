﻿#include "include.h"

//그래픽 관련 함수들
void TTF_DrawText(SDL_Renderer *Renderer, TTF_Font* Font, wchar_t* sentence, int x, int y) {
	SDL_Color Color = { 0,0,0 };
	SDL_Surface * Surface = TTF_RenderUNICODE_Blended(Font, sentence, Color);// 폰트의 종류,문자열, 색깔을 보내서 유니코드로 렌더한다음 서피스에 저장한다
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);// 서피스로부터 텍스쳐를 생성한다
	SDL_FreeSurface(Surface);//서피스 메모리를 해제 해준다.
	SDL_Rect Src;
	Src.x = 0;
	Src.y = 0;
	SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h);
	SDL_Rect Dst;
	Dst.x = x;
	Dst.y = y;
	Dst.w = Src.w;
	Dst.h = Src.h;
	SDL_RenderCopy(Renderer, Texture, &Src, &Dst); //그대로 렌더러에 저장한다
	SDL_DestroyTexture(Texture);

	return;
}

int PutButton(SDL_Renderer * renderer, char * sentence, int x, int y, int size, SDL_Event * event)
{
	int plussize = 0;		//마우스를 가져다될때 커지는 사이즈
	SDL_PollEvent(event);	//SDL에서 이벤트를 꺼냄
	if (event->type == SDL_MOUSEBUTTONDOWN)	//클릭 되었을때
		if (event->button.x > x && event->button.y > y && event->button.x < (x + (signed int)strlen(sentence) * (size / 2)) && event->button.y < y + size + 5)
		{	//마우스가 해당 글씨위에 클릭하면
			return 1;	//1을 반환
		}
	if (event->type == SDL_QUIT)	//종료하려고 하면
		exit(1);		//종료 - 나중에 바꿔줘야함
	if (event->motion.x > x && event->motion.y > y && event->motion.x < (x + (signed int)strlen(sentence) * (size / 2)) && event->motion.y < y + size + 5)
	{	//마우스의 위치가 글씨 위에 있으면
		plussize = 5;	//커지는 효과
	}
	Unicode unicode[128] = L"";	//han2unicode를 쓰기 위해 unsigned short(UNICODE)를 생성
	han2unicode(sentence, unicode);		//옮김

	TTF_Font *font = TTF_OpenFont(".\\font\\NanumGothic.ttf", size + plussize);	 //폰트를 불러온다. 하지만 Draw할때마다 불러오는건 비효율적이긴 함.
	TTF_DrawText(renderer, font, unicode, x - (int)(plussize * (strlen(sentence) / 4)), y - (plussize / 2));	//Text를 적음
	TTF_CloseFont(font);	//임시로 출력하기위한 폰트를 닫음
	return 0;	//클릭이 안되었으니 0을 리턴
}
int PutText(SDL_Renderer * renderer, char * sentence, unsigned int x, unsigned int y, int size)
{
	Unicode unicode[128] = L"";		//역시나 임시로 TTF_DrawText를 쓰기 위한 unicode생성
	han2unicode(sentence, unicode);	//옮긴다
	TTF_Font *font = TTF_OpenFont(".\\font\\NanumGothic.ttf", size);	//폰트를 불러온다. 하지만 Draw할때마다 불러오는건 비효율적이긴 함.
	TTF_DrawText(renderer, font, unicode, x, y);			//Text를 적음
	TTF_CloseFont(font);	//폰트를 닫음
	return 0;	//평소에도 0을 리턴
}
SDL_Texture * LoadTexture(SDL_Renderer * Renderer, const char *file) { // 텍스쳐에 이미지파일 로드하는 함수 선언
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;// JPG파일과 PNG파일 로드 가능
	if (IMG_Init(imgFlags) != imgFlags) {//IMG 초기화하고 초기화 안되면 if문 실행
		IMG_ErrorLog("IMG_Init");
		return nullptr;//널포인터 반환
	}
	SDL_Surface* Surface = IMG_Load(file);//서피스에 이미지로드
	if (Surface == nullptr) {//서피스에 이미지로드가 안되면 
		IMG_ErrorLog("IMG_Load");
		IMG_Quit();// IMG 종료
		return nullptr;// 널포인터 반환
	}
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);//서피스로부터 텍스쳐 생성
	SDL_FreeSurface(Surface);// 서피스 메모리해제
	if (Texture == nullptr) {// 텍스쳐 생성 실패시 if문실행
		SDL_ErrorLog("SDL_CreateTextureFromSurface");// 에러 코드 출력
		IMG_Quit();// IMG 종료
		return nullptr;// 널포인터 반환
	}
	IMG_Quit();// IMG 종료
	return Texture;// Texture포인터 반환
}
void RenderTexture(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Rect * Rect) {//텍스쳐를 출력하는 함수 선언
	SDL_Rect Src;// 직사각형 선언
	Src.x = 0;// 직사각형의 왼쪽위 꼭짓점의 x좌표초기화
	Src.y = 0;// 직사각형의 왼쪽위 꼭짓점의 y좌표초기화
	SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
	SDL_Rect Dst;
	Dst.x = Rect->x;//매개변수x를 왼쪽위 꼭짓점의 x좌표에 대입
	Dst.y = Rect->y;//매개변수y를 왼쪽위 꼭짓점의 y좌표에 대입
	Dst.w = Rect->w;//매개변수w를 직사각형의 너비에 대입
	Dst.h = Rect->h;//매개변수h를 직사각형의 높이에 대입
	SDL_RenderCopy(Renderer, Texture, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장
	return;
}
SDL_Texture * LoadTextureEx(SDL_Renderer * Renderer, const char *file, int r, int g, int b) { // 텍스쳐에 이미지파일 로드하는 함수 선언
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;// JPG파일과 PNG파일 로드 가능
	if (IMG_Init(imgFlags) != imgFlags) {//IMG 초기화하고 초기화 안되면 if문 실행
		return nullptr;//널포인터 반환
	}
	SDL_Surface* Surface = IMG_Load(file);//서피스에 이미지로드
	if (Surface == nullptr) {//서피스에 이미지로드가 안되면 

		IMG_Quit();// IMG 종료
		return nullptr;// 널포인터 반환
	}
	SDL_SetColorKey(Surface, 1, SDL_MapRGB(Surface->format, r, g, b));// r,g,b값에 해당하는 색상을 지우는 함수임
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);//서피스로부터 텍스쳐 생성
	SDL_FreeSurface(Surface);// 서피스 메모리해제
	if (Texture == nullptr) {// 텍스쳐 생성 실패시 if문실행

		IMG_Quit();// IMG 종료
		return nullptr;// 널포인터 반환
	}
	IMG_Quit();// IMG 종료
	return Texture;// Texture포인터 반환
}
void RenderTextureEx(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Rect * Rect, int angle) {//텍스쳐를 출력하는 함수 선언
	SDL_Rect Src;// 직사각형 선언
	Src.x = 0;// 직사각형의 왼쪽위 꼭짓점의 x좌표초기화
	Src.y = 0;// 직사각형의 왼쪽위 꼭짓점의 y좌표초기화
	SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
	SDL_Rect Dst;
	Dst.x = Rect->x;//매개변수x를 왼쪽위 꼭짓점의 x좌표에 대입
	Dst.y = Rect->y;//매개변수y를 왼쪽위 꼭짓점의 y좌표에 대입
	Dst.w = Rect->w;//매개변수w를 직사각형의 너비에 대입
	Dst.h = Rect->h;//매개변수h를 직사각형의 높이에 대입
	SDL_Point center;
	center.x = (Rect->w / 2);
	center.y = (Rect->h / 2);

	SDL_RenderCopyEx(Renderer, Texture, &Src, &Dst, angle, &center, SDL_FLIP_NONE);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장
	return;
}
void RenderTexture(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Rect * Rect) {//텍스쳐를 출력하는 함수 선언
	SDL_Rect Src;// 직사각형 선언
	Src.x = 0;// 직사각형의 왼쪽위 꼭짓점의 x좌표초기화
	Src.y = 0;// 직사각형의 왼쪽위 꼭짓점의 y좌표초기화
	SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
	SDL_Rect Dst;
	Dst.x = Rect->x;//매개변수x를 왼쪽위 꼭짓점의 x좌표에 대입
	Dst.y = Rect->y;//매개변수y를 왼쪽위 꼭짓점의 y좌표에 대입
	Dst.w = Rect->w;//매개변수w를 직사각형의 너비에 대입
	Dst.h = Rect->h;//매개변수h를 직사각형의 높이에 대입
	SDL_RenderCopy(Renderer, Texture, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장
	return;
}