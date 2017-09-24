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
	settings(&Display_X, &Display_Y, &BGmusic, &Sound, &Full);
	SDL_Init(SDL_INIT_EVERYTHING);						//SDL 초기화
	if (Full)
		Window = SDL_CreateWindow("HitMind_2", 100, 100, Display_X, Display_Y, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN_DESKTOP);		//해당 해상도로 Window를 생성함
	else
		Window = SDL_CreateWindow("HitMind_2", 100, 100, Display_X, Display_Y, SDL_WINDOW_ALLOW_HIGHDPI);		//해당 해상도로 Window를 생성함
	renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture * WaitBar = LoadTexture(renderer, ".\\maintema\\touch.png");		//계속하려면 클릭해주세요... 이미지
	SDL_Texture * TitleText = LoadTexture(renderer, ".\\mainicon\\MainText.png");	//HitMind 글씨 이미지
	SDL_Texture * TitleImage = LoadTexture(renderer, ".\\mainicon\\main_wallpaper.jpg");

	SDL_Texture * LoadingBar = LoadTexture(renderer, ".\\maintema\\loading.png");
	int qquit = false;
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
	int setting_main = 0;
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
	// 테스트 코드
	//Canvas * canvas = (Canvas*)malloc(sizeof(canvas));
	//CreateCanvas(canvas,renderer,10+14,10+14, Display_X * 0.8-2*14, Display_Y * 0.76-2*14,10);
	//Slider * StrongSlider = (Slider *)malloc(sizeof(Slider));
	//SDL_Texture * BarTexture = LoadTexture(renderer, ".//design//slider.png");
	//SDL_Texture * BoxTexture = LoadTexture(renderer, ".//design//val4.png");
	//CreateSlider(StrongSlider, BoxTexture, BarTexture, Display_X * 0.8 + 22 + (Display_X*0.1825*0.07), Display_Y * 0.64 + 10 + (Display_Y * 0.34*0.275), Display_X * 0.1825 - 2 * (Display_X*0.1825*0.07), (Display_Y * 0.34*0.05), Display_X*0.02, Display_Y*0.05, &canvas->Strong,1.0, 50.0, 10.0, HORIZONTAL);
	//SDL_Texture * RgbCode = LoadTexture(renderer,".//design//RgbCode.jpg");
	//SDL_Rect RgbRect = { Display_X * 0.8 + 22+(Display_X*0.1825*0.07), Display_Y * 0.64 + 10+ (Display_Y * 0.34*0.375), Display_X * 0.1825-2* (Display_X*0.1825*0.07), (Display_Y * 0.34*0.6) };
	//SDL_SetRenderDrawColor(renderer, 191, 191, 191, 0);
	//SDL_RenderClear(renderer);
	////1번구역
	//FillRoundRect(renderer, 255, 255, 255, 10, 10, Display_X * 0.8, Display_Y * 0.76, 14);
	//DrawRoundRect(renderer, 191, 191, 191, 9, 9, Display_X * 0.8 + 2, Display_Y * 0.76 + 2, 14, 1);
	////4번구역
	//FillRoundRect(renderer, 255, 255, 255, 10, Display_Y * 0.77 + 10, Display_X * 0.8, Display_Y * 0.21, 14);
	//DrawRoundRect(renderer, 191, 191, 191, 9, Display_Y * 0.77 + 10 - 1, Display_X * 0.8 + 2, Display_Y * 0.21 + 2, 14, 1);
	////5번구역
	//FillRoundRect(renderer, 255, 255, 255, Display_X * 0.8 + 22, Display_Y * 0.64 + 10, Display_X * 0.1825, Display_Y * 0.34, 14);
	//DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.8 + 21, Display_Y * 0.64 + 9, Display_X * 0.1825 + 2, Display_Y * 0.34 + 2, 14, 1);
	////3번구역
	//FillRoundRect(renderer, 255, 255, 255, Display_X * 0.8 + 22, Display_Y * 0.2 + 10, Display_X * 0.1825, Display_Y * 0.43, 14);
	//DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.8 + 21, Display_Y * 0.2 + 9, Display_X * 0.1825 + 2, Display_Y * 0.43 + 2, 14, 1);
	////2번구역
	//FillRoundRect(renderer, 255, 255, 255, Display_X * 0.8 + 22, 10, Display_X * 0.1825, Display_Y * 0.19, 3);
	//DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.8 + 21, 9, Display_X * 0.1825 + 2, Display_Y * 0.19 + 2, 3, 1);

	//while (!quit)//로그인 성공 후 대기창
	//{
	//	SDL_WaitEvent(&event);
	//	
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
	//				//drag = false;//마우스가 창에서 나갔으므로 드래그 기능을 중지시킴
	//				break;
	//			case SDL_WINDOWEVENT_FOCUS_GAINED:
	//				break;
	//			}
	//		}
	//	
	//	SDL_SetRenderDrawColor(renderer, canvas->Color.r, canvas->Color.g, canvas->Color.b, canvas->Color.a);
	//	for(int i=0;i<15;i++)
	//		SDL_RenderDrawLine(renderer,0,i,100,100);
	//	RenderTexture(renderer, RgbCode, &RgbRect);
	//	DrawSlider(renderer, StrongSlider);
	//	ChangeColor(&event, &canvas->Color, RgbRect);
	//	UpdateSlider(StrongSlider, &event);
	//	UpdateCanvas(canvas, &event);
	//	SDL_RenderPresent(renderer);
	//}
	_beginthreadex(NULL, 0, (_beginthreadex_proc_type)Thread_MySQL, (void *)&status, 0, 0);
	while (roop)
	{
		roop = 0;
		quit = 0;
		loginsuccess = 0;
		while (!quit && !loginsuccess)
		{
			//	if (SDL_PollEvent(&event)) {

			SDL_WaitEvent(&event);
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
			//	}
			RenderTextureXYWH(renderer, TitleImage, 0, 0, Display_X, Display_Y);
			RenderTextureXYWH(renderer, TitleText, Display_X / 4, Display_Y / 10, Display_X / 2, Display_Y / 3);
			PutText(renderer, version, 20, (Display_Y / 20) * 19, Display_X / 48, 255, 255, 255);

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
											//	printf("\n아이디 오류");
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
											//	printf("\n비밀번호 오류");
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
											else {
												sprintf(query, "update user set auto_login = 'not' where ownnum = %d", myuser->ownnum);
												if (mysql_query(cons, query) == 0)
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
						if (pass_length != 0)
						{
							if (autologin_checking == 1) {
								ID_INPUT = 0;
								PASSWORD_INPUT = 0;
							}
						}
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
									sprintf(query, "update user set auto_login = PASSWORD('%s') where ownnum = %d", GetDefaultMyIP(), myuser->ownnum);
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
						if (pass_length == 0)
							for (i = 0; i < wcslen(Password_put); i++)
								query[i] = '*';
						else
							for (i = 0; i < pass_length; i++)
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
			int allchating_cnt = 0;
			sprintf(query, "update user set status = 1 where ownnum = %d", myuser->ownnum);
			mysql_query(cons, query);
			char MemBerList[30][30] = { 0, };
			Chating chatings[12] = { 0, };
			int usercount = 0;
			memset(&ID_put, 0, sizeof(ID_put));
			int chattingput = 0;
			int chattingdrag = 0;
			long long timer = SDL_GetTicks() % 1000;
			SDL_Texture * WaitRoom_setting_noclick = LoadTexture(renderer, ".\\design\\settingicon1.png");
			SDL_Texture * WaitRoom_setting_click = LoadTexture(renderer, ".\\design\\settingicon2.png");
			SDL_Texture * User_Pencil = LoadTexture(renderer, ".\\design\\pencil.png");
			SDL_Texture * Chating_noput = LoadTexture(renderer, ".\\design\\chatting1.png");
			SDL_Texture * Chating_put = LoadTexture(renderer, ".\\design\\chatting2.png");
			SDL_Texture * Chating_click = LoadTexture(renderer, ".\\design\\chattingput.png");
			SDL_Texture * Slider_Box = LoadTextureEx(renderer, ".\\design\\Box.png", 255, 255, 255);

			SDL_Texture * Slider_slider_up = LoadTexture(renderer, ".\\design\\slider_up.png");
			Slider * chatslide = (Slider *)malloc(sizeof(Slider));
			CreateSlider(chatslide, Slider_Box, Slider_slider_up, Display_X * 0.68, Display_Y * 0.78, Display_X * 0.01, Display_Y * 0.16, Display_X * 0.02, Display_Y * 0.04, &chattingdrag, 0, (Display_Y * 0.2) - ((int)(Display_Y * 0.2) % 10), Display_Y * 0.2 - ((int)(Display_Y * 0.2) % 10), VERTICAL);
			quit = 0;
			sprintf(query, "LV %d", myuser->level);
			warning.ison = 0;
			usercount = getUesrStatus(cons, MemBerList);
			allchating_cnt = ReadChating_all(cons, chatings);
			while (loginsuccess && !quit)	//로그인 성공 후 대기창
			{
				//		if (SDL_PollEvent(&event))
				//		{
				SDL_WaitEventTimeout(&event, 1000);
				UpdateSlider(chatslide, &event);
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
									allchating_cnt = ReadChating_all(cons, chatings);
									MoveSlider_value(chatslide, chatslide->End);
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
								//		printf("\nslice상태");
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
						}
					}
					if (event.wheel.y == -1) {
						//		if (event.motion.x < Display_X * 0.7 && event.motion.y > Display_Y * 0.7)
						if (chattingdrag >= chatslide->Start && chattingdrag < chatslide->End)
						{
							MoveSlider_value(chatslide, chattingdrag + 10);
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
				SDL_SetRenderDrawColor(renderer, 191, 191, 191, 0);
				SDL_RenderClear(renderer);
				FillRoundRect(renderer, 255, 255, 255, 10, 10, Display_X * 0.7, Display_Y * 0.69, 14);
				DrawRoundRect(renderer, 191, 191, 191, 9, 9, Display_X * 0.7 + 2, Display_Y * 0.69 + 2, 14, 1);
				FillUpRoundRect(renderer, 146, 208, 80, 10, 10, Display_X * 0.7, Display_Y * 0.035, 14);
				PutText(renderer, "방 목록", (Display_X * 0.33), 10, 30 * ((float)Display_X / 1920), 255, 255, 255);

				//4번구역
				FillRoundRect(renderer, 255, 255, 255, 10, Display_Y * 0.7 + 10, Display_X * 0.7, Display_Y * 0.27, 14);
				DrawRoundRect(renderer, 191, 191, 191, 9, Display_Y * 0.7 + 10 - 1, Display_X * 0.7 + 2, Display_Y * 0.27 + 2, 14, 1);
				FillUpRoundRect(renderer, 146, 208, 80, 10, Display_Y * 0.7 + 10, Display_X * 0.7, Display_Y * 0.035, 14);
				PutText(renderer, "채팅", (Display_X * 0.335), Display_Y * 0.7 + 10, 30 * ((float)Display_X / 1920), 255, 255, 255);

				//5번구역
				FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, Display_Y * 0.7 + 10, Display_X * 0.275, Display_Y * 0.27, 14);
				DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, Display_Y * 0.7 + 9, Display_X * 0.275 + 2, Display_Y * 0.27 + 2, 14, 1);
				FillUpRoundRect(renderer, 146, 208, 80, Display_X * 0.7 + 22, Display_Y * 0.7 + 10, Display_X * 0.275, Display_Y * 0.035, 14);
				PutText(renderer, "내 정보", (Display_X * 0.83), Display_Y * 0.7 + 10, 30 * ((float)Display_X / 1920), 255, 255, 255);

				//3번구역
				FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, Display_Y * 0.11, Display_X * 0.275, Display_Y * 0.59, 14);
				DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, Display_Y * 0.11 - 1, Display_X * 0.275 + 2, Display_Y * 0.59 + 2, 14, 1);
				FillUpRoundRect(renderer, 146, 208, 80, Display_X * 0.7 + 22, Display_Y * 0.11, Display_X * 0.275, Display_Y * 0.035, 14);
				PutText(renderer, "접속자 명단", (Display_X * 0.815), Display_Y * 0.113, 30 * ((float)Display_X / 1920), 255, 255, 255);

				//2번구역
				FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, 10, Display_X * 0.275, Display_Y * 0.09, 3);
				DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, 9, Display_X * 0.275 + 2, Display_Y * 0.09 + 2, 3, 1);

				PutText(renderer, myuser->name, Display_X * 0.87, Display_Y * 0.8, 40 * ((float)Display_X / 1920), 0, 0, 0);	//개인정보 - 이름 출력
				PutText(renderer, query, Display_X * 0.88, Display_Y * 0.85, 30 * ((float)Display_X / 1920), 0, 0, 0);	//개인정보 - 이름 출력
				DrawSlider(renderer, chatslide);
				if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 59, 127, 172, Display_X * 0.61, Display_Y * 0.915, Display_X * 0.05, Display_Y * 0.05, 8, 0, &event))
				{

					if (chattingput == 0)
						chattingput = 1;
					else if (wcslen(ID_put) > 0)
					{

						InsertChating_all(cons, myuser->name, ID_put);
						memset(&ID_put, 0, sizeof(ID_put));
						enter = false;
						textinput = true;
						allchating_cnt = ReadChating_all(cons, chatings);
						MoveSlider_value(chatslide, chatslide->End);
					}
					MouseUP_Wait;

				}
				if (chattingput == 0)
				{
					if (PutButtonImage(renderer, Chating_noput, Chating_put, Display_X * 0.03, Display_Y * 0.91, Display_X * 0.56, Display_Y * 0.07, &event))
						chattingput = 1;
				}
				else
				{
					if (PutButtonImage_click(renderer, Chating_click, Chating_click, Display_X * 0.03, Display_Y * 0.92, Display_X * 0.56, Display_Y * 0.04, &event) == -1) {
						chattingput = 0;
					}
					PutText_Unicode(renderer, ID_put, Display_X * 0.04, Display_Y * 0.92, 30 * ((float)Display_X / 1920), color);

				}
				
				PutText(renderer, "전송", Display_X * 0.62, Display_Y * 0.925, 30 * ((float)Display_X / 1920), 255, 255, 255);

				if (timer < SDL_GetTicks() % 1000)
				{

					timer++;
					usercount = getUesrStatus(cons, MemBerList);
					allchating_cnt = ReadChating_all(cons, chatings);

				}
				for (i = 0; i < allchating_cnt; i++)
				{

					sprintf(db_id, "%s : %s", chatings[i].name, chatings[i].message);
					if (Display_Y * (1.08 - (0.03 * i)) - chattingdrag < Display_Y * 0.89 && Display_Y * (1.08 - (0.03 * i)) - chattingdrag > Display_Y * 0.76)
						PutText(renderer, db_id, Display_X * 0.04, Display_Y * (1.08 - (0.03 * i)) - chattingdrag, 25 * ((float)Display_X / 1920), 0, 0, 0);
				}
				for (i = 0; i < usercount; i++)
				{
					sprintf(db_id, "LV:%d", MemBerList[i][27]);
					RenderTextureXYWH(renderer, User_Pencil, Display_X * 0.73, Display_Y * (0.20 + i * 0.05), 33 * ((float)Display_X / 1920), 33 * ((float)Display_X / 1920));
					PutText(renderer, db_id, Display_X * 0.76, Display_Y * (0.20 + i * 0.05), 30 * ((float)Display_X / 1920), 0, 0, 0);
					PutText(renderer, MemBerList[i], Display_X * 0.82, Display_Y * (0.20 + i * 0.05), 30 * ((float)Display_X / 1920), 0, 0, 0);
					if (MemBerList[i][28] == 1)
					{
						PutText(renderer, "로비", Display_X * 0.93, Display_Y * (0.20 + i * 0.05), 30 * ((float)Display_X / 1920), 0, 0, 0);
					}
					else if (MemBerList[i][28] == 2)
					{

						PutText(renderer, "게임 중", Display_X * 0.93, Display_Y * (0.20 + i * 0.05), 30 * ((float)Display_X / 1920), 255, 0, 0);
					}
					else if (MemBerList[i][28] == 3)
					{
						PutText(renderer, "대기방", Display_X * 0.93, Display_Y * (0.20 + i * 0.05), 30 * ((float)Display_X / 1920), 0, 255, 0);
					}
				}
				if (PutRoundButton(renderer, 3, 114, 237, 23, 134, 255, 3, 114, 237, Display_X * 0.71 + 22, Display_Y * 0.025, Display_X / 11, Display_Y / 18, 8, 0, &event)) //방만들기 버튼
				{

				}
				if (PutRoundButton(renderer, 255, 0, 0, 230, 0, 0, 255, 0, 0, Display_X * 0.81 + 22, Display_Y * 0.025, Display_X / 11, Display_Y / 18, 8, 0, &event)) //빠른 시작 버튼
				{
					SDL_Texture * can = LoadTexture(renderer, ".\\design\\can.png");

					while (!qquit) {

						/*
						화면을 전체적으로 4등분함

						|
						1번구역		 |
						|
						|    2번구역
						|
						---------------------|-----------------
						3번구역		 |
						|     4번구역
						|
						|
						*/

						if (SDL_PollEvent(&event))
						{
							switch (event.type)
							{
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
						}
						//배경
						SDL_SetRenderDrawColor(renderer, 191, 191, 191, 0);
						SDL_RenderClear(renderer);

						//1번구역
						FillRoundRect(renderer, 255, 255, 255, 10, 10, Display_X * 0.7, Display_Y * 0.69, 14);
						DrawRoundRect(renderer, 191, 191, 191, 9, 9, Display_X * 0.7 + 2, Display_Y * 0.69 + 2, 14, 1);
						FillUpRoundRect(renderer, 146, 208, 80, 10, 10, Display_X * 0.7, Display_Y * 0.035, 14);
						PutText(renderer, "대기실", (Display_X * 0.33), 10, 30 * ((float)Display_X / 1920), 255, 255, 255);

						//2번구역
						FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, 10, Display_X * 0.275, Display_Y * 0.69, 14);
						RenderTextureXYWH(renderer, can, Display_X * 0.7 + 22, Display_Y*0.042, Display_X*0.277, Display_Y*0.046); //앙
						DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, 9, Display_X * 0.275 + 2, Display_Y * 0.69 + 2, 14, 1);
						FillUpRoundRect(renderer, 146, 208, 80, Display_X * 0.7 + 22, 10, Display_X * 0.275, Display_Y * 0.035, 14);
						PutText(renderer, "방 정보", (Display_X * 0.815), 10, 30 * ((float)Display_X / 1920), 255, 255, 255);



						//3번구역
						FillRoundRect(renderer, 255, 255, 255, 10, Display_Y * 0.7 + 10, Display_X * 0.7, Display_Y * 0.27, 14);
						DrawRoundRect(renderer, 191, 191, 191, 9, Display_Y * 0.7 + 10 - 1, Display_X * 0.7 + 2, Display_Y * 0.27 + 2, 14, 1);
						FillUpRoundRect(renderer, 146, 208, 80, 10, Display_Y * 0.7 + 10, Display_X * 0.7, Display_Y * 0.035, 14);
						PutText(renderer, "채팅", (Display_X * 0.335), Display_Y * 0.7 + 10, 30 * ((float)Display_X / 1920), 255, 255, 255);

						//4번구역
						FillRoundRect(renderer, 255, 255, 255, Display_X * 0.7 + 22, Display_Y * 0.7 + 10, Display_X * 0.275, Display_Y * 0.27, 14);
						DrawRoundRect(renderer, 191, 191, 191, Display_X * 0.7 + 21, Display_Y * 0.7 + 9, Display_X * 0.275 + 2, Display_Y * 0.27 + 2, 14, 1);


						if (PutRoundButton(renderer, 3, 114, 237, 23, 134, 255, 3, 114, 237, Display_X*0.7317, Display_Y*0.7222, Display_X*0.2343, Display_Y*0.1157, 20, 0, &event)) //나가기 버튼 
						{
							qquit = true;
						}

						if (PutRoundButton(renderer, 255, 0, 0, 230, 0, 0, 255, 0, 0, Display_X*0.7317, Display_Y*0.85, Display_X*0.2343, Display_Y*0.1157, 20, 0, &event)) //시작하기, 준비 버튼
						{
							qquit = true;
						}

						PutText(renderer, "나가기", Display_X*0.807, Display_Y*0.75, 57 * ((float)Display_X) / 1920, 255, 255, 255);
						PutText(renderer, "준비하기", Display_X*0.796, Display_Y*0.87, 57 * ((float)Display_X) / 1920, 255, 255, 255);    //방장일때는 시작하기


						SDL_RenderPresent(renderer);
					}
					qquit = false;
				}
				PutText(renderer, "방만들기", Display_X * 0.72 + 20, Display_Y * 0.03, 35 * ((float)Display_X) / 1920, 255, 255, 255);
				PutText(renderer, "빠른시작", Display_X * 0.82 + 22, Display_Y * 0.03, 35 * ((float)Display_X) / 1920, 255, 255, 255);

				if (PutButtonImage(renderer, WaitRoom_setting_noclick, WaitRoom_setting_click, Display_X * 0.92 + 10, Display_Y * 0.02, 86 * ((float)Display_X / 1920), 82 * ((float)Display_X / 1920), &event))//설정 버튼
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

					CreateSlider(slider_sound, Slider_Box, Slider_slider, set_start_x + set_start_w * 0.3, set_start_y + set_start_h * 0.24, set_start_w * 0.5, set_start_h * 0.03, set_start_w * 0.03, set_start_h * 0.08, &Sound, 0, 100, 30, HORIZONTAL);
					CreateSlider(slider_bgsound, Slider_Box, Slider_slider, set_start_x + set_start_w * 0.3, set_start_y + set_start_h * 0.42, set_start_w * 0.5, set_start_h * 0.03, set_start_w * 0.03, set_start_h * 0.08, &BGmusic, 0, 100, 30, HORIZONTAL);
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
						if (PutButtonImage(renderer, Setting_Close_noclick, Setting_Close_click, set_start_x + set_start_w - 110 * ((float)Display_X / 1920), set_start_y, 110 * ((float)Display_X / 1920), 84 * ((float)Display_X / 1920), &event))
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
						PutText(renderer, "효과음", set_start_x + set_start_w * 0.08, set_start_y + set_start_h * 0.21, 35 * ((float)Display_X / 1920), 0, 0, 0);
						FillRoundRect(renderer, 0, 176, 240, set_start_x + set_start_w * 0.81, set_start_y + set_start_h * 0.2, set_start_w * 0.15, set_start_h * 0.1, 25 * ((float)Display_X / 1920));
						PutText(renderer, _itoa(Sound, db_id, 10), set_start_x + set_start_w * 0.85, set_start_y + set_start_h * 0.216, 30 * ((float)Display_X / 1920), 255, 255, 255);

						//배경음악
						FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.36, set_start_w * 0.94, set_start_h * 0.14, 13);
						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.36 - 3, set_start_w * 0.94 + 6, set_start_h * 0.14 + 6, 13, 2);
						SDL_FillRectXYWH(renderer, set_start_x + set_start_w * 0.27, set_start_y + set_start_h * 0.36, 6 * ((float)Display_X / 1920), set_start_h * 0.143, 91, 155, 213);
						PutText(renderer, "배경음악", set_start_x + set_start_w * 0.06, set_start_y + set_start_h * 0.39, 32 * ((float)Display_X / 1920), 0, 0, 0);
						FillRoundRect(renderer, 0, 176, 240, set_start_x + set_start_w * 0.81, set_start_y + set_start_h * 0.38, set_start_w * 0.15, set_start_h * 0.1, 25 * ((float)Display_X / 1920));
						PutText(renderer, _itoa(BGmusic, db_id, 10), set_start_x + set_start_w * 0.85, set_start_y + set_start_h * 0.396, 30 * ((float)Display_X / 1920), 255, 255, 255);

						//해상도 설정
						FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.54, set_start_w * 0.94, set_start_h * 0.22, 13);
						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.54 - 3, set_start_w * 0.94 + 6, set_start_h * 0.22 + 6, 13, 2);
						SDL_FillRectXYWH(renderer, set_start_x + set_start_w * 0.27, set_start_y + set_start_h * 0.54, 6 * ((float)Display_X / 1920), set_start_h * 0.223, 91, 155, 213);
						PutText(renderer, "해상도 설정", set_start_x + set_start_w * 0.04, set_start_y + set_start_h * 0.61, 30 * ((float)Display_X / 1920), 0, 0, 0);
						sprintf(db_id, "%d X %d", 320 * display_value, 180 * display_value);

						PutText(renderer, db_id, set_start_x + set_start_w * 0.35, set_start_y + set_start_h * 0.65, 30 * ((float)Display_X / 1920), 0, 0, 0);
						if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 0, 176, 240, set_start_x + set_start_w * 0.7, set_start_y + set_start_h * 0.65, set_start_x * 0.2, set_start_h * 0.1, 25 * ((float)Display_X / 1920), 0, &event)) {
							if (Full == 0)
								Full = 1;
							else
								Full = 0;
							MouseUP_Wait;
						}
						if (Full == 1)
						{
							PutText(renderer, "FULL", set_start_x + set_start_w * 0.74, set_start_y + set_start_h * 0.67, 30 * ((float)Display_X / 1920), 255, 255, 255);
							display_value = 6;
							slider_display->Box.x = slider_display->Bar.x + slider_display->Bar.w - slider_display->Box.w / 2;
						}
						else
						{
							PutText(renderer, "FULL", set_start_x + set_start_w * 0.74, set_start_y + set_start_h * 0.67, 30 * ((float)Display_X / 1920), 189, 189, 189);
							UpdateSlider(slider_display, &event);
						}
						UpdateSlider(slider_sound, &event);
						UpdateSlider(slider_bgsound, &event);
						//고객문의, 크래딧, 설문조사
						FillRoundRect(renderer, 255, 255, 255, set_start_x + set_start_w * 0.03, set_start_y + set_start_h * 0.8, set_start_w * 0.94, set_start_h * 0.16, 13);
						DrawRoundRect(renderer, 191, 191, 191, set_start_x + set_start_w * 0.03 - 3, set_start_y + set_start_h * 0.8 - 3, set_start_w * 0.94 + 6, set_start_h * 0.16 + 6, 13, 2);

						//고객문의 버튼
						if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 0, 176, 240, set_start_x + set_start_w * 0.06, set_start_y + set_start_h * 0.82, set_start_x * 0.3, set_start_h * 0.12, 25 * ((float)Display_X / 1920), 0, &event))
						{
							system("start https://goo.gl/forms/tdCMgM3uRR1ZoNHO2");
						}
						//크래딧 버튼
						if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 0, 176, 240, set_start_x + set_start_w * 0.36, set_start_y + set_start_h * 0.82, set_start_x * 0.3, set_start_h * 0.12, 25 * ((float)Display_X / 1920), 0, &event))
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
						if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 0, 176, 240, set_start_x + set_start_w * 0.66, set_start_y + set_start_h * 0.82, set_start_x * 0.3, set_start_h * 0.12, 25 * ((float)Display_X / 1920), 0, &event))
						{
							system("start https://goo.gl/forms/guFd08v7sFrK6Pe93");
						}
						DrawSlider(renderer, slider_sound);
						DrawSlider(renderer, slider_bgsound);
						DrawSlider(renderer, slider_display);
						PutText(renderer, "고객문의", set_start_x + set_start_w * 0.093, set_start_y + set_start_h * 0.83, 35 * ((float)Display_X / 1920), 255, 255, 255);
						PutText(renderer, "크래딧", set_start_x + set_start_w * 0.42, set_start_y + set_start_h * 0.83, 35 * ((float)Display_X / 1920), 255, 255, 255);
						PutText(renderer, "설문조사", set_start_x + set_start_w * 0.693, set_start_y + set_start_h * 0.83, 35 * ((float)Display_X / 1920), 255, 255, 255);

						SDL_RenderPresent(renderer);


					}
					SDL_DestroyTexture(Setting_back);
					SDL_DestroyTexture(Setting_Close_click);
					SDL_DestroyTexture(Setting_Close_noclick);
					SDL_DestroyTexture(Slider_slider);
					free(slider_sound);
					free(slider_bgsound);
					free(slider_display);
					CreateSlider(chatslide, Slider_Box, Slider_slider_up, Display_X * 0.68, Display_Y * 0.78, Display_X * 0.01, Display_Y * 0.16, Display_X * 0.02, Display_Y * 0.04, &chattingdrag, 0, (Display_Y * 0.2) - ((int)(Display_Y * 0.2) % 10), Display_Y * 0.2 - ((int)(Display_Y * 0.2) % 10), VERTICAL);

				}

				if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 59, 127, 172, Display_X * 0.74, Display_Y * 0.93, Display_X * 0.09, Display_Y * 0.04, 8, 1, &event)) //닉네임 변경 버튼
				{
					roop = 1;
					break;
				}
				PutText(renderer, "닉네임 변경", Display_X * 0.75, Display_Y * 0.935, 25 * ((float)Display_X / 1920), 255, 255, 255);

				if (PutRoundButton(renderer, 0, 176, 240, 20, 196, 255, 59, 127, 172, Display_X * 0.86, Display_Y * 0.93, Display_X * 0.09, Display_Y * 0.04, 8, 1, &event)) //로그아웃 버튼
				{
					roop = 1;
					break;
				}
				PutText(renderer, "로그아웃", Display_X * 0.88, Display_Y * 0.935, 25 * ((float)Display_X / 1920), 255, 255, 255);
				if (warning.ison == 1)
				{
					PutText(renderer, warning.message, warning.x, warning.y, warning.size, warning.r, warning.g, warning.b);
				}
				SDL_RenderPresent(renderer);

			}
			free(chatslide);
			SDL_DestroyTexture(WaitRoom_setting_click);
			SDL_DestroyTexture(WaitRoom_setting_noclick);
			SDL_DestroyTexture(User_Pencil);
			SDL_DestroyTexture(Slider_slider_up);
			SDL_DestroyTexture(Chating_click);
			SDL_DestroyTexture(Chating_put);
			SDL_DestroyTexture(Slider_Box);

			SDL_DestroyTexture(Chating_noput);
			sprintf(query, "update user set status = 0 where ownnum = %d", myuser->ownnum);
			mysql_query(cons, query);
		}

	}






	if (myuser != 0)
		free(myuser);
	if (status.ishappen == 1)
		mysql_close(status.arg);
	SDL_DestroyTexture(LoadingBar);
	SDL_DestroyTexture(WaitBar);
	SDL_DestroyTexture(TitleText);
	SDL_DestroyTexture(TitleImage);
	SDL_DestroyTexture(LoadingBar);
	SDL_DestroyTexture(WaitBar);
	SDL_DestroyTexture(TitleText);
	SDL_DestroyTexture(TitleImage);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);


	SDL_DestroyWindow(Window);
	SDL_Quit();


	return 0;
}

