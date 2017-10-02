/*
HitMind with C.ver_2 프로젝트를 시작합니다.
조원: 장민석, 배수한, 신상호, 서상희

해당 프로젝트를 git을 연동하여 공동으로 작업을 하며 각각의 파트가아닌 전부가 참여합니다.

먼저 함수의 선언은 include.h에 선언, 함수의 정의는 각각의 헤더파일(console,socket,mysql,graphic)에 작성합니다.

공동으로 작업:
Ⅰ. 프로젝트 올리기
1. 팀 탐색기 - 홈(팀 탐색기 제일 위에 집모양을 클릭) 에 들어가 변경 내용을 클릭합니다.
2. 자신의 작업한 내용을 커밋 메시지에 입력합니다.
3. 모두 커밋(I)를 클릭합니다.  혹은 모두커밋 옆에 화살표를 눌러 모두 커밋 후 동기화를 눌러도 됨
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
	//	getchar();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Connect_status status;	//MySQL이 연결된 상태를 저장하는 구조체
	MYSQL *cons = 0;		//MySQL선언
	status.arg = cons;		//status에 mysql의 주소를 저장한다
	status.ishappen = false;//연결이 안된 상태
	SDL_Window * Window = NULL;		//SDL 관련
	SDL_Renderer *renderer;			//SDL - 렌더러로 그리기에 씀
	SDL_Event event;				//SDL 이벤트를 저장함
	Warning_M warning = { 0, "", 0, 0, 0,0, 0, 0 };
	TTF_Init();		//TTF 초기화
	HitMind_TTF_Init();
	HitMind_TTF2_Init();
	char version[] = "1.0.1 - Beta";		//현제 버전
	TTF_Font *font = TTF_OpenFont(".\\font\\NanumGothic.ttf", 30);	//나눔고딕 폰트를 불러옴
	SockParam ServerParam;
	SockParam ClientParam;
	uintptr_t server;
	uintptr_t client;
	ZeroMemory(&ServerParam, sizeof(SockParam));
	ZeroMemory(&ClientParam, sizeof(SockParam));
	int bangsang;

	ServerParam.s = &server;
	ServerParam.c = &client;
	if (font == 0)
	{
		printf("error");
		getchar();
	}
	Mix_Music *lobbymusic = Mix_LoadMUS("sound/lobby.mp3");
	Mix_Music *mainmusic = Mix_LoadMUS("sound/login.mp3");
	settings(&Display_X, &Display_Y, &BGmusic, &Sound, &Full);
	Mix_VolumeMusic(BGmusic);

	//_beginthreadex(NULL, NULL, (_beginthreadex_proc_type)soundplay, NULL, NULL, NULL); //나중에 게임 들어가면 쓸 음악

	SDL_Init(SDL_INIT_EVERYTHING);						//SDL 초기화
	if (Full)
		Window = SDL_CreateWindow("HitMind_2", 100, 100, Display_X, Display_Y, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN_DESKTOP);		//해당 해상도로 Window를 생성함
	else
		Window = SDL_CreateWindow("HitMind_2", 100, 100, Display_X, Display_Y, SDL_WINDOW_ALLOW_HIGHDPI);		//해당 해상도로 Window를 생성함
	renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_SOFTWARE/* | SDL_RENDERER_PRESENTVSYNC*/);

	SDL_Texture * WaitBar = LoadTexture(renderer, ".\\maintema\\touch.png");		//계속하려면 클릭해주세요... 이미지
	SDL_Texture * TitleText = LoadTexture(renderer, ".\\mainicon\\MainText.png");	//HitMind 글씨 이미지
	SDL_Texture * TitleImage = LoadTexture(renderer, ".\\mainicon\\main_wallpaper.jpg");
	SDL_Surface * mousesurface = NULL;
	mousesurface = IMG_Load(".\\design\\pencil.png");
	if (!mousesurface)
	{
		printf("loadbmp");

	}

	SDL_Cursor*cursor = SDL_CreateColorCursor(mousesurface, 0, 43);
	if (!cursor)
	{
		printf("cursor");
		getchar();
	}
	SDL_SetCursor(cursor);
	SDL_Texture * LoadingBar = LoadTexture(renderer, ".\\maintema\\loading.png");
	int qquit = false;
	int quit = false; // while문 조건문에 쓰이는 불 변수
	int loginpopup = false; //로그인 팝업 반복문 상태
	int create_password_status = false;
	int loginsuccess = false; //로그인 성공 상태
	int find_password_status = false;
	Hit_User * myuser = 0;
	int hanyeong = false; // 한영키상태에 쓰이는 불 변수
	User gameuser[4] = { 0, };
	int i, j;
	Hit_Room My_Room;
	memset(&My_Room, 0, sizeof(My_Room));
	int happen = 0;
	int backspacehappen = false;
	int pass_reset_mode = 1;
	int hangeul = false; // 현재 입력하고 있는 글자가 한글인지 아닌지 식별해주는 불 변수
	int textinput = true; // 글자가 하나 더 입력되었는지 알려주는 불 변수
	int enter = false; // 엔터가 입력되었는지 알려주는 불 변수
	wchar_t wchar[2] = L""; // 한글자 한글자 입력에 쓰이는 배열
	wchar_t change_password[5][256] = { L"", L"", L"", L"" };
	Unicode ID_put[256] = L"";
	Unicode Password_put[256] = L"";
	char db_id[256] = "";
	char db_password[256] = "";
	int setting_main = 0;
	int isplaygame = 0;
	int pass_length = 0;
	char query[128];
	char utf8[256] = ""; // utf8 변환에 필요한 배열
	int slice = 0;
	int sum;
	SDL_Color color = { 0,0,0 ,0 };
	int ID_INPUT;
	int roop = 1;
	int PASSWORD_INPUT;
	int PressButton = 0;
	int autologin_checking;
	int roomchange = 1; //방선택
	char roomtmp[10] = { 0, }; //방선택 tmp

	//	 테스트 코드
	//char Topics[5][30] = {
	//	"하스스톤",
	//	"대구소프트웨어고등학교",
	//	"기모",
	//	"마인크래프트",
	//	"스타크래프트"
	//};
	//int MaxTopic = 5; //총 토픽 개수
	//int NowTopic = 2; // 현재 토픽이 몇번째 토픽인지 보여줌
	//char Now_Max[10];
	//sprintf(Now_Max, "%d/%d", NowTopic, MaxTopic);
	//wchar_t InGameChat[128] = L"";
	//char euckrofchat[128] = "";
	//char utf8ofchat[128] = "";
	//int Shift = 0; int Chat = DEACTIVATED; int Enter = DEACTIVATED; textinput = false;

	//float MaxStrong = 70.0*Display_X / 1920, PencilStrong = 55.0, EraserStrong = 55.0;
	//SDL_Point Sample = { Display_X * 0.8 + Display_X*0.011 + (Display_X*0.1825*0.07) + MaxStrong / 2, Display_Y * 0.64 + Display_X*0.005 + (Display_Y * 0.34*0.13) };
	//SDL_Rect RgbRect = { Display_X * 0.8 + Display_X*0.011 + (Display_X*0.1825*0.07), Display_Y * 0.64 + Display_X*0.005 + (Display_Y * 0.34*0.375), Display_X * 0.1825 - 2 * (Display_X*0.1825*0.07), (Display_Y * 0.34*0.6) };
	//SDL_Rect LineRect = { Display_X * 0.8 + Display_X*0.011, Display_X*0.005 + Display_Y*0.21*0.633, Display_X * 0.1825, Display_Y * 0.004 };
	//SDL_Rect TopicRect = { Display_X * 0.8 + Display_X * 0.1825*0.1 + Display_X*0.011, Display_X*0.005 + Display_Y*0.21*0.063, Display_X * 0.1825 - 2 * Display_X * 0.1825*0.1, Display_Y * 0.05 };
	//SDL_Rect CountRect = { Display_X * 0.8 + Display_X * 0.1825*0.1 + Display_X*0.011, Display_X*0.005 + Display_Y*0.21*0.333, Display_X * 0.1825 - 2 * Display_X * 0.1825*0.1, Display_Y * 0.05 };
	//SDL_Rect ChatRect = { Display_X * 0.8 + Display_X*0.1825*0.035 + Display_X*0.011, Display_X*0.005 + Display_Y*0.62*0.933, Display_X * 0.1825*0.96 - 2 * Display_X*0.1825*0.1, Display_Y * 0.05 };
	//SDL_Rect EnterRect = { Display_X * 0.8 + Display_X*0.1825*0.825 + Display_X*0.011, Display_X*0.005 + Display_Y*0.62*0.93635, Display_X * 0.1825*0.15, Display_Y * 0.04 };
	//SDL_Rect TimerRect = { Display_X*0.011,Display_Y*0.76,Display_X*0.8 - Display_X*0.017,Display_Y*0.007 };
	//SDL_Rect UserRect = { Display_X*0.011,Display_Y*0.79,Display_X*0.8*0.24,Display_Y*0.19 };
	//SDL_Color TextColor = { 0,0,0,0 };


	//SDL_Texture * PencilTexture = LoadTexture(renderer, ".//design//pencil2.png");
	//SDL_Texture * RecycleTexture = LoadTexture(renderer, ".//design//Recycle.jpg");
	//SDL_Texture * PassTexture = LoadTexture(renderer, ".//design//Pass.jpg");
	//SDL_Texture * MagTexture = LoadTexture(renderer, ".//design//magnifying.png");
	//SDL_Texture * NewTexture = LoadTexture(renderer, ".//design/Newpile.png");
	//SDL_Texture * EraserTexture = LoadTexture(renderer, ".//design//Eraser.png");
	//SDL_Texture * BarTexture = LoadTexture(renderer, ".//design//slider.png");
	//SDL_Texture * BoxTexture = LoadTexture(renderer, ".//design//val4.png");
	//SDL_Texture * RgbCode = LoadTexture(renderer, ".//design//RgbCode.png");
	//SDL_Texture * DChatTexture = LoadTexture(renderer, ".//design//defaultchat.png");
	//SDL_Texture * HChatTexture = LoadTexture(renderer, ".//design//onchat.png");
	//SDL_Texture * ChatTexture = LoadTexture(renderer, ".//design//chatting.png");
	//SDL_Texture * EnterTexture = LoadTexture(renderer, ".//design//Enter.png");
	//SDL_Texture * HEnterTexture = LoadTexture(renderer, ".//design//Enter2.png");
	//SDL_Texture * CharacterTexture = LoadTextureEx(renderer, ".//design//Character.png", 255, 255, 255);
	//SDL_Texture * StatusTexture = LoadTexture(renderer, ".//design//Status.png");

	//User Player[4] = {
	//	{
	//		CharacterTexture,
	//		StatusTexture,
	//		"신상호",
	//		1, //master
	//		1, //level
	//		0, //turn
	//		0,//count
	//		1// Th
	//	},
	//	{
	//		CharacterTexture,
	//		StatusTexture,
	//		"장민석",
	//		0,
	//		1,
	//		1,
	//		0,
	//		2
	//	},
	//	{
	//		CharacterTexture,
	//		StatusTexture,
	//		"배수한",
	//		0,
	//		1,
	//		0,
	//		0,
	//		3
	//	},
	//	{
	//		CharacterTexture,
	//		StatusTexture,
	//		"서상희",
	//		0,
	//		1,
	//		0,
	//		0,
	//		4
	//	}
	//};
	//User * Me = &Player[1];
	//Canvas * canvas = (Canvas*)malloc(sizeof(Canvas));
	//Slider * StrongSlider = (Slider *)malloc(sizeof(Slider));
	//Button * PencilButton = (Button *)malloc(sizeof(Button));
	//Button * NewButton = (Button *)malloc(sizeof(Button));
	//Button * EraserButton = (Button *)malloc(sizeof(Button));
	//Button * PassButton = (Button *)malloc(sizeof(Button));
	//Button * MagButton = (Button *)malloc(sizeof(Button));
	//Button * RecycleButton = (Button *)malloc(sizeof(Button));
	//Text * TopicText = (Text *)malloc(sizeof(Text));
	//Text * CountText = (Text *)malloc(sizeof(Text));
	//int RenderUpdate = false;

	//CreateCanvas(canvas, renderer, 10 + 14, 10 + 14, Display_X * 0.8 - 2 * 14, Display_Y * 0.76 - 2 * 14, 10);
	//CreateSlider(StrongSlider, BoxTexture, BarTexture, Display_X * 0.8 + Display_X*0.011 + (Display_X*0.1825*0.07), Display_Y * 0.64 + 10 + (Display_Y * 0.34*0.275), Display_X * 0.1825 - 2 * (Display_X*0.1825*0.07), (Display_Y * 0.34*0.05), Display_X*0.02, Display_Y*0.05, &canvas->Strong, 1.0, MaxStrong, 20.0 / 70 * MaxStrong, HORIZONTAL);
	//CreateButton(PencilButton, renderer, PencilTexture, floor(MaxStrong * 10 / 70.0), Sample.x - MaxStrong / 2.0 + (Display_X*0.1825*0.22), Sample.y - MaxStrong / 2.0, MaxStrong, MaxStrong, 0, 0, 255, 64);
	//CreateButton(EraserButton, renderer, EraserTexture, floor(MaxStrong * 10 / 70.0), Sample.x - MaxStrong / 2.0 + 2 * (Display_X*0.1825*0.22), Sample.y - MaxStrong / 2.0, MaxStrong, MaxStrong, 0, 0, 255, 64);
	//CreateButton(NewButton, renderer, NewTexture, floor(MaxStrong * 7.5 / 70.0), Sample.x - MaxStrong / 2.0 + 3 * (Display_X*0.1825*0.22), Sample.y - MaxStrong / 2.0, MaxStrong, MaxStrong, 0, 0, 255, 64);
	//CreateButton(MagButton, renderer, MagTexture, floor(MaxStrong * 7.5 / 70.0), Display_X*0.0035 + Sample.x - MaxStrong / 2.0 + 3 * (Display_X*0.1825*(0.22 - 0.019 / 3)), Display_X*0.005 + Display_Y * 0.21*0.67, MaxStrong * 70 / 70.0, MaxStrong * 70 / 70.0, 0, 0, 255, 64);
	//CreateButton(PassButton, renderer, PassTexture, floor(MaxStrong * 7.5 / 70.0), Display_X*0.0035 + Sample.x - MaxStrong / 2.0 + (Display_X*0.1825*(0.22*1.5 - 0.019)), Display_X*0.005 + Display_Y * 0.21*0.67, MaxStrong * 70 / 70.0, MaxStrong * 70 / 70.0, 0, 0, 255, 64);
	//CreateButton(RecycleButton, renderer, RecycleTexture, floor(MaxStrong * 7.5 / 70.0), Display_X*0.0035 + Sample.x - MaxStrong / 2.0 - (Display_X*0.1825*0.019), Display_X*0.005 + Display_Y * 0.21*0.67, MaxStrong * 70 / 70.0, MaxStrong * 70 / 70.0, 0, 0, 255, 64);
	//CreateText(TopicText, renderer, Topics[NowTopic - 1], TopicRect.x, TopicRect.y, TopicRect.w, TopicRect.h, 255, 255, 255, Display_Y*0.035, 1);
	//CreateText(CountText, renderer, Now_Max, CountRect.x, CountRect.y, CountRect.w, CountRect.h, 255, 255, 255, Display_Y*0.035, 1);

	//SDL_SetRenderDrawColor(renderer, 191, 191, 191, 0);
	//SDL_RenderClear(renderer);
	////1번구역
	//FillRoundRect(renderer, 255, 255, 255, Display_X*0.005, Display_X*0.005, Display_X * 0.8, Display_Y * 0.76, Display_X*0.007);
	//DrawRoundRect(renderer, 191, 191, 191, Display_X*0.005 - 1, Display_X*0.005 - 1, Display_X * 0.8 + 2, Display_Y * 0.76 + 2, Display_X*0.007, 1);
	////4번구역
	//FillRoundRect(renderer, 255, 255, 255, Display_X*0.005, Display_Y * 0.77 + Display_X*0.005, Display_X * 0.8, Display_Y * 0.21, Display_X*0.007);
	//DrawRoundRect(renderer, 191, 191, 191, Display_X*0.005 - 1, Display_Y * 0.77 + Display_X*0.005 - 1, Display_X * 0.8 + 2, Display_Y * 0.21 + 2, Display_X*0.007, 1);
	////5번구역
	//FillRoundRect(renderer, 255, 255, 255, Display_X * 0.8 + Display_X*0.011, Display_Y * 0.64 + Display_X*0.005, Display_X * 0.1825, Display_Y * 0.34, Display_X*0.007);
	//DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.8 + Display_X*0.011 - 1, Display_Y * 0.64 + Display_X*0.005 - 1, Display_X * 0.1825 + 2, Display_Y * 0.34 + 2, Display_X*0.007, 1);
	////3번구역
	//FillRoundRect(renderer, 255, 255, 255, Display_X * 0.8 + Display_X*0.011, Display_Y * 0.22 + Display_X*0.005, Display_X * 0.1825, Display_Y * 0.41, Display_X*0.007);
	//DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.8 + Display_X*0.011 - 1, Display_Y * 0.22 + Display_X*0.005 - 1, Display_X * 0.1825 + 2, Display_Y * 0.41 + 2, Display_X*0.007, 1);
	////2번구역
	//FillRoundRect(renderer, 255, 255, 255, Display_X * 0.8 + Display_X*0.011, Display_X*0.005, Display_X * 0.1825, Display_Y * 0.21, Display_X*0.005);
	//DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.8 + Display_X*0.011 - 1, Display_X*0.005 - 1, Display_X * 0.1825 + 2, Display_Y * 0.21 + 2, 3, 1);
	//// Rgb 색상표
	//RenderTexture(renderer, RgbCode, &RgbRect);
	//// 슬라이더와 버튼들
	//DrawSlider(renderer, StrongSlider);
	//PencilButton->Flag=ACTIVATED;
	//DrawButton(PencilButton);
	//DrawButton(EraserButton);
	//DrawButton(NewButton);
	//DrawButton(MagButton);
	//DrawButton(RecycleButton);
	//DrawButton(PassButton);
	////
	//// 샘플링 
	//canvas->Strong *= PencilStrong / 70.0;
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//FillCircle(renderer, Sample.x, Sample.y, canvas->Strong / 2.0 + 1);
	//SDL_SetRenderDrawColor(renderer, canvas->Color.r, canvas->Color.g, canvas->Color.b, 0);
	//FillCircle(renderer, Sample.x, Sample.y, canvas->Strong / 2.0);
	////
	//// 채팅창
	//RenderTexture(renderer, DChatTexture, &ChatRect);
	//RenderTexture(renderer, EnterTexture, &EnterRect);
	////
	//for (int i = 0; i < 4; i++)
	//	PrintUserInfo(renderer, Player + i, UserRect);
	//// 유저정보
	////
	//// 토픽과 문제수
	//FillRoundRect(renderer, 146, 208, 80, TopicRect.x, TopicRect.y, TopicRect.w, TopicRect.h, Display_X*0.004);
	//CenterArrange(TopicText);
	//RenderText(TopicText);
	////	PutText(renderer, Topics[NowTopic-1], TopicRect.x+TopicRect.w*0.05, TopicRect.y + TopicRect.h*0.07, Display_Y*0.035,255,255,255,1);
	//SDL_RenderFillRect(renderer, &LineRect);
	//FillRoundRect(renderer, 0, 176, 240, CountRect.x, CountRect.y, CountRect.w, CountRect.h, Display_X*0.004);
	//CenterArrange(CountText);
	//RenderText(CountText);
	////
	//// 타이머 생성
	//int LimitTime = 30; // 초단위 (최소 1초 이상이여야한다 )
	//int Time = 50; // ms 단위(10의 배수로) 너무 크게하면 타이머가 스무스하지 않고 너무 작게하면 keyboardRepeat가 빨라진다
	//double TimerTemp = (double)TimerRect.w;
	//double TimerRate = (TimerRect.w/(double)LimitTime)*(Time/(double)1000); // 타이머가 Time(ms)초 마다 줄어드는 길이
	//// 
	//SDL_RenderPresent(renderer);
	//_beginthreadex(NULL, 0, (_beginthreadex_proc_type)Timer, Time, 0, 0);
	//while (!quit)//로그인 성공 후 대기창
	//{
	//	SDL_WaitEvent(&event);
	//	if (UpdateCanvas(canvas, &event) == 1 && Chat != ACTIVATED) {
	//		SDL_RenderPresent(renderer);
	//		printf("render	");
	//		continue;
	//	}
	//	if (PutButtonWithImage(renderer, DChatTexture, HChatTexture, ChatTexture, ChatRect.x, ChatRect.y, ChatRect.w, ChatRect.h, &event, &Chat) == 1) {
	//		if (Chat == DEACTIVATED) {
	//			wcscpy(InGameChat, L"");
	//		}
	//		SDL_RenderPresent(renderer);
	//		printf("render	");
	//		continue;
	//	}
	//	switch (event.type)
	//	{
	//	case SDL_USEREVENT:
	//		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	//		SDL_RenderFillRect(renderer, &TimerRect);
	//		TimerTemp -= TimerRate;
	//		TimerRect.w = TimerTemp;
	//		SDL_SetRenderDrawColor(renderer, 146, 208, 80, 0);
	//		SDL_RenderFillRect(renderer, &TimerRect);
	//		SDL_RenderPresent(renderer);
	//		break;
	//	case SDL_TEXTINPUT: // 채팅 입력 이벤트
	//		if (Chat != ACTIVATED)
	//			break;
	//		if (hanyeong == true && (event.text.text[0] == -29 || event.text.text[0] + 256 >= 234 && event.text.text[0] + 256 <= 237))// 한글일 경우
	//		{
	//			wcscpy(wchar, L"");
	//			sum = (event.text.text[0] + 22) * 64 * 64 + (event.text.text[1] + 128) * 64 + event.text.text[2] + 41088;
	//			wchar[0] = sum;
	//			wcscat(InGameChat, wchar);
	//			if (event.text.text[0] == -29)
	//				slice = 1;
	//			else
	//				slice = 1 + !((wchar[0] - 0xac00) % 28);
	//			textinput = true;
	//		}
	//		else if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {// 영어 입력 시
	//			wcscpy(wchar, L"");
	//			swprintf(wchar, sizeof(wchar) / sizeof(wchar_t), L"%hs", event.text.text);// event.text.text 문자열 그냥 연결시켜버림
	//			wcscat(InGameChat, wchar);
	//			hangeul = false;
	//			slice = 0;
	//			textinput = true;
	//		}
	//		break;
	//	case SDL_KEYDOWN:
	//		if (Chat != ACTIVATED)
	//			break;
	//		if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
	//			if (hangeul == true && enter == false) {
	//				enter = true;
	//			}
	//			else {
	//				Shift = 0;
	//				strcpy(utf8ofchat, UNICODE2UTF8(InGameChat, wcslen(InGameChat)));
	//				UTF82EUCKR(euckrofchat, strlen(euckrofchat), utf8ofchat, strlen(utf8ofchat));
	//				wcscpy(InGameChat, L"");
	//				enter = false;
	//				textinput = true;
	//			}
	//		}
	//		else if (event.key.keysym.sym == SDLK_RALT)
	//			hanyeong = !(hanyeong);
	//		else if (event.key.keysym.sym == SDLK_BACKSPACE && wcslen(InGameChat) > 0)// 키보드 백스페이스고 배열의 길이가 1이상일때
	//		{
	//			if (slice == 0) {
	//				if (Shift > 0)
	//					Shift--;
	//				InGameChat[wcslen(InGameChat) - 1] = '\0';
	//				textinput = true;
	//			}
	//			else {
	//				slice--;
	//			}
	//		}
	//		else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {// 컨트롤 모드이고 c를 눌렀다면			
	//			strcpy(utf8, UNICODE2UTF8(InGameChat, wcslen(InGameChat)));
	//			SDL_SetClipboardText(utf8);// 클립보드에 넣음
	//		}
	//		else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {// 컨트롤 모드이고 v를 눌렀다면
	//			wcscat(InGameChat, UTF82UNICODE(SDL_GetClipboardText(), strlen(SDL_GetClipboardText())));// 클립보드에서 가져옴
	//			hangeul = false;
	//			textinput = true;
	//		}
	//		else {
	//			hangeul = true;
	//			slice++;
	//		}
	//		break;
	//	case SDL_QUIT:
	//		quit = true;
	//		break;
	//	case SDL_WINDOWEVENT:
	//		switch (event.window.event) {
	//		case SDL_WINDOWEVENT_CLOSE:// 다수 창에서의 닫기이벤트가 발생할경우
	//			quit = true;
	//			Sleep(100);
	//			break;// 브레이크
	//		case SDL_WINDOWEVENT_ENTER:// 윈도우
	//			SDL_RaiseWindow(SDL_GetWindowFromID(event.window.windowID));//포커스 이동시킴
	//			break;
	//		case SDL_WINDOWEVENT_LEAVE:
	//			//drag = false;//마우스가 창에서 나갔으므로 드래그 기능을 중지시킴
	//			break;
	//		case SDL_WINDOWEVENT_FOCUS_GAINED:
	//			break;
	//		}
	//	}
	//	if (textinput == true) {
	//		RenderTexture(renderer, ChatTexture, &ChatRect);
	//		while (PutText_Unicode_Limit(renderer, InGameChat + Shift, ChatRect.x + Display_Y*0.01, ChatRect.y + ChatRect.h / 5.0, Display_Y*0.02, ChatRect.w - Display_Y*0.013, TextColor) == -1) {
	//			Shift++;
	//		}
	//		SDL_RenderPresent(renderer);
	//		printf("render	");
	//		textinput = false;
	//		continue;
	//	}
	//	if (UpdateSlider(StrongSlider, &event) == true) {
	//		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	//		SDL_Rect rect = { StrongSlider->Bar.x - StrongSlider->Box.w / 2.0, StrongSlider->Box.y, StrongSlider->Bar.w + StrongSlider->Box.w, StrongSlider->Box.h };
	//		SDL_RenderFillRect(renderer, &rect);
	//		DrawSlider(renderer, StrongSlider);
	//		SDL_Rect rect1 = { Sample.x - MaxStrong / 2.0,Sample.y - MaxStrong / 2.0,MaxStrong + 2,MaxStrong + 2 };
	//		SDL_RenderFillRect(renderer, &rect1);
	//		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//		if (canvas->Flag == ERASER) {
	//			canvas->Strong *= EraserStrong / 70.0;
	//			SDL_Rect rect2 = { Sample.x - canvas->Strong / 2.0,Sample.y - canvas->Strong / 2.0,canvas->Strong,canvas->Strong };
	//			SDL_RenderDrawRect(renderer, &rect2);
	//			SDL_RenderPresent(renderer);
	//			printf("render	");
	//		}
	//		else if (canvas->Flag == PENCIL) {
	//			canvas->Strong *= PencilStrong / 70.0;
	//			FillCircle(renderer, Sample.x, Sample.y, canvas->Strong / 2.0 + 1);
	//			SDL_SetRenderDrawColor(renderer, canvas->Color.r, canvas->Color.g, canvas->Color.b, 0);
	//			FillCircle(renderer, Sample.x, Sample.y, canvas->Strong / 2.0);
	//			SDL_RenderPresent(renderer);
	//			printf("render	");
	//		}
	//		continue;
	//	}
	//	if (ChangeColor(&event, &canvas->Color, RgbRect) == 1) {
	//		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//		if (canvas->Flag == ERASER) {
	//			SDL_Rect rect2 = { Sample.x - canvas->Strong / 2.0,Sample.y - canvas->Strong / 2.0,canvas->Strong,canvas->Strong };
	//			SDL_RenderDrawRect(renderer, &rect2);
	//			SDL_RenderPresent(renderer);
	//			printf("render	");
	//		}
	//		else if (canvas->Flag == PENCIL) {
	//			FillCircle(renderer, Sample.x, Sample.y, canvas->Strong / 2.0 + 1);
	//			SDL_SetRenderDrawColor(renderer, canvas->Color.r, canvas->Color.g, canvas->Color.b, 0);
	//			FillCircle(renderer, Sample.x, Sample.y, canvas->Strong / 2.0);
	//			SDL_RenderPresent(renderer);
	//			printf("render	");
	//		}
	//		continue;
	//	}
	//	if (UpdateButton(PencilButton, &event) == 1) {
	//		DrawButton(PencilButton);
	//		if (PencilButton->Flag == ACTIVATED) {
	//			EraserButton->Flag = DEACTIVATED;
	//			DrawButton(EraserButton);
	//			canvas->Flag = PENCIL;
	//			canvas->Strong = SDL_floor((float)canvas->Strong*PencilStrong / EraserStrong);
	//			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	//			SDL_Rect rect1 = { Sample.x - MaxStrong / 2.0,Sample.y - MaxStrong / 2.0,MaxStrong + 2,MaxStrong + 2 };
	//			SDL_RenderFillRect(renderer, &rect1);
	//			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//			FillCircle(renderer, Sample.x, Sample.y, canvas->Strong / 2.0 + 1);
	//			SDL_SetRenderDrawColor(renderer, canvas->Color.r, canvas->Color.g, canvas->Color.b, 0);
	//			FillCircle(renderer, Sample.x, Sample.y, canvas->Strong / 2.0);
	//		}
	//		SDL_RenderPresent(renderer);
	//		printf("render	");
	//		continue;
	//	}
	//	if (UpdateButton(EraserButton, &event) == 1) {
	//		DrawButton(EraserButton);
	//		if (EraserButton->Flag == ACTIVATED) {
	//			PencilButton->Flag = DEACTIVATED;
	//			DrawButton(PencilButton);
	//			canvas->Flag = ERASER;
	//			canvas->Strong = SDL_floor((float)canvas->Strong*EraserStrong / PencilStrong);
	//			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	//			SDL_Rect rect1 = { Sample.x - MaxStrong / 2.0,Sample.y - MaxStrong / 2.0,MaxStrong + 2,MaxStrong + 2 };
	//			SDL_RenderFillRect(renderer, &rect1);
	//			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//			SDL_Rect rect2 = { Sample.x - canvas->Strong / 2.0,Sample.y - canvas->Strong / 2.0,canvas->Strong,canvas->Strong };
	//			SDL_RenderDrawRect(renderer, &rect2);
	//		}
	//		SDL_RenderPresent(renderer);
	//		printf("render	");
	//		continue;
	//	}
	//	if (UpdateButton(NewButton, &event) == 1) {
	//		DrawButton(NewButton);
	//		SDL_RenderPresent(renderer);
	//		if (NewButton->Flag == ACTIVATED) {
	//			SDL_Delay(100);
	//			canvas->Flag = PENCIL;
	//			PencilButton->Flag = ACTIVATED;
	//			EraserButton->Flag = DEACTIVATED;
	//			NewButton->Flag = HIGHLIGHT;
	//			SDL_SetRenderDrawColor(canvas->Renderer, 255, 255, 255, 0);
	//			SDL_RenderFillRect(canvas->Renderer, &canvas->Rect);
	//			canvas->Strong = SDL_floor((float)canvas->Strong*PencilStrong / EraserStrong);
	//			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	//			SDL_Rect rect1 = { Sample.x - MaxStrong / 2.0,Sample.y - MaxStrong / 2.0,MaxStrong + 2,MaxStrong + 2 };
	//			SDL_RenderFillRect(renderer, &rect1);
	//			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	//			FillCircle(renderer, Sample.x, Sample.y, canvas->Strong / 2.0 + 1);
	//			SDL_SetRenderDrawColor(renderer, canvas->Color.r, canvas->Color.g, canvas->Color.b, 0);
	//			FillCircle(renderer, Sample.x, Sample.y, canvas->Strong / 2.0);
	//		}
	//		DrawButton(NewButton);
	//		DrawButton(EraserButton);
	//		DrawButton(PencilButton);
	//		SDL_RenderPresent(renderer);
	//		printf("render	");
	//		continue;
	//	}
	//	if (UpdateButton(MagButton, &event) == 1) {
	//		DrawButton(MagButton);
	//		SDL_RenderPresent(renderer);
	//		if (MagButton->Flag == ACTIVATED) {
	//			MagButton->Flag = HIGHLIGHT;
	//			SDL_Delay(100);
	//		}
	//		DrawButton(MagButton);
	//		SDL_RenderPresent(renderer);
	//		printf("render	");
	//		continue;
	//	}
	//	if (UpdateButton(RecycleButton, &event) == 1) {
	//		DrawButton(RecycleButton);
	//		SDL_RenderPresent(renderer);
	//		if (RecycleButton->Flag == ACTIVATED) {
	//			RecycleButton->Flag = HIGHLIGHT;
	//			SDL_Delay(100);
	//		}
	//		DrawButton(RecycleButton);
	//		SDL_RenderPresent(renderer);
	//		printf("render	");
	//		continue;
	//	}
	//	if (UpdateButton(PassButton, &event) == 1) {
	//		DrawButton(PassButton);
	//		SDL_RenderPresent(renderer);
	//		if (PassButton->Flag == ACTIVATED) {
	//			PassButton->Flag = HIGHLIGHT;
	//			SDL_Delay(100);
	//		}
	//		DrawButton(PassButton);
	//		SDL_RenderPresent(renderer);
	//		printf("render	");
	//		continue;
	//	}
	//	if (PutButtonWithImage(renderer, EnterTexture, HEnterTexture, NULL, EnterRect.x, EnterRect.y, EnterRect.w, EnterRect.h, &event, &Enter)) {
	//		if (Enter == ACTIVATED) {
	//			wcscpy(InGameChat, L"");
	//			Enter = HIGHLIGHT;
	//		}
	//		SDL_RenderPresent(renderer);
	//		printf("render   ");
	//		continue;
	//	}
	//}
	//return 0;

	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)Thread_MySQL, (void *)&status, 0, 0);
	Mix_FadeInMusic(mainmusic, -1, 3000);

	while (roop)
	{


		roop = 0;

		while (!quit && !loginsuccess)
		{
			SDL_WaitEvent(&event);

			switch (event.type) {
			case SDL_KEYDOWN:
				PressButton = 1;
				break;
			case SDL_MOUSEBUTTONDOWN:
				PressButton = 1;
				break;
			case SDL_QUIT:
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
			//	}
			RenderTextureXYWH(renderer, TitleImage, 0, 0, Display_X, Display_Y);
			RenderTextureXYWH(renderer, TitleText, Display_X / 4, Display_Y / 10, Display_X / 2, Display_Y / 3);
			PutText(renderer, version, 20, (Display_Y / 20) * 19, Display_X / 48, 255, 255, 255, 1);

			if (status.ishappen == false)
				RenderTextureXYWH(renderer, LoadingBar, 0, Display_Y / 1.3, Display_X, Display_Y / 15);
			else {
				RenderTextureXYWH(renderer, WaitBar, 0, Display_Y / 1.3, Display_X, Display_Y / 15);
				if (PressButton)	//계속하려면 클릭하세요 버튼을 누를때
				{
					warning.ison = 0;
					cons = status.arg;
					ID_INPUT = 1;
					PASSWORD_INPUT = 0;
					loginpopup = true;
					autologin_checking = 0;
					SDL_Texture * autologin_noclick = LoadTexture(renderer, ".\\login\\autologin1.png");
					SDL_Texture * autologin_click = LoadTexture(renderer, ".\\login\\autologin2.png");
					SDL_Texture * login_base = LoadTexture(renderer, ".\\login\\base.png");
					SDL_Texture * login_close_noclick = LoadTexture(renderer, ".\\login\\close1.png");
					SDL_Texture * login_close_click = LoadTexture(renderer, ".\\login\\close2.png");
					SDL_Texture * login_input_id_noclick = LoadTexture(renderer, ".\\login\\ID1.png");
					SDL_Texture * login_input_id_click = LoadTexture(renderer, ".\\login\\ID2.png");
					SDL_Texture * login_button_id_noclick = LoadTexture(renderer, ".\\login\\loginbutton1.png");
					SDL_Texture * login_button_id_click = LoadTexture(renderer, ".\\login\\loginbutton2.png");
					SDL_Texture * autologin_check = LoadTexture(renderer, ".\\login\\loginbuttonup.png");
					SDL_Texture * login_findpassword_noclick = LoadTexture(renderer, ".\\login\\repassword1.png");
					SDL_Texture * login_findpassword_click = LoadTexture(renderer, ".\\login\\repassword2.png");
					SDL_Texture * login_signup_noclick = LoadTexture(renderer, ".\\login\\signup1.png");
					SDL_Texture * login_signup_click = LoadTexture(renderer, ".\\login\\signup2.png");
					if (myuser != 0)
					{
						free(myuser);
						myuser = 0;

					}
					int dkdk = 0;
					memset(&ID_put, 0, sizeof(ID_put));
					memset(&Password_put, 0, sizeof(Password_put));
					myuser = IsAutoLogin(cons);
					if (myuser != 0)
					{
						myuser->id[strlen(myuser->id)] = 0;
						han2unicode(myuser->id, ID_put);
						pass_length = myuser->pass_length;
						autologin_checking = 1;
						myuser->password[strlen(myuser->password)] = 0;
						//printf("%s", myuser->password);

						han2unicode(myuser->password, Password_put);
					}
					while (loginpopup && !loginsuccess)
					{
						////printf("%d\n", dkdk++);
						SDL_WaitEvent(&event);
						switch (event.type)
						{
						case SDL_TEXTINPUT: // 채팅 입력 이벤트
							if (hanyeong == true && (event.text.text[0] == -29 || event.text.text[0] + 256 >= 234 && event.text.text[0] + 256 <= 237))// 한글일 경우
							{
								wcscpy(wchar, L"");
								sum = (event.text.text[0] + 22) * 64 * 64 + (event.text.text[1] + 128) * 64 + event.text.text[2] + 41088;
								wchar[0] = sum;
								if (ID_INPUT == 1)
									wcscat(ID_put, wchar);
								else if (PASSWORD_INPUT)
									wcscat(Password_put, wchar);

								if (event.text.text[0] == -29)
									slice = 1;
								else
									slice = 1 + !((wchar[0] - 0xac00) % 28);
							}
							else if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {// 영어 입력 시
								wcscpy(wchar, L"");
								swprintf(wchar, sizeof(wchar) / sizeof(wchar_t), L"%hs", event.text.text);// event.text.text 문자열 그냥 연결시켜버림
								if (ID_INPUT == 1)
									wcscat(ID_put, wchar);
								else if (PASSWORD_INPUT)
									wcscat(Password_put, wchar);
								hangeul = false;
								slice = 0;
							}
							textinput = true;
							break;
						case SDL_KEYDOWN:
							if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
								if (hangeul == true && enter == false)
									enter = true;
								else {
									if (ID_INPUT == 1)
									{
										PASSWORD_INPUT = 1;
										ID_INPUT = 0;

									}
									else if (PASSWORD_INPUT == 1 || pass_length > 0) {
										strcpy(utf8, UNICODE2UTF8(ID_put, wcslen(ID_put)));
										UTF82EUCKR(db_id, 512, utf8, 768);
										db_id[strlen(db_id)] = '\0';
										strcpy(utf8, UNICODE2UTF8(Password_put, wcslen(Password_put)));
										UTF82EUCKR(db_password, 512, utf8, 768);
										db_password[strlen(db_password)] = '\0';
										myuser = User_Login_sql(cons, db_id, db_password);
										if (myuser == -1)
										{
											//	//printf("\n아이디 오류");
											warning.ison = 1;
											strcpy(warning.message, "아이디가 틀립니다");
											warning.size = 20;
											warning.x = Display_X / 4 + 130;
											warning.y = Display_Y / 4 + 80;
											warning.r = 255;
											warning.g = 0;
											warning.b = 0;

										}
										else if (myuser == 0)
										{
											//	//printf("\n비밀번호 오류");
											warning.ison = 1;
											strcpy(warning.message, "비밀번호가 틀립니다");
											warning.size = 20;
											warning.x = Display_X / 4 + 130;
											warning.y = Display_Y / 4 + 180;
											warning.r = 255;
											warning.g = 0;
											warning.b = 0;
										}
										else {
											sprintf(query, "update user set auto_login = 'not' where auto_login = PASSWORD('%s')", GetDefaultMyIP());
											if (mysql_query(cons, query) == 0);
											if (autologin_checking == 1) {
												sprintf(query, "update user set auto_login = PASSWORD('%s') where ownnum = %d", GetDefaultMyIP(), myuser->ownnum);
												if (mysql_query(cons, query) == 0)
													loginsuccess = true;
												else
												{
													warning.ison = 1;
													strcpy(warning.message, "자동 로그인 등록 실패");
													warning.size = 15;
													warning.x = Display_X / 4 + 220;
													warning.y = Display_Y / 4 + 290;
													warning.r = 255;
													warning.g = 0;
													warning.b = 0;

												}
											}
											else {
												loginsuccess = true;
											}
										}
										enter = false;
										textinput = true;
									}
								}
							}
							else if (event.key.keysym.sym == SDLK_RALT)
								hanyeong = !(hanyeong);
							else if (event.key.keysym.sym == SDLK_BACKSPACE && (ID_INPUT ? wcslen(ID_put) > 0 : (PASSWORD_INPUT ? wcslen(Password_put) > 0 : 0)))// 키보드 백스페이스고 배열의 길이가 1이상일때
							{
								if (slice == 0) {
									//		printf("\nslice아니 상태");
									if (ID_INPUT == 1)
										ID_put[wcslen(ID_put) - 1] = '\0';
									else if (PASSWORD_INPUT == 1)
										Password_put[wcslen(Password_put) - 1] = '\0';
									textinput = true;
								}
								else {
									//		printf("\nslice상태");
									slice--;
								}
							}
							else if (event.key.keysym.sym == SDLK_TAB)
							{
								if (hangeul == true && enter == false)
									enter = true;
								else {
									if (ID_INPUT) {
										ID_INPUT = 0;
										PASSWORD_INPUT = 1;
									}
								}
							}

							else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {// 컨트롤 모드이고 c를 눌렀다면
								if (ID_INPUT)
								{
									strcpy(utf8, UNICODE2UTF8(ID_put, wcslen(ID_put)));
									SDL_SetClipboardText(utf8);// 클립보드에 넣음
								}
							}
							else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {// 컨트롤 모드이고 v를 눌렀다면
								if (ID_INPUT)
									wcscat(ID_put, UTF82UNICODE(SDL_GetClipboardText(), strlen(SDL_GetClipboardText())));// 클립보드에서 가져옴

								hangeul = false;
								textinput = true;
							}
							else {
								hangeul = true;
								slice++;
							}
							break;
						case SDL_MOUSEBUTTONUP:
							break;
						case SDL_MOUSEMOTION:
							break;
						case SDL_QUIT:
							quit = true;
							break;
						case SDL_WINDOWEVENT:
							switch (event.window.event) {
							case SDL_WINDOWEVENT_CLOSE:// 다수 창에서의 닫기이벤트가 발생할경우
								loginpopup = false;// 팝업창을 닫음
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

						RenderTextureXYWH(renderer, login_base, Display_X / 4, Display_Y / 4, 666, 411);
						if (PutButtonImage(renderer, login_close_noclick, login_close_click, Display_X / 4 + 565, Display_Y / 4, 101, 83, &event, &happen)) {
							MouseUP_Wait;
							loginpopup = false;
						}
						if (ID_INPUT == 0) {	//아이디 입력창
							if (PutButtonImage(renderer, login_input_id_noclick, login_input_id_noclick, Display_X / 4 + 22, Display_Y / 4 + 110, 617, 63, &event, &happen))
							{
								ID_INPUT = 1;
								PASSWORD_INPUT = 0;
							}
						}
						else
							RenderTextureXYWH(renderer, login_input_id_click, Display_X / 4 + 22, Display_Y / 4 + 110, 617, 63);

						if (PASSWORD_INPUT == 0) {	//비밀번호 입력창
							if (PutButtonImage(renderer, login_input_id_noclick, login_input_id_noclick, Display_X / 4 + 22, Display_Y / 4 + 208, 617, 63, &event, &happen))
							{
								ID_INPUT = 0;
								PASSWORD_INPUT = 1;
							}
						}
						else
							RenderTextureXYWH(renderer, login_input_id_click, Display_X / 4 + 22, Display_Y / 4 + 208, 617, 63);
						if (pass_length != 0)
						{
							if (autologin_checking == 1) {
								ID_INPUT = 0;
								PASSWORD_INPUT = 0;
							}
						}
						if (PutButtonImage(renderer, login_button_id_noclick, login_button_id_click, Display_X / 4 + 489, Display_Y / 4 + 273, 147, 71, &event, &happen))	//로그인 버튼
						{
							strcpy(utf8, UNICODE2UTF8(ID_put, wcslen(ID_put)));
							UTF82EUCKR(db_id, 512, utf8, 768);
							db_id[strlen(db_id)] = '\0';
							strcpy(utf8, UNICODE2UTF8(Password_put, wcslen(Password_put)));
							UTF82EUCKR(db_password, 512, utf8, 768);
							db_password[strlen(db_password)] = '\0';
							if (myuser != 0 && myuser != -1) {

								free(myuser);
								myuser = NULL;
							}
							myuser = User_Login_sql(cons, db_id, db_password);
							if (myuser == -1)
							{
								//printf("\n아이디 오류");
								warning.ison = 1;
								strcpy(warning.message, "아이디가 틀립니다");
								warning.size = 20;
								warning.x = Display_X / 4 + 130;
								warning.y = Display_Y / 4 + 80;
								warning.r = 255;
								warning.g = 0;
								warning.b = 0;
								myuser = NULL;

							}
							else if (myuser == 0)
							{
								//printf("\n비밀번호 오류");
								warning.ison = 1;
								strcpy(warning.message, "비밀번호가 틀립니다");
								warning.size = 20;
								warning.x = Display_X / 4 + 130;
								warning.y = Display_Y / 4 + 180;
								warning.r = 255;
								warning.g = 0;
								warning.b = 0;
							}
							else {
								if (autologin_checking == 1) {
									sprintf(query, "update user set auto_login = PASSWORD('%s') where ownnum = %d", GetDefaultMyIP(), myuser->ownnum);
									if (mysql_query(cons, query) == 0) {
										Mix_FadeInMusic(lobbymusic, -1, 3000);
										loginsuccess = true;
									}
									else
									{
										//printf("\n자동 로그인 오류");
										warning.ison = 1;
										strcpy(warning.message, "자동 로그인 등록 실패");
										warning.size = 15;
										warning.x = Display_X / 4 + 220;
										warning.y = Display_Y / 4 + 290;
										warning.r = 255;
										warning.g = 0;
										warning.b = 0;

									}
								}
								else {
									Mix_FadeInMusic(lobbymusic, -1, 3000);
									loginsuccess = true;
								}
							}
						}

						if (PutButtonImage(renderer, autologin_noclick, autologin_click, Display_X / 4 + 40, Display_Y / 4 + 280, 194, 47, &event, &happen))	//자동로그인 체크박스
						{
							MouseUP_Wait;
							if (autologin_checking == 0)
								autologin_checking = 1;
							else if (pass_length > 0)
							{
								memset(&Password_put, 0, sizeof(Password_put));
								autologin_checking = 0;
								pass_length = 0;
							}
							else
								autologin_checking = 0;
						}
						if (autologin_checking == 1)		//로그인 체크
						{
							RenderTextureXYWH(renderer, autologin_check, Display_X / 4 + 23, Display_Y / 4 + 255, 211, 80);
						}
						if (PutButtonImage(renderer, login_signup_noclick, login_signup_click, Display_X / 4 + 85, Display_Y / 4 + 335, 182, 71, &event, &happen))	//회원가입 버튼
						{
							MouseUP_Wait;
							RESET(&change_password);
							create_password_status = 1;
							pass_reset_mode = 1;
							SDL_Texture * create_back = LoadTexture(renderer, ".\\login\\signupbase.png");
							SDL_Texture * create_ID_noclick = LoadTexture(renderer, ".\\login\\ID1.png");
							SDL_Texture * create_ID_click = LoadTexture(renderer, ".\\login\\ID2.png");
							SDL_Texture * create_button_noclick = LoadTexture(renderer, ".\\login\\signupbutton1.png");
							SDL_Texture * create_button_click = LoadTexture(renderer, ".\\login\\signupbutton2.png");
							SDL_Texture * create_father_noclick = LoadTexture(renderer, ".\\login\\fathername1.png");
							SDL_Texture * create_father_click = LoadTexture(renderer, ".\\login\\fathername2.png");
							while (create_password_status)
							{
								SDL_WaitEvent(&event);
								switch (event.type)
								{
								case SDL_TEXTINPUT: // 채팅 입력 이벤트
									if (hanyeong == true && (event.text.text[0] == -29 || event.text.text[0] + 256 >= 234 && event.text.text[0] + 256 <= 237))// 한글일 경우
									{
										wcscpy(wchar, L"");
										int sum = (event.text.text[0] + 22) * 64 * 64 + (event.text.text[1] + 128) * 64 + event.text.text[2] + 41088;
										wchar[0] = sum;

										if (event.text.text[0] == -29)
											slice = 1;
										else
											slice = 1 + !((wchar[0] - 0xac00) % 28);
									}
									else if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {// 영어 입력 시
										wcscpy(wchar, L"");
										swprintf(wchar, sizeof(wchar) / sizeof(wchar_t), L"%hs", event.text.text);// event.text.text 문자열 그냥 연결시켜버림

										hangeul = false;
										slice = 0;
									}
									textinput = true;
									break;
								case SDL_KEYDOWN:
									if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
										if (hangeul == true && enter == false)
											enter = true;
										else {

											if (pass_reset_mode < 5)
												pass_reset_mode += 1;
											else
											{
												warning.ison = 0;
												if (wcscmp(change_password[1], change_password[2]) != 0)
												{
													warning.ison = 1;
													warning.r = 255;
													warning.g = 0;
													warning.b = 0;
													strcpy(warning.message, "비밀번호가 틀립니다");
													warning.size = 20;
													warning.x = Display_X / 4 + 250;
													warning.y = Display_Y / 4 + 270;

												}
												else if (wcslen(change_password[1]) < 4)
												{
													warning.ison = 1;
													warning.r = 255;
													warning.g = 0;
													warning.b = 0;
													strcpy(warning.message, "비밀번호는 최소 4글자 이상으로 해주세요");
													warning.size = 20;
													warning.x = Display_X / 4 + 250;
													warning.y = Display_Y / 4 + 270;
												}
												else
												{

													i = User_Signin_sql(cons, change_password[0], change_password[1], change_password[3], change_password[4]);
													if (i == 0)
													{
														warning.ison = 1;
														warning.r = 255;
														warning.g = 0;
														warning.b = 0;
														strcpy(warning.message, "해당 ID가 존재합니다");
														warning.size = 20;
														warning.x = Display_X / 4 + 150;
														warning.y = Display_Y / 4 + 80;
													}
													else if (i == -1) {

														warning.ison = 1;
														warning.r = 255;
														warning.g = 0;
														warning.b = 0;
														strcpy(warning.message, "등록 실패");
														warning.size = 17;
														warning.x = Display_X / 4 + 480;
														warning.y = Display_Y / 4 + 450;
													}
													else if (i == -2) {

														warning.ison = 1;
														warning.r = 255;
														warning.g = 0;
														warning.b = 0;
														strcpy(warning.message, "해당 닉네임이 존재합니다.");
														warning.size = 17;
														warning.x = Display_X / 4 + 300;
														warning.y = Display_Y / 4 + 365;
													}
													else
													{
														memset(&change_password, 0, sizeof(change_password));
														create_password_status = 0;
														warning.ison = 1;
														warning.r = 0;
														warning.g = 0;
														warning.b = 0;
														strcpy(warning.message, "성공");
														warning.size = 20;
														warning.x = Display_X / 4 + 470;
														warning.y = Display_Y / 4 + 70;
													}
												}
											}
											enter = false;
											//textinput = true;
										}
									}
									else if (event.key.keysym.sym == SDLK_TAB)
									{
										if (hangeul == true && enter == false)
											enter = true;
										else {
											if (pass_reset_mode < 5)
												pass_reset_mode += 1;
										}
									}
									else if (event.key.keysym.sym == SDLK_RALT)
										hanyeong = !(hanyeong);
									else if (event.key.keysym.sym == SDLK_BACKSPACE && wcslen(change_password[pass_reset_mode - 1]) > 0)// 키보드 백스페이스고 배열의 길이가 1이상일때
									{
										backspacehappen = true;
									}
									else {
										hangeul = true;
										slice++;
									}
								case SDL_QUIT:
									quit = true;
									break;
								case SDL_WINDOWEVENT:
									switch (event.window.event) {
									case SDL_WINDOWEVENT_CLOSE:// 다수 창에서의 닫기이벤트가 발생할경우
										SDL_DestroyTexture(create_button_noclick);
										create_password_status = false;// 팝업창을 닫음
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

								RenderTextureXYWH(renderer, create_back, Display_X / 4, Display_Y / 4, 666, 570);
								if (PutButtonImage(renderer, login_close_noclick, login_close_click, Display_X / 4 + 565, Display_Y / 4, 101, 83, &event, &happen))
									create_password_status = false;
								if (PutButtonImage(renderer, create_button_noclick, create_button_click, Display_X / 4 + 480, Display_Y / 4 + 495, 166, 71, &event, &happen)) {
									warning.ison = 0;
									if (wcscmp(change_password[1], change_password[2]) != 0)
									{
										warning.ison = 1;
										warning.r = 255;
										warning.g = 0;
										warning.b = 0;
										strcpy(warning.message, "비밀번호가 틀립니다");
										warning.size = 20;
										warning.x = Display_X / 4 + 250;
										warning.y = Display_Y / 4 + 270;

									}
									else if (wcslen(change_password[1]) < 4)
									{
										warning.ison = 1;
										warning.r = 255;
										warning.g = 0;
										warning.b = 0;
										strcpy(warning.message, "비밀번호는 최소 4글자 이상으로 해주세요");
										warning.size = 20;
										warning.x = Display_X / 4 + 250;
										warning.y = Display_Y / 4 + 270;
									}
									else
									{

										i = User_Signin_sql(cons, change_password[0], change_password[1], change_password[3], change_password[4]);
										if (i == 0)
										{
											warning.ison = 1;
											warning.r = 255;
											warning.g = 0;
											warning.b = 0;
											strcpy(warning.message, "해당 ID가 존재합니다");
											warning.size = 20;
											warning.x = Display_X / 4 + 150;
											warning.y = Display_Y / 4 + 80;
										}
										else if (i == -1) {

											warning.ison = 1;
											warning.r = 255;
											warning.g = 0;
											warning.b = 0;
											strcpy(warning.message, "등록 실패");
											warning.size = 17;
											warning.x = Display_X / 4 + 480;
											warning.y = Display_Y / 4 + 450;
										}
										else if (i == -2) {

											warning.ison = 1;
											warning.r = 255;
											warning.g = 0;
											warning.b = 0;
											strcpy(warning.message, "해당 닉네임이 존재합니다.");
											warning.size = 17;
											warning.x = Display_X / 4 + 300;
											warning.y = Display_Y / 4 + 365;
										}
										else
										{
											memset(&change_password, 0, sizeof(change_password));
											create_password_status = 0;
											warning.ison = 1;
											warning.r = 0;
											warning.g = 0;
											warning.b = 0;
											strcpy(warning.message, "성공");
											warning.size = 20;
											warning.x = Display_X / 4 + 470;
											warning.y = Display_Y / 4 + 70;
										}
									}
								}


								for (i = 1; i <= 4; i++)
								{
									if (pass_reset_mode != i) {
										if (PutButtonImage(renderer, create_ID_noclick, create_ID_noclick, Display_X / 4 + 22, Display_Y / 4 + 15 + (95 * i), 617, 63, &event, &happen))
										{
											pass_reset_mode = i;
										}
									}
									else {
										RenderTextureXYWH(renderer, create_ID_click, Display_X / 4 + 22, Display_Y / 4 + 15 + (95 * i), 617, 63);
									}

								}
								if (pass_reset_mode != 5)
								{
									if (PutButtonImage(renderer, create_father_noclick, create_father_noclick, Display_X / 4 + 25, Display_Y / 4 + 493, 428, 64, &event, &happen))
										pass_reset_mode = 5;
								}
								else
								{
									RenderTextureXYWH(renderer, create_father_click, Display_X / 4 + 25, Display_Y / 4 + 493, 428, 64);
								}
								for (i = 1; i <= 5; i++)
								{
									if (pass_reset_mode == i)
									{
										if (textinput == true) {
											wcscat(change_password[i - 1], wchar);
											textinput = false;
										}
										if (backspacehappen == true) {
											if (slice == 0) {
												change_password[i - 1][wcslen(change_password[i - 1]) - 1] = '\0';
											}
											else {
												slice--;
											}
											backspacehappen = false;
										}
									}
									if (!(i == 2 || i == 3))
										PutText_Unicode(renderer, change_password[i - 1], Display_X / 4 + 40, Display_Y / 4 + 30 + (95 * i), 25, color, 1);
									else
									{
										for (j = 0; j < wcslen(change_password[i - 1]); j++)
											query[j] = '*';
										query[j] = 0;
										PutText(renderer, query, Display_X / 4 + 40, Display_Y / 4 + 30 + (95 * i), 25, 0, 0, 0, 1);
									}
								}
								if (warning.ison == 1)
								{
									PutText(renderer, warning.message, warning.x, warning.y, warning.size, warning.r, warning.g, warning.b, 1);
								}

								SDL_RenderPresent(renderer);

							}
							if (warning.r == 255)
								warning.ison = 0;
							RenderTextureXYWH(renderer, TitleImage, 0, 0, Display_X, Display_Y);
							RenderTextureXYWH(renderer, TitleText, Display_X / 4, Display_Y / 10, Display_X / 2, Display_Y / 4);
							PutText(renderer, version, 20, (Display_Y / 20) * 19, Display_X / 48, 255, 255, 255, 1);
							SDL_DestroyTexture(create_back);
							SDL_DestroyTexture(create_ID_click);
							SDL_DestroyTexture(create_ID_noclick);
							SDL_DestroyTexture(create_button_click);
							SDL_DestroyTexture(create_button_noclick);
							SDL_DestroyTexture(create_father_click);
							SDL_DestroyTexture(create_father_noclick);
						}
						if (PutButtonImage(renderer, login_findpassword_noclick, login_findpassword_click, Display_X / 4 + 305, Display_Y / 4 + 335, 269, 71, &event, &happen))
						{
							MouseUP_Wait;
							memset(&change_password, 0, sizeof(change_password));
							find_password_status = 1;
							pass_reset_mode = 1;
							SDL_Texture * find_back = LoadTexture(renderer, ".\\login\\repasswordbase.png");
							SDL_Texture * find_ID_noclick = LoadTexture(renderer, ".\\login\\ID1.png");
							SDL_Texture * find_ID_click = LoadTexture(renderer, ".\\login\\ID2.png");
							SDL_Texture * find_button_noclick = LoadTexture(renderer, ".\\login\\resetting1.png");
							SDL_Texture * find_button_click = LoadTexture(renderer, ".\\login\\resetting2.png");
							SDL_Texture * find_father_noclick = LoadTexture(renderer, ".\\login\\fathername1.png");
							SDL_Texture * find_father_click = LoadTexture(renderer, ".\\login\\fathername2.png");
							warning.ison = 0;
							while (find_password_status)
							{
								SDL_WaitEvent(&event);
								switch (event.type)
								{
								case SDL_TEXTINPUT: // 채팅 입력 이벤트
									if (hanyeong == true && (event.text.text[0] == -29 || event.text.text[0] + 256 >= 234 && event.text.text[0] + 256 <= 237))// 한글일 경우
									{
										wcscpy(wchar, L"");
										int sum = (event.text.text[0] + 22) * 64 * 64 + (event.text.text[1] + 128) * 64 + event.text.text[2] + 41088;
										wchar[0] = sum;

										if (event.text.text[0] == -29)
											slice = 1;
										else
											slice = 1 + !((wchar[0] - 0xac00) % 28);
									}
									else if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {// 영어 입력 시
										wcscpy(wchar, L"");
										swprintf(wchar, sizeof(wchar) / sizeof(wchar_t), L"%hs", event.text.text);// event.text.text 문자열 그냥 연결시켜버림

										hangeul = false;
										slice = 0;
									}
									textinput = true;
									break;
								case SDL_KEYDOWN:
									if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
										if (hangeul == true && enter == false)
											enter = true;
										else {

											if (pass_reset_mode < 4)
												pass_reset_mode += 1;
											else
											{
												if (wcscmp(change_password[1], change_password[2]) != 0)
												{
													warning.ison = 1;
													warning.r = 255;
													warning.g = 0;
													warning.b = 0;
													strcpy(warning.message, "비밀번호가 틀립니다");
													warning.size = 20;
													warning.x = Display_X / 4 + 250;
													warning.y = Display_Y / 4 + 270;

												}
												else if (wcslen(change_password[1]) < 4)
												{
													warning.ison = 1;
													warning.r = 255;
													warning.g = 0;
													warning.b = 0;
													strcpy(warning.message, "비밀번호는 최소 4글자 이상으로 해주세요");
													warning.size = 20;
													warning.x = Display_X / 4 + 250;
													warning.y = Display_Y / 4 + 270;
												}
												else
												{

													i = Password_Change_sql(cons, change_password[0], change_password[1], change_password[3]);
													if (i == -1)
													{
														warning.ison = 1;
														warning.r = 255;
														warning.g = 0;
														warning.b = 0;
														strcpy(warning.message, "해당 ID가 없습니다");
														warning.size = 20;
														warning.x = Display_X / 4 + 150;
														warning.y = Display_Y / 4 + 80;
													}
													if (i == 0) {
														warning.ison = 1;
														warning.r = 255;
														warning.g = 0;
														warning.b = 0;
														strcpy(warning.message, "질문의 답이 틀렸습니다");
														warning.size = 17;
														warning.x = Display_X / 4 + 470;
														warning.y = Display_Y / 4 + 370;
													}
													if (i == -2) {
														warning.ison = 1;
														warning.r = 255;
														warning.g = 0;
														warning.b = 0;
														strcpy(warning.message, "알수 없는 오류");
														warning.size = 17;
														warning.x = Display_X / 4 + 470;
														warning.y = Display_Y / 4 + 370;
													}
													if (i == 1)
													{
														warning.ison = 1;
														warning.r = 0;
														warning.g = 0;
														warning.b = 0;
														strcpy(warning.message, "성공");
														warning.size = 20;
														warning.x = Display_X / 4 + 470;
														warning.y = Display_Y / 4 + 80;
														memset(&change_password, 0, sizeof(change_password));
													}
												}
											}
											enter = false;
											//textinput = true;
										}

									}
									else if (event.key.keysym.sym == SDLK_TAB)
									{
										if (hangeul == true && enter == false)
											enter = true;
										else {
											if (pass_reset_mode < 4)
												pass_reset_mode += 1;
										}
									}
									else if (event.key.keysym.sym == SDLK_RALT)
										hanyeong = !(hanyeong);
									else if (event.key.keysym.sym == SDLK_BACKSPACE && wcslen(change_password[pass_reset_mode - 1]) > 0)// 키보드 백스페이스고 배열의 길이가 1이상일때
									{
										backspacehappen = true;
									}
									else {
										hangeul = true;
										slice++;
									}
								case SDL_QUIT:
									quit = true;
									break;
								case SDL_WINDOWEVENT:
									switch (event.window.event) {
									case SDL_WINDOWEVENT_CLOSE:// 다수 창에서의 닫기이벤트가 발생할경우
										SDL_DestroyTexture(find_button_noclick);
										find_password_status = false;// 팝업창을 닫음
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

								RenderTextureXYWH(renderer, find_back, Display_X / 4, Display_Y / 4, 666, 484);
								if (PutButtonImage(renderer, login_close_noclick, login_close_click, Display_X / 4 + 565, Display_Y / 4, 101, 83, &event, &happen))
									find_password_status = false;
								if (PutButtonImage(renderer, find_button_noclick, find_button_click, Display_X / 4 + 480, Display_Y / 4 + 400, 161, 71, &event, &happen))
								{
									if (wcscmp(change_password[1], change_password[2]) != 0)
									{
										warning.ison = 1;
										warning.r = 255;
										warning.g = 0;
										warning.b = 0;
										strcpy(warning.message, "비밀번호가 틀립니다");
										warning.size = 20;
										warning.x = Display_X / 4 + 250;
										warning.y = Display_Y / 4 + 270;

									}
									else if (wcslen(change_password[1]) < 4)
									{
										warning.ison = 1;
										warning.r = 255;
										warning.g = 0;
										warning.b = 0;
										strcpy(warning.message, "비밀번호는 최소 4글자 이상으로 해주세요");
										warning.size = 20;
										warning.x = Display_X / 4 + 250;
										warning.y = Display_Y / 4 + 270;
									}
									else
									{

										i = Password_Change_sql(cons, change_password[0], change_password[1], change_password[3]);
										if (i == -1)
										{
											warning.ison = 1;
											warning.r = 255;
											warning.g = 0;
											warning.b = 0;
											strcpy(warning.message, "해당 ID가 없습니다");
											warning.size = 20;
											warning.x = Display_X / 4 + 150;
											warning.y = Display_Y / 4 + 80;
										}
										if (i == 0) {
											warning.ison = 1;
											warning.r = 255;
											warning.g = 0;
											warning.b = 0;
											strcpy(warning.message, "질문의 답이 틀렸습니다");
											warning.size = 17;
											warning.x = Display_X / 4 + 470;
											warning.y = Display_Y / 4 + 370;
										}
										if (i == -2) {
											warning.ison = 1;
											warning.r = 255;
											warning.g = 0;
											warning.b = 0;
											strcpy(warning.message, "알수 없는 오류");
											warning.size = 17;
											warning.x = Display_X / 4 + 470;
											warning.y = Display_Y / 4 + 370;
										}
										if (i == 1)
										{
											warning.ison = 1;
											warning.r = 0;
											warning.g = 0;
											warning.b = 0;
											strcpy(warning.message, "성공");
											warning.size = 20;
											warning.x = Display_X / 4 + 470;
											warning.y = Display_Y / 4 + 80;
											memset(&change_password, 0, sizeof(change_password));
										}
									}
								}
								for (i = 1; i <= 3; i++)
								{
									if (pass_reset_mode != i) {
										if (PutButtonImage(renderer, find_ID_noclick, find_ID_noclick, Display_X / 4 + 22, Display_Y / 4 + 15 + (95 * i), 617, 63, &event, &happen))
										{
											pass_reset_mode = i;
										}
									}
									else {
										RenderTextureXYWH(renderer, find_ID_click, Display_X / 4 + 22, Display_Y / 4 + 15 + (95 * i), 617, 63);


									}

								}
								if (pass_reset_mode != 4)
								{
									if (PutButtonImage(renderer, find_father_noclick, find_father_noclick, Display_X / 4 + 25, Display_Y / 4 + 395, 428, 64, &event, &happen))
										pass_reset_mode = 4;
								}
								else
								{
									RenderTextureXYWH(renderer, find_father_click, Display_X / 4 + 25, Display_Y / 4 + 395, 428, 64);
								}
								for (i = 1; i <= 4; i++)
								{
									if (pass_reset_mode == i)
									{
										if (textinput == true) {
											wcscat(change_password[i - 1], wchar);
											textinput = false;
										}
										if (backspacehappen == true) {
											if (slice == 0) {
												change_password[i - 1][wcslen(change_password[i - 1]) - 1] = '\0';
											}
											else {
												slice--;
											}
											backspacehappen = false;
										}
									}
									if (!(i == 2 || i == 3))
										PutText_Unicode(renderer, change_password[i - 1], Display_X / 4 + 40, Display_Y / 4 + 30 + (95 * i), 25, color, 1);
									else
									{
										for (j = 0; j < wcslen(change_password[i - 1]); j++)
											query[j] = '*';
										query[j] = 0;
										PutText(renderer, query, Display_X / 4 + 40, Display_Y / 4 + 30 + (95 * i), 25, 0, 0, 0, 1);
									}
								}
								if (warning.ison == 1)
								{
									PutText(renderer, warning.message, warning.x, warning.y, warning.size, warning.r, warning.g, warning.b, 1);
								}

								SDL_RenderPresent(renderer);

							}
							RenderTextureXYWH(renderer, TitleImage, 0, 0, Display_X, Display_Y);
							RenderTextureXYWH(renderer, TitleText, Display_X / 4, Display_Y / 10, Display_X / 2, Display_Y / 4);
							PutText(renderer, version, 20, (Display_Y / 20) * 19, Display_X / 48, 255, 255, 255, 1);
							SDL_DestroyTexture(find_back);
							SDL_DestroyTexture(find_ID_click);
							SDL_DestroyTexture(find_ID_noclick);
							SDL_DestroyTexture(find_button_click);
							SDL_DestroyTexture(find_button_noclick);
							SDL_DestroyTexture(find_father_click);
							SDL_DestroyTexture(find_father_noclick);
							warning.ison = 0;
						}

						PutText_Unicode(renderer, ID_put, Display_X / 4 + 35, Display_Y / 4 + 117, 30, color, 1);
						if (pass_length == 0)
							for (i = 0; i < wcslen(Password_put); i++)
								query[i] = '*';
						else
							for (i = 0; i < pass_length; i++)
								query[i] = '*';
						query[i] = 0;
						PutText(renderer, query, Display_X / 4 + 35, Display_Y / 4 + 215, 30, 0, 0, 0, 1);

						textinput = false;
						if (warning.ison == 1)
						{
							PutText(renderer, warning.message, warning.x, warning.y, warning.size, warning.r, warning.g, warning.b, 1);
						}

						SDL_RenderPresent(renderer);


					}
					SDL_DestroyTexture(autologin_check);
					SDL_DestroyTexture(autologin_click);
					SDL_DestroyTexture(autologin_noclick);
					SDL_DestroyTexture(login_base);
					SDL_DestroyTexture(login_button_id_click);
					SDL_DestroyTexture(login_button_id_noclick);
					SDL_DestroyTexture(login_close_click);
					SDL_DestroyTexture(login_close_noclick);
					SDL_DestroyTexture(login_findpassword_click);
					SDL_DestroyTexture(login_findpassword_noclick);
					SDL_DestroyTexture(login_input_id_click);
					SDL_DestroyTexture(login_input_id_noclick);
					SDL_DestroyTexture(login_signup_click);
					SDL_DestroyTexture(login_signup_noclick);
					PressButton = 0;

				}
			}


			textinput = false;
			SDL_RenderPresent(renderer);

		}


		if (loginsuccess)
		{

			ZeroMemory(&ServerParam, sizeof(SockParam));
			ZeroMemory(&ClientParam, sizeof(SockParam));
			int allchating_cnt = 0;
			sprintf(query, "update user set status = 4 where ownnum = %d", myuser->ownnum);
			mysql_query(cons, query);
			Hit_Room rooms[20];
			int newdata[3] = { 1, 1, 1 };
			int roomcount = Get_Room_List(cons, rooms);
			int pastroomcount = roomcount;
			char MemBerList[30][30] = { 0, };
			int RefrashEvent = 1;

			Hit_Timer Refrash = { 0, };
			Refrash.event = &RefrashEvent;
			Refrash.time = 500;
			_beginthreadex(NULL, 0, (_beginthreadex_proc_type)HitMind_Timer, &Refrash, 0, NULL);
			Chating chatings[12] = { 0, };
			int usercount = 0;
			memset(&ID_put, 0, sizeof(ID_put));
			int chattingput = 0;
			int chattingdrag = 0;

			ClientParam.myuser = myuser;
			long long timer = SDL_GetTicks() % 1000;
			SDL_Texture * WaitRoom_setting_noclick = LoadTexture(renderer, ".\\design\\settingicon1.png");
			SDL_Texture * WaitRoom_setting_click = LoadTexture(renderer, ".\\design\\settingicon2.png");
			SDL_Texture * User_Pencil = LoadTexture(renderer, ".\\design\\pencil.png");
			SDL_Texture * Chating_noput = LoadTexture(renderer, ".\\design\\chatting1.png");
			SDL_Texture * Chating_put = LoadTexture(renderer, ".\\design\\chatting2.png");
			SDL_Texture * Chating_click = LoadTexture(renderer, ".\\design\\chattingput.png");
			SDL_Texture * Slider_Box = LoadTextureEx(renderer, ".\\design\\Box.png", 255, 255, 255);
			SDL_Texture * Room_Back_noclick = LoadTexture(renderer, ".\\design\\room1.png");
			SDL_Texture * Room_Back_click = LoadTexture(renderer, ".\\design\\room2.png");
			SDL_Texture * Slider_slider_up = LoadTexture(renderer, ".\\design\\slider_up.png");
			SDL_Texture * Room_Lock = LoadTexture(renderer, ".\\design\\lockicon.png");
			SDL_Texture * left1 = LoadTexture(renderer, ".\\design\\left1.png");
			SDL_Texture * left2 = LoadTexture(renderer, ".\\design\\left2.png");
			SDL_Texture * right1 = LoadTexture(renderer, ".\\design\\right1.png");
			SDL_Texture * right2 = LoadTexture(renderer, ".\\design\\right2.png");
			SDL_Texture * myProfile = LoadTextureEx(renderer, myuser->profile, 255, 255, 255);
			Slider * chatslide = (Slider *)malloc(sizeof(Slider));
			CreateSlider(chatslide, Slider_Box, Slider_slider_up, Display_X * 0.68, Display_Y * 0.78, Display_X * 0.01, Display_Y * 0.16, Display_X * 0.02, Display_Y * 0.04, &chattingdrag, 0, (Display_Y * 0.2) - ((int)(Display_Y * 0.2) % 10), Display_Y * 0.2 - ((int)(Display_Y * 0.2) % 10), VERTICAL);
			quit = 0;
			ClientParam.gameuser = gameuser;
			ServerParam.gameuser = gameuser;

			int maxchating = 0;
			int dkdkdk = 0;
			sprintf(query, "LV %d", myuser->level);
			warning.ison = 0;
			long long firsttime = SDL_GetTicks();
			int nonhappen = 0;
			usercount = getUesrStatus(cons, MemBerList);
			int pastusercount = usercount;
			if (ReadChating_all(cons, chatings) != 0)
				allchating_cnt = chatings[0].ownnum;
			int pastchating_cnt = allchating_cnt;
			int chatmovehappen = 0;
			int newdataed = 1;
			SDL_Delay(100);
			while (loginsuccess && !quit && !isplaygame)	//로그인 성공 후 대기창
			{
				if (newdataed)
				{
					SDL_SetRenderDrawColor(renderer, 191, 191, 191, 0);
					SDL_RenderClear(renderer);
					FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, Display_Y * 0.7 + 10, Display_X * 0.275, Display_Y * 0.27, 14);
					DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, Display_Y * 0.7 + 9, Display_X * 0.275 + 2, Display_Y * 0.27 + 2, 14, 1);
					FillUpRoundRect(renderer, 146, 208, 80, Display_X * 0.7 + 22, Display_Y * 0.7 + 10, Display_X * 0.275, Display_Y * 0.035, 14);
					PutText(renderer, "내 정보", (Display_X * 0.83), Display_Y * 0.7 + 10, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
					FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, 10, Display_X * 0.275, Display_Y * 0.09, 3);
					DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, 9, Display_X * 0.275 + 2, Display_Y * 0.09 + 2, 3, 1);
					PutText(renderer, myuser->name, Display_X * 0.87, Display_Y * 0.8, 40 * ((float)Display_X / 1920), 0, 0, 0, 1);	//개인정보 - 이름 출력
					PutText(renderer, query, Display_X * 0.88, Display_Y * 0.85, 30 * ((float)Display_X / 1920), 0, 0, 0, 1);	//개인정보 - 이름 출력
					RenderTextureXYWH(renderer, myProfile, Display_X * 0.75, Display_Y * 0.75, 148 * ((float)Display_X / 1920), 173 * ((float)Display_X / 1920));
					newdata[0] = 1;
					newdata[1] = 1;
					newdata[2] = 1;
					happen = true;
					newdataed = 0;
				}
				//printf("%d\n", dkdkdk++);
				//		if (SDL_PollEvent(&event))
				//		{
				//	SDL_WaitEvent(&event);
				SDL_WaitEventTimeout(&event, 1000);
				//	SDL_PollEvent(&event);
				if (UpdateSlider(chatslide, &event)) {
					chatmovehappen = 1;
				}
				if (RefrashEvent)
				{
					usercount = getUesrStatus(cons, MemBerList);
					if (usercount != pastusercount) {
						newdata[2] = 1;
						pastusercount = usercount;
					}
					if ((maxchating = ReadChating_all(cons, chatings)) != 0)
						allchating_cnt = chatings[0].ownnum;
					if (allchating_cnt != pastchating_cnt) {
						newdata[1] = 1;
						pastchating_cnt = allchating_cnt;

						chatmovehappen = 1;

					}
					roomcount = Get_Room_List(cons, rooms);
					if (roomcount != pastroomcount)
					{
						newdata[0] = 1;
						pastroomcount = roomcount;

					}
					RefrashEvent = 0;

				}
				switch (event.type)
				{
				case SDL_TEXTINPUT: // 채팅 입력 이벤트
					if (chattingput) {
						if (hanyeong == true && (event.text.text[0] == -29 || event.text.text[0] + 256 >= 234 && event.text.text[0] + 256 <= 237))// 한글일 경우
						{
							wcscpy(wchar, L"");
							sum = (event.text.text[0] + 22) * 64 * 64 + (event.text.text[1] + 128) * 64 + event.text.text[2] + 41088;
							wchar[0] = sum;
							wcscat(ID_put, wchar);


							if (event.text.text[0] == -29)
								slice = 1;
							else
								slice = 1 + !((wchar[0] - 0xac00) % 28);
						}
						else if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {// 영어 입력 시
							wcscpy(wchar, L"");
							swprintf(wchar, sizeof(wchar) / sizeof(wchar_t), L"%hs", event.text.text);// event.text.text 문자열 그냥 연결시켜버림
							wcscat(ID_put, wchar);
							hangeul = false;
							slice = 0;
						}
						textinput = true;
					}
					break;
				case SDL_KEYDOWN:
					if (chattingput) {
						if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
							if (hangeul == true && enter == false)
								enter = true;
							else if (wcslen(ID_put) > 0) {
								if (wstrcmp(ID_put, "/clear") == 0)
								{
									mysql_query(cons, "delete from all_chating");
									mysql_query(cons, "alter table all_chating auto_increment = 1");
									mysql_query(cons, "insert into all_chating (name, message) values('[관리자]', '채팅을 지웁니다')");
									memset(&ID_put, 0, sizeof(ID_put));
								}
								else {
									InsertChating_all(cons, myuser->name, ID_put);
									memset(&ID_put, 0, sizeof(ID_put));
									enter = false;
									textinput = true;
									if ((maxchating = ReadChating_all(cons, chatings)) != 0)
										allchating_cnt = chatings[0].ownnum;
									MoveSlider_value(chatslide, chatslide->End);
									chatmovehappen = 1;
								}
							}
						}

						else if (event.key.keysym.sym == SDLK_RALT)
							hanyeong = !(hanyeong);
						else if (event.key.keysym.sym == SDLK_BACKSPACE && wcslen(ID_put) > 0)// 키보드 백스페이스고 배열의 길이가 1이상일때
						{
							if (slice == 0) {

								ID_put[wcslen(ID_put) - 1] = '\0';

								textinput = true;
							}
							else {
								//		//printf("\nslice상태");
								slice--;
							}
						}
						else if (event.key.keysym.sym == SDLK_TAB)
						{
							if (hangeul == true && enter == false)
								enter = true;

						}

						else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {// 컨트롤 모드이고 c를 눌렀다면
							strcpy(utf8, UNICODE2UTF8(ID_put, wcslen(ID_put)));
							SDL_SetClipboardText(utf8);// 클립보드에 넣음

						}
						else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {// 컨트롤 모드이고 v를 눌렀다면
							wcscat(ID_put, UTF82UNICODE(SDL_GetClipboardText(), strlen(SDL_GetClipboardText())));// 클립보드에서 가져옴

							hangeul = false;
							textinput = true;
						}
						else {
							hangeul = true;
							slice++;
						}
					}
					break;
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
					case SDL_WINDOWEVENT_CLOSE:// 다수 창에서의 닫기이벤트가 발생할경우
						quit = true;
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
					break;
				case SDL_MOUSEWHEEL:
					if (event.wheel.y == 1) {

						//	if (event.motion.x < Display_X * 0.7 && event.motion.y > Display_Y * 0.7)
						if (chattingdrag > chatslide->Start && chattingdrag <= chatslide->End)
						{
							MoveSlider_value(chatslide, chattingdrag - 10);
							chatmovehappen = true;
						}
					}
					if (event.wheel.y == -1) {
						//		if (event.motion.x < Display_X * 0.7 && event.motion.y > Display_Y * 0.7)
						if (chattingdrag >= chatslide->Start && chattingdrag < chatslide->End)
						{
							MoveSlider_value(chatslide, chattingdrag + 10);
							chatmovehappen = true;
						}
					}
				}

				//	}
				/*
				화면을 전체적으로 4등분함

			|	   2번구역
			1번구역		 |----------------
			|
			|    3번구역
			---------------------|
			|-----------------
			4번구역		 |
			|     5번구역
			|
			|
			*/



			//1번구역
				if (newdata[0])
				{
					FillRoundRect(renderer, 255, 255, 255, 10, 10, Display_X * 0.7, Display_Y * 0.69, 14);
					DrawRoundRect(renderer, 191, 191, 191, 9, 9, Display_X * 0.7 + 2, Display_Y * 0.69 + 2, 14, 1);
					FillUpRoundRect(renderer, 146, 208, 80, 10, 10, Display_X * 0.7, Display_Y * 0.035, 14);
					PutText(renderer, "방 목록", (Display_X * 0.33), 10, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
					sprintf(roomtmp, "%d", roomchange);
					Put_Text_Center(renderer, roomtmp, 10, Display_Y * 0.655, Display_X * 0.7, Display_Y * 0.05, 0, 0, 0, 30 * ((float)Display_X / 1920), 1);
					happen = true;
				}
				//4번구역
				if (newdata[1] || chatmovehappen) {
					FillRoundRect(renderer, 255, 255, 255, 10, Display_Y * 0.7 + 10, Display_X * 0.7, Display_Y * 0.27, 14);
					DrawRoundRect(renderer, 191, 191, 191, 9, Display_Y * 0.7 + 10 - 1, Display_X * 0.7 + 2, Display_Y * 0.27 + 2, 14, 1);
					FillUpRoundRect(renderer, 146, 208, 80, 10, Display_Y * 0.7 + 10, Display_X * 0.7, Display_Y * 0.035, 14);
					PutText(renderer, "채팅", (Display_X * 0.335), Display_Y * 0.7 + 10, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
					DrawSlider(renderer, chatslide);
					happen = true;
				}
				//5번구역

				if (newdata[1] || chatmovehappen) {
					for (i = 0; i < maxchating; i++)
					{

						sprintf(db_id, "%s : %s", chatings[i].name, chatings[i].message);
						if (Display_Y * (1.08 - (0.03 * i)) - chattingdrag < Display_Y * 0.89 && Display_Y * (1.08 - (0.03 * i)) - chattingdrag > Display_Y * 0.76)
							PutText(renderer, db_id, Display_X * 0.04, Display_Y * (1.08 - (0.03 * i)) - chattingdrag, 25 * ((float)Display_X / 1920), 0, 0, 0, 1);
					}
					newdata[1] = 0;
					chatmovehappen = 0;
					happen = true;
				}
				//3번구역
				if (newdata[2]) {
					FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, Display_Y * 0.11, Display_X * 0.275, Display_Y * 0.59, 14);
					DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, Display_Y * 0.11 - 1, Display_X * 0.275 + 2, Display_Y * 0.59 + 2, 14, 1);
					FillUpRoundRect(renderer, 146, 208, 80, Display_X * 0.7 + 22, Display_Y * 0.11, Display_X * 0.275, Display_Y * 0.035, 14);
					PutText(renderer, "접속자 명단", (Display_X * 0.815), Display_Y * 0.113, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
					happen = true;
				}
				//2번구역

				if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 59, 127, 172, Display_X * 0.61, Display_Y * 0.915, Display_X * 0.05, Display_Y * 0.05, 8, 0, &event, &happen))
				{

					if (wstrcmp(ID_put, "/clear") == 0)
					{
						mysql_query(cons, "delete from all_chating");
						mysql_query(cons, "alter table all_chating auto_increment = 1");
						mysql_query(cons, "insert into all_chating (name, message) values('[관리자]', '채팅을 지웁니다')");
						memset(&ID_put, 0, sizeof(ID_put));
					}
					else if (wstrcmp(ID_put, "") == 0) {

					}
					else {
						FillUpRoundRect(renderer, 255, 255, 255, 61, 810, 1080, 177, 0);
						RenderTextureXYWH(renderer, Chating_noput, Display_X * 0.03, Display_Y * 0.91, Display_X * 0.56, Display_Y * 0.07);
						InsertChating_all(cons, myuser->name, ID_put);
						memset(&ID_put, 0, sizeof(ID_put));
						enter = false;
						textinput = true;
						allchating_cnt = ReadChating_all(cons, chatings);
						MoveSlider_value(chatslide, chatslide->End);
						newdata[1] = 1;
						chatmovehappen = 1;

					}
					//MouseUP_Wait;

				}



				if (chattingput == 0)
				{
					if (PutButtonImage(renderer, Chating_noput, Chating_put, Display_X * 0.03, Display_Y * 0.91, Display_X * 0.56, Display_Y * 0.07, &event, &happen))
						chattingput = 1;
				}
				else
				{
					if (PutButtonImage_click(renderer, Chating_click, Chating_click, Display_X * 0.03, Display_Y * 0.918, Display_X * 0.56, Display_Y * 0.047, &event, &happen) == -1) {
						chattingput = 0;
					}
					PutText_Unicode(renderer, ID_put, Display_X * 0.04, Display_Y * 0.92, 30 * ((float)Display_X / 1920), color, 1);

				}

				PutText(renderer, "전송", Display_X * 0.62, Display_Y * 0.925, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);

				/*	for (i = 0; i < roomcount; i++)
					{
						if (i % 2 == 0)
						{
							PutButtonImage(renderer, Room_Back_noclick, Room_Back_click, Display_X * 0.02, Display_Y * (0.07 + 0.16 * (i / 2)), Display_X * 0.335, Display_Y * 0.14, &event, &happen);
						}
						else {
							PutButtonImage(renderer, Room_Back_noclick, Room_Back_click, Display_X * 0.365, Display_Y * (0.07 + 0.16 * (i / 2)), Display_X * 0.335, Display_Y * 0.14, &event, &happen);
						}
					}*/
					//if (newdata[0]) {




				for (i = roomchange * 8 - 8, j = 0; i < roomcount && j < 8; i++, j++)
				{
					if (i % 2 == 0)
					{
						if (PutButtonImage(renderer, Room_Back_noclick, Room_Back_click, Display_X * 0.02, Display_Y * (0.07 + 0.15 * (j / 2)), Display_X * 0.335, Display_Y * 0.14, &event, &happen)) {
							memcpy(&My_Room, &rooms[i], sizeof(Hit_Room));
							strcpy(ClientParam.serverip, My_Room.ip);
							client = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)connectServer, &ClientParam, 0, NULL);

							isplaygame = true;
						}
						sprintf(db_id, "%.3d", rooms[i].ownnum);
						PutText(renderer, db_id, Display_X * 0.027, Display_Y * (0.107 + 0.15 * (j / 2)), 50 * ((float)Display_X / 1920), 0, 0, 0, 1);	//번호 출력

						PutText(renderer, rooms[i].name, Display_X * 0.09, Display_Y * (0.09 + 0.15 * (j / 2)), 40 * ((float)Display_X / 1920), 0, 0, 0, 2);	//제목 출력

						Put_Text_Center(renderer, rooms[i].mode, Display_X * 0.085, Display_Y * (0.165 + 0.15 * (j / 2)),Display_X*0.058,Display_Y*0.035, 0, 0, 0, 30 * ((float)Display_X / 1920),  1);	//모드 출력

						sprintf(db_id, "%d문제", rooms[i].question);
						PutText(renderer, db_id, Display_X * 0.16, Display_Y * (0.165 + 0.15 * (j / 2)), 30 * ((float)Display_X / 1920), 0, 0, 0, 1);	//문제 수 출력

						sprintf(db_id, "%d초", rooms[i].time);
						Put_Text_Center(renderer, db_id, Display_X * 0.23, Display_Y * (0.165 + 0.15 * (j / 2)), Display_X*0.048, Display_Y*0.035, 0, 0, 0, 30 * ((float)Display_X / 1920), 1);	//문제 시간 출력

						sprintf(db_id, "%d/%d", rooms[i].people, rooms[i].max_people);
						PutText(renderer, db_id, Display_X * 0.305, Display_Y * (0.165 + 0.15 * (j / 2)), 30 * ((float)Display_X / 1920), 0, 0, 0, 1);	//인원 수

						if (strlen(rooms[i].password) > 0)
						{
							RenderTextureXYWH(renderer, Room_Lock, Display_X * 0.3, Display_Y * (0.08 + 0.15 * (j / 2)), Display_X / 30, Display_X / 30);
						}
					}
					else {
						if (PutButtonImage(renderer, Room_Back_noclick, Room_Back_click, Display_X * 0.365, Display_Y * (0.07 + 0.15 * (j / 2)), Display_X * 0.335, Display_Y * 0.14, &event, &happen)) {
							memcpy(&My_Room, &rooms[i], sizeof(Hit_Room));
							strcpy(ClientParam.serverip, My_Room.ip);
							client = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)connectServer, &ClientParam, 0, NULL);

							isplaygame = true;
						}
						sprintf(db_id, "%.3d", rooms[i].ownnum);
						PutText(renderer, db_id, Display_X * 0.372, Display_Y * (0.107 + 0.15 * (j / 2)), 50 * ((float)Display_X / 1920), 0, 0, 0, 1);	//번호 출력

						PutText(renderer, rooms[i].name, Display_X * 0.435, Display_Y * (0.09 + 0.15 * (j / 2)), 40 * ((float)Display_X / 1920), 0, 0, 0, 2);	//제목 출력

						Put_Text_Center(renderer, rooms[i].mode, Display_X * 0.43, Display_Y * (0.165 + 0.15 * (j / 2)),Display_X*0.058, Display_Y*0.035, 0, 0, 0, 30 * ((float)Display_X / 1920), 1);;	//모드 출력
						sprintf(db_id, "%d문제", rooms[i].question);
						PutText(renderer, db_id, Display_X * 0.505, Display_Y * (0.165 + 0.15 * (j / 2)), 30 * ((float)Display_X / 1920), 0, 0, 0, 1);	//문제 수 출력

						sprintf(db_id, "%d초", rooms[i].time);
						Put_Text_Center(renderer, db_id, Display_X * 0.575, Display_Y * (0.165 + 0.15 * (j / 2)), Display_X*0.048, Display_Y*0.035, 0, 0, 0, 30 * ((float)Display_X / 1920),1);	//문제 시간 출력

						sprintf(db_id, "%d/%d", rooms[i].people, rooms[i].max_people);
						PutText(renderer, db_id, Display_X * 0.65, Display_Y * (0.165 + 0.15 * (j / 2)), 30 * ((float)Display_X / 1920), 0, 0, 0, 1);	//인원 수

					}
				}

				newdata[0] = 0;

				if (PutButtonImage(renderer, left1, left2, Display_X * 0.25, Display_Y * 0.655, Display_X * 0.06, Display_Y * 0.05, &event, &happen) && roomchange != 1) {
					roomchange--;
					newdata[0] = 1;

				}
				else if (PutButtonImage(renderer, right1, right2, Display_X * 0.4, Display_Y * 0.655, Display_X * 0.06, Display_Y * 0.05, &event, &happen) && roomchange * 8 < roomcount) {
					roomchange++;
					newdata[0] = 1;

				}



				//	}

				if (newdata[2]) {
					for (i = 0; i < usercount; i++)
					{
						sprintf(db_id, "LV:%d", MemBerList[i][27]);
						RenderTextureXYWH(renderer, User_Pencil, Display_X * 0.73, Display_Y * (0.20 + i * 0.05), 33 * ((float)Display_X / 1920), 33 * ((float)Display_X / 1920));
						PutText(renderer, db_id, Display_X * 0.76, Display_Y * (0.20 + i * 0.05), 30 * ((float)Display_X / 1920), 0, 0, 0, 1);
						PutText(renderer, MemBerList[i], Display_X * 0.82, Display_Y * (0.20 + i * 0.05), 30 * ((float)Display_X / 1920), 0, 0, 0, 1);
						if (MemBerList[i][28] == 1)
						{
							PutText(renderer, "로비", Display_X * 0.93, Display_Y * (0.20 + i * 0.05), 30 * ((float)Display_X / 1920), 0, 0, 0, 1);
						}
						else if (MemBerList[i][28] == 2)
						{
							PutText(renderer, "게임 중", Display_X * 0.93, Display_Y * (0.20 + i * 0.05), 30 * ((float)Display_X / 1920), 255, 0, 0, 1);
						}
						else if (MemBerList[i][28] == 3)
						{
							PutText(renderer, "대기방", Display_X * 0.93, Display_Y * (0.20 + i * 0.05), 30 * ((float)Display_X / 1920), 0, 255, 0, 1);
						}
						else if (MemBerList[i][28] == 4)
						{
							PutText(renderer, "개발 중", Display_X * 0.91, Display_Y * (0.20 + i * 0.05), 30 * ((float)Display_X / 1920), 155, 16, 175, 1);
						}
					}
					newdata[2] = 0;
				}
				if (PutRoundButton(renderer, 3, 114, 237, 23, 134, 255, 3, 114, 237, Display_X * 0.71 + 22, Display_Y * 0.037 - (Display_Y*Display_Y) / (1080 * 1080.0)*11.5, Display_X / 11, Display_Y / 18, 8, 0, &event, &happen)) //방만들기 버튼
				{
					SDL_Texture * Create_back = LoadTexture(renderer, ".\\design\\bangcreate.png");
					SDL_Texture * Create_Close_noclick = LoadTexture(renderer, ".\\login\\close1.png");
					SDL_Texture * Create_Close_click = LoadTexture(renderer, ".\\login\\close2.png");
					SDL_Texture * Slider_Bar = LoadTextureEx(renderer, ".\\design\\Box.png", 255, 255, 255);
					SDL_Texture * Slider_slide = LoadTexture(renderer, ".\\design\\slider.png");
					int createroom = 1;
					int set_start_x = Display_X / 2 - (346 * ((float)Display_X / 1920));
					int set_start_y = Display_Y / 2 - (268 * ((float)Display_X / 1920));
					int set_start_w = 696 * ((float)Display_X / 1920);
					int set_start_h = 587 * ((float)Display_X / 1920);
					wchar_t  Room_Name_put[128] = L"";
					wchar_t  Room_Password_put[128] = L"";
					int Nameput = 1;
					int mode = 1;
					warning.ison = 0;
					PutText(renderer, "방만들기", Display_X * 0.72 + 20, Display_Y * 0.047 - (Display_Y*Display_Y) / (1080 * 1080.0)*11.5, 35 * ((float)Display_Y) / 1080, 255, 255, 255, 2);
					int question_value = 10;	//5 ~ 50
					int question_time = 30;		// 10 ~ 180
					Slider * slide_question = (Slider *)malloc(sizeof(Slider));
					Slider * slide_time = (Slider *)malloc(sizeof(Slider));
					CreateSlider(slide_question, Slider_Bar, Slider_slide, set_start_x + set_start_w * 0.3, set_start_y + set_start_h * 0.72, set_start_w * 0.5, set_start_h * 0.03, set_start_w * 0.03, set_start_h * 0.08, &question_value, 5, 50, question_value, HORIZONTAL);
					CreateSlider(slide_time, Slider_Bar, Slider_slide, set_start_x + set_start_w * 0.3, set_start_y + set_start_h * 0.89, set_start_w * 0.5, set_start_h * 0.03, set_start_w * 0.03, set_start_h * 0.08, &question_time, 10, 180, question_time, HORIZONTAL);
					int Passwordput = 0;
					while (createroom) {
						SDL_WaitEvent(&event);
						switch (event.type)
						{
						case SDL_TEXTINPUT: // 채팅 입력 이벤트
							if (hanyeong == true && (event.text.text[0] == -29 || event.text.text[0] + 256 >= 234 && event.text.text[0] + 256 <= 237))// 한글일 경우
							{
								wcscpy(wchar, L"");
								sum = (event.text.text[0] + 22) * 64 * 64 + (event.text.text[1] + 128) * 64 + event.text.text[2] + 41088;
								wchar[0] = sum;
								if (Nameput)
								{
									if (wcslen(Room_Name_put) < 10)
										wcscat(Room_Name_put, wchar);

								}
								else if (Passwordput)
								{

									if (wcslen(Room_Password_put) < 12)
										wcscat(Room_Password_put, wchar);
								}
								if (event.text.text[0] == -29)
									slice = 1;
								else
									slice = 1 + !((wchar[0] - 0xac00) % 28);
							}
							else if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {// 영어 입력 시
								wcscpy(wchar, L"");
								swprintf(wchar, sizeof(wchar) / sizeof(wchar_t), L"%hs", event.text.text);// event.text.text 문자열 그냥 연결시켜버림
								if (Nameput)
								{
									if (wcslen(Room_Name_put) < 10)
										wcscat(Room_Name_put, wchar);

								}
								else if (Passwordput)
								{
									if (wcslen(Room_Password_put) < 12)
										wcscat(Room_Password_put, wchar);
								}
								hangeul = false;
								slice = 0;
							}
							textinput = true;

							break;
						case SDL_KEYDOWN:
							if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
								if (hangeul == true && enter == false)
									enter = true;
								else {
									if (Nameput)
									{
										Nameput = 0;
										Passwordput = 1;
									}
									else if (Passwordput)
									{
										if (mode == 0)
										{
											warning.ison = 1;
											warning.r = 255;
											warning.g = 0;
											warning.b = 0;
											warning.size = 15;
											strcpy(warning.message, "모드 선택은 필수입니다.");
											warning.x = set_start_x + set_start_w * 0.25;
											warning.y = set_start_y + set_start_h * 0.46;

										}
										else if (wcslen(Room_Name_put) > 0)
										{
											i = Create_Room_sql(cons, Room_Name_put, Room_Password_put, mode, question_value, question_time);
											if (i == -1)
											{
												warning.ison = 1;
												warning.r = 255;
												warning.g = 0;
												warning.b = 0;
												warning.size = 15;
												strcpy(warning.message, "해당 제목이 존재합니다.");
												warning.x = set_start_x + set_start_w * 0.25;
												warning.y = set_start_y + set_start_h * 0.13;
												memset(&Room_Name_put, 0, sizeof(Room_Name_put));
											}
											else
											{
												bangsang = 1;
												gameuser[0].Master = 1;
												server = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)OpenServer, &ServerParam, 0, NULL);

												roomcount = Get_Room_List(cons, rooms);
												memcpy(&My_Room, &rooms[roomcount - 1], sizeof(Hit_Room));
												strcpy(ClientParam.serverip, My_Room.ip);
												client = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)connectServer, &ClientParam, 0, NULL);
												createroom = false;
												isplaygame = true;
											}
										}
									}
								}
							}

							else if (event.key.keysym.sym == SDLK_RALT)
								hanyeong = !(hanyeong);
							else if (event.key.keysym.sym == SDLK_BACKSPACE && (Nameput ? wcslen(Room_Name_put) > 0 : Passwordput ? wcslen(Room_Password_put) > 0: 0))// 키보드 백스페이스고 배열의 길이가 1이상일때
							{
								if (slice == 0) {

									if (Nameput)
										Room_Name_put[wcslen(Room_Name_put) - 1] = '\0';
									else if (Passwordput)
										Room_Password_put[wcslen(Room_Password_put) - 1] = '\0';

									textinput = true;
								}
								else {
									slice--;
								}
							}
							else if (event.key.keysym.sym == SDLK_TAB)
							{
								if (hangeul == true && enter == false)
									enter = true;
								else if (Nameput)
								{
									Nameput = 0;
									Passwordput = 1;
								}
							}

							else {
								hangeul = true;
								slice++;
							}

							break;
						case SDL_QUIT:
							createroom = false;
							break;
						case SDL_WINDOWEVENT:
							switch (event.window.event) {
							case SDL_WINDOWEVENT_CLOSE:// 다수 창에서의 닫기이벤트가 발생할경우
								createroom = false;
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
						UpdateSlider(slide_question, &event);
						UpdateSlider(slide_time, &event);
						RenderTextureXYWH(renderer, Create_back, set_start_x, set_start_y, set_start_w, set_start_h);
						if (PutButtonImage(renderer, Create_Close_noclick, Create_Close_click, set_start_x + set_start_w - 110 * ((float)Display_X / 1920), set_start_y - Display_Y*0.0009, 110 * ((float)Display_X / 1920), 84 * ((float)Display_X / 1920), &event, &happen))
						{
							MouseUP_Wait;
							createroom = false;
						}
						//방 제목 입력창
						if (!Nameput) {
							if (PutRoundButton(renderer, 244, 244, 244, 255, 255, 255, 191, 191, 191, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.16, set_start_w * 0.7, set_start_h * 0.13, 13, 0, &event, &happen))
							{
								Nameput = true;
								Passwordput = false;
							}
						}
						else
							FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.16, set_start_w * 0.7, set_start_h * 0.13, 13);

						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.16 - 3, set_start_w * 0.7 + 6, set_start_h * 0.13 + 6, 13, 2);
						SDL_FillRectXYWH(renderer, set_start_x + set_start_w * 0.27, set_start_y + set_start_h * 0.16, 6 * ((float)Display_X / 1920), set_start_h * 0.133, 91, 155, 213);
						PutText(renderer, "방 제목", set_start_x + set_start_w * 0.08, set_start_y + set_start_h * 0.18, 35 * ((float)Display_X / 1920), 0, 0, 0, 2);
						//입력
						PutText_Unicode(renderer, Room_Name_put, set_start_x + set_start_w * 0.3, set_start_y + set_start_h * 0.2, 30 * ((float)Display_X / 1920), color, 1);

						//만들기 창
						if (PutRoundButton(renderer, 3, 114, 237, 23, 134, 255, 3, 114, 237, set_start_x + set_start_w * 0.75, set_start_y + set_start_h * 0.16, set_start_w * 0.22, set_start_h * 0.13, 13, 0, &event, &happen)) { //만들기 클릭
							if (mode == 0)
							{
								warning.ison = 1;
								warning.r = 255;
								warning.g = 0;
								warning.b = 0;
								warning.size = 15;
								strcpy(warning.message, "모드 선택은 필수입니다.");
								warning.x = set_start_x + set_start_w * 0.25;
								warning.y = set_start_y + set_start_h * 0.46;

							}
							else if (wcslen(Room_Name_put) > 0)
							{
								i = Create_Room_sql(cons, Room_Name_put, Room_Password_put, mode, question_value, question_time);
								if (i == -1)
								{
									warning.ison = 1;
									warning.r = 255;
									warning.g = 0;
									warning.b = 0;
									warning.size = 15;
									strcpy(warning.message, "해당 제목이 존재합니다.");
									warning.x = set_start_x + set_start_w * 0.25;
									warning.y = set_start_y + set_start_h * 0.13;
									memset(&Room_Name_put, 0, sizeof(Room_Name_put));
								}
								else
								{
									bangsang = 1;
									server = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)OpenServer, &ServerParam, 0, NULL);

									roomcount = Get_Room_List(cons, rooms);
									memcpy(&My_Room, &rooms[roomcount - 1], sizeof(Hit_Room));
									strcpy(ClientParam.serverip, My_Room.ip);
									client = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)connectServer, &ClientParam, 0, NULL);
									createroom = false;
									isplaygame = true;
								}
							}
						}

						PutText(renderer, "만들기", set_start_x + set_start_w * 0.79, set_start_y + set_start_h * 0.18, 35 * ((float)Display_X / 1920), 255, 255, 255, 1);

						//방 비밀번호 입력창
						if (!Passwordput) {
							if (PutRoundButton(renderer, 244, 244, 244, 255, 255, 255, 191, 191, 191, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.33, set_start_w * 0.94, set_start_h * 0.13, 13, 0, &event, &happen)) {
								Nameput = false;
								Passwordput = true;

							}
						}
						else
							FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.33, set_start_w * 0.94, set_start_h * 0.13, 13);

						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.33 - 3, set_start_w * 0.94 + 6, set_start_h * 0.13 + 6, 13, 2);
						SDL_FillRectXYWH(renderer, set_start_x + set_start_w * 0.27, set_start_y + set_start_h * 0.33, 6 * ((float)Display_X / 1920), set_start_h * 0.133, 91, 155, 213);
						PutText(renderer, "비밀번호", set_start_x + set_start_w * 0.06, set_start_y + set_start_h * 0.35, 35 * ((float)Display_X / 1920), 0, 0, 0, 2);

						//방 게임모드 입력창
						FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.5, set_start_w * 0.94, set_start_h * 0.13, 13);
						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.5 - 3, set_start_w * 0.94 + 6, set_start_h * 0.13 + 6, 13, 2);
						SDL_FillRectXYWH(renderer, set_start_x + set_start_w * 0.27, set_start_y + set_start_h * 0.5, 6 * ((float)Display_X / 1920), set_start_h * 0.133, 91, 155, 213);
						PutText(renderer, "게임모드", set_start_x + set_start_w * 0.06, set_start_y + set_start_h * 0.52, 35 * ((float)Display_X / 1920), 0, 0, 0, 2);

						//방 문제 수 입력창
						FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.67, set_start_w * 0.94, set_start_h * 0.13, 13);
						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.67 - 3, set_start_w * 0.94 + 6, set_start_h * 0.13 + 6, 13, 2);
						SDL_FillRectXYWH(renderer, set_start_x + set_start_w * 0.27, set_start_y + set_start_h * 0.67, 6 * ((float)Display_X / 1920), set_start_h * 0.133, 91, 155, 213);
						PutText(renderer, "문제 수", set_start_x + set_start_w * 0.08, set_start_y + set_start_h * 0.69, 35 * ((float)Display_X / 1920), 0, 0, 0, 2);
						FillRoundRect(renderer, 0, 176, 240, set_start_x + set_start_w * 0.83, set_start_y + set_start_h * 0.685, set_start_w* 0.12, set_start_h * 0.1, 32 * ((float)Display_X / 1920));
						DrawSlider(renderer, slide_question);

						//방 문제당 시간 입력창
						FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.84, set_start_w * 0.94, set_start_h * 0.13, 13);
						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.84 - 3, set_start_w * 0.94 + 6, set_start_h * 0.13 + 6, 13, 2);
						SDL_FillRectXYWH(renderer, set_start_x + set_start_w * 0.27, set_start_y + set_start_h * 0.84, 6 * ((float)Display_X / 1920), set_start_h * 0.133, 91, 155, 213);
						PutText(renderer, "1문제/초", set_start_x + set_start_w * 0.075, set_start_y + set_start_h * 0.87, 32 * ((float)Display_X / 1920), 0, 0, 0, 2);
						FillRoundRect(renderer, 0, 176, 240, set_start_x + set_start_w * 0.83, set_start_y + set_start_h * 0.855, set_start_w* 0.12, set_start_h * 0.1, 32 * ((float)Display_X / 1920));

						//question_value 출력
						PutText(renderer, _itoa(question_value, db_id, 10), set_start_x + set_start_w * 0.85, set_start_y + set_start_h * 0.7, 35 * ((float)Display_X / 1920), 255, 255, 255, 1);
						//question_time 출력
						PutText(renderer, _itoa(question_time, db_id, 10), set_start_x + set_start_w * 0.845, set_start_y + set_start_h * 0.87, 35 * ((float)Display_X / 1920), 255, 255, 255, 1);

						DrawSlider(renderer, slide_time);

						if (mode != 1)
						{
							if (PutRoundButton(renderer, 0, 176, 240, 10, 186, 250, 0, 176, 240, set_start_x + set_start_w * 0.31, set_start_y + set_start_h * 0.51, set_start_w * 0.16, set_start_h * 0.1, 30 * ((float)Display_X / 1920), 0, &event, &happen))
								mode = 1;
						}
						else
							FillRoundRect(renderer, 0, 112, 192, set_start_x + set_start_w * 0.31, set_start_y + set_start_h * 0.51, set_start_w * 0.16, set_start_h * 0.1, 30 * ((float)Display_X / 1920));
						PutText(renderer, "일반", set_start_x + set_start_w * 0.345, set_start_y + set_start_h * 0.53, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
						if (mode != 2) {
							if (PutRoundButton(renderer, 0, 176, 240, 10, 186, 250, 0, 176, 240, set_start_x + set_start_w * 0.51, set_start_y + set_start_h * 0.51, set_start_w * 0.2, set_start_h * 0.1, 30 * ((float)Display_X / 1920), 0, &event, &happen))
								mode = 2;
						}
						else
							FillRoundRect(renderer, 0, 112, 192, set_start_x + set_start_w * 0.51, set_start_y + set_start_h * 0.51, set_start_w * 0.2, set_start_h * 0.1, 30 * ((float)Display_X / 1920));
						PutText(renderer, "콘테스트", set_start_x + set_start_w * 0.535, set_start_y + set_start_h * 0.535, 25 * ((float)Display_X / 1920), 255, 255, 255, 1);
						if (mode != 3) {
							if (PutRoundButton(renderer, 0, 176, 240, 10, 186, 250, 0, 176, 240, set_start_x + set_start_w * 0.74, set_start_y + set_start_h * 0.51, set_start_w * 0.16, set_start_h * 0.1, 30 * ((float)Display_X / 1920), 0, &event, &happen))
								mode = 3;
						}
						else
							FillRoundRect(renderer, 0, 112, 192, set_start_x + set_start_w * 0.74, set_start_y + set_start_h * 0.51, set_start_w * 0.16, set_start_h * 0.1, 30 * ((float)Display_X / 1920));
						PutText(renderer, "FPS", set_start_x + set_start_w * 0.78, set_start_y + set_start_h * 0.53, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);


						for (j = 0; j < wcslen(Room_Password_put); j++)
							db_id[j] = '*';
						db_id[j] = 0;
						PutText(renderer, db_id, set_start_x + set_start_w * 0.3, set_start_y + set_start_h * 0.35, 35 * ((float)Display_X / 1920), 0, 0, 0, 1);
						//	PutText_Unicode(renderer, Room_Password_put, set_start_x + set_start_w * 0.3, set_start_y + set_start_h * 0.35, 30 * ((float)Display_X / 1920), color,1);

						if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 0, 176, 240, set_start_x + set_start_w * 0.8, set_start_y + set_start_h * 0.345, set_start_w * 0.12, set_start_h * 0.1, 32 * ((float)Display_X / 1920), 0, &event, &happen)) {
							if (wcslen(Room_Password_put) > 0)
								memset(&Room_Password_put, 0, sizeof(Room_Password_put));
						}

						if (wcslen(Room_Password_put) > 0)
							PutText(renderer, "on", set_start_x + set_start_w * 0.83, set_start_y + set_start_h * 0.358, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
						else
							PutText(renderer, "off", set_start_x + set_start_w * 0.83, set_start_y + set_start_h * 0.358, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
						if (warning.ison == 1)
						{
							PutText(renderer, warning.message, warning.x, warning.y, warning.size, warning.r, warning.g, warning.b, 1);
						}
						SDL_RenderPresent(renderer);

					}
					warning.ison = 0;
					free(slide_question);
					free(slide_time);
					SDL_DestroyTexture(Slider_slide);
					SDL_DestroyTexture(Slider_Bar);
					SDL_DestroyTexture(Create_Close_noclick);
					SDL_DestroyTexture(Create_Close_click);
					SDL_DestroyTexture(Create_back);
					newdataed = 1;
					continue;
				}
				if (PutRoundButton(renderer, 255, 0, 0, 210, 0, 0, 255, 0, 0, Display_X * 0.81 + 22, Display_Y * 0.037 - (Display_Y*Display_Y) / (1080 * 1080.0)*11.5, Display_X / 11, Display_Y / 18, 8, 0, &event, &happen)) //빠른 시작 버튼
				{
					qquit = false;
				}
				PutText(renderer, "방만들기", Display_X * 0.72 + 20, Display_Y * 0.047 - (Display_Y*Display_Y) / (1080 * 1080.0)*11.5, 35 * ((float)Display_Y) / 1080, 255, 255, 255, 2);
				PutText(renderer, "빠른시작", Display_X * 0.82 + 22, Display_Y * 0.047 - (Display_Y*Display_Y) / (1080 * 1080.0)*11.5, 35 * ((float)Display_Y) / 1080, 255, 255, 255, 2);

				if (PutButtonImage(renderer, WaitRoom_setting_noclick, WaitRoom_setting_click, Display_X * 0.92 + 10, Display_Y * 0.027 - (Display_Y*Display_Y*Display_Y) / (1080 * 1080 * 1080.0)*11.5, 86 * ((float)Display_X / 1920), 82 * ((float)Display_X / 1920), &event, &happen))//설정 버튼
				{

					setting_main = 1;
					int display_value = Display_X / 320;

					SDL_Texture * Setting_back = LoadTexture(renderer, ".\\design\\settingmain.png");
					SDL_Texture * Setting_Close_noclick = LoadTexture(renderer, ".\\login\\close1.png");
					SDL_Texture * Setting_Close_click = LoadTexture(renderer, ".\\login\\close2.png");
					int set_start_x = Display_X / 2 - (346 * ((float)Display_X / 1920));
					int set_start_y = Display_Y / 2 - (268 * ((float)Display_X / 1920));
					int set_start_w = 693 * ((float)Display_X / 1920);
					int set_start_h = 537 * ((float)Display_X / 1920);
					Slider * slider_sound = (Slider*)malloc(sizeof(Slider));
					Slider * slider_bgsound = (Slider*)malloc(sizeof(Slider));
					Slider * slider_display = (Slider*)malloc(sizeof(Slider));
					SDL_Texture * Slider_slider = LoadTexture(renderer, ".\\design\\slider.png");

					CreateSlider(slider_sound, Slider_Box, Slider_slider, set_start_x + set_start_w * 0.3, set_start_y + set_start_h * 0.24, set_start_w * 0.5, set_start_h * 0.03, set_start_w * 0.03, set_start_h * 0.08, &Sound, 0, 100, Sound, HORIZONTAL);
					CreateSlider(slider_bgsound, Slider_Box, Slider_slider, set_start_x + set_start_w * 0.3, set_start_y + set_start_h * 0.42, set_start_w * 0.5, set_start_h * 0.03, set_start_w * 0.03, set_start_h * 0.08, &BGmusic, 0, 100, BGmusic, HORIZONTAL);
					CreateSlider(slider_display, Slider_Box, Slider_slider, set_start_x + set_start_w * 0.32, set_start_y + set_start_h * 0.58, set_start_w * 0.6, set_start_h * 0.03, set_start_w * 0.03, set_start_h * 0.08, &display_value, 3, 6, display_value, HORIZONTAL);

					while (setting_main) {
						//	if (SDL_PollEvent(&event))
						//	{
						SDL_WaitEvent(&event);
						switch (event.type)
						{
						case SDL_QUIT:
							setting_main = false;
							break;
						case SDL_WINDOWEVENT:
							switch (event.window.event) {
							case SDL_WINDOWEVENT_CLOSE:// 다수 창에서의 닫기이벤트가 발생할경우
								setting_main = false;
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


						//	}

						RenderTextureXYWH(renderer, Setting_back, set_start_x, set_start_y, set_start_w, set_start_h);
						if (PutButtonImage(renderer, Setting_Close_noclick, Setting_Close_click, set_start_x + set_start_w - 110 * ((float)Display_X / 1920), set_start_y, 110 * ((float)Display_X / 1920), 84 * ((float)Display_X / 1920), &event, &happen))
						{

							Re_Load(Window, renderer, display_value * 320, display_value * 180, Sound, BGmusic, Full);
							changesetting(BGmusic, Sound, display_value * 320, display_value * 180, Full);
							Display_X = display_value * 320;
							Display_Y = display_value * 180;

							setting_main = 0;
						}
						//효과음
						FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.18, set_start_w * 0.94, set_start_h * 0.14, 13);
						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.18 - 3, set_start_w * 0.94 + 6, set_start_h * 0.14 + 6, 13, 2);
						SDL_FillRectXYWH(renderer, set_start_x + set_start_w * 0.27, set_start_y + set_start_h * 0.18, 6 * ((float)Display_X / 1920), set_start_h * 0.143, 91, 155, 213);
						PutText(renderer, "효과음", set_start_x + set_start_w * 0.08, set_start_y + set_start_h * 0.21, 35 * ((float)Display_X / 1920), 0, 0, 0, 2);
						FillRoundRect(renderer, 0, 176, 240, set_start_x + set_start_w * 0.81, set_start_y + set_start_h * 0.2, set_start_w * 0.15, set_start_h * 0.1, 25 * ((float)Display_X / 1920));
						PutText(renderer, _itoa(Sound, db_id, 10), set_start_x + set_start_w * 0.85, set_start_y + set_start_h * 0.216, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);

						//배경음악
						FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.36, set_start_w * 0.94, set_start_h * 0.14, 13);
						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.36 - 3, set_start_w * 0.94 + 6, set_start_h * 0.14 + 6, 13, 2);
						SDL_FillRectXYWH(renderer, set_start_x + set_start_w * 0.27, set_start_y + set_start_h * 0.36, 6 * ((float)Display_X / 1920), set_start_h * 0.143, 91, 155, 213);
						PutText(renderer, "배경음악", set_start_x + set_start_w * 0.06, set_start_y + set_start_h * 0.39, 32 * ((float)Display_X / 1920), 0, 0, 0, 2);
						FillRoundRect(renderer, 0, 176, 240, set_start_x + set_start_w * 0.81, set_start_y + set_start_h * 0.38, set_start_w * 0.15, set_start_h * 0.1, 25 * ((float)Display_X / 1920));
						PutText(renderer, _itoa(BGmusic, db_id, 10), set_start_x + set_start_w * 0.85, set_start_y + set_start_h * 0.396, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);

						//해상도 설정
						FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.54, set_start_w * 0.94, set_start_h * 0.22, 13);
						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.54 - 3, set_start_w * 0.94 + 6, set_start_h * 0.22 + 6, 13, 2);
						SDL_FillRectXYWH(renderer, set_start_x + set_start_w * 0.27, set_start_y + set_start_h * 0.54, 6 * ((float)Display_X / 1920), set_start_h * 0.223, 91, 155, 213);
						PutText(renderer, "해상도 설정", set_start_x + set_start_w * 0.04, set_start_y + set_start_h * 0.61, 30 * ((float)Display_X / 1920), 0, 0, 0, 2);
						sprintf(db_id, "%d X %d", 320 * display_value, 180 * display_value);

						PutText(renderer, db_id, set_start_x + set_start_w * 0.35, set_start_y + set_start_h * 0.65, 30 * ((float)Display_X / 1920), 0, 0, 0, 1);
						if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 0, 176, 240, set_start_x + set_start_w * 0.7, set_start_y + set_start_h * 0.65, set_start_x * 0.2, set_start_h * 0.1, 25 * ((float)Display_X / 1920), 0, &event, &happen)) {
							if (Full == 0)
								Full = 1;
							else
								Full = 0;
							MouseUP_Wait;
						}
						if (Full == 1)
						{
							PutText(renderer, "FULL", set_start_x + set_start_w * 0.74, set_start_y + set_start_h * 0.67, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
							display_value = 6;
							slider_display->Box.x = slider_display->Bar.x + slider_display->Bar.w - slider_display->Box.w / 2;
						}
						else
						{
							PutText(renderer, "FULL", set_start_x + set_start_w * 0.74, set_start_y + set_start_h * 0.67, 30 * ((float)Display_X / 1920), 189, 189, 189, 1);
							UpdateSlider(slider_display, &event);
						}
						UpdateSlider(slider_sound, &event);
						UpdateSlider(slider_bgsound, &event);
						//고객문의, 크래딧, 설문조사
						FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.8, set_start_w * 0.94, set_start_h * 0.16, 13);
						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.8 - 3, set_start_w * 0.94 + 6, set_start_h * 0.16 + 6, 13, 2);

						//고객문의 버튼
						if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 0, 176, 240, set_start_x + set_start_w * 0.06, set_start_y + set_start_h * 0.82, set_start_x * 0.3, set_start_h * 0.12, 25 * ((float)Display_X / 1920), 0, &event, &happen))
						{
							system("start https://goo.gl/forms/tdCMgM3uRR1ZoNHO2");
						}
						//크래딧 버튼
						if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 0, 176, 240, set_start_x + set_start_w * 0.36, set_start_y + set_start_h * 0.82, set_start_x * 0.3, set_start_h * 0.12, 25 * ((float)Display_X / 1920), 0, &event, &happen))
						{
							MouseUP_Wait;

							SDL_Texture * Credit_Image = LoadTexture(renderer, ".\\design\\credit.png");

							while (1)
							{
								if (event.type == SDL_MOUSEBUTTONDOWN)
								{
									MouseUP_Wait;
									break;
								}
								RenderTextureXYWH(renderer, Credit_Image, 0, 0, Display_X, Display_Y);
								SDL_RenderPresent(renderer);
								SDL_WaitEvent(&event);
							}
							SDL_DestroyTexture(Credit_Image);
						}
						//설문조사 버튼
						if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 0, 176, 240, set_start_x + set_start_w * 0.66, set_start_y + set_start_h * 0.82, set_start_x * 0.3, set_start_h * 0.12, 25 * ((float)Display_X / 1920), 0, &event, &happen))
						{
							system("start https://goo.gl/forms/guFd08v7sFrK6Pe93");
						}
						DrawSlider(renderer, slider_sound);
						DrawSlider(renderer, slider_bgsound);
						DrawSlider(renderer, slider_display);
						PutText(renderer, "고객문의", set_start_x + set_start_w * 0.093, set_start_y + set_start_h * 0.83, 35 * ((float)Display_X / 1920), 255, 255, 255, 1);
						PutText(renderer, "크래딧", set_start_x + set_start_w * 0.42, set_start_y + set_start_h * 0.83, 35 * ((float)Display_X / 1920), 255, 255, 255, 1);
						PutText(renderer, "설문조사", set_start_x + set_start_w * 0.693, set_start_y + set_start_h * 0.83, 35 * ((float)Display_X / 1920), 255, 255, 255, 1);

						SDL_RenderPresent(renderer);


					}
					changesetting(BGmusic, Sound, Display_X, Display_Y, Full);
					Mix_VolumeMusic(BGmusic*1.28);

					SDL_DestroyTexture(Setting_back);
					SDL_DestroyTexture(Setting_Close_click);
					SDL_DestroyTexture(Setting_Close_noclick);
					SDL_DestroyTexture(Slider_slider);
					free(slider_sound);
					free(slider_bgsound);
					free(slider_display);
					newdataed = 1;
					CreateSlider(chatslide, Slider_Box, Slider_slider_up, Display_X * 0.68, Display_Y * 0.78, Display_X * 0.01, Display_Y * 0.16, Display_X * 0.02, Display_Y * 0.04, &chattingdrag, 0, (Display_Y * 0.2) - ((int)(Display_Y * 0.2) % 10), Display_Y * 0.2 - ((int)(Display_Y * 0.2) % 10), VERTICAL);
					continue;
				}

				if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 59, 127, 172, Display_X * 0.74, Display_Y * 0.93, Display_X * 0.09, Display_Y * 0.04, 8, 1, &event, &happen)) //닉네임 변경 버튼
				{
					roop = 1;
					break;
				}
				PutText(renderer, "닉네임 변경", Display_X * 0.75, Display_Y * 0.935, 25 * ((float)Display_X / 1920), 255, 255, 255, 1);

				if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 59, 127, 172, Display_X * 0.86, Display_Y * 0.93, Display_X * 0.09, Display_Y * 0.04, 8, 1, &event, &happen)) //로그아웃 버튼
				{
					quit = 0;
					loginsuccess = 0;
					roop = 1;
					break;
				}
				PutText(renderer, "로그아웃", Display_X * 0.88, Display_Y * 0.935, 25 * ((float)Display_X / 1920), 255, 255, 255, 1);
				if (warning.ison == 1)
				{
					PutText(renderer, warning.message, warning.x, warning.y, warning.size, warning.r, warning.g, warning.b, 1);
				}

				if (nonhappen == true && happen == false) {
					happen = true;
					nonhappen = false;
				}
				if (happen == true)
				{
					nonhappen = true;
				}
				if (happen || textinput) {
					happen = false;
					textinput = false;
					SDL_RenderPresent(renderer);
				}

			}
			free(chatslide);
			SDL_DestroyTexture(WaitRoom_setting_click);
			SDL_DestroyTexture(WaitRoom_setting_noclick);
			SDL_DestroyTexture(User_Pencil);
			SDL_DestroyTexture(Slider_slider_up);
			SDL_DestroyTexture(Chating_click);
			SDL_DestroyTexture(Chating_put);
			SDL_DestroyTexture(Room_Lock);
			SDL_DestroyTexture(Slider_Box);
			SDL_DestroyTexture(Room_Back_click);
			SDL_DestroyTexture(Room_Back_noclick);
			SDL_DestroyTexture(Chating_noput);
			SDL_DestroyTexture(myProfile);
			RefrashEvent = -1;
			sprintf(query, "update user set status = 0 where ownnum = %d", myuser->ownnum);
			mysql_query(cons, query);
		}
		system("cls");
		if (isplaygame)
		{
			qquit = 0;
			if (ClientParam.Cconnect_socket == 0)
			{
				loginsuccess = 1;
				roop = 1;
				qquit = 1;
			}
			SDL_Texture * can = LoadTexture(renderer, ".\\design\\can.png");

			//배경
			SDL_SetRenderDrawColor(renderer, 191, 191, 191, 0);
			SDL_RenderClear(renderer);
			//1번구역
			FillRoundRect(renderer, 255, 255, 255, 10, 10, Display_X * 0.7, Display_Y * 0.69, 14);
			DrawRoundRect(renderer, 191, 191, 191, 9, 9, Display_X * 0.7 + 2, Display_Y * 0.69 + 2, 14, 1);
			FillUpRoundRect(renderer, 146, 208, 80, 10, 10, Display_X * 0.7, Display_Y * 0.035, 14);
			PutText(renderer, "대기실", (Display_X * 0.33), 10, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
			//1

			//2번구역
			FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, 10, Display_X * 0.275, Display_Y * 0.69, 14);
			RenderTextureXYWH(renderer, can, Display_X * 0.7 + 22, Display_Y*0.042, Display_X*0.277, Display_Y*0.046); //앙
			DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, 9, Display_X * 0.275 + 2, Display_Y * 0.69 + 2, 14, 1);
			FillUpRoundRect(renderer, 146, 208, 80, Display_X * 0.7 + 22, 10, Display_X * 0.275, Display_Y * 0.035, 14);
			PutText(renderer, "방 정보", (Display_X * 0.815), 10, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);

			//방 정보 출력
			PutText(renderer, My_Room.mode, Display_X * (0.77 - strlen(My_Room.mode) * 0.005), Display_Y * 0.05, 30 * ((float)Display_X / 1920), 0, 0, 0, 1);
			sprintf(query, "%d문제", My_Room.question);
			PutText(renderer, query, Display_X * 0.823, Display_Y * 0.05, 30 * ((float)Display_X / 1920), 0, 0, 0, 1);
			sprintf(query, "%d초", My_Room.time);
			PutText(renderer, query, Display_X * 0.92, Display_Y * 0.05, 30 * ((float)Display_X / 1920), 0, 0, 0, 1);
			//3번구역
			FillRoundRect(renderer, 255, 255, 255, 10, Display_Y * 0.7 + 10, Display_X * 0.7, Display_Y * 0.27, 14);
			DrawRoundRect(renderer, 191, 191, 191, 9, Display_Y * 0.7 + 10 - 1, Display_X * 0.7 + 2, Display_Y * 0.27 + 2, 14, 1);
			FillUpRoundRect(renderer, 146, 208, 80, 10, Display_Y * 0.7 + 10, Display_X * 0.7, Display_Y * 0.035, 14);
			PutText(renderer, "채팅", (Display_X * 0.335), Display_Y * 0.7 + 10, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);

			//4번구역
			FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, Display_Y * 0.7 + 10, Display_X * 0.275, Display_Y * 0.27, 14);
			DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, Display_Y * 0.7 + 9, Display_X * 0.275 + 2, Display_Y * 0.27 + 2, 14, 1);


			while (!qquit) {
				SDL_WaitEventTimeout(&event, 500);
				switch (event.type)
				{
				case SDL_MOUSEMOTION:

					break;
				case SDL_QUIT:
					qquit = true;
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
					case SDL_WINDOWEVENT_CLOSE:// 다수 창에서의 닫기이벤트가 발생할경우
						qquit = true;
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

				if (ClientParam.sockethappen == 1)
				{

					GetRoomUser(cons, gameuser, renderer);
					FillRoundRect(renderer, 255, 255, 255, 10, 10, Display_X * 0.7, Display_Y * 0.69, 14);
					DrawRoundRect(renderer, 191, 191, 191, 9, 9, Display_X * 0.7 + 2, Display_Y * 0.69 + 2, 14, 1);
					FillUpRoundRect(renderer, 146, 208, 80, 10, 10, Display_X * 0.7, Display_Y * 0.035, 14);
					PutText(renderer, "대기실", (Display_X * 0.33), 10, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);

					if (gameuser[0].status) {
						FillRoundRect(renderer, 232, 232, 232, Display_X * 0.03, Display_Y * 0.07, Display_X * 0.32, Display_Y * 0.275, 20);
						FillUpRoundRect(renderer, 0, 176, 240, Display_X * 0.03, Display_Y * 0.07, Display_X * 0.32, Display_Y * 0.04, 20);
						RenderTextureXYWH(renderer, gameuser[0].Profile, Display_X * 0.08, Display_Y * 0.12, 148 * ((float)Display_X / 1920), 173 * ((float)Display_X / 1920));
						if (gameuser[0].status == 2)
							PutText(renderer, "Ready", Display_X * 0.166, Display_Y * 0.07, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
						PutText(renderer, gameuser[0].Nickname, Display_X * 0.2, Display_Y * 0.15, 40 * ((float)Display_X / 1920), 0, 0, 0, 1);
						sprintf(query, "Lv %.2d", gameuser[0].Level);
						PutText(renderer, query, Display_X * 0.2, Display_Y * 0.25, 30 * ((float)Display_X / 1920), 0, 0, 0, 1);
					}
					//2
					if (gameuser[1].status) {
						FillRoundRect(renderer, 232, 232, 232, Display_X * 0.37, Display_Y * 0.07, Display_X * 0.32, Display_Y * 0.275, 20);
						FillUpRoundRect(renderer, 0, 176, 240, Display_X * 0.37, Display_Y * 0.07, Display_X * 0.32, Display_Y * 0.04, 20);
						RenderTextureXYWH(renderer, gameuser[1].Profile, Display_X * 0.42, Display_Y * 0.12, 148 * ((float)Display_X / 1920), 173 * ((float)Display_X / 1920));
						if (gameuser[1].status == 2)
							PutText(renderer, "Ready", Display_X * 0.51, Display_Y * 0.07, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
						PutText(renderer, gameuser[1].Nickname, Display_X * 0.55, Display_Y * 0.15, 40 * ((float)Display_X / 1920), 0, 0, 0, 1);
						sprintf(query, "Lv %.2d", gameuser[1].Level);
						PutText(renderer, query, Display_X * 0.55, Display_Y * 0.25, 30 * ((float)Display_X / 1920), 0, 0, 0, 1);
					}
					//3
					if (gameuser[2].status) {
						FillRoundRect(renderer, 232, 232, 232, Display_X * 0.03, Display_Y * 0.37, Display_X * 0.32, Display_Y * 0.275, 20);
						FillUpRoundRect(renderer, 0, 176, 240, Display_X * 0.03, Display_Y * 0.37, Display_X * 0.32, Display_Y * 0.04, 20);
						RenderTextureXYWH(renderer, gameuser[2].Profile, Display_X * 0.08, Display_Y * 0.42, 148 * ((float)Display_X / 1920), 173 * ((float)Display_X / 1920));
						if (gameuser[2].status == 2)
							PutText(renderer, "Ready", Display_X * 0.166, Display_Y * 0.37, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
						PutText(renderer, gameuser[2].Nickname, Display_X * 0.2, Display_Y * 0.47, 40 * ((float)Display_X / 1920), 0, 0, 0, 1);
						sprintf(query, "Lv %.2d", gameuser[2].Level);
						PutText(renderer, query, Display_X * 0.2, Display_Y * 0.57, 30 * ((float)Display_X / 1920), 0, 0, 0, 1);

					}
					//4
					if (gameuser[3].status) {
						FillRoundRect(renderer, 232, 232, 232, Display_X * 0.37, Display_Y * 0.37, Display_X * 0.32, Display_Y * 0.275, 20);
						FillUpRoundRect(renderer, 0, 176, 240, Display_X * 0.37, Display_Y * 0.37, Display_X * 0.32, Display_Y * 0.04, 20);
						RenderTextureXYWH(renderer, gameuser[3].Profile, Display_X * 0.42, Display_Y * 0.42, 148 * ((float)Display_X / 1920), 173 * ((float)Display_X / 1920));
						if (gameuser[3].status == 2)
							PutText(renderer, "Ready", Display_X * 0.51, Display_Y * 0.37, 30 * ((float)Display_X / 1920), 255, 255, 255, 1);
						PutText(renderer, gameuser[3].Nickname, Display_X * 0.55, Display_Y * 0.47, 40 * ((float)Display_X / 1920), 0, 0, 0, 1);
						sprintf(query, "Lv %.2d", gameuser[3].Level);
						PutText(renderer, query, Display_X * 0.55, Display_Y * 0.57, 30 * ((float)Display_X / 1920), 0, 0, 0, 1);
					}
					ClientParam.sockethappen = 0;
				}
				if (ClientParam.sockethappen == -1)
				{
					loginsuccess = 1;
					roop = 1;
					qquit = true;
				}
				if (PutRoundButton(renderer, 3, 114, 237, 23, 134, 255, 3, 114, 237, Display_X*0.7317, Display_Y*0.7222, Display_X*0.2343, Display_Y*0.1157, 20, 0, &event, &happen)) //나가기 버튼 
				{
					loginsuccess = 1;
					roop = 1;
					send(ClientParam.Cconnect_socket, "exit", 30, 0);
					Sleep(100);
					ClientParam.sockethappen = 5;
					ClientParam.Cconnect_socket = 0;

					ServerParam.sockethappen = 5;
					if (bangsang == 1) {
						sprintf(query, "delete from room where num = %d", My_Room.ownnum);
						ServerParam.sockethappen = 5;
						mysql_query(cons, query);
						closesocket(ServerParam.Slisten_socket);

						bangsang = 0;
					}
					WSACleanup();
					qquit = true;
				}
				PutText(renderer, "나가기", Display_X*0.807, Display_Y*0.75, 57 * ((float)Display_X) / 1920, 255, 255, 255, 1);


				if (PutRoundButton(renderer, 255, 0, 0, 210, 0, 0, 255, 0, 0, Display_X*0.7317, Display_Y*0.85, Display_X*0.2343, Display_Y*0.1157, 20, 0, &event, &happen)) //시작하기, 준비 버튼
				{

					send(ClientParam.Cconnect_socket, "ready", 40, 0);
				}
				PutText(renderer, "준비하기", Display_X*0.796, Display_Y*0.87, 57 * ((float)Display_X) / 1920, 255, 255, 255, 1);    //방장일때는 시작하기


				SDL_RenderPresent(renderer);
			}


			SDL_DestroyTexture(can);
			isplaygame = 0;
		}
	}
	HitMind_TTF_Close();
	HitMind_TTF2_Close();
	if (myuser != 0)
		free(myuser);
	if (status.ishappen == 1)
		mysql_close(status.arg);
	if (cursor)
	{
		SDL_FreeCursor(cursor);
	}
	Mix_FreeMusic(lobbymusic);
	Mix_FreeMusic(mainmusic);
	SDL_DestroyTexture(LoadingBar);
	SDL_DestroyTexture(WaitBar);
	SDL_DestroyTexture(TitleText);
	SDL_DestroyTexture(TitleImage);
	SDL_DestroyTexture(LoadingBar);
	SDL_DestroyTexture(WaitBar);
	SDL_DestroyTexture(TitleText);
	SDL_DestroyTexture(TitleImage);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);


	SDL_DestroyWindow(Window);
	SDL_Quit();


	return 0;
}

