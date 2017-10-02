#include "include.h"
//그래픽 관련 함수들
TTF_Font * Font_Size[100];
TTF_Font * Font_Size2[100];
int TTF_DrawText(SDL_Renderer *Renderer, TTF_Font* Font, wchar_t* sentence, int x, int y, SDL_Color Color ) {
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
	return Src.w;// 출력할 문자열의 너비를 반환
}
void HitMind_TTF_Init()
{
	for (int i = 0; i < 100; i++)
	{
		Font_Size[i] = TTF_OpenFont(".\\font\\NanumGothic.ttf", i);
	}
}
void HitMind_TTF_Close() {

	for (int i = 0; i < 100; i++)
	{
		TTF_CloseFont(Font_Size[i]);
	}

}
void HitMind_TTF2_Init()
{
	for (int i = 0; i < 100; i++)
	{
		Font_Size2[i] = TTF_OpenFont(".\\font\\NanumGothicBold.ttf", i);
	}
}
void HitMind_TTF2_Close() {

	for (int i = 0; i < 100; i++)
	{
		TTF_CloseFont(Font_Size2[i]);
	}

}
int PutButtonImage(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, int x, int y, int w, int h, SDL_Event * event, int *happen) {//이미지 버튼 선언
	SDL_Rect Src;// 직사각형 선언
	Src.x = 0;// 직사각형의 왼쪽위 꼭짓점의 x좌표초기화
	Src.y = 0;// 직사각형의 왼쪽위 꼭짓점의 y좌표초기화
	SDL_Rect Dst;
	Dst.x = x;//매개변수x를 왼쪽위 꼭짓점의 x좌표에 대입
	Dst.y = y;//매개변수y를 왼쪽위 꼭짓점의 y좌표에 대입
	Dst.w = w;//매개변수w를 직사각형의 너비에 대입
	Dst.h = h;//매개변수h를 직사각형의 높이에 대입
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	if (mouse_x > x && mouse_y > y && mouse_x < x + w && mouse_y < y + h)
	{
		SDL_QueryTexture(MouseOnImage, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
		SDL_RenderCopy(Renderer, MouseOnImage, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장
		*happen = true;
	}
	else {
		SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
		SDL_RenderCopy(Renderer, Texture, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장
	}
	if (event->type == SDL_MOUSEBUTTONDOWN)
		if (event->button.x > x && event->button.y > y && event->button.x < x + w && event->button.y < y + h)
			return 1;
	return 0;
}
int PutButtonImage_click(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, int x, int y, int w, int h, SDL_Event * event, int *happen) {//이미지 버튼 선언
	SDL_Rect Src;// 직사각형 선언
	Src.x = 0;// 직사각형의 왼쪽위 꼭짓점의 x좌표초기화
	Src.y = 0;// 직사각형의 왼쪽위 꼭짓점의 y좌표초기화
	SDL_Rect Dst;
	Dst.x = x;//매개변수x를 왼쪽위 꼭짓점의 x좌표에 대입
	Dst.y = y;//매개변수y를 왼쪽위 꼭짓점의 y좌표에 대입
	Dst.w = w;//매개변수w를 직사각형의 너비에 대입
	Dst.h = h;//매개변수h를 직사각형의 높이에 대입
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	if (mouse_x > x && mouse_y > y && mouse_x < x + w && mouse_y < y + h)
	{
		SDL_QueryTexture(MouseOnImage, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
		SDL_RenderCopy(Renderer, MouseOnImage, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장
		*happen = true;
	}
	else {

		SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
		SDL_RenderCopy(Renderer, Texture, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장
	}
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		if (event->button.x > x && event->button.y > y && event->button.x < x + w && event->button.y < y + h)
			return 1;
		else {
			*happen = true;
			return -1;
		}
	}
	return 0;
}
/*
	마우스를 올려놓으면 MouseOnImage출력 후 리턴 0, 이미지 클릭시에는 리턴 1, 다른 곳 클릭 시 원래 이미지 출력하고 리턴 -1
*/
int PutButtonWithImage(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, SDL_Texture * MouseClickImage,int x, int y, int w, int h, SDL_Event * event, int *Flag) {//이미지 버튼 선언
	SDL_Rect Src;// 직사각형 선언
	Src.x = 0;// 직사각형의 왼쪽위 꼭짓점의 x좌표초기화
	Src.y = 0;// 직사각형의 왼쪽위 꼭짓점의 y좌표초기화
	SDL_Rect Dst;
	Dst.x = x;//매개변수x를 왼쪽위 꼭짓점의 x좌표에 대입
	Dst.y = y;//매개변수y를 왼쪽위 꼭짓점의 y좌표에 대입
	Dst.w = w;//매개변수w를 직사각형의 너비에 대입
	Dst.h = h;//매개변수h를 직사각형의 높이에 대입
	if (event->type == SDL_MOUSEMOTION) {
		if (*Flag == ACTIVATED) {
			return 0;
		}
		if (event->motion.x >= x && event->motion.y >= y && event->motion.x <= x + w && event->button.y <= y + h)
		{
			if (*Flag == HIGHLIGHT) {
				return 0;
			}
			else {
				SDL_QueryTexture(MouseOnImage, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
				SDL_RenderCopy(Renderer, MouseOnImage, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장	
				*Flag = HIGHLIGHT;
				return 1;
			}
		}
		else {
			if (*Flag == DEACTIVATED) {
				return 0;
			}
			else {
				*Flag = DEACTIVATED;
				SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
				SDL_RenderCopy(Renderer, Texture, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장
				return 1;
			}
		}
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN) {
		if (event->button.button != 1)
			return 0;
		if (event->button.x >= x && event->button.y >= y && event->button.x <= x + w && event->button.y <= y + h) {

			if (*Flag == ACTIVATED) {
				return 0;
			}
			else {
				if (MouseClickImage != NULL) {
					SDL_QueryTexture(MouseClickImage, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
					SDL_RenderCopy(Renderer, MouseClickImage, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장	
				}
				*Flag = ACTIVATED;
				return 1;
			}
		}
		else {

			if (*Flag == DEACTIVATED) {
				return 0;
			}
			else {
				*Flag = DEACTIVATED;
				SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
				SDL_RenderCopy(Renderer, Texture, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장

				return 1;
			}
		}
	}
	return 0;
}
int PutButton(SDL_Renderer * renderer, char * sentence, int x, int y, int size, int r, int g, int b, SDL_Event * event)
{
	SDL_Color color = { r, g, b };
	int plussize = 0;		//마우스를 가져다될때 커지는 사이즈

	if (event->type == SDL_MOUSEBUTTONDOWN)	//클릭 되었을때
		if (event->button.x > x && event->button.y > y && event->button.x < (x + (signed int)strlen(sentence) * (size / 2)) && event->button.y < y + size + 5)
		{	//마우스가 해당 글씨위에 클릭하면
			return 1;	//1을 반환
		}

	if (event->motion.x > x && event->motion.y > y && event->motion.x < (x + (signed int)strlen(sentence) * (size / 2)) && event->motion.y < y + size + 5)
	{	//마우스의 위치가 글씨 위에 있으면
		plussize = 5;	//커지는 효과
	}
	Unicode unicode[128] = L"";	//han2unicode를 쓰기 위해 unsigned short(UNICODE)를 생성
	han2unicode(sentence, unicode);		//옮김

	TTF_Font *font = TTF_OpenFont(".\\font\\NanumGothic.ttf", size + plussize);	 //폰트를 불러온다. 하지만 Draw할때마다 불러오는건 비효율적이긴 함.
	TTF_DrawText(renderer, font, unicode, x - (int)(plussize * (strlen(sentence) / 4)), y - (plussize / 2), color);	//Text를 적음
	TTF_CloseFont(font);	//임시로 출력하기위한 폰트를 닫음
	return 0;	//클릭이 안되었으니 0을 리턴
}
int PutText(SDL_Renderer * renderer, char * sentence, unsigned int x, unsigned int y, int size, int r, int g, int b, int m)
{
	SDL_Color color = { r, g, b };
	Unicode unicode[128] = L"";		//역시나 임시로 TTF_DrawText를 쓰기 위한 unicode생성
	han2unicode(sentence, unicode);	//옮긴다
	if(m==1)
		TTF_DrawText(renderer, Font_Size[size], unicode, x, y, color);			//Text를 적음
	else if(m==2)          
		TTF_DrawText(renderer, Font_Size2[size], unicode, x, y, color);         //볼드체
	return 0;	//평소에도 0을 리턴
}
int PutText_Unicode(SDL_Renderer * renderer, Unicode * unicode, unsigned int x, unsigned int y, int size, SDL_Color color, int m)
{

	if (m == 1)
		TTF_DrawText(renderer, Font_Size[size], unicode, x, y, color);			//Text를 적음
	else if (m == 2)
		TTF_DrawText(renderer, Font_Size2[size], unicode, x, y, color);

	return 0;	//평소에도 0을 리턴
}
int PutText_Unicode_Limit(SDL_Renderer * renderer, Unicode * unicode, unsigned int x, unsigned int y, int size,int Limit, SDL_Color color)
{
	SDL_Surface * Surface = TTF_RenderUNICODE_Blended(Font_Size[size], unicode, color);// 폰트의 종류,문자열, 색깔을 보내서 유니코드로 렌더한다음 서피스에 저장한다
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, Surface);// 서피스로부터 텍스쳐를 생성한다
	SDL_FreeSurface(Surface);//서피스 메모리를 해제 해준다.
	SDL_Rect Src;
	Src.x = 0;
	Src.y = 0;
	SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h);
	if (Src.w > Limit) {
		SDL_DestroyTexture(Texture);
		return -1;
	}
	SDL_Rect Dst;
	Dst.x = x;
	Dst.y = y;
	Dst.w = Src.w;
	Dst.h = Src.h;
	SDL_RenderCopy(renderer, Texture, &Src, &Dst); //그대로 렌더러에 저장한다
	SDL_DestroyTexture(Texture);
	return 0;	//평소에도 0을 리턴
}
SDL_Texture * LoadTexture(SDL_Renderer * Renderer, const char *file) { // 텍스쳐에 이미지파일 로드하는 함수 선언
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;// JPG파일과 PNG파일 로드 가능
	if (IMG_Init(imgFlags) != imgFlags) {//IMG 초기화하고 초기화 안되면 if문 실행

		return nullptr;//널포인터 반환
	}
	SDL_Surface* Surface = IMG_Load(file);//서피스에 이미지로드
	if (Surface == nullptr) {//서피스에 이미지로드가 안되면 

		IMG_Quit();// IMG 종료
		return nullptr;// 널포인터 반환
	}
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);//서피스로부터 텍스쳐 생성
	SDL_FreeSurface(Surface);// 서피스 메모리해제
	if (Texture == nullptr) {// 텍스쳐 생성 실패시 if문실행

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
void RenderTextureXYWH(SDL_Renderer* Renderer, SDL_Texture * Texture, double xx, double yy, double ww, double hh) {//텍스쳐를 출력하는 함수 선언
	int x = round(xx);
	int y = round(yy);
	int w = round(ww);
	int h = round(hh);
	SDL_Rect Src;// 직사각형 선언
	Src.x = 0;// 직사각형의 왼쪽위 꼭짓점의 x좌표초기화
	Src.y = 0;// 직사각형의 왼쪽위 꼭짓점의 y좌표초기화
	SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
	SDL_Rect Dst;
	Dst.x = x;//매개변수x를 왼쪽위 꼭짓점의 x좌표에 대입
	Dst.y = y;//매개변수y를 왼쪽위 꼭짓점의 y좌표에 대입
	Dst.w = w;//매개변수w를 직사각형의 너비에 대입
	Dst.h = h;//매개변수h를 직사각형의 높이에 대입
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
void SDL_DrawRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius, int strong) {
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	int out_x, out_y;
	int left_x, left_y;
	double y;
	double Center_x = Rect->x + radius, Center_y = Rect->y + radius;
	for (y = 0; y < radius;) {
		out_x = floor(Center_x - sqrt((radius + strong)*(radius + strong) - y*y));
		out_y = Center_y - y;
		y++;
		SDL_RenderDrawLine(Renderer, out_x, out_y, floor(Center_x - sqrt(radius*radius - y*y)), Center_y - y);
	}
	Center_x = Rect->x + Rect->w - radius;
	for (y = 0; y < radius; ) {
		out_x = floor(Center_x + sqrt((radius + strong)*(radius + strong) - y*y));
		out_y = Center_y - y;
		y++;
		SDL_RenderDrawLine(Renderer, out_x, out_y, floor(Center_x + sqrt(radius*radius - y*y)), Center_y - y);
	}
	for (; y < radius + strong; y++) {
		left_x = floor(Center_x - Rect->w + 2 * radius - sqrt((radius + strong)*(radius + strong) - y*y));
		left_y = Center_y - y;
		SDL_RenderDrawLine(Renderer, left_x, left_y, floor(Center_x + sqrt((radius + strong)*(radius + strong) - y*y)), Center_y - y);
	}
	Center_y = Rect->y + Rect->h - radius;
	for (y = 0; y < radius; ) {
		out_x = floor(Center_x + sqrt((radius + strong)*(radius + strong) - y*y));
		out_y = Center_y + y;
		y++;
		SDL_RenderDrawLine(Renderer, out_x, out_y, floor(Center_x + sqrt(radius*radius - y*y)), Center_y + y);
	}
	Center_x = Rect->x + radius;
	for (y = 0; y < radius;) {
		out_x = floor(Center_x - sqrt((radius + strong)*(radius + strong) - y*y));
		out_y = Center_y + y;
		y++;
		SDL_RenderDrawLine(Renderer, out_x, out_y, floor(Center_x - sqrt(radius*radius - y*y)), Center_y + y);
	}
	for (; y < radius + strong; y++) {
		left_x = floor(Center_x + Rect->w - 2 * radius + sqrt((radius + strong)*(radius + strong) - y*y));
		left_y = Center_y + y;
		SDL_RenderDrawLine(Renderer, left_x, left_y, floor(Center_x - sqrt((radius + strong)*(radius + strong) - y*y)), Center_y + y);
	}
}
void SDL_FillRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius) {
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	int Left_Center_x, Left_Center_y, Right_Center_x, Right_Center_y;
	double y;
	Right_Center_x = Rect->x + Rect->w - radius;
	Right_Center_y = Rect->y + radius;
	Left_Center_x = Rect->x + radius;
	Left_Center_y = Rect->y + radius;
	for (y = 0; y < radius; y++) {
		SDL_RenderDrawLine(Renderer, Left_Center_x - (int)sqrt(radius*radius - y*y) + !y, Left_Center_y - y, Right_Center_x + (int)sqrt(radius*radius - y*y) - !y, Right_Center_y - y);
	}
	Left_Center_y = Rect->y + Rect->h - radius;
	Right_Center_y = Rect->y + Rect->h - radius;
	for (y = 0; y < radius; y++) {
		SDL_RenderDrawLine(Renderer, Left_Center_x - (int)sqrt(radius*radius - y*y) + !y, Left_Center_y + y, Right_Center_x + (int)sqrt(radius*radius - y*y) - !y, Right_Center_y + y);
	}
	return;
}
void DrawRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius, int strong) {
	SDL_Rect rect = { x + strong,y + strong,w - 2 * strong,h - 2 * strong };
	SDL_Color color = { r,g,b,0 };
//	SDL_DrawRoundRect(Renderer, &rect, color, radius, strong);
	rect.x = x; rect.w = strong; rect.y = y + strong + radius - 1; rect.h = h - 2 * (strong + radius) + 2;
//	SDL_RenderFillRect(Renderer, &rect);
	rect.x = x + w - strong; rect.w = strong; rect.y = y + strong + radius - 1; rect.h = h - 2 * (strong + radius) + 2;
//s	SDL_RenderFillRect(Renderer, &rect);
	return;
}
void FillRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius) {
	SDL_Rect rect = { x,y  ,w,h };
	SDL_Color color = { r,g,b, 0 };
	SDL_FillRoundRect(Renderer, &rect, color, radius);
	rect.x = x+1; rect.y = y + radius; rect.w = w-1; rect.h = h - 2 * radius;
	SDL_RenderFillRect(Renderer, &rect);
	return;
}
void SDL_DrawUpRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius, int strong) {
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	int out_x, out_y;
	int left_x, left_y;
	double y;
	double Center_x = Rect->x + radius, Center_y = Rect->y + radius;
	for (y = 0; y < radius;) {
		out_x = floor(Center_x - sqrt((radius + strong)*(radius + strong) - y*y));
		out_y = Center_y - y;
		y++;
		SDL_RenderDrawLine(Renderer, out_x, out_y, floor(Center_x - sqrt(radius*radius - y*y)), Center_y - y);
	}
	Center_x = Rect->x + Rect->w - radius;
	for (y = 0; y < radius; ) {
		out_x = floor(Center_x + sqrt((radius + strong)*(radius + strong) - y*y));
		out_y = Center_y - y;
		y++;
		SDL_RenderDrawLine(Renderer, out_x, out_y, floor(Center_x + sqrt(radius*radius - y*y)), Center_y - y);
	}
	for (; y < radius + strong; y++) {
		left_x = floor(Center_x - Rect->w + 2 * radius - sqrt((radius + strong)*(radius + strong) - y*y));
		left_y = Center_y - y;
		SDL_RenderDrawLine(Renderer, left_x, left_y, floor(Center_x + sqrt((radius + strong)*(radius + strong) - y*y)), Center_y - y);
	}
}
void SDL_FillUpRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius) {
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	int Left_Center_x, Left_Center_y,Right_Center_x,Right_Center_y;
	double y;
	Right_Center_x = Rect->x + Rect->w - radius;
	Right_Center_y = Rect->y + radius;
	Left_Center_x = Rect->x + radius;
	Left_Center_y = Rect->y + radius;
	for (y = 0; y < radius; y++) {
		SDL_RenderDrawLine(Renderer, Left_Center_x- (int)sqrt(radius*radius - y*y)+!y, Left_Center_y-y, Right_Center_x + (int)sqrt(radius*radius - y*y)-!y, Right_Center_y - y);
	}
}
int PutRoundButton(SDL_Renderer* Renderer, int r, int g, int b, int put_r, int put_g, int put_b, int rect_r, int rect_g, int rect_b, int x, int y, int w, int h, int radius, int strong, SDL_Event *event, int *happen)
{
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	if (mouse_x > x && mouse_y > y && mouse_x < x + w && mouse_y < y + h) {
		FillRoundRect(Renderer, put_r, put_g, put_b, x, y, w, h, radius);
		if (strong != 0)
		DrawRoundRect(Renderer, rect_r, rect_g, rect_b, x - strong, y - strong, w + strong, h + strong, radius, strong);
		*happen = true;
	}
	else {
		FillRoundRect(Renderer, r, g, b, x, y, w, h, radius);
		if (strong != 0)
		DrawRoundRect(Renderer, rect_r, rect_g, rect_b, x - strong, y - strong, w + strong, h + strong, radius, strong);
	}
	if (event->type == SDL_MOUSEBUTTONDOWN) {

		if (event->button.x > x && event->button.y > y && event->button.x < x + w && event->button.y < y + h)
			return 1;
	}
	return 0;
}
void FillUpRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius) {
	SDL_Rect rect = { x,y  ,w,h };
	SDL_Color color = { r,g,b, 0 };
	SDL_FillUpRoundRect(Renderer, &rect, color, radius);
	rect.x = x+1; rect.y = y + radius; rect.w = w-1; rect.h = h - radius;
	SDL_RenderFillRect(Renderer, &rect);
	return;
}
void DrawUpRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius, int strong) {
	SDL_Rect rect = { x + strong,y + strong,w - 2 * strong,h - 2 * strong };
	SDL_Color color = { r,g,b,0 };
	SDL_DrawUpRoundRect(Renderer, &rect, color, radius, strong);
	rect.x = x; rect.w = strong; rect.y = y + strong + radius - 1; rect.h = h - 2 * strong - radius + 2;
	SDL_RenderFillRect(Renderer, &rect);
	rect.x = x + w - strong; rect.w = strong; rect.y = y + strong + radius - 1; rect.h = h - 2 * strong - radius + 2;
	SDL_RenderFillRect(Renderer, &rect);
	rect.x = x; rect.y = y + h - strong; rect.w = w; rect.h = strong;
	SDL_RenderFillRect(Renderer, &rect);

	return;
}
void CreateSlider(Slider * Slider, SDL_Texture * BoxTexture, SDL_Texture * BarTexture, int Bar_x, int Bar_y, int Bar_w, int Bar_h, int Box_w, int Box_h, int * Value, float Start, float End, float Default, int Flag) {
	Slider->BarTexture = BarTexture;
	Slider->BoxTexture = BoxTexture;
	Slider->Bar.x = Bar_x;
	Slider->Bar.y = Bar_y;
	Slider->Bar.w = Bar_w;
	Slider->Bar.h = Bar_h;
	Slider->Flag = Flag;
	Slider->End = End;
	Slider->Start = Start;
	if (Flag == HORIZONTAL) {
		Slider->Box.x = floor(Bar_x + Bar_w * (Default - Start) / (End - Start) - Box_w / 2.0);
		Slider->Box.y = floor(Bar_y + Bar_h / 2.0 - Box_h / 2.0);
	}
	else if (Flag == VERTICAL) {
		Slider->Box.x = floor(Bar_x + Bar_w / 2.0 - Box_w / 2.0);
		Slider->Box.y = floor(Bar_y + Bar_h * (Default - Start) / (End - Start) - Box_h / 2.0);
	}
	Slider->Box.w = Box_w;
	Slider->Box.h = Box_h;
	Slider->Value = Value;
	*Value = Default;
	Slider->Click = false;
	return;
}
void MoveSlider_value(Slider *Slider, int value) {
	Slider->Box.x = floor(Slider->Bar.x + Slider->Bar.w / 2.0 - Slider->Box.w / 2.0);
	Slider->Box.y = floor(Slider->Bar.y + Slider->Bar.h * (value - Slider->Start) / (Slider->End - Slider->Start) - Slider->Box.h / 2.0);
	*Slider->Value = value;
}
void DrawSlider(SDL_Renderer *Renderer, Slider * Slider) {
	RenderTexture(Renderer, Slider->BarTexture, &Slider->Bar);
	RenderTexture(Renderer, Slider->BoxTexture, &Slider->Box);
	return;
}
int UpdateSlider(Slider* Slider,  SDL_Event * event) {
	if (event->type == SDL_MOUSEBUTTONUP) {
		Slider->Click = false;
		return 0;
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN) {
		int x = event->button.x;
		int y = event->button.y;
		if (Slider->Flag == HORIZONTAL) {
			if (x >= Slider->Bar.x&&x <= Slider->Bar.x + Slider->Bar.w&&y >= Slider->Box.y&&y <= Slider->Box.y + Slider->Box.h) {
				Slider->Box.x = x - Slider->Box.w / 2;
				*Slider->Value = floor((Slider->Box.x + Slider->Box.w / 2.0 - Slider->Bar.x) / Slider->Bar.w*(Slider->End - Slider->Start) + Slider->Start);

				Slider->Click = true;
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (Slider->Flag == VERTICAL) {
			if (y >= Slider->Bar.y&&y <= Slider->Bar.y + Slider->Bar.h&&x >= Slider->Box.x&&x <= Slider->Box.x + Slider->Box.w) {
				Slider->Box.y = y - Slider->Box.h / 2;
				*Slider->Value = floor((Slider->Box.y + Slider->Box.h / 2.0 - Slider->Bar.y) / Slider->Bar.h*(Slider->End - Slider->Start) + Slider->Start);
				Slider->Click = true;
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	else if (event->type == SDL_MOUSEMOTION) {
		int x = event->motion.x;
		int y = event->motion.y;

		if (Slider->Click == true) {
			if (Slider->Flag == HORIZONTAL) {
				if (x > Slider->Bar.x + Slider->Bar.w)
					Slider->Box.x = Slider->Bar.x + Slider->Bar.w - Slider->Box.w / 2;
				else if (x < Slider->Bar.x)
					Slider->Box.x = Slider->Bar.x - Slider->Box.w / 2;
				else {
					Slider->Box.x = x - Slider->Box.w / 2;
				}
				*Slider->Value = floor((Slider->Box.x + Slider->Box.w / 2.0 - Slider->Bar.x) / Slider->Bar.w*(Slider->End - Slider->Start) + Slider->Start);
			}
			else if (Slider->Flag == VERTICAL) {
				if (y > Slider->Bar.y + Slider->Bar.h)
					Slider->Box.y = Slider->Bar.y + Slider->Bar.h - Slider->Box.h / 2;
				else if (y < Slider->Bar.y)
					Slider->Box.y = Slider->Bar.y - Slider->Box.h / 2;
				else {
					Slider->Box.y = y - Slider->Box.h / 2;
				}
				*Slider->Value = floor((Slider->Box.y + Slider->Box.h / 2.0 - Slider->Bar.y) / Slider->Bar.h*(Slider->End - Slider->Start) + Slider->Start);
			}
			return 1;
		}
		else
			return 0;
	}
	return 0;
}
wchar_t* UTF82UNICODE(char* UTF8, int len) {
	wchar_t wstr[256] = L"";
	wchar_t wchar[2] = L"";
	int temp;
	int i;
	for (i = 0; i < len; i += 3) {
		temp = (UTF8[i] + 22) * 64 * 64 + (UTF8[i + 1] + 128) * 64 + UTF8[i + 2] + 41088;
		if (hancheck(temp) == false) {
			wchar[0] = UTF8[i];
			if (wchar[0] == 92) {
				wchar[0] = UTF8[i + 1];
				i++;
			}
			i -= 2;
		}
		else
			wchar[0] = temp;
		wcscat(wstr, wchar);
	}
	wcscat(wstr, L"\0");
	return wstr;
}
char* UNICODE2UTF8(wchar_t* unicode, int len) {
	char str[192] = "";
	int i = 0, j = 0;
	for (i = 0; j < len; j++) {
		if (unicode[j] == 92 || unicode[j] == 39) {// 유니코드 92번(역슬래시)나 39번(작은따운표는) mysql에서 각각 \\, \"로 입력해야하므로 예외 처리를 해준다
			str[i] = 92;
			str[i + 1] = unicode[j];
			i += 2;
		}
		else if (unicode[j] >= 0xac00 && unicode[j] <= 0xD7A0) {// 완성형 한글일경우
			str[i] = (unicode[j] - 40960) / (64 * 64) - 22;
			str[i + 1] = (unicode[j] - 40960) % (4096) / 64 - 128;
			str[i + 2] = (unicode[j] - 40960) % 64 - 128;
			i += 3;
		}
		else if (unicode[j] >= 0x3131 && unicode[j] <= 0x3163) {// 초중종성일 경우
			str[i] = (unicode[j] - 12544) / (64 * 64) - 29;
			str[i + 1] = (unicode[j] - 12544) % (4096) / 64 - 124;
			str[i + 2] = (unicode[j] - 12544) % 64 - 128;
			i += 3;
		}
		else {
			str[i] = unicode[j];
			i++;
		}
	}
	strcat(str, "\0");
	return str;
}
int UTF82EUCKR(char *outBuf, int outLength, char *inBuf, int inLength)
{
	iconv_t cd = iconv_open("EUC-KR", "UTF-8");
	int ires = (int)iconv(cd, &inBuf, (size_t*)&inLength, &outBuf, (size_t*)&outLength);
	iconv_close(cd);
	return ires;
}
int hannum(wchar_t unicode[], int len) {
	int i, cnt = 0;
	for (i = 0; i < len; i++) {
		if ((unicode[i] >= 0xac00 && unicode[i] <= 0xd7a0) || (unicode[i] >= 0x3131 && unicode[i] <= 0x3163))
			cnt++;
	}
	return cnt;
}
int hancheck(int unicode) {
	int cnt = 0;
	if ((unicode >= 0xac00 && unicode <= 0xd7a0) || (unicode >= 0x3131 && unicode <= 0x3163))
		cnt++;
	return cnt;
}
int ChangeColor(SDL_Event * event, SDL_Color * color, SDL_Rect rect) {
	int r, g, b;
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		if (event->button.button == 1) {
			if ((event->button.x >= rect.x&&event->button.x <= rect.x + rect.w) && (event->button.y >= rect.y&&event->button.y <= rect.y + rect.h)) {// RgbCode 이미지 안이면 if문 실행
				int	alpha = (event->button.y - rect.y) / (rect.h / 9);// RgbCode 안에서의 y축 계산 == 명도채도계산
				switch ((event->button.x - rect.x) / (rect.w / 13)) {// RgbCode안에서의 x축 계산
				case 0:// 색 설정 코드
					r = 255; g = 0; b = 0;
					break;
				case 1:
					r = 255; g = 128; b = 0;
					break;
				case 2:
					r = 255; g = 255; b = 0;
					break;
				case 3:
					r = 128; g = 255; b = 0;
					break;
				case 4:
					r = 0; g = 255; b = 0;
					break;
				case 5:
					r = 0; g = 255; b = 128;
					break;
				case 6:
					r = 0; g = 255; b = 255;
					break;
				case 7:
					r = 0; g = 128; b = 255;
					break;
				case 8:
					r = 0; g = 0; b = 255;
					break;
				case 9:
					r = 127; g = 0; b = 255;
					break;
				case 10:
					r = 255; g = 0; b = 255;
					break;
				case 11:
					r = 255; g = 0; b = 127;
					break;
				case 12:// case 12는 회색계열이라서 특수한 알고리즘임 그래서 따로 코드를 써줌
					r = 128 + (255 / 8.0)*(alpha - 4); g = 128 + (255 / 8.0) * (alpha - 4); b = 128 + (255 / 8.0) * (alpha - 4);
					alpha = 4;
					break;
				default:
					return 0;
				}
				// 수식으로 rgb값 설정
				if (alpha <= 4) {
					color->r = r + r / 5 * (alpha - 4);
					color->g = g + g / 5 * (alpha - 4);
					color->b = b + b / 5 * (alpha - 4);
					return 1;
				}
				else {
					color->r = r + (255 - r) / 5 * (alpha - 4);
					color->g = g + (255 - g) / 5 * (alpha - 4);
					color->b = b + (255 - b) / 5 * (alpha - 4);
					return 1;
				}
			}
		}
	}
	return 0;
}
void SDL_FillRectXYWH(SDL_Renderer *renderer, int x, int y, int w, int h, int r, int g, int b) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	SDL_RenderFillRect(renderer, &rect);

}
void CreateCanvas(Canvas * Canvas, SDL_Renderer *Renderer, int x, int y, int w, int h, int strong) {
	Canvas->Click = false;
	Canvas->Strong = strong;
	Canvas->Color.r = 0; Canvas->Color.g = 0; Canvas->Color.b = 0; Canvas->Color.a = 0;
	Canvas->Flag = PENCIL;
	Canvas->Rect.x = x; Canvas->Rect.y = y; Canvas->Rect.w = w; Canvas->Rect.h = h;
	Canvas->Renderer = Renderer;
	return;
}
int UpdateCanvas(Canvas * Canvas, SDL_Event * event) {
	if (event->type == SDL_MOUSEBUTTONDOWN&&event->button.button ==1||(event->type==SDL_MOUSEMOTION&&Canvas->Click==false&&event->motion.state==1)) {
		int x = event->button.x; int y = event->button.y;
		if (x >= Canvas->Rect.x + Canvas->Strong / 2.0&&x <= Canvas->Rect.x + Canvas->Rect.w - Canvas->Strong / 2.0&&y >= Canvas->Rect.y + Canvas->Strong / 2.0&&y <= Canvas->Rect.y + Canvas->Rect.h - Canvas->Strong / 2.0) {
			if (Canvas->Flag == PENCIL) {
				SDL_SetRenderDrawColor(Canvas->Renderer, Canvas->Color.r, Canvas->Color.g, Canvas->Color.b, 0);
				FillCircle(Canvas->Renderer, x, y, Canvas->Strong / 2.0);
				Canvas->Last.x = x;
				Canvas->Last.y = y;
				Canvas->Click = true;
				return 1;
			}
			else if (Canvas->Flag == ERASER) {
				SDL_SetRenderDrawColor(Canvas->Renderer, 255,255,255, 0);
				SDL_Rect rect = { x - Canvas->Strong / 2, y - Canvas->Strong / 2,Canvas->Strong,Canvas->Strong };
				SDL_RenderFillRect(Canvas->Renderer, &rect);
				Canvas->Last.x = x;
				Canvas->Last.y = y;
				Canvas->Click = true;
				return 1;
			}
		}
		Canvas->Click= false;
		return 0;
	}
	else if (event->type == SDL_MOUSEMOTION&&event->motion.state == 1) {
		int x = event->motion.x; int y = event->motion.y;
		if (x >= Canvas->Rect.x + Canvas->Strong / 2.0&&x <= Canvas->Rect.x + Canvas->Rect.w - Canvas->Strong / 2.0&&y >= Canvas->Rect.y + Canvas->Strong / 2.0&&y <= Canvas->Rect.y + Canvas->Rect.h - Canvas->Strong / 2.0) {
			if (Canvas->Click == true) {
				int deltax = x - Canvas->Last.x; int deltay = y - Canvas->Last.y;
				double length = sqrt(deltax*deltax + deltay*deltay);
				if (length == 0) {
					return 0;
				}
				double dx = deltax / length; double dy = deltay / length;

				SDL_Renderer * Renderer = Canvas->Renderer; // 연산을 줄이기 위해 구조체의 참조 변수들을 지역변수로 선언
				int Last_x = Canvas->Last.x; int Last_y = Canvas->Last.y; //마지막으로 찍었던 점의 x,y좌표
				int Strong = Canvas->Strong;//굵기
				int radius = Strong*0.5;// 굵기의 1/2 또는 반지름
				SDL_Rect rect;
				rect.x = Last_x-radius; rect.y = Last_y-radius;
				rect.w = rect.h = Strong;
				if (Canvas->Flag == PENCIL) {
					
					SDL_SetRenderDrawColor(Canvas->Renderer, Canvas->Color.r, Canvas->Color.g, Canvas->Color.b, 0);
					if (Strong >= 4) {
						LineCircle(Renderer, Strong, Last_x, Last_y, x, y);
					}
					else {
						LineThick(Renderer, Strong, Last_x, Last_y, x, y);
					}
					Canvas->Last.x = x; Canvas->Last.y = y;
					return 1;
				}
				else if (Canvas->Flag == ERASER) {
					SDL_SetRenderDrawColor(Canvas->Renderer, 255, 255, 255, 0);
					LineThick(Renderer,Strong,Last_x,Last_y,x,y);
					Canvas->Last.x = x; Canvas->Last.y = y;
					return 1;
				}
			}
			return 0;
		}
		else {
			Canvas->Click = false;
			return 0;
		}
	}
	else if (event->type == SDL_MOUSEBUTTONUP) {
		Canvas->Click = false;
		return 0;
	}
	else if (event->type == SDL_WINDOWEVENT) {
		if (event->window.type == SDL_WINDOWEVENT_LEAVE) {
			Canvas->Click = false;
		}
		return 0;
	}
	else {
		return 0;
	}
	//SDL_SetRenderDrawColor(Canvas->Renderer, 255, 0, 255, 0);
	//rect.x = x - 2*Strong;
	//rect.y = y - 2*Strong;                              // 소실되는 이벤트를 알아보기 위한 코드
	//rect.w = rect.h = 4* Strong;
	//SDL_RenderFillRect(Renderer, &rect);
}
void Re_Load(SDL_Window *window, SDL_Renderer *renderer, int dis_x, int dis_y, int bg_music, int music, int isfull)
{
	if (isfull)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else {
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowSize(window, dis_x, dis_y);
	}
}
void CreateButton(Button * Button, SDL_Renderer *Renderer, SDL_Texture *ButtonTexture, int Padding, int x, int y, int w, int h, int r, int g, int b,int a) {
	Button->ButtonTexture = ButtonTexture;
	Button->ButtonRect.x = x; Button->ButtonRect.y = y; Button->ButtonRect.w = w; Button->ButtonRect.h = h;
	Button->Renderer = Renderer;
	Button->Color.r = r; Button->Color.g = g; Button->Color.b = b; Button->Color.a = a;
	Button->Flag = DEACTIVATED;
	Button->Padding = Padding;
	return;
}
int UpdateButton(Button * Button, SDL_Event * event) {
	if (Button->Flag == ACTIVATED) {
		return 0;
	}
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		if (Button->Flag == ACTIVATED) {
			return 0;
		}
		int x = event->button.x; int y = event->button.y;
		if (x >= Button->ButtonRect.x&&x <= Button->ButtonRect.x + Button->ButtonRect.w&&y >= Button->ButtonRect.y&& y <= Button->ButtonRect.y +Button->ButtonRect.h) {
			Button->Flag = ACTIVATED;
			return 1;
		}
		return 0;
	}
	else if (event->type == SDL_MOUSEMOTION) {
		int x = event->motion.x; int y = event->motion.y;
		if (x >= Button->ButtonRect.x&&x <= Button->ButtonRect.x + Button->ButtonRect.w&&y >= Button->ButtonRect.y&& y <= Button->ButtonRect.y + Button->ButtonRect.h) {
			if (Button->Flag == HIGHLIGHT) {
				return 0;
			}
			else {
				Button->Flag = HIGHLIGHT;
				return 1;
			}
		}
		else if ( Button->Flag == HIGHLIGHT) {
			Button->Flag = DEACTIVATED;
			return 1;
		}
	}
	return 0;
}
void DrawButton(Button * Button) {
	if (Button->Flag == DEACTIVATED) {
		SDL_SetRenderDrawColor(Button->Renderer,255,255,255,0);// 지우기
		SDL_RenderFillRect(Button->Renderer,&Button->ButtonRect);//
		SDL_Rect rect = { Button->ButtonRect.x+Button->Padding,Button->ButtonRect.y+ Button->Padding,Button->ButtonRect.w - 2 * Button->Padding,Button->ButtonRect.h-2*Button->Padding };
		RenderTexture(Button->Renderer,Button->ButtonTexture,&rect);
		return;
	}
	else if (Button->Flag == HIGHLIGHT) {
		SDL_SetRenderDrawColor(Button->Renderer, 255, 255, 255, 0);// 지우기
		SDL_RenderFillRect(Button->Renderer, &Button->ButtonRect);// 지우기
		SDL_SetRenderDrawColor(Button->Renderer, Button->Color.r, Button->Color.g, Button->Color.b, 0);
		SDL_Rect rect = { Button->ButtonRect.x + Button->Padding,Button->ButtonRect.y + Button->Padding,Button->ButtonRect.w - 2 * Button->Padding,Button->ButtonRect.h - 2 * Button->Padding };
		RenderTexture(Button->Renderer, Button->ButtonTexture, &rect);
		SDL_RenderDrawRect(Button->Renderer, &Button->ButtonRect);
		return;
	}
	else if (Button->Flag == ACTIVATED) {
		SDL_SetRenderDrawColor(Button->Renderer, 255, 255, 255, 0);// 지우기
		SDL_RenderFillRect(Button->Renderer, &Button->ButtonRect); // 지우기
		SDL_SetRenderDrawColor(Button->Renderer, Button->Color.r, Button->Color.g, Button->Color.b, Button->Color.a);
		SDL_Rect rect = { Button->ButtonRect.x + Button->Padding,Button->ButtonRect.y + Button->Padding,Button->ButtonRect.w - 2 * Button->Padding,Button->ButtonRect.h - 2 * Button->Padding };
		RenderTexture(Button->Renderer, Button->ButtonTexture, &rect);
		SDL_SetRenderDrawBlendMode(Button->Renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(Button->Renderer, &Button->ButtonRect);
		SDL_SetRenderDrawColor(Button->Renderer, Button->Color.r, Button->Color.g, Button->Color.b, 0);
		SDL_SetRenderDrawBlendMode(Button->Renderer, SDL_BLENDMODE_NONE);
		SDL_RenderDrawRect(Button->Renderer, &Button->ButtonRect);
		return;
	}
	return;
}
void FillCircle(SDL_Renderer * Renderer,int Center_x, int Center_y,int radius) {
	int left_x, right_x,up_y,down_y;
	double y;
	for (y = 0; y < radius; y++) {
		left_x = Center_x - (int)sqrt(radius*radius - y*y) + !y;
		right_x = Center_x + (int)sqrt(radius*radius - y*y) - !y;
		up_y = Center_y - y;
		down_y = Center_y + y;
		SDL_RenderDrawLine(Renderer, left_x, up_y, right_x, up_y);
		SDL_RenderDrawLine(Renderer, left_x, down_y,right_x, down_y);
	}
}
void Line(SDL_Renderer* Renderer,float x1, float y1, float x2, float y2)
{
	// Bresenham's line algorithm
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		swap(&x1, &y1);
		swap(&x2, &y2);
	}

	if (x1 > x2)
	{
		swap(&x1, &x2);
		swap(&y1, &y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x<=maxX; x++)
	{
		if (steep)
		{
			SDL_RenderDrawPoint(Renderer,y, x);
		}
		else
		{
			SDL_RenderDrawPoint(Renderer,x, y);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}
void LineThick(SDL_Renderer* Renderer, int Thick, float x1, float y1, float x2, float y2)
{
	// Bresenham's line algorithm
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		swap(&x1, &y1);
		swap(&x2, &y2);
	}

	if (x1 > x2)
	{
		swap(&x1, &x2);
		swap(&y1, &y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x<=maxX; x++)
	{
		if (steep)
		{
			SDL_Rect rect= { y - Thick / 2.0, x - Thick / 2.0,Thick,Thick };
			SDL_RenderFillRect(Renderer,&rect );
		}
		else
		{
			SDL_Rect rect= { x - Thick / 2.0, y - Thick / 2.0,Thick,Thick };
			SDL_RenderFillRect(Renderer, &rect);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}
void LineCircle(SDL_Renderer*Renderer, int Thick, float x1, float y1, float x2, float y2) {
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		swap(&x1, &y1);
		swap(&x2, &y2);
	}

	if (x1 > x2)
	{
		swap(&x1, &x2);
		swap(&y1, &y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x <= maxX; x++)
	{
		if (steep)
		{
			FillCircle(Renderer, y, x, Thick / 2.0);
		}
		else
		{
			FillCircle(Renderer, x, y, Thick / 2.0);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}
void swap(float  *a, float *b) {
	float tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}
void PrintUserInfo(SDL_Renderer* Renderer,User *User,SDL_Rect UserRect) {
	SDL_Color color;
	if (User->Turn == 1) {
		color.r = 0; color.g = 112; color.b = 192;
	}
	else {
		color.r = 0; color.g = 176; color.b = 240;
	}
	FillRoundRect(Renderer, 242, 242, 242, UserRect.x + (User->Th-1) * (UserRect.w + UserRect.w / 24.0), UserRect.y, UserRect.w, UserRect.h, Display_X*0.011);
	FillUpRoundRect(Renderer, color.r, color.g, color.b, UserRect.x+ (User->Th - 1)*(UserRect.w+UserRect.w/24.0), UserRect.y, UserRect.w, Display_X*0.018, Display_X*0.011);
	RenderTextureXYWH(Renderer, User->Profile, UserRect.x +(User->Th-1) * (UserRect.w + UserRect.w / 24.0)+UserRect.w*0.05, UserRect.y+ Display_X*0.018, UserRect.w/2.0-UserRect.w*0.1, UserRect.h- UserRect.h * 3 / 20.0);
	RenderTextureXYWH(Renderer, User->Status, UserRect.x +(User->Th-1)* (UserRect.w + UserRect.w / 24.0)+UserRect.w/2.0, UserRect.y+ Display_X*0.018, UserRect.w/2.0, UserRect.h- Display_X*0.018);
	char User_Level[10],User_Count[10];
	_itoa(User->Level, User_Level, 10);
	_itoa(User->Count, User_Count, 10);
	Put_Text_Center(Renderer, User->Nickname, UserRect.x + (User->Th - 1)*(UserRect.w + UserRect.w / 24.0), UserRect.y, UserRect.w, Display_X*0.018, 255,255,255, Display_X*0.011,2);
	Put_Text_Center(Renderer, User_Count, UserRect.x + (User->Th - 1)*(UserRect.w + UserRect.w / 24.0) +UserRect.w*0.75, UserRect.y + Display_X*0.018, UserRect.w*0.25, 0.5*(UserRect.h - Display_X*0.018), 0,0,0, Display_X*0.02, 1);
	Put_Text_Center(Renderer, User_Level, UserRect.x + (User->Th - 1)*(UserRect.w + UserRect.w / 24.0) +UserRect.w*0.75, UserRect.y + Display_X*0.018+(UserRect.h - Display_X*0.018)*0.5 , UserRect.w*0.25, 0.5*(UserRect.h - Display_X*0.018), 0,0,0, Display_X*0.02, 1);
	return;
}
void CreateText(Text* Text, SDL_Renderer * Renderer,char *sentence, int x,int y,int w, int h, int r,int g, int b,int size, int m ) {
	Text->Renderer = Renderer;
	strcpy(Text->sentence, sentence);
	Text->Limit.x =Text->Rect.x= x; Text->Limit.y =Text->Rect.y= y; Text->Limit.w =Text->Rect.w= w; Text->Limit.h = Text->Rect.h = h;
	Text->Color.r = r; Text->Color.g = g; Text->Color.b = b; 
	Text->size = Text->size_fixed=size;  size; Text->m = m;
	return;
}
void CenterArrange(Text * Text) {
	Unicode unicode[128] = L"";		//역시나 임시로 TTF_DrawText를 쓰기 위한 unicode생성
	han2unicode(Text->sentence, unicode);	//옮긴다
	SDL_Surface * Surface;
	SDL_Texture* Texture;
	SDL_Rect Src;
	Src.x = 0;
	Src.y = 0;
	while (1) {
		if (Text->m == 1) 
			Surface = TTF_RenderUNICODE_Blended(Font_Size[Text->size_fixed], unicode, Text->Color);// 폰트의 종류,문자열, 색깔을 보내서 유니코드로 렌더한다음 서피스에 저장한다
		else if (Text->m == 2)
			Surface = TTF_RenderUNICODE_Blended(Font_Size2[Text->size_fixed], unicode, Text->Color);// 폰트의 종류,문자열, 색깔을 보내서 유니코드로 렌더한다음 서피스에 저장한다
		Texture = SDL_CreateTextureFromSurface(Text->Renderer, Surface);// 서피스로부터 텍스쳐를 생성한다
		SDL_FreeSurface(Surface);//서피스 메모리를 해제 해준다.
		SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h);
		if ((Src.w > Text->Limit.w||Src.h>Text->Limit.h)&&Text->size_fixed>1) {				
			Text->size_fixed--;
		}
		else {
			break;
		}
	}
	Text->Rect.x = Text->Limit.x + Text->Limit.w/2.0 - Src.w / 2.0;
	Text->Rect.y = Text->Limit.y + Text->Limit.h/2.0 - Src.h / 2.0;
	Text->Rect.w = Src.w;
	Text->Rect.h = Src.h;
//	SDL_RenderCopy(Text->Renderer, Texture, &Src, &Dst); //그대로 렌더러에 저장한다
	SDL_DestroyTexture(Texture);
	return;	//평소에도 0을 리턴
}
void RenderText( Text * Text) {
	Unicode unicode[128] = L"";		//역시나 임시로 TTF_DrawText를 쓰기 위한 unicode생성
	han2unicode(Text->sentence, unicode);	//옮긴다
	if (Text->m == 1)
		TTF_DrawText(Text->Renderer, Font_Size[Text->size_fixed], unicode, Text->Rect.x, Text->Rect.y, Text->Color);			//Text를 적음
	else if (Text->m == 2)
		TTF_DrawText(Text->Renderer, Font_Size2[Text->size_fixed], unicode, Text->Rect.x, Text->Rect.y, Text->Color);         //볼드체
	return;	//평소에도 0을 리턴
}
void Put_Text_Center(SDL_Renderer* Renderer, char *sentence, int x, int y, int w,int h,int r,int g,int b,int size,int m) {
	Unicode unicode[128] = L"";		//역시나 임시로 TTF_DrawText를 쓰기 위한 unicode생성
	han2unicode(sentence, unicode);	//옮긴다
	SDL_Color Color = { r,g,b,0 };
	SDL_Surface * Surface;
	SDL_Texture* Texture;
	SDL_Rect Src;
	SDL_Rect Dst;
	Src.x = 0;
	Src.y = 0;
	while (1) {
		if (m == 1)
			Surface = TTF_RenderUNICODE_Blended(Font_Size[size], unicode, Color);// 폰트의 종류,문자열, 색깔을 보내서 유니코드로 렌더한다음 서피스에 저장한다
		else if (m == 2)
			Surface = TTF_RenderUNICODE_Blended(Font_Size2[size], unicode, Color);// 폰트의 종류,문자열, 색깔을 보내서 유니코드로 렌더한다음 서피스에 저장한다
		Texture = SDL_CreateTextureFromSurface(Renderer, Surface);// 서피스로부터 텍스쳐를 생성한다
		SDL_FreeSurface(Surface);//서피스 메모리를 해제 해준다.
		SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h);
		if ((Src.w > w||Src.h > h)&&size>1) {
			size--;
		}
		else {
			break;
		}
	}
	Dst.x = x + w / 2.0 - Src.w / 2.0;
	Dst.y = y + h / 2.0 - Src.h / 2.0;
	Dst.w = Src.w;
	Dst.h = Src.h;
	SDL_RenderCopy(Renderer, Texture, &Src, &Dst); //그대로 렌더러에 저장한다
	SDL_DestroyTexture(Texture);
	return;	//평소에도 0을 리턴
}