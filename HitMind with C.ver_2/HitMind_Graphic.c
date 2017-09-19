#include "include.h"

//그래픽 관련 함수들
void TTF_DrawText(SDL_Renderer *Renderer, TTF_Font* Font, wchar_t* sentence, int x, int y, SDL_Color Color) {

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
int PutButtonImage(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, int x, int y, int w, int h, SDL_Event * event) {//이미지 버튼 선언
	SDL_Rect Src;// 직사각형 선언
	Src.x = 0;// 직사각형의 왼쪽위 꼭짓점의 x좌표초기화
	Src.y = 0;// 직사각형의 왼쪽위 꼭짓점의 y좌표초기화
	SDL_Rect Dst;
	Dst.x = x;//매개변수x를 왼쪽위 꼭짓점의 x좌표에 대입
	Dst.y = y;//매개변수y를 왼쪽위 꼭짓점의 y좌표에 대입
	Dst.w = w;//매개변수w를 직사각형의 너비에 대입
	Dst.h = h;//매개변수h를 직사각형의 높이에 대입
	
	if (event->type == SDL_MOUSEBUTTONDOWN)
		if (event->button.x > x && event->button.y > y && event->button.x < x + w && event->button.y < y + h)
			return 1;
	if (event->motion.x > x && event->motion.y > y && event->motion.x < x + w && event->button.y < y + h)
	{

		SDL_QueryTexture(MouseOnImage, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
		SDL_RenderCopy(Renderer, MouseOnImage, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장
	}
	else {
		SDL_QueryTexture(Texture, NULL, NULL, &Src.w, &Src.h); // Texture의 너비와 높이 정보를 Src.w, Src.h에 저장
		SDL_RenderCopy(Renderer, Texture, &Src, &Dst);//Src의 정보를 가지고 있는 Texture를 Dst의 정보를 가진 Texture 로 변환하여 렌더러에 저장
	
	}
	return 0;
}
int PutButton(SDL_Renderer * renderer, char * sentence, int x, int y, int size,int r, int g, int b, SDL_Event * event)
{
	SDL_Color color = { r, g, b };
	int plussize = 0;		//마우스를 가져다될때 커지는 사이즈
	
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
	TTF_DrawText(renderer, font, unicode, x - (int)(plussize * (strlen(sentence) / 4)), y - (plussize / 2), color);	//Text를 적음
	TTF_CloseFont(font);	//임시로 출력하기위한 폰트를 닫음
	return 0;	//클릭이 안되었으니 0을 리턴
}
int PutText(SDL_Renderer * renderer, char * sentence, unsigned int x, unsigned int y, int size, int r, int g, int b)
{
	SDL_Color color = { r, g, b };
	Unicode unicode[128] = L"";		//역시나 임시로 TTF_DrawText를 쓰기 위한 unicode생성
	han2unicode(sentence, unicode);	//옮긴다
	TTF_Font *font = TTF_OpenFont(".\\font\\NanumGothic.ttf", size);	//폰트를 불러온다. 하지만 Draw할때마다 불러오는건 비효율적이긴 함.
	TTF_DrawText(renderer, font, unicode, x, y, color);			//Text를 적음
	TTF_CloseFont(font);	//폰트를 닫음
	return 0;	//평소에도 0을 리턴
}
int PutText_Unicode(SDL_Renderer * renderer, Unicode * unicode, unsigned int x, unsigned int y, int size, SDL_Color color)
{
	TTF_Font *font = TTF_OpenFont(".\\font\\NanumGothic.ttf", size);	//폰트를 불러온다. 하지만 Draw할때마다 불러오는건 비효율적이긴 함.
	TTF_DrawText(renderer, font, unicode, x, y, color);			//Text를 적음
	TTF_CloseFont(font);	//폰트를 닫음
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
void SDL_DrawRoundRect(SDL_Renderer* Renderer, SDL_Rect * Rect,SDL_Color color, int radius) {
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	int old_x, old_y;
	for (float angle = 90; angle < 180; angle++) {
		old_x = Rect->x + radius + radius*cos(M_PI / 180 * angle);
		old_y = Rect->y + radius - radius*sin(M_PI / 180 * angle);
		SDL_RenderDrawLine(Renderer, old_x, old_y, Rect->x + radius + radius*cos(M_PI / 180 * (angle+1)), Rect->y + radius - radius*sin(M_PI / 180 * (angle+1)));	
	}
	SDL_RenderDrawLine(Renderer, Rect->x + radius, Rect->y, Rect->x + Rect->w - radius, Rect->y);
	for (float angle = 0; angle <= 90; angle++) {
		old_x = 1+Rect->x + Rect->w - radius + radius*cos(M_PI / 180 * angle);
		old_y = Rect->y + radius - radius*sin(M_PI / 180 * angle);
		SDL_RenderDrawLine(Renderer,old_x,old_y,1+ Rect->x + Rect->w - radius + radius*cos(M_PI / 180 * (angle+1)), Rect->y + radius - radius*sin(M_PI / 180 * (angle+1)));
	}
	SDL_RenderDrawLine(Renderer, Rect->x + Rect->w, Rect->y + radius, Rect->x + Rect->w, Rect->y + Rect->h - radius);
	for (float angle = 270; angle <= 360; angle++) {
		old_x = 1 + Rect->x + Rect->w - radius + radius*cos(M_PI / 180 * angle);
		old_y = 1 + Rect->y + Rect->h - radius - radius*sin(M_PI / 180 * angle);
		SDL_RenderDrawLine(Renderer,old_x,old_y,1+ Rect->x + Rect->w - radius + radius*cos(M_PI / 180 * (angle+1)),1+ Rect->y + Rect->h - radius - radius*sin(M_PI / 180 * (angle+1)));
	}
	SDL_RenderDrawLine(Renderer, Rect->x + Rect->w - radius, Rect->y + Rect->h, Rect->x + radius, Rect->y + Rect->h);
	for (float angle = 180; angle <= 270; angle++) {
		old_x = Rect->x + radius + radius*cos(M_PI / 180 * angle);
		old_y = 1 + Rect->y + Rect->h - radius - radius*sin(M_PI / 180 * angle);
		SDL_RenderDrawLine(Renderer, old_x,old_y,Rect->x + radius + radius*cos(M_PI / 180 * (angle+1)),1+ Rect->y + Rect->h - radius - radius*sin(M_PI / 180 * (angle+1)));
	}
	SDL_RenderDrawLine(Renderer, Rect->x, Rect->y + Rect->h - radius, Rect->x, Rect->y + radius);
}
void SDL_DrawRoundLine(SDL_Renderer* Renderer, SDL_Rect * Rect, SDL_Color color, int radius, int strong) {
	/*SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	int in_x, in_y;
	for (float angle = 90; angle < 180; angle++) {
		in_x = Rect->x+strong + radius + radius*cos(M_PI / 180 * angle);
		in_y = Rect->y+strong + radius - radius*sin(M_PI / 180 * angle);
		SDL_RenderDrawLine(Renderer, in_x, in_y, Rect->x + radius + radius*cos(M_PI / 180 * angle), Rect->y + radius - radius*sin(M_PI / 180 * angle));
	}
	SDL_RenderDrawLine(Renderer, Rect->x + radius, Rect->y, Rect->x + Rect->w - radius, Rect->y);
	for (float angle = 0; angle <= 90; angle++) {
		in_x = 1 + Rect->x + strong + Rect->w - 2*strong - radius + radius*cos(M_PI / 180 * angle);
		in_y = Rect->y + strong + radius - radius*sin(M_PI / 180 * angle);
		SDL_RenderDrawLine(Renderer, in_x, in_y, 1 + Rect->x + Rect->w - radius + radius*cos(M_PI / 180 * angle), Rect->y + radius - radius*sin(M_PI / 180 * angle ));
	}
	SDL_RenderDrawLine(Renderer, Rect->x + Rect->w, Rect->y + radius, Rect->x + Rect->w, Rect->y + Rect->h - radius);
	for (float angle = 270; angle <= 360; angle++) {
		in_x = 1 + Rect->x + strong + Rect->w - 2*strong - radius + radius*cos(M_PI / 180 * angle);
		in_y = 1 + Rect->y + strong + Rect->h - 2*strong - radius - radius*sin(M_PI / 180 * angle);
		SDL_RenderDrawLine(Renderer, in_x, in_y, 1 + Rect->x + Rect->w - radius + radius*cos(M_PI / 180 *angle), 1 + Rect->y + Rect->h - radius - radius*sin(M_PI / 180 * angle ));
	}
	SDL_RenderDrawLine(Renderer, Rect->x + Rect->w - radius, Rect->y + Rect->h, Rect->x + radius, Rect->y + Rect->h);
	for (float angle = 180; angle <= 270; angle++) {
		in_x = Rect->x + strong + radius + radius*cos(M_PI / 180 * angle);
		in_y = 1 + Rect->y + strong + Rect->h -2*strong- radius - radius*sin(M_PI / 180 * angle);
		SDL_RenderDrawLine(Renderer, in_x, in_y, Rect->x + radius + radius*cos(M_PI / 180 * angle), 1 + Rect->y + Rect->h - radius - radius*sin(M_PI / 180 * angle ));
	}
	SDL_RenderDrawLine(Renderer, Rect->x, Rect->y + Rect->h - radius, Rect->x, Rect->y + radius);*/
	for (int i = 0; i < 180; i++) {
		int x1 = sin(3.14 / 180 * i)*radius;
		int y1 = cos(3.14 / 180 * i)*radius;
		int x2 = sin(3.14 / 180 * (360 - i))*(radius);
		int y2 = cos(3.14 / 180 * (360 - i))*radius;
		SDL_RenderDrawLine(Renderer, x1 + Rect->x+Rect->w/2, y1 + Rect->y + Rect->h / 2, x2 + Rect->x + Rect->w / 2, y2 + Rect->y + Rect->h / 2);
	}
}

void DrawRoundRect(SDL_Renderer* Renderer,SDL_Color color,int x, int y, int w, int h, int radius, int strong) {
	SDL_Rect rect = { x-strong/2,y-strong/2,w+strong,h+strong };
	SDL_DrawRoundLine( Renderer, &rect,color,radius,strong);
	for (int i = 0; i < strong; i++) {
		SDL_DrawRoundRect(Renderer, &rect, color, radius);
		for (int j = 0; j < 1; j++) {
			rect.x++;
			rect.y++;
			rect.w -= 2;
			rect.h -= 2;
		}
	}
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
		if (unicode[j] == 92 || unicode[j] == 39) {// 유니코드 92번(역슬래시)나 39번(작은따운표는) mysql에서 각각 \\, \'로 입력해야하므로 예외 처리를 해준다
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

void fill_circle(SDL_Renderer *gRenderer, int radius, int cx, int cy, int r, int g, int b, int a)
{

	for (double dy = 1; dy <= radius; dy += 1.0)
	{
		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		int x = cx - dx;
		SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
		SDL_RenderDrawLine(gRenderer, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		if (dy != circle.radius)
			SDL_RenderDrawLine(gRenderer, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
	}
}