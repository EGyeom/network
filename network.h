#pragma once
#ifdef __linux__
#include <sys/types.h> // open
#include <sys/stat.h>
#include <unistd.h> // read,write
#include <sys/socket.h> // socket
#include <arpa/inet.h>

#define SOCKADDR sockaddr_in
#define send(s,buf,len,flag) write(s,buf,len)
#define recv(s,buf,len,flag) read(s,buf,len)
#define SOCKET int
#define CLOSESOCK(fd) close(fd)
#elif WIN32
#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#define SOCKADDR SOCKADDR_IN
#define write(s,buf,len) send(s,buf,len,0)
#define read(s,buf,len) recv(s,buf,len,0)
#define SOCKET SOCKET
#define CLOSESOCK(handle) closesocket(handle)

#endif

#include <cstdio>
#include <stdlib.h> // atoi
#include <string.h> // strlen

void error_handling(const char* msg)
{
    fputs(msg, stderr);
    fputs("\n", stderr);
    exit(1);
}

