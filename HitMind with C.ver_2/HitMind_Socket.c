#include "include.h"

//Socket통신 관련 함수들
void OpenServer() {
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	Slisten_socket = socket(PF_INET, SOCK_STREAM, 0);

	memset(&Slisten_socket, 0, sizeof(listen_addr));

	listen_addr.sin_family = AF_INET;
	listen_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	listen_addr.sin_port = htons(PORT);

	bind(Slisten_socket, (SOCKADDR*)&listen_addr, sizeof(listen_addr));

	listen(Slisten_socket, 5);

	sockaddr_in_size = sizeof(connect_addr);
	
	int idx = 0;
	while (1) {
		if (Sconnect_socket[idx] == 0) {
			idx++;
			continue;
		}
		break;
	}
	Sconnect_socket[idx] = accept(Slisten_socket, (SOCKADDR*)&connect_addr, &sockaddr_in_size);
	Serverthread[idx] = _beginthreadex(0, 0, (_beginthreadex_proc_type)HandleClient, idx, 0, 0);
	
	// 서버 켜짐
}
void connectServer(char *serverIP) {
	Cconnect_socket = socket(PF_INET, SOCK_STREAM, 0);	//connect_sock변수에 소켓 할당
	connect_addr.sin_family = AF_INET;				//연결할 서버의 주소 설정
	connect_addr.sin_addr.S_un.S_addr = inet_addr(serverIP); //서버 IP
	connect_addr.sin_port = htons(5555);					 //서버 포트

	connect(Cconnect_socket, (SOCKADDR *)&connect_addr, sizeof(connect_addr));
	sprintf(message, "player connect");
	send(Cconnect_socket, message, 180, 0);
	Clientthread = _beginthreadex(0, 0, (_beginthreadex_proc_type)Clientrecv, 0, 0, 0);

	
}
void HandleClient(int num) {
	while (1) {
		if (recv(Sconnect_socket[num], message, 180, 0) > 0) {
			if (strcmp(message, "player connect") == 0) {
				send(Sconnect_socket[num], "playercheck start", 180, 0);
				for (int i = 0; i < 8; i++) {
					if (Serverthread[i] != 0) {
						sprintf(message, "%d online", i);
						send(Sconnect_socket[num], message, 180, 0);
					}
					else {
						sprintf(message, "%d offline", i);
						send(Sconnect_socket[num], message, 180, 0);
					}
				}
				send(Sconnect_socket[num], "playercheck finish", 180, 0);
			}
		}
	}
}
void sendall(char *lmessage, int c) {
	for (int i = 0; i < 8; i++) {
		if (i == c)
			continue;
		if (Sconnect_socket[i] != 0)
			send(Sconnect_socket[i], lmessage, 180, 0);
	}
}
void Clientrecv() {
	while (1) {
		int i = 0;
		if (recv(Cconnect_socket, message, 180, 0)) {
			if (strcmp(message, "playercheck start") == 0) {
				while ((strcmp(message, "playercheck finish") == 0)) {
					recv(Cconnect_socket, message, 180, 0);
					strcpy(playerinfo[i++], message);
				}
			}
		}
	}
}