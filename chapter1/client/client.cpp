#include <network.h>

int main(int argc, char* argv[])
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        error_handling("WSAStartup() error!");

    SOCKET sock = 0;
    SOCKADDR sock_addr;
    int sock_addr_len =0;
    char buf[256] = {0,};

    sock = socket(PF_INET,SOCK_STREAM,0);
    sock_addr.sin_addr.s_addr = inet_addr(argv[1]);
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(atoi(argv[2]));

    sock_addr_len = sizeof(sock_addr);
    if(connect(sock,(sockaddr*)&sock_addr,sock_addr_len) == -1)
    {
        printf("connect error\n");
    }
    int slength = read(sock,buf,sizeof(buf));
    buf[slength] = 0;
    printf("received : %s\n", buf);
    while(1)
    {
        memset(buf,0,sizeof(buf));
        scanf("%s", buf);
        slength = strlen(buf);
        write(sock,buf,slength);

        slength = read(sock,buf,sizeof(buf));
        buf[slength] = 0;
        printf("received : %s\n", buf);
    }
    CLOSESOCK(sock);
    WSACleanup();
    return 0;
}
//#pragma comment(lib, "ws2_32.lib")
//
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <winsock2.h>
//void ErrorHandling(char* message);
//
//int main(int argc, char* argv[])
//{
//	WSADATA wsaData;
//	SOCKET hSocket;
//	SOCKADDR_IN servAddr;
//
//	char message[30];
//	int strLen;
//
//	if (argc != 3)
//	{
//		printf("Usage : %s <IP> <port>\n", argv[0]);
//		exit(1);
//	}
//
//	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
//		ErrorHandling("WSAStartup() error!");
//
//	hSocket = socket(PF_INET, SOCK_STREAM, 0);
//	if (hSocket == INVALID_SOCKET)
//		ErrorHandling("socket() error");
//
//	memset(&servAddr, 0, sizeof(servAddr));
//	servAddr.sin_family = AF_INET;
//	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
//	servAddr.sin_port = htons(atoi(argv[2]));
//
//	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
//		ErrorHandling("connect() error!");
//
//	strLen = recv(hSocket, message, sizeof(message) - 1, 0);
//	if (strLen == -1)
//		ErrorHandling("read() error!");
//	printf("Message from server: %s \n", message);
//
//	closesocket(hSocket);
//	WSACleanup();
//	return 0;
//}
//
//void ErrorHandling(char* message)
//{
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}