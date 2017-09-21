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
	Connect_status status;	//MySQL이 연결된 상태를 저장하는 구조체
	MYSQL *cons = 0;		//MySQL선언
	status.arg = cons;		//status에 mysql의 주소를 저장한다
	status.ishappen = false;//연결이 안된 상태
	SDL_Window * Window = NULL;		//SDL 관련
	SDL_Renderer *renderer;			//SDL - 렌더러로 그리기에 씀
	SDL_Event event;				//SDL 이벤트를 저장함
	Warning_M warning = { 0, "", 0, 0, 0,0, 0, 0 };
	TTF_Init();		//TTF 초기화
	char version[] = "1.0.1 - Beta";		//현제 버전
	TTF_Font *font = TTF_OpenFont(".\\font\\NanumGothic.ttf", 30);	//나눔고딕 폰트를 불러옴
	if (font == 0)
	{
		printf("error");
		getchar();
	}
	SDL_Init(SDL_INIT_EVERYTHING);						//SDL 초기화
	Window = SDL_CreateWindow("HitMind_2", 0, 0, Display_X, Display_Y, SDL_WINDOW_ALLOW_HIGHDPI);		//해당 해상도로 Window를 생성함
	renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture * WaitBar = LoadTexture(renderer, ".\\maintema\\touch.png");		//계속하려면 클릭해주세요... 이미지
	SDL_Texture * TitleText = LoadTexture(renderer, ".\\mainicon\\MainText.png");	//HitMind 글씨 이미지
	SDL_Texture * TitleImage = LoadTexture(renderer, ".\\mainicon\\main_wallpaper.jpg");

	SDL_Texture * LoadingBar = LoadTexture(renderer, ".\\maintema\\loading.png");
	int quit = false; // while문 조건문에 쓰이는 불 변수
	int loginpopup = false; //로그인 팝업 반복문 상태
	int create_password_status = false;
	int loginsuccess = false; //로그인 성공 상태
	int find_password_status = false;
	Hit_User * myuser = 0;
	int hanyeong = false; // 한영키상태에 쓰이는 불 변수
	int i, j;
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
	char query[128];
	char utf8[256] = ""; // utf8 변환에 필요한 배열
	int slice = 0;
	int sum;
	SDL_Color color = { 0,0,0 ,0 };
	int ID_INPUT;
	int PASSWORD_INPUT;
	int PressButton = 0;
	int autologin_checking;
	//while (!quit)	//로그인 성공 후 대기창
	//{
	//	if (SDL_PollEvent(&event))
	//	{
	//		switch (event.type)
	//		{
	//		case SDL_QUIT:
	//			quit = true;
	//			break;
	//		case SDL_WINDOWEVENT:
	//			switch (event.window.event) {
	//			case SDL_WINDOWEVENT_CLOSE:// 다수 창에서의 닫기이벤트가 발생할경우

	//				quit = true;
	//				Sleep(100);
	//				break;// 브레이크
	//			case SDL_WINDOWEVENT_ENTER:// 윈도우
	//				SDL_RaiseWindow(SDL_GetWindowFromID(event.window.windowID));//포커스 이동시킴
	//				break;
	//			case SDL_WINDOWEVENT_LEAVE:
	//				//	drag = false;//마우스가 창에서 나갔으므로 드래그 기능을 중지시킴
	//				break;
	//			case SDL_WINDOWEVENT_FOCUS_GAINED:
	//				break;

	//			}
	//		}
	//	}

	//	SDL_SetRenderDrawColor(renderer, 216, 216, 216, 0);
	//	SDL_RenderClear(renderer);
	//	FillRoundRect(renderer, 255, 255, 255, 10, 10, Display_X * 0.7, Display_Y * 0.7, 14, 0);

	//	FillRoundRect(renderer, 0, 176, 255, Display_X / 13, Display_Y / 15, Display_X / 4, Display_Y / 8, 14, 0);

	//	FillRoundRect(renderer, 255, 0, 0, Display_X / 2.5, Display_Y / 15, Display_X / 4, Display_Y / 8, 15, 10);
	//	SDL_RenderPresent(renderer);
	//}
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)Thread_MySQL, (void *)&status, 0, 0);

	while (!quit && !loginsuccess)
	{
		if (SDL_PollEvent(&event)) {
			switch (event.type) {/*
			case SDL_TEXTINPUT: // 채팅 입력 이벤트
				if (hanyeong == true && (event.text.text[0] == -29 || event.text.text[0] + 256 >= 234 && event.text.text[0] + 256 <= 237))// 한글일 경우
				{
					wcscpy(wchar, L"");
					int sum = (event.text.text[0] + 22) * 64 * 64 + (event.text.text[1] + 128) * 64 + event.text.text[2] + 41088;
					wchar[0] = sum;
					wcscat(wstr, wchar);
					if (event.text.text[0] == -29)
						slice = 1;
					else
						slice = 1 + !((wchar[0] - 0xac00) % 28);
				}
				else if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') && (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {// 영어 입력 시
					wcscpy(wchar, L"");
					swprintf(wchar, sizeof(wchar) / sizeof(wchar_t), L"%hs", event.text.text);// event.text.text 문자열 그냥 연결시켜버림
					wcscat(wstr, wchar);// 문자열 연결
					hangeul = false;
					slice = 0;
				}
				textinput = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_RETURN) {
					if (hangeul == true && enter == false)
						enter = true;
					else {
						strcpy(utf8, UNICODE2UTF8(wstr, wcslen(wstr)));
						UTF82EUCKR(euckr, 512, utf8, 768);
						euckr[strlen(euckr)] = '\0';
						han2unicode(euckr, unicode);
						if (hannum(unicode, wcslen(unicode)) != hannum(wstr, wcslen(wstr))) {
							strcpy(euckr, "[Error] invalid conversion");
						}
						// euckr을 DB에 올리면 됨
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
					if (slice == 0) {
						wstr[wcslen(wstr) - 1] = '\0';// 마지막문자를 널문자로 바꿈
						textinput = true;
					}
					else {
						slice--;
					}
				}
				else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {// 컨트롤 모드이고 c를 눌렀다면
					strcpy(utf8, UNICODE2UTF8(wstr, wcslen(wstr)));
					SDL_SetClipboardText(utf8);// 클립보드에 넣음
				}
				else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {// 컨트롤 모드이고 v를 눌렀다면
					wcscat(wstr, UTF82UNICODE(SDL_GetClipboardText(), strlen(SDL_GetClipboardText())));// 클립보드에서 가져옴
					hangeul = false;
					textinput = true;
				}
				else {
					hangeul = true;
					slice++;
				}
				break;*/
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
		}
		RenderTextureXYWH(renderer, TitleImage, 0, 0, Display_X, Display_Y);
		RenderTextureXYWH(renderer, TitleText, Display_X / 4, Display_Y / 10, Display_X / 2, Display_Y / 3);
		PutText(renderer, version, 20, (Display_Y / 20) * 19, Display_X / 48, 255, 255, 255);

		if (status.ishappen == false)
			RenderTextureXYWH(renderer, LoadingBar, 0, Display_Y / 1.3, Display_X, Display_Y / 15);
		else {
			RenderTextureXYWH(renderer, WaitBar, 0, Display_Y / 1.3, Display_X, Display_Y / 15);
			if (PressButton)	//계속하려면 클릭하세요 버튼을 누를때
			{
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
				memset(&ID_put, 0, sizeof(ID_put));
				memset(&Password_put, 0, sizeof(Password_put));
				while (loginpopup && !loginsuccess)
				{
					if (SDL_PollEvent(&event))
					{
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
									else if (PASSWORD_INPUT == 1) {
										strcpy(utf8, UNICODE2UTF8(ID_put, wcslen(ID_put)));
										UTF82EUCKR(db_id, 512, utf8, 768);
										db_id[strlen(db_id)] = '\0';
										strcpy(utf8, UNICODE2UTF8(Password_put, wcslen(Password_put)));
										UTF82EUCKR(db_password, 512, utf8, 768);
										db_password[strlen(db_password)] = '\0';
										myuser = User_Login_sql(cons, db_id, db_password);
										if (myuser == -1)
										{
											printf("\n아이디 오류");
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
											printf("\n비밀번호 오류");
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
											else
												loginsuccess = true;
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
									printf("\nslice아니 상태");
									if (ID_INPUT == 1)
										ID_put[wcslen(ID_put) - 1] = '\0';
									else if (PASSWORD_INPUT == 1)
										Password_put[wcslen(Password_put) - 1] = '\0';
									textinput = true;
								}
								else {
									printf("\nslice상태");
									slice--;
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
						if (PutButtonImage(renderer, login_close_noclick, login_close_click, Display_X / 4 + 565, Display_Y / 4, 101, 83, &event)) {
							MouseUP_Wait;
							loginpopup = false;
						}


						if (ID_INPUT == 0) {	//아이디 입력창
							if (PutButtonImage(renderer, login_input_id_noclick, login_input_id_noclick, Display_X / 4 + 22, Display_Y / 4 + 110, 617, 63, &event))
							{
								ID_INPUT = 1;
								PASSWORD_INPUT = 0;
							}
						}
						else
							RenderTextureXYWH(renderer, login_input_id_click, Display_X / 4 + 22, Display_Y / 4 + 110, 617, 63);

						if (PASSWORD_INPUT == 0) {	//비밀번호 입력창
							if (PutButtonImage(renderer, login_input_id_noclick, login_input_id_noclick, Display_X / 4 + 22, Display_Y / 4 + 208, 617, 63, &event))
							{
								ID_INPUT = 0;
								PASSWORD_INPUT = 1;
							}
						}
						else
							RenderTextureXYWH(renderer, login_input_id_click, Display_X / 4 + 22, Display_Y / 4 + 208, 617, 63);

						if (PutButtonImage(renderer, login_button_id_noclick, login_button_id_click, Display_X / 4 + 489, Display_Y / 4 + 273, 147, 71, &event))	//로그인 버튼
						{
							strcpy(utf8, UNICODE2UTF8(ID_put, wcslen(ID_put)));
							UTF82EUCKR(db_id, 512, utf8, 768);
							db_id[strlen(db_id)] = '\0';
							strcpy(utf8, UNICODE2UTF8(Password_put, wcslen(Password_put)));
							UTF82EUCKR(db_password, 512, utf8, 768);
							db_password[strlen(db_password)] = '\0';
							myuser = User_Login_sql(cons, db_id, db_password);
							if (myuser == -1)
							{
								printf("\n아이디 오류");
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
								printf("\n비밀번호 오류");
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
									sprintf(query, "update user set auto_login = '%s' where ownnum = %d", GetDefaultMyIP(), myuser->ownnum);
									if (mysql_query(cons, query) == 0)
										loginsuccess = true;
									else
									{
										printf("\n자동 로그인 오류");
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
								else
									loginsuccess = true;
							}
						}

						if (PutButtonImage(renderer, autologin_noclick, autologin_click, Display_X / 4 + 40, Display_Y / 4 + 280, 194, 47, &event))	//자동로그인 체크박스
						{
							MouseUP_Wait;
							if (autologin_checking == 0)
								autologin_checking = 1;
							else
								autologin_checking = 0;
						}
						if (autologin_checking == 1)		//로그인 체크
						{
							RenderTextureXYWH(renderer, autologin_check, Display_X / 4 + 23, Display_Y / 4 + 255, 211, 80);
						}
						if (PutButtonImage(renderer, login_signup_noclick, login_signup_click, Display_X / 4 + 85, Display_Y / 4 + 335, 182, 71, &event))	//회원가입 버튼
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
								if (SDL_PollEvent(&event))
								{
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
											if (pass_reset_mode < 5)
												pass_reset_mode += 1;
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
								}
								RenderTextureXYWH(renderer, create_back, Display_X / 4, Display_Y / 4, 666, 570);
								if (PutButtonImage(renderer, login_close_noclick, login_close_click, Display_X / 4 + 565, Display_Y / 4, 101, 83, &event))
									create_password_status = false;
								if (PutButtonImage(renderer, create_button_noclick, create_button_click, Display_X / 4 + 480, Display_Y / 4 + 495, 166, 71, &event)) {
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
										if (PutButtonImage(renderer, create_ID_noclick, create_ID_noclick, Display_X / 4 + 22, Display_Y / 4 + 15 + (95 * i), 617, 63, &event))
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
									if (PutButtonImage(renderer, create_father_noclick, create_father_noclick, Display_X / 4 + 25, Display_Y / 4 + 493, 428, 64, &event))
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
										PutText_Unicode(renderer, change_password[i - 1], Display_X / 4 + 40, Display_Y / 4 + 30 + (95 * i), 25, color);
									else
									{
										for (j = 0; j < wcslen(change_password[i - 1]); j++)
											query[j] = '*';
										query[j] = 0;
										PutText(renderer, query, Display_X / 4 + 40, Display_Y / 4 + 30 + (95 * i), 25, 0, 0, 0);
									}
								}
								if (warning.ison == 1)
								{
									PutText(renderer, warning.message, warning.x, warning.y, warning.size, warning.r, warning.g, warning.b);
								}
								SDL_RenderPresent(renderer);

							}
							if (warning.r == 255)
								warning.ison = 0;
							RenderTextureXYWH(renderer, TitleImage, 0, 0, Display_X, Display_Y);
							RenderTextureXYWH(renderer, TitleText, Display_X / 4, Display_Y / 10, Display_X / 2, Display_Y / 4);
							PutText(renderer, version, 20, (Display_Y / 20) * 19, Display_X / 48, 255, 255, 255);
							SDL_DestroyTexture(create_back);
							SDL_DestroyTexture(create_ID_click);
							SDL_DestroyTexture(create_ID_noclick);
							SDL_DestroyTexture(create_button_click);
							SDL_DestroyTexture(create_button_noclick);
							SDL_DestroyTexture(create_father_click);
							SDL_DestroyTexture(create_father_noclick);
						}
						if (PutButtonImage(renderer, login_findpassword_noclick, login_findpassword_click, Display_X / 4 + 305, Display_Y / 4 + 335, 269, 71, &event))
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
								if (SDL_PollEvent(&event))
								{
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
											if (pass_reset_mode < 4)
												pass_reset_mode += 1;
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
								}
								RenderTextureXYWH(renderer, find_back, Display_X / 4, Display_Y / 4, 666, 484);
								if (PutButtonImage(renderer, login_close_noclick, login_close_click, Display_X / 4 + 565, Display_Y / 4, 101, 83, &event))
									find_password_status = false;
								if (PutButtonImage(renderer, find_button_noclick, find_button_click, Display_X / 4 + 480, Display_Y / 4 + 400, 161, 71, &event))
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
										if (PutButtonImage(renderer, find_ID_noclick, find_ID_noclick, Display_X / 4 + 22, Display_Y / 4 + 15 + (95 * i), 617, 63, &event))
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
									if (PutButtonImage(renderer, find_father_noclick, find_father_noclick, Display_X / 4 + 25, Display_Y / 4 + 395, 428, 64, &event))
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
										PutText_Unicode(renderer, change_password[i - 1], Display_X / 4 + 40, Display_Y / 4 + 30 + (95 * i), 25, color);
									else
									{
										for (j = 0; j < wcslen(change_password[i - 1]); j++)
											query[j] = '*';
										query[j] = 0;
										PutText(renderer, query, Display_X / 4 + 40, Display_Y / 4 + 30 + (95 * i), 25, 0, 0, 0);
									}
								}
								if (warning.ison == 1)
								{
									PutText(renderer, warning.message, warning.x, warning.y, warning.size, warning.r, warning.g, warning.b);
								}
								SDL_RenderPresent(renderer);

							}
							RenderTextureXYWH(renderer, TitleImage, 0, 0, Display_X, Display_Y);
							RenderTextureXYWH(renderer, TitleText, Display_X / 4, Display_Y / 10, Display_X / 2, Display_Y / 4);
							PutText(renderer, version, 20, (Display_Y / 20) * 19, Display_X / 48, 255, 255, 255);
							SDL_DestroyTexture(find_back);
							SDL_DestroyTexture(find_ID_click);
							SDL_DestroyTexture(find_ID_noclick);
							SDL_DestroyTexture(find_button_click);
							SDL_DestroyTexture(find_button_noclick);
							SDL_DestroyTexture(find_father_click);
							SDL_DestroyTexture(find_father_noclick);
							warning.ison = 0;
						}

						PutText_Unicode(renderer, ID_put, Display_X / 4 + 35, Display_Y / 4 + 117, 30, color);
						for (i = 0; i < wcslen(Password_put); i++)
							query[i] = '*';
						query[i] = 0;
						PutText(renderer, query, Display_X / 4 + 35, Display_Y / 4 + 215, 30, 0, 0, 0);

						textinput = false;
						if (warning.ison == 1)
						{
							PutText(renderer, warning.message, warning.x, warning.y, warning.size, warning.r, warning.g, warning.b);
						}
						SDL_RenderPresent(renderer);
					}
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
		//	PutButtonImage(renderer, WaitBar, LoadingBar, 0, Display_Y / 1.3, Display_X, Display_Y / 15, &event);
		/*if (textinput == true) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			SDL_RenderClear(renderer);
			PutText_Unicode(renderer, wstr, 0, 0, 30, color);



			textinput = false;
		}*/
			SDL_RenderPresent(renderer);
		//SDL_WaitEvent(&event);
	}
	SDL_DestroyTexture(LoadingBar);
	SDL_DestroyTexture(WaitBar);
	SDL_DestroyTexture(TitleText);
	SDL_DestroyTexture(TitleImage);
	if (loginsuccess == 1)
	{
		
	}
	quit = 0;
	while (loginsuccess && !quit)	//로그인 성공 후 대기창
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
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
			}
		}
		SDL_SetRenderDrawColor(renderer, 216, 216, 216, 0);
		SDL_RenderClear(renderer);
		FillRoundRect(renderer, 255, 255, 255, 10, 10, Display_X * 0.7, Display_Y * 0.69, 14, 0);
		DrawRoundRect(renderer, 191, 191, 191, 9, 9, Display_X * 0.7 + 2, Display_Y * 0.69 + 2, 14, 1);
		FillRoundRect(renderer, 255, 255, 255, 10, Display_Y * 0.7 + 10, Display_X * 0.7, Display_Y * 0.27, 14, 0);
		DrawRoundRect(renderer, 191, 191, 191, 9, Display_Y * 0.7 + 10 -1, Display_X * 0.7 + 2, Display_Y * 0.27 + 2, 14, 1);

		FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, Display_Y * 0.7 + 10, Display_X * 0.275, Display_Y * 0.275, 14, 0);
		DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, Display_Y * 0.7 + 9, Display_X * 0.275 + 2, Display_Y * 0.275 + 2, 14, 1);


		FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, Display_Y * 0.2, Display_X * 0.275, Display_Y * 0.5, 14, 0);
		DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, Display_Y * 0.2 - 1, Display_X * 0.275 + 2, Display_Y * 0.5 + 2, 14, 1);

		FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, 10, Display_X * 0.275, Display_Y * 0.178, 3, 0);
		DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, 9, Display_X * 0.275 + 2, Display_Y * 0.178 + 2, 3, 1);


		//FillRoundRect(renderer, 0, 176, 255, Display_X / 13, Display_Y / 15, Display_X / 4, Display_Y / 8, 14, 0);
		//FillRoundRect(renderer, 255, 0, 0, Display_X / 2.5, Display_Y / 15, Display_X / 4, Display_Y / 8, 15, 10);
		SDL_RenderPresent(renderer);
	}

	if (status.ishappen == 1)
		mysql_close(status.arg);


	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
	return 0;
}

