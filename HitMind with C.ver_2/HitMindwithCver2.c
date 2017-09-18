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
	
	MYSQL *cons = Mysql_Connect("10.80.162.92");
	SDL_Window * Window = NULL;		//SDL 관련
	SDL_Renderer *renderer;
	SDL_Event event;
	TTF_Init();
	char version[] = "1.0.1 - Beta";
	TTF_Font *font = TTF_OpenFont(".\\font\\NanumGothic.ttf", 30);
	if (font == 0)
	{
		printf("error");
		getchar();
	}
	SDL_Init(SDL_INIT_EVERYTHING);
	Window = SDL_CreateWindow("Orbit or Beat with C", 300, 200, Display_X, Display_Y, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN);
	renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture * WaitBar = LoadTexture(renderer, ".\\maintema\\touch.png");
	if (WaitBar == 0)
		getchar();
	SDL_Texture * TitleImage = LoadTextureEx(renderer, ".\\mainicon\\main_wallpaper.jpg", 255, 255, 255);
	SDL_Texture * TitleText = LoadTexture(renderer, ".\\mainicon\\MainText.png"); 
	
	SDL_Rect TitleRect;
	TitleRect.x = 100;
	TitleRect.y = 100;
	TitleRect.w = 1280;
	TitleRect.h = 720;
	int quit = false; // while문 조건문에 쓰이는 불 변수
	int hanyeong = false; // 한영키상태에 쓰이는 불 변수
	int hangeul = false; // 현재 입력하고 있는 글자가 한글인지 아닌지 식별해주는 불 변수
	int textinput = true; // 글자가 하나 더 입력되었는지 알려주는 불 변수
	int enter = false; // 엔터가 입력되었는지 알려주는 불 변수
	wchar_t wchar[2] = L""; // 한글자 한글자 입력에 쓰이는 배열
	wchar_t wstr[64] = L"";// 지금까지 입력한 텍스트를 저장하는 배열
	char euckr[128] = ""; // euckr 변환에 필요한 배열
	char utf8[192] = ""; // utf8 변환에 필요한 배열
	wchar_t unicode[64] = L""; // unicode 변환에 필요한 배열
	
	while (!quit)
	{
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_TEXTINPUT: // 채팅 입력 이벤트
					if (hanyeong == true && (event.text.text[0] == -29 || event.text.text[0] + 256 >= 234 && event.text.text[0] + 256 <= 237))// 한글일 경우
					{
						wcscpy(wchar, L"");
						int sum = (event.text.text[0] + 22) * 64 * 64 + (event.text.text[1] + 128) * 64 + event.text.text[2] + 41088;
						wchar[0] = sum;
						wcscat(wstr, wchar);
					}
					else if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {// 영어 입력 시
						wcscpy(wchar, L"");
						swprintf(wchar, sizeof(wchar) / sizeof(wchar_t), L"%hs", event.text.text);// event.text.text 문자열 그냥 연결시켜버림
						wcscat(wstr, wchar);// 문자열 연결
						hangeul = false;
					}
					textinput = true;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_RETURN) {
						if (hangeul == true && enter == false)
							enter = true;
						else {
							strcpy(utf8, UNICODE2UTF8(wstr, wcslen(wstr)));
							UTF82EUCKR(euckr, 128, utf8, 192);
							euckr[strlen(euckr)] = '\0';
							han2unicode(euckr, unicode);
							if (hannum(unicode, wcslen(unicode)) != hannum(wstr, wcslen(wstr))) {
								strcpy(euckr, "[Error] invalid conversion");
							}
							strcpy(utf8, "");
							wcscpy(wstr, L"");
							wcscpy(unicode, L"");
							strcpy(euckr, "");
							enter = false;
							textinput = true;
						}
					}
					else if (event.key.keysym.sym == SDLK_RALT)
						hanyeong = !(hanyeong);
					else if (event.key.keysym.sym == SDLK_BACKSPACE && wcslen(wstr) > 0)// 키보드 백스페이스고 배열의 길이가 1이상일때
					{
						wstr[wcslen(wstr) - 1] = '\0';// 마지막문자를 널문자로 바꿈
						textinput = true;
					}
					else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {// 컨트롤 모드이고 c를 눌렀다면
						strcpy(utf8, UNICODE2UTF8(wstr, wcslen(wstr)));
						SDL_SetClipboardText(utf8);// 클립보드에 넣음
					}
					else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)// 컨트롤 모드이고 v를 눌렀다면
						wcscpy(wstr, UTF82UNICODE(SDL_GetClipboardText(), strlen(SDL_GetClipboardText())));// 클립보드에서 가져옴
					else
						hangeul = true;
					textinput = true;
					break;
				case SDL_QUIT :
					quit = true;
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_CLOSE:// 다수 창에서의 닫기이벤트가 발생할경우
							quit = true;// quit를 true로 변경
							Sleep(100);
							break;// 브레이크
						case SDL_WINDOWEVENT_ENTER:// 윈도우
							SDL_RaiseWindow(SDL_GetWindowFromID(event.window.windowID));//포커스 이동시킴
							break;
						case SDL_WINDOWEVENT_LEAVE:
						//	drag = false;//마우스가 창에서 나갔으므로 드래그 기능을 중지시킴
							break;
						case SDL_WINDOWEVENT_FOCUS_GAINED:
							break;
					}
			}
		}
		
		RenderTextureXYWH(renderer, TitleImage, 0, 0, Display_X, Display_Y);
		PutText(renderer, version, 20, (Display_Y / 20) * 19, Display_X / 48, 255, 255, 255);
		RenderTextureXYWH(renderer, TitleText, Display_X / 3, Display_Y / 10, Display_X / 3, Display_Y / 3);
		RenderTextureXYWH(renderer, WaitBar, 0, Display_Y / 1.3, Display_X, Display_Y / 15);
		SDL_RenderPresent(renderer);
		if (textinput == true) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			SDL_RenderClear(renderer);
			PutText_Unicode(renderer, wstr, 0, 0, 30, 255, 255, 255);
			textinput = false;
		}
	}
	SDL_DestroyTexture(WaitBar);
	SDL_DestroyTexture(TitleImage);
	SDL_DestroyTexture(TitleText);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
	return 0;
}

