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