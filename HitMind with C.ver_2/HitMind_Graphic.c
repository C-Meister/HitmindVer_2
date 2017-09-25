#include "include.h"
//그래픽 관련 함수들
TTF_Font * Font_Size[100];
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
int PutButtonImage(SDL_Renderer* Renderer, SDL_Texture * Texture, SDL_Texture * MouseOnImage, int x, int y, int w, int h, SDL_Event * event, int *happen) {//이미지 버튼 선언
	SDL_Rect Src;// 직사각형 선언
	Src.x = 0;// 직사각형의 왼쪽위 꼭짓점의 x좌표초기화
	Src.y = 0;// 직사각형의 왼쪽위 꼭짓점의 y좌표초기화
	SDL_Rect Dst;
	Dst.x = x;//매개변수x를 왼쪽위 꼭짓점의 x좌표에 대입
	Dst.y = y;//매개변수y를 왼쪽위 꼭짓점의 y좌표에 대입
	Dst.w = w;//매개변수w를 직사각형의 너비에 대입
	Dst.h = h;//매개변수h를 직사각형의 높이에 대입


	if (event->motion.x > x && event->motion.y > y && event->motion.x < x + w && event->button.y < y + h)
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


	if (event->motion.x > x && event->motion.y > y && event->motion.x < x + w && event->button.y < y + h)
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
int PutText(SDL_Renderer * renderer, char * sentence, unsigned int x, unsigned int y, int size, int r, int g, int b)
{
	SDL_Color color = { r, g, b };
	Unicode unicode[128] = L"";		//역시나 임시로 TTF_DrawText를 쓰기 위한 unicode생성
	han2unicode(sentence, unicode);	//옮긴다
	TTF_DrawText(renderer, Font_Size[size], unicode, x, y, color);			//Text를 적음
																			//폰트를 닫음
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
	int left_x, left_y;
	double y;
	double Center_x, Center_y;
	Center_x = Rect->x + Rect->w - radius;
	Center_y = Rect->y + radius;
	for (y = 0; y <= radius; y++) {
		left_x = floor(Center_x - Rect->w + 2 * radius - sqrt(radius*radius - y*y));
		left_y = Center_y - y;
		SDL_RenderDrawLine(Renderer, left_x, left_y, floor(Center_x + sqrt(radius*radius - y*y)), Center_y - y);
	}
	Center_x = Rect->x + radius;
	Center_y = Rect->y + Rect->h - radius;
	for (y = 0; y <= radius; y++) {
		left_x = floor(Center_x + Rect->w - 2 * radius + sqrt(radius*radius - y*y));
		left_y = Center_y + y;
		SDL_RenderDrawLine(Renderer, left_x, left_y, floor(Center_x - sqrt(radius*radius - y*y)), Center_y + y);
	}
}
void DrawRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius, int strong) {
	SDL_Rect rect = { x + strong,y + strong,w - 2 * strong,h - 2 * strong };
	SDL_Color color = { r,g,b,0 };
	SDL_DrawRoundRect(Renderer, &rect, color, radius, strong);
	rect.x = x; rect.w = strong; rect.y = y + strong + radius - 1; rect.h = h - 2 * (strong + radius) + 2;
	SDL_RenderFillRect(Renderer, &rect);
	rect.x = x + w - strong; rect.w = strong; rect.y = y + strong + radius - 1; rect.h = h - 2 * (strong + radius) + 2;
	SDL_RenderFillRect(Renderer, &rect);
	return;
}
void FillRoundRect(SDL_Renderer* Renderer, int r, int g, int b, int x, int y, int w, int h, int radius) {
	SDL_Rect rect = { x,y  ,w,h };
	SDL_Color color = { r,g,b, 0 };
	SDL_FillRoundRect(Renderer, &rect, color, radius);
	rect.x = x; rect.y = y + radius - 1; rect.w = w; rect.h = h - 2 * radius + 2;
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
	int left_x, left_y;
	double y;
	double Center_x, Center_y;
	Center_x = Rect->x + Rect->w - radius;
	Center_y = Rect->y + radius;
	for (y = 0; y < radius; y++) {
		left_x = floor(Center_x - Rect->w + 2 * radius - sqrt(radius*radius - y*y));
		left_y = Center_y - y;
		SDL_RenderDrawLine(Renderer, left_x, left_y, floor(Center_x + sqrt(radius*radius - y*y)), Center_y - y);
	}
}
int PutRoundButton(SDL_Renderer* Renderer, int r, int g, int b, int put_r, int put_g, int put_b, int rect_r, int rect_g, int rect_b, int x, int y, int w, int h, int radius, int strong, SDL_Event *event, int *happen)
{

	if (event->motion.x > x && event->motion.y > y && event->motion.x < x + w && event->motion.y < y + h)
	{
		FillRoundRect(Renderer, put_r, put_g, put_b, x, y, w, h, radius);
		DrawRoundRect(Renderer, rect_r, rect_g, rect_b, x - strong, y - strong, w + strong, h + strong, radius, strong);
		*happen = true;
	}
	else {
		FillRoundRect(Renderer, r, g, b, x, y, w, h, radius);
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
	rect.x = x; rect.y = y + radius - 1; rect.w = w; rect.h = h - radius + 2;
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
	if (event->type == SDL_MOUSEBUTTONDOWN) {
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
	else if (event->type == SDL_MOUSEMOTION) {
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

				if (Canvas->Flag == PENCIL) {
					ConnectCircle(Renderer, Last_x, Last_y, dx, dy, length, radius);
				/*	int old_x = Last_x; int old_y = Last_y;
					int i;
					for (i = 1; i < length; i++) {
						rect.x = (int)floor(Last_x + i*dx);
						rect.y = (int)floor(Last_y + i*dy);
						if (rect.x == old_x && rect.y == old_y) {
							continue;
						}
						FillCircle(Renderer,rect.x,rect.y,radius);
						old_x = rect.x;
						old_y = rect.y;
					}*/
					Canvas->Last.x = x; Canvas->Last.y = y;
					return 1;
				}
				else if (Canvas->Flag == ERASER) {
					rect.w = rect.h = Strong;
					SDL_SetRenderDrawColor(Canvas->Renderer,255, 255, 255, 0);
					int x_Exp = Last_x - radius; int y_Exp = Last_y - radius;
					int old_x = x_Exp; int old_y = y_Exp;
					int i;
					for (i = 1; i < length; i++) {
						rect.x = (int)floor(x_Exp + i*dx);
						rect.y = (int)floor(y_Exp + i*dy);
						if (rect.x == old_x && rect.y == old_y) {
							continue;
						}
						SDL_RenderFillRect(Renderer, &rect);
						old_x = rect.x;
						old_y = rect.y;
					}
					Canvas->Last.x = x; Canvas->Last.y = y;
					return 1;
				}
			}
			return 0;
		}
		else {
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
	else
		return 0;
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
void ConnectCircle(SDL_Renderer * Renderer, int Last_x, int Last_y, double dx, double dy, double length,int radius) {
	int left_x, right_x, up_y, down_y;
	double y; int i, old_x, old_y;
	for (y = 0; y < radius; y++) {
		left_x = Last_x - (int)sqrt(radius*radius - y*y) + !y;
		right_x = Last_x + (int)sqrt(radius*radius - y*y) - !y;
		old_x =old_y = 0;
		up_y = Last_y - y;
		down_y = Last_y + y;
		for (i = 1; i < length; i++) {
			if (floor(i*dx) == old_x && floor(i*dy) == old_y) {
				continue;
			}
			old_x = floor(i * dx);
			old_y = floor(i * dy);
			SDL_RenderDrawLine(Renderer, left_x+old_x, up_y+old_y, right_x+old_x, up_y+old_y);
			SDL_RenderDrawLine(Renderer, left_x+old_x, down_y+old_y,right_x+old_x, down_y+old_y);
		}
	}
}