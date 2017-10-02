#include "include.h"

//Socket통신 관련 함수들
/*
서버를 여는 함수
소켓을 열고 클라이언트가 올 때까지 대기하고있다가 클라이언트가 접속하면
비어있는 쓰레드에 할당 후 클라이언트가 보내는 패킷을 계속 받음
*/
void OpenServer(SockParam *param) {
	WSAStartup(MAKEWORD(2, 2), &(param->wsadata));
	printf("WSAStartup() %d\n", param->Slisten_socket);

	param->Slisten_socket = socket(PF_INET, SOCK_STREAM, 0);
	printf("socket() errcode : %d\n", param->Slisten_socket);

	memset(&(param->listen_addr), 0, sizeof(param->listen_addr));

	param->listen_addr.sin_family = AF_INET;
	param->listen_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	param->listen_addr.sin_port = htons(PORT);

	int err = bind(param->Slisten_socket, (SOCKADDR*)&(param->listen_addr), sizeof(param->listen_addr));
	printf("bind() errcode : %d\n", err);

	listen(param->Slisten_socket, 5);
	printf("listen()\n");

	int sockaddr_in_size = sizeof(param->connect_addr);
	int idx = 0;
	int bye = 1;
	/*
	여기서부터 무한 반복을 하는데
	연결요청이 올때까지 계속 대기함
	연결요청이 들어오면 빈 쓰레드,소켓에 할당하는 역할을 하고있음
	*/
	memset(&(param->Sconnect_socket), 0, sizeof(param->Sconnect_socket));
	while (bye) {
		idx = 0;
		
		while (param->Sconnect_socket[idx] != 0)
			idx++;
		param->Sconnect_socket[idx] = accept(param->Slisten_socket, (SOCKADDR*)&(param->connect_addr), &sockaddr_in_size);
		printf("accept()\n");
		if (param->sockethappen == 5)
		{
			bye = 1;
			closesocket(param->Slisten_socket);

			break;
		}
		else if (param->Sconnect_socket[idx] == -1) {

			printf("error\n");
			closesocket(param->Slisten_socket);
			
			Sleep(2000);

			exit(1);
		}
		else if (param->Sconnect_socket[idx] != 0) {

			param->num = idx;
			//	printf("OpenServer: %x\n", &(param->Sconnect_socket[idx]));
			param->Serverthread[idx] = _beginthreadex(0, 0, (_beginthreadex_proc_type)HandleClient, param, 0, 0);
		}
		
		Sleep(1);
	}

	// 서버 켜짐
}
/*
서버에 연결하는 함수
param.serverip에 들어있는 ip로 접속함
서버에 연결되고 서버에게 연결되었다는 신호를 보낸 후
서버로부터 오는 패킷을 계속해서 받음
*/
void connectServer(SockParam *param) {
	WSAStartup(MAKEWORD(2, 2), &(param->wsadata));
	printf("WSAStartup()\n");
	param->Cconnect_socket = socket(PF_INET, SOCK_STREAM, 0);	//connect_sock변수에 소켓 할당
	printf("socket()\n");
	param->connect_addr.sin_family = AF_INET;				//연결할 서버의 주소 설정
	param->connect_addr.sin_addr.S_un.S_addr = inet_addr(param->serverip); //서버 IP
	param->connect_addr.sin_port = htons(PORT);					 //서버 포트

	if (connect(param->Cconnect_socket, (SOCKADDR *)&(param->connect_addr), sizeof(param->connect_addr)))
	{
		printf("connecterror\n");
		param->sockethappen = -1;
		return;
	}
	printf("connect()\n");
	Sleep(10);
	char query[64];
	sprintf(query, "player connect %d", param->myuser->ownnum);
	send(param->Cconnect_socket, query, 40, 0);
	printf("send\n");
	param->Clientthread = _beginthreadex(0, 0, (_beginthreadex_proc_type)Clientrecv, param, 0, 0);

}
/*
각각의 클라이언트를 제어하는 함수
클라이언트에게 신호가 오면 send로 보내주는 역할을 함
echo서버를 할때에는 sendall함수를 불러 모든 클라이언트에게 보내주어야 함
*/
void HandleClient(SockParam *param) {
	int ClientNumber = param->num;
	int saveownnum;
	while (1) {
		if (param->sockethappen == 5)
		{
			closesocket(param->Sconnect_socket[ClientNumber]);
			break;
		}
		if (recv(param->Sconnect_socket[ClientNumber], param->message, 40, 0) > 0) { //ClientNumber번 클라이언트에게 패킷을 받았을 때

			printf("Recv()");
			if (strncmp(param->message, "player connect", 13) == 0) { //받은 패킷이 player connect라면
				printf("%d 접속\n", ClientNumber);
				sscanf(param->message, "player connect %d", &(param->gameuser[ClientNumber].ownnum));
				/*
				여기서 서버에 접속해있는 플레이어는 online 접속하지 않은 곳은 offline을 보내어
				클라이언트가 처리할 수 있도록 만듬
				*/
				send(param->Sconnect_socket[ClientNumber], "playercheck start", 180, 0);
				for (int i = 0; i < 8; i++) {
					if (param->Sconnect_socket[i] != 0) { // 클라이언트가 접속해있을때
						printf("%d online\n", i);
						sprintf(param->message, "%d online %d", i, param->gameuser[ClientNumber].ownnum);
						send(param->Sconnect_socket[ClientNumber], param->message, 180, 0);
					}
					else {	// 아닐때
						printf("%d offline\n", i);
						sprintf(param->message, "%d offline", i);
						send(param->Sconnect_socket[ClientNumber], param->message, 180, 0);
					}
				}
				send(param->Sconnect_socket[ClientNumber], "playercheck finish", 180, 0); // 플레이어 온라인여부가 전송이 완료되었음을 보냄
			}
			if (strcmp(param->message, "nexthostip") == 0) {
				strcpy(param->message, "nexthostis");
				recv(param->Sconnect_socket[ClientNumber], param->message, 180, 0);
				sendall(param);
			}
			/*
			여기서부터 작성하면 됨
			*/
		}
	}

}
/*
접속해있는 모든 클라이언트에게 패킷을 전송함
param.message를 수정하면 됨
*/
void sendall(SockParam *param) {
	for (int i = 0; i < 8; i++) {
		if (param->Sconnect_socket[i] != 0)
			send(param->Sconnect_socket[i], param->message, 180, 0);
	}
}
/*
클라이언트가 서버로부터 오는 패킷을 처리하는 함수
*/
void Clientrecv(SockParam *param) {
	char query[128] = { 0, };
	int i = 0;
	while (1) {

		if (param->sockethappen == 5) {
			closesocket(param->Cconnect_socket);
			break;
		}
		if (recv(param->Cconnect_socket, param->message, 180, 0)) { // 패킷을 받았을 때


			if (strcmp(param->message, "playercheck start") == 0) {	// 받은 패킷이 playercheck start라면

				i = 0;
				while (1) {
					recv(param->Cconnect_socket, param->message, 180, 0);
					
					printf("%s\n", param->message);
					if (!(strcmp(param->message, "playercheck finish")))
						break;
					strcpy(param->playerinfo[i], param->message);	// param.playerinfo[0]~param.playerinfo[7]에다가 플레이어 정보 저장
					
					sprintf(query, "%d online %%d", i);
					if (strncmp(query, param->message, 7) == 0) {
						sscanf(param->message, query, &(param->gameuser[i].ownnum));
						param->gameuser[i].status = 1;
					}
					else
						param->gameuser[i].status = 0;
					i++;
				}
				param->sockethappen = true;
			}
			if (strcmp(param->message, "nexthost") == 0) { // nexthost를 받았을 경우
				send(param->Cconnect_socket, "nexthostip", 180, 0);
				strcpy(param->message, GetDefaultMyIP()); // 자신의 ip를 보냄
				send(param->Cconnect_socket, param->message, 180, 0);
				// 소켓 닫음
				closesocket(param->Cconnect_socket);
				// 오픈 서버
				_endthreadex(param->c);
				WSACleanup(param->wsadata);
				OpenServer(param);
			}
			if (strcmp(param->message, "nexthostis") == 0) { // nexthostis를 받았을 경우
				recv(param->Cconnect_socket, param->message, 180, 0); // 호스트의 ip를 받음
				strcpy(param->serverip, param->message);
				// 소켓 닫음
				closesocket(param->Cconnect_socket);
				// 서버 연결
				_endthreadex(param->c);
				WSACleanup(param->wsadata);
				connectServer(param);

			}

		}
	}

}
/*
서버를 연 호스트가 나갔을 때 호스트를 바꿈
*/
void hostChange(SockParam *param) {
	int nexthost = 0;

	// 다음 호스트를 정함(랜덤)
	while (1) {
		int nexthost = rand() % 8;
		if (param->Sconnect_socket[nexthost] != 0) {
			break;
		}
	}
	// 다음 호스트에게 nexthost를 보냄
	if (param->Sconnect_socket[nexthost] != 0) {
		send(param->Sconnect_socket[nexthost], "nexthost", 180, 0);
	}
	else { // 만약 다음 호스트가 없을경우(나갔을경우) 다시 뽑음 (의미없을듯)
		hostChange(param);
		return;
	}

}

