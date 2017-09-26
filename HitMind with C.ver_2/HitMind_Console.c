#include "include.h"

//Console관련 함수들 (콘솔을 쓸일이 있을까)

char * GetDefaultMyIP()
{

	char localhostname[MAX_PATH];
	IN_ADDR addr = { 0, };

	if (gethostname(localhostname, MAX_PATH) == SOCKET_ERROR)//호스트 이름 얻어오기
	{
		return inet_ntoa(addr);
	}
	HOSTENT *ptr = gethostbyname(localhostname);//호스트 엔트리 얻어오기
	while (ptr && ptr->h_name)
	{
		if (ptr->h_addrtype == PF_INET)//IPv4 주소 타입일 때
		{
			memcpy(&addr, ptr->h_addr_list[0], ptr->h_length);//메모리 복사
			break;//반복문 탈출
		}
		ptr++;
	}
	return inet_ntoa(addr);
}

void settings(int *x, int *y, int *music, int *sound, int *full) {
	FILE *set = fopen("setting.txt", "rt");
	fscanf(set, "<HitMid_Setting>\n");
	fscanf(set, "배경음악 : %d\n", music);
	fscanf(set, "효과음 : %d\n", sound);
	fscanf(set, "Display_X : %d\n", x);
	fscanf(set, "Display_Y : %d\n", y);
	fscanf(set, "fullscreen : %d\n", full);
}
uintptr_t CreateTimer(unsigned int time, int * event) {
	Hit_Timer arg;
	arg.event = event;
	arg.time = time;
	
	return _beginthreadex(NULL, 0, (_beginthreadex_proc_type)HitMind_Timer, &arg, 0, NULL);
}
void HitMind_Timer(Hit_Timer *arg)
{
	UINT32 now_time = clock();
	while (*(arg->event) != -1)
	{
		if (clock() - now_time > arg->time)
		{
			*(arg->event) = 1;
			printf("%d\n", *(arg->event));
			now_time = clock();
		}
	}
}
void changesetting(int bgmusic, int sound, int x, int y, int full) {

	Display_X = x;
	Display_Y = y;
	Sound = sound;
	BGmusic = bgmusic;

	FILE *set = fopen("setting.txt", "wt");
	fprintf(set, "<HitMid_Setting>\n");
	fprintf(set, "배경음악 : %d\n", bgmusic);
	fprintf(set, "효과음 : %d\n", sound);
	fprintf(set, "Display_X : %d\n", x);
	fprintf(set, "Display_Y : %d\n", y);
	fprintf(set, "fullscreen : %d\n", full);
	fclose(set);
}
int wstrcmp(wchar_t *First, char *second) {
	char query[384];
	char euc_kr[128];
	strcpy(query, UNICODE2UTF8(First, 128));
	UTF82EUCKR(euc_kr, 128, query, 384);
	euc_kr[strlen(euc_kr)] = 0;
	return strcmp(euc_kr, second);
}

void soundplay() {
	
	

	srand((unsigned)time(NULL));

	int bgmrand = 0;
	int i;
	char tmpbgm[20] = { 0, };
	Mix_Music *bgm[12];
	int colbgm[12] = { 180,120,170,230,100,325,102,185,155,95,125,160 };

	for (i = 0; i < 12; i++) {
		sprintf(tmpbgm, "sound/%d.mp3", i + 1);
		bgm[i] = Mix_LoadMUS(tmpbgm);
		colbgm[i] *= 1000;
	}

	while (1) {
		bgmrand = rand() % 12;
		Mix_PlayMusic(bgm[bgmrand], 1);
		Sleep(colbgm[bgmrand]);
	}



	for (i = 0; i < 12; i++) {
		Mix_FreeMusic(bgm[i]);
	}


}

