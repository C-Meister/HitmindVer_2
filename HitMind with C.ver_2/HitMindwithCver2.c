/*
HitMind with C.ver_2 프로젝트를 시작합니다.
조원: 장민석, 배수한, 신상호, 서상희

해당 프로젝트를 git을 연동하여 공동으로 작업을 하며 각각의 파트가아닌 전부가 참여합니다.

먼저 함수의 선언은 include.h에 선언, 함수의 정의는 각각의 헤더파일(console,socket,mysql,graphic)에 작성합니다.

공동으로 작업:
	Ⅰ. 프로젝트 올리기
		1. 팀 탐색기 - 홈(팀 탐색기 제일 위에 집모양을 클릭) 에 들어가 변경 내용을 클릭합니다. 
		2. 자신의 작업한 내용을 커밋 메시지에 입력합니다.
		3. 모두 커밋(I)를 클릭합니다.
		4. 프로젝트를 저장합니다.
		5. 변경 내용 아래에 "커밋 ********을(를) 로컬에서 만들었습니다.... 라고 내용이 나오면 
		"내용을 공유하여 동기화합니다"에서 동기화를 클릭합니다.
		6. 동기화로 넘어가면 "분기: master" 아래에 동기화를 클릭합니다.
		7. 끝
	Ⅱ. 프로젝트 받기
		1. 팀 탐색기 - 홈(팀 탐색기 제일 위에 집모양을 클릭) 에 들어가 동기화를 클릭합니다.
		2. "분기: master"아래에 페치를 클릭합니다.
		3. "분기: master"아래에 끌어오기를 클릭합니다.
		4. 끝
*/

#include "include.h"

int main(int argc, char *argv[])
{
	
	SDL_Window * Window = nullptr;		//SDL 관련
	SDL_Renderer *renderer;
	SDL_Event event;
	TTF_Init();
	TTF_Font *font = TTF_OpenFont(".\\font\\NanumGothic.ttf", 30);
	if (font == 0)
	{
		printf("error");
		getchar();
	}
	SDL_Init(SDL_INIT_EVERYTHING);
	Window = SDL_CreateWindow("Orbit or Beat with C", 300, 200, Display_X, Display_Y, SDL_WINDOW_ALLOW_HIGHDPI);
	renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Rect TitleRect;
	TitleRect.x = 100;
	TitleRect.y = 100;
	TitleRect.w = 1280;
	TitleRect.h = 720;
	SDL_Texture * TitleImage = LoadTextureEx(renderer, ".\\wallpapers\\test.jpg", 255, 255, 255);
	int exit = 1;
	while (exit)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);
		SDL_RenderClear(renderer);
		SDL_PollEvent(&event);
		RenderTexture(renderer, TitleImage, &TitleRect);
		SDL_RenderPresent(renderer);
		
	}

	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();

	
	return 0;
}

